//
//  JoyousPlayer.swift
//  Joyous
//
//  Created by AugustRush on 2017/8/11.
//  Copyright © 2017年 August. All rights reserved.
//

import AVFoundation
import AudioToolbox

internal enum QueuePlayerError: Error {
    case createNewOutputError
    case allocateBufferError
    case startError
    case stopError
    case openAudioFileError
    case getAudioFileFormatError
    case getAudioFilePropertyError
    case allocBufferError
    case readAudioFilePacketDataError
    case enableTimePitchError
    case setTimePitchAlgorithmError
}

// 缓冲个数
let BUFFER_NUM = 3
//
let PER_PACKET_TIME = 0.2

internal class AudioQueueController {
    var audioQueue: AudioQueueRef?
    var audioQueueBuffers: [AudioQueueBufferRef] = Array()
    var audioFile = AudioFileID(bitPattern: 0)
    var playingBufferIndex = 0
    var audioFormat = AudioStreamBasicDescription()
    var packetDescription: UnsafeMutablePointer<AudioStreamPacketDescription>? = nil
    var currentPacket: Int64 = 0
    var bufferSize: UInt32 = 0
    var numberOfPacketsToRead: UInt32 = 0
    var isRuning = false
    var callbackQueue = DispatchQueue(label: NSUUID().uuidString)
    lazy var estimateDuration: TimeInterval = {
        var duration: TimeInterval = 0.0
        var size = UInt32(MemoryLayout.size(ofValue: duration))
        AudioFileGetProperty(self.audioFile!, kAudioFilePropertyEstimatedDuration, &size, &duration)
        return duration
    }()
    
    //MARK: public methods
    func play(atPath path: String) throws {
        let fileUrl = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, path as CFString, CFURLPathStyle.cfurlposixPathStyle, false)
        
        var osStatus = AudioFileOpenURL(fileUrl!, .readPermission, 0, &self.audioFile)
        try Check(status: osStatus, throwError: .openAudioFileError)
        
        var dataFormatSize = UInt32(MemoryLayout<AudioStreamBasicDescription>.size)
        osStatus = AudioFileGetProperty(self.audioFile!, kAudioFilePropertyDataFormat, &dataFormatSize, &self.audioFormat)
        try Check(status: osStatus, throwError: .getAudioFileFormatError)
        //should use weak because this can cause retain cycle
        osStatus = AudioQueueNewOutputWithDispatchQueue(&self.audioQueue, &self.audioFormat, 0, callbackQueue, {[weak self] (AQ, Buffer) in
            try? self?.handleOutputCallback(inAQ: AQ, inBuffer: Buffer)
        })
        try Check(status: osStatus, throwError: .createNewOutputError)
        //
        observePlayingQueueRuningStatus()
        //volumn
        try basicSetting()
        //
        var maxPacketSize: UInt32 = 0
        var propertySize = UInt32(MemoryLayout.size(ofValue: maxPacketSize))
        osStatus = AudioFileGetProperty(self.audioFile!, kAudioFilePropertyPacketSizeUpperBound, &propertySize, &maxPacketSize)
        try Check(status: osStatus, throwError: .getAudioFilePropertyError)
        //
        DeriveBufferSize(inDescription: self.audioFormat, maxPacketSize: maxPacketSize, inSeconds: PER_PACKET_TIME, bufferSize: &self.bufferSize, numberOfPacketsToRead: &self.numberOfPacketsToRead)
        let isFormatVBR = (self.audioFormat.mBytesPerPacket == 0 || self.audioFormat.mFramesPerPacket == 0)
        if isFormatVBR {
            self.packetDescription = UnsafeMutablePointer.allocate(capacity: Int(self.numberOfPacketsToRead))
        } else {
            self.packetDescription = nil
        }
        //Set a Magic Cookie for a Playback Audio Queue
        CopyEncoderCookieToQueue(file: self.audioFile!, queue: self.audioQueue!)
        //Allocate and Prime Audio Queue Buffers
        self.currentPacket = 0
        
        for index in 0..<BUFFER_NUM {
            var buffer: AudioQueueBufferRef?
            osStatus = AudioQueueAllocateBuffer(self.audioQueue!,self.bufferSize,&buffer)
            try Check(status: osStatus, throwError: .allocBufferError)
            self.audioQueueBuffers.append(buffer!)
            try handleOutputCallback(inAQ: self.audioQueue!, inBuffer: self.audioQueueBuffers[index])
        }
        
        //Start and Run an Audio Queue
        osStatus = AudioQueueStart(self.audioQueue!,nil);
        
        try Check(status: osStatus, throwError: .startError)
    }
    
    //MARK: playing controls
    func set(volumn: Float32) -> Bool {
        return (AudioQueueSetParameter(self.audioQueue!, kAudioQueueParam_Volume, volumn) == noErr)
    }
    
    func set(playRate: Float32) -> Bool {
        return (AudioQueueSetParameter(self.audioQueue!, kAudioQueueParam_PlayRate, playRate) == noErr)
    }

    func set(pitch: Float32) -> Bool {
        return (AudioQueueSetParameter(self.audioQueue!, kAudioQueueParam_Pitch, pitch) == noErr)
    }
    
    func set(volumeRampTime: Float32) -> Bool {
        return (AudioQueueSetParameter(self.audioQueue!, kAudioQueueParam_VolumeRampTime, volumeRampTime) == noErr)
    }

    func set(pan: Float32) -> Bool {
        return (AudioQueueSetParameter(self.audioQueue!, kAudioQueueParam_Pan, pan) == noErr)
    }
    
    func stopPlay(inImmediate: Bool = false) throws {
        //Clean Up After Playing
        let osStatus = AudioQueueStop(self.audioQueue!,inImmediate)
        try Check(status: osStatus, throwError: .stopError)
    }
    
    func seek(toTime time: TimeInterval) {
        let framesPerPacket = Double(audioFormat.mFramesPerPacket)
        let framesPerSecond = audioFormat.mSampleRate
        let numberOfFrames = framesPerSecond * estimateDuration
        let numberOfPackets = numberOfFrames / framesPerPacket
        let curPacket = (time / estimateDuration) * numberOfPackets
        currentPacket = Int64(curPacket)
    }
    
    func pause() -> Bool {
        return (AudioQueuePause(self.audioQueue!) == noErr)
    }
    
    private func basicSetting() throws {
        _ = set(volumn: 1.0)
        // enable time_pitch
        var propValue: UInt32 = 1
        let size = UInt32(MemoryLayout.size(ofValue: propValue))
        
        var osStatus = AudioQueueSetProperty(self.audioQueue!, kAudioQueueProperty_EnableTimePitch, &propValue, size)
        try Check(status: osStatus, throwError: .enableTimePitchError)
        //
        propValue = kAudioQueueTimePitchAlgorithm_Spectral // supports rate and pitch
        osStatus =  AudioQueueSetProperty(self.audioQueue!, kAudioQueueProperty_TimePitchAlgorithm, &propValue, size)
        try Check(status: osStatus, throwError: .setTimePitchAlgorithmError)
        //
        propValue = 1;
        AudioQueueSetProperty(self.audioQueue!, kAudioQueueProperty_TimePitchBypass, &propValue, size);
    }

    //MARK: private methods
    private func selfPointer() -> UnsafeMutableRawPointer {
        return unsafeBitCast(self, to: UnsafeMutableRawPointer.self)
    }
    //
    func playingTime() -> TimeInterval {
        var timeinterval = 100000.0
        var timeline = AudioQueueTimelineRef(bitPattern: 0)
        var osStatus = AudioQueueCreateTimeline(self.audioQueue!, &timeline)
        if osStatus == noErr {
            var timestamp = AudioTimeStamp()
            osStatus = AudioQueueGetCurrentTime(self.audioQueue!, timeline!, &timestamp, nil)
            if osStatus == noErr {
                timeinterval = timestamp.mSampleTime / self.audioFormat.mSampleRate
            }
        }
        return timeinterval
    }
    //
    private func observePlayingQueueRuningStatus() {
        AudioQueueAddPropertyListener(self.audioQueue!, kAudioQueueProperty_IsRunning, { (pointer, AQ, propertyID) in
            
            if propertyID == kAudioQueueProperty_IsRunning {
                if pointer == nil {
                    return
                }
                //get context
                let queueControler = Unmanaged<AudioQueueController>.fromOpaque(pointer!).takeUnretainedValue()
                //Get the status of the property
                var isRunning: UInt32 = 1
                var size = UInt32(MemoryLayout.size(ofValue: isRunning))
                AudioQueueGetProperty(AQ, kAudioQueueProperty_IsRunning, &isRunning, &size);
                if isRunning == 0 {
                    queueControler.isRuning = false
                    print("stoped .....")
                } else {
                    queueControler.isRuning = true
                    print("is runing....")
                }
            }
        }, selfPointer())
    }
    //The Playback Audio Queue Callback
    private func handleOutputCallback(inAQ: AudioQueueRef,inBuffer: AudioQueueBufferRef) throws {
        var numBytesReadFromFile: UInt32 = self.bufferSize
        var numPackets: UInt32 = self.numberOfPacketsToRead
        print("self playing time is \(playingTime()) \(estimateDuration)")
        var osStatus = AudioFileReadPacketData(self.audioFile!, false, &numBytesReadFromFile, self.packetDescription, self.currentPacket, &numPackets, inBuffer.pointee.mAudioData)
        
        try Check(status: osStatus, throwError: .readAudioFilePacketDataError)
        
        if (numPackets > 0) {
            inBuffer.pointee.mAudioDataByteSize = numBytesReadFromFile
            osStatus = AudioQueueEnqueueBuffer(inAQ,inBuffer,(self.packetDescription?.pointee != nil ? numPackets : 0),self.packetDescription)
            self.currentPacket = self.currentPacket + Int64(numPackets)
        } else {
            try stopPlay()
        }
    }
    
    // clean after playing
    private func cleanup() {
        //free buffers
        for bufferRef in self.audioQueueBuffers {
            AudioQueueFreeBuffer(self.audioQueue!, bufferRef)
        }
        self.audioQueueBuffers.removeAll()
        if self.audioFile != nil {
            AudioFileClose (self.audioFile!)
        }
        if self.packetDescription != nil {
            free(self.packetDescription)
        }
        if self.audioQueue != nil {
            if isRuning {
                try? stopPlay(inImmediate: true)
            }
            AudioQueueDispose(self.audioQueue!,true)
        }
    }
    
    deinit {
        cleanup()
    }
}

private func DeriveBufferSize(inDescription: AudioStreamBasicDescription, maxPacketSize: UInt32, inSeconds: Float64, bufferSize: inout UInt32, numberOfPacketsToRead: inout UInt32) {
    let maxBufferSize: UInt32 = 0x10000
    let minBufferSize: UInt32 = 0x4000
    
    if inDescription.mFramesPerPacket != 0 {
        let numberOfPacketsForTime = inDescription.mSampleRate / Float64(inDescription.mFramesPerPacket) * inSeconds
        bufferSize = UInt32(numberOfPacketsForTime) * maxPacketSize
    } else {
        bufferSize = maxBufferSize > maxPacketSize ? maxBufferSize : maxPacketSize
    }
    
    if bufferSize > maxBufferSize && bufferSize > maxPacketSize {
        bufferSize = maxBufferSize
    } else if bufferSize < minBufferSize {
        bufferSize = minBufferSize
    }
    
    numberOfPacketsToRead = bufferSize / maxPacketSize
}

private func CopyEncoderCookieToQueue(file: AudioFileID, queue: AudioQueueRef) {
    var cookieSize: UInt32 = 0
    let result = AudioFileGetPropertyInfo(file,kAudioFilePropertyMagicCookieData,&cookieSize,nil)
    
    if (result == noErr && cookieSize > 0) {
        var magicCookie = malloc(Int(cookieSize))
        AudioFileGetProperty(file,kAudioFilePropertyMagicCookieData,&cookieSize,&magicCookie);
        AudioQueueSetProperty(queue,kAudioQueueProperty_MagicCookie,magicCookie!,cookieSize);
        free (magicCookie);
    }
}

private func Check(status: OSStatus, throwError: QueuePlayerError) throws {
    guard status == noErr else {
        throw throwError
    }
}

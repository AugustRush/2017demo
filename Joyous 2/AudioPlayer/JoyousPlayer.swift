//
//  JoyousPlayer.swift
//  Joyous
//
//  Created by AugustRush on 2017/8/12.
//  Copyright © 2017年 August. All rights reserved.
//

import Foundation

class JoyousPlayer {
    // sgington player
    static let singleton = JoyousPlayer()
    //
    private var playingQueue = DispatchQueue(label: "august.audio-playing-queue", attributes: .concurrent)
    private var audioQueueController: AudioQueueController?
    //MARK: public methods
    func playMusic(atPath path: String) {
        playingQueue.async {
            self.audioQueueController = AudioQueueController()
            try? self.audioQueueController?.play(atPath: path)
        }
    }
    
    @discardableResult
    func set(volumn: Float32) -> Bool {
        if let controller = self.audioQueueController {
            return controller.set(volumn: volumn)
        }
        return false
    }
    
    @discardableResult
    func set(pitch: Float32) -> Bool {
        if let controller = self.audioQueueController {
            return controller.set(pitch: pitch)
        }
        return false
    }
    
    @discardableResult
    func set(playRate: Float32) -> Bool {
        if let controller = self.audioQueueController {
            return controller.set(playRate: playRate)
        }
        return false
    }
    
    @discardableResult
    func set(pan: Float32) -> Bool {
        if let controller = self.audioQueueController {
            return controller.set(pan: pan)
        }
        return false
    }
    
    func seek(toTime time: TimeInterval) {
        if let controller = self.audioQueueController {
            controller.seek(toTime: time)
        }
    }
}

//
//  ViewController.swift
//  Joyous
//
//  Created by AugustRush on 2017/8/11.
//  Copyright © 2017年 August. All rights reserved.
//

import UIKit
import AVFoundation

class ViewController: UIViewController {

    var audioPlayer: AVAudioPlayer!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        let path = Bundle.main.path(forResource: "bellz", ofType: "mp3")

        try? AVAudioSession.sharedInstance().setCategory(AVAudioSessionCategoryPlayback, with: .allowBluetooth)
        JoyousPlayer.singleton.playMusic(atPath: path!)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
//        JoyousPlayer.singleton.set(volumn: 1.5)
//        JoyousPlayer.singleton.set(playRate: 1.5)
//        JoyousPlayer.singleton.set(pan: 1)
        JoyousPlayer.singleton.seek(toTime: 30)
//        let path = Bundle.main.path(forResource: "sourcePCM", ofType: "aif")
//        JoyousPlayer.singleton.playMusic(atPath: path!)

    }
}


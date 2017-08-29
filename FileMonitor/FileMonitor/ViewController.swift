//
//  ViewController.swift
//  FileMonitor
//
//  Created by AugustRush on 2017/3/19.
//  Copyright © 2017年 August. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    let monitor = ARFilesMonitor.init(directoryPath: "/Users/baidu/Test Demos 2017/FileMonitor/sources")
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        monitor?.start()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}


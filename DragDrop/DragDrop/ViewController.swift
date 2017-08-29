//
//  ViewController.swift
//  DragDrop
//
//  Created by fanminhu on 2017/7/4.
//  Copyright © 2017年 fanminhu. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UIDropInteractionDelegate, UIDragInteractionDelegate {
    
    var imageView: UIImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        imageView = UIImageView()
        imageView.image = UIImage(named: "picture1")
        imageView.isUserInteractionEnabled = true
        self.view.addSubview(imageView)
        //add drag and drop
        let drag = UIDragInteraction(delegate: self)
        drag.isEnabled = true
        imageView.addInteraction(drag)
        
        let drop = UIDropInteraction(delegate: self)
        self.view.addInteraction(drop)
        
        imageView.translatesAutoresizingMaskIntoConstraints = false
        
        imageView.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true
        imageView.centerYAnchor.constraint(equalTo: self.view.centerYAnchor).isActive = true
        imageView.widthAnchor.constraint(equalToConstant: 300).isActive = true;
        imageView.heightAnchor.constraint(equalToConstant: 300).isActive = true;
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
//    override func resignFirstResponder() -> Bool {
//        print("\(#function)")
//        return false
//    }
//
//    override func setEditing(_ editing: Bool, animated: Bool) {
//        print("\(#function)")
//    }
    //MARK: UIDragInteractionDelegate methods
    
    func dragInteraction(_ interaction: UIDragInteraction, itemsForBeginning session: UIDragSession) -> [UIDragItem] {
        print("session is \(session)")
        
        let itemProvider = NSItemProvider(object: UIImage(named: "picture1")!)
        return [UIDragItem(itemProvider: itemProvider)]
    }
    
    //MARK: UIDropInteractionDelegate methods
    
    func dropInteraction(_ interaction: UIDropInteraction, canHandle session: UIDropSession) -> Bool {
        print("\(#function)")
        return session.canLoadObjects(ofClass: UIImage.self)
    }
    
    func dropInteraction(_ interaction: UIDropInteraction, sessionDidEnter session: UIDropSession) {
        print("-------------------------> did enter")
        session.loadObjects(ofClass: UIImage.self) { (reading) in
            print("---------------------> reading is \(reading)")
        }
    }
    
    func dropInteraction(_ interaction: UIDropInteraction, sessionDidUpdate session: UIDropSession) -> UIDropProposal {
        print("\(#function)")
        return UIDropProposal(operation: .copy)
    }
    
    func dropInteraction(_ interaction: UIDropInteraction, performDrop session: UIDropSession) {
        // 读取 items 数组并处理它们
        session.loadObjects(ofClass: UIImage.self) { imageItems in
            let images = imageItems as! [UIImage]
            self.imageView.image = images.first
        }
    }
}

class TextField: UITextField {
    
//    override func resignFirstResponder() -> Bool {
//        print(#function)
//        return false
//    }
}


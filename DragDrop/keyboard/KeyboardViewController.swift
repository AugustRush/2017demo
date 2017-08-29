//
//  KeyboardViewController.swift
//  keyboard
//
//  Created by fanminhu on 2017/7/4.
//  Copyright © 2017年 fanminhu. All rights reserved.
//

import UIKit

class KeyboardViewController: UIInputViewController, UIDragInteractionDelegate {

    @IBOutlet var nextKeyboardButton: UIButton!
    var imageView: UIImageView!
    
    override func updateViewConstraints() {
        super.updateViewConstraints()
        
        // Add custom view sizing constraints here
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Perform custom UI setup here
        self.nextKeyboardButton = UIButton(type: .system)
        
        self.nextKeyboardButton.setTitle(NSLocalizedString("Next Keyboard", comment: "Title for 'Next Keyboard' button"), for: [])
        self.nextKeyboardButton.sizeToFit()
        self.nextKeyboardButton.translatesAutoresizingMaskIntoConstraints = false
        
        self.nextKeyboardButton.addTarget(self, action: #selector(handleInputModeList(from:with:)), for: .allTouchEvents)
        
        self.view.addSubview(self.nextKeyboardButton)
        
        self.nextKeyboardButton.leftAnchor.constraint(equalTo: self.view.leftAnchor).isActive = true
        self.nextKeyboardButton.bottomAnchor.constraint(equalTo: self.view.bottomAnchor).isActive = true
        
        imageView = UIImageView()
        imageView.image = UIImage(named: "icecream")
        imageView.isUserInteractionEnabled = true
        self.view.addSubview(imageView)
        //add drag and drop
        let drag = UIDragInteraction(delegate: self)
        drag.isEnabled = true
        imageView.addInteraction(drag)
        
//        let drop = UIDropInteraction(delegate: self)
//        self.view.addInteraction(drop)
        
        imageView.translatesAutoresizingMaskIntoConstraints = false
        
        imageView.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true
        imageView.centerYAnchor.constraint(equalTo: self.view.centerYAnchor).isActive = true
        imageView.widthAnchor.constraint(equalToConstant: 300).isActive = true;
        imageView.heightAnchor.constraint(equalToConstant: 300).isActive = true;
        
        
        // change image button
        let button = UIButton(type: .custom)
        button.addTarget(self, action: #selector(changeImage(sender:)), for: .touchUpInside)
        button.setTitle("change image", for: .normal)
        button.setTitleColor(UIColor.blue, for: .highlighted)
        button.backgroundColor = UIColor.red
        self.view.addSubview(button)
        
        button.translatesAutoresizingMaskIntoConstraints = false
        button.leftAnchor.constraint(equalTo: self.view.leftAnchor).isActive = true
        button.centerYAnchor.constraint(equalTo: imageView.centerYAnchor).isActive = true
        imageView.widthAnchor.constraint(equalToConstant: 100).isActive = true;
        imageView.heightAnchor.constraint(equalToConstant: 100).isActive = true;
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated
    }
    
    override func textWillChange(_ textInput: UITextInput?) {
        // The app is about to change the document's contents. Perform any preparation here.
    }
    
    override func textDidChange(_ textInput: UITextInput?) {
        // The app has just changed the document's contents, the document context has been updated.
        
        var textColor: UIColor
        let proxy = self.textDocumentProxy
        if proxy.keyboardAppearance == UIKeyboardAppearance.dark {
            textColor = UIColor.white
        } else {
            textColor = UIColor.black
        }
        self.nextKeyboardButton.setTitleColor(textColor, for: [])
    }
    
    //MARK: event methods
    
    @objc func changeImage(sender: AnyObject) {
        let imageSet = [ "icecream","owl","panda"]
        let image = UIImage(named: imageSet[Int(arc4random() % 3)])
        self.imageView.image = image!
    }
    
    //MARK: UIDragInteractionDelegate methods
    
    func dragInteraction(_ interaction: UIDragInteraction, itemsForBeginning session: UIDragSession) -> [UIDragItem] {
        print(#function)
        let itemProvider = NSItemProvider(object: self.imageView.image!)
        return [UIDragItem(itemProvider: itemProvider)]
    }
    
    //MARK: UIDropInteractionDelegate methods
    
//    func dropInteraction(_ interaction: UIDropInteraction, canHandle session: UIDropSession) -> Bool {
//        return true
//    }
}

/*
 Copyright (C) 2016 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The detail view controller in the Custom Back Button example.
 */

import UIKit

class CustomBackButtonDetailViewController: UIViewController {
    
    @IBOutlet var cityLabel: UILabel!
    var city: String?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        cityLabel.text = city
    }
}

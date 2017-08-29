//
//  ViewController.swift
//  UIKitAnimation
//
//  Created by AugustRush on 2017/6/22.
//  Copyright © 2017年 August. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var animationView: UIView!
    var animator: UIViewPropertyAnimator!
    var processWhenInterrupted: CGFloat = 0.0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        let panGesture = UIPanGestureRecognizer(target: self, action: #selector(handlePan(recognizer:)))
        animationView.addGestureRecognizer(panGesture)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @objc func handlePan(recognizer: UIPanGestureRecognizer) {
        switch recognizer.state {
        case .began:
            animator = UIViewPropertyAnimator(duration: 1, curve: .easeOut, animations: {
                self.animationView.frame = self.animationView.frame.offsetBy(dx: 0, dy: 300)
            })
            animator.addCompletion{_ in
                self.view.setNeedsLayout()
                self.view.layoutIfNeeded()
            }
            animator.pauseAnimation()
            processWhenInterrupted = animator.fractionComplete
        case .changed:
            let translation = recognizer.translation(in: animationView)
            animator.fractionComplete = (translation.y / 300.0) + processWhenInterrupted
        case  .ended:
            let speed = recognizer.velocity(in: animationView)
            let timing = UISpringTimingParameters(dampingRatio: 0.5)
            animator.continueAnimation(withTimingParameters: timing, durationFactor: 300.0 / speed.y)
        default:
            print("nothing to do.")
        }
    }

}


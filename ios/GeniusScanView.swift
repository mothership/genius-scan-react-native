//
//  GeniusScanView.swift
//  RNGeniusScan
//
//  Created by Raúl Muñoz Benavente on 7/13/23.
//  Copyright © 2023 Facebook. All rights reserved.
//

import Foundation
import UIKit
import GSSDKCore

typealias RCTBubblingEventBlock = (Dictionary<String, Any>) -> Void

extension UIView {
    var parentViewController: UIViewController? {
        var parentResponder: UIResponder? = self
        while parentResponder != nil {
            parentResponder = parentResponder!.next
            if let viewController = parentResponder as? UIViewController {
                return viewController
            }
        }
        return nil
    }
}

class CustomCameraViewController: GSKCameraViewController {
        
    var reactOnEnableTakePicture: RCTBubblingEventBlock?
    var reactOnImageCaptured: RCTBubblingEventBlock?
        
    init(cameraSession: GSKCameraSession, reactOnEnableTakePicture: RCTBubblingEventBlock?, reactOnImageCaptured: RCTBubblingEventBlock?) {
        self.reactOnEnableTakePicture = reactOnEnableTakePicture
        self.reactOnImageCaptured = reactOnImageCaptured
        super.init(cameraSession: cameraSession)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupConstraints()
    }
    
    override func cameraSessionWillSnapPhoto(_ cameraSession: GSKCameraSession) {
        super.cameraSessionWillSnapPhoto(cameraSession)
    }
    
    override func cameraSession(_ cameraSession: GSKCameraSession, didGenerate scan: GSKScan) {
        super.cameraSession(cameraSession, didGenerate: scan)
        
        let documentDetector = GSKDocumentDetector()
        
        DispatchQueue.global(qos: .userInitiated).async {
            var result: GSKDocumentDetectionResult?
            
            do {
                result = try documentDetector.detectDocument(in: scan.image)
            } catch {
                print("Error while detecting document frame: \(error)")
            }
            
            print("Quadrangle analysis finished. Found: \(String(describing: result?.quadrangle))")
            
            var quadrangle: GSKQuadrangle
            
            if let q = result?.quadrangle, !q.isEmpty() {
                quadrangle = q
            } else {
                quadrangle = GSKQuadrangle.full()
            }
            
            let perspectiveCorrectionConfiguration = GSKPerspectiveCorrectionConfiguration(quadrangle: quadrangle)
            let curvatureCorrectionConfiguration = GSKCurvatureCorrectionConfiguration(curvatureCorrection: false)
            
            let enhancementConfiguration: GSKEnhancementConfiguration
            enhancementConfiguration = GSKEnhancementConfiguration.automatic()
            
            let processingResult: GSKProcessingResult
            do {
                let configuration = GSKProcessingConfiguration(perspectiveCorrectionConfiguration: perspectiveCorrectionConfiguration,
                                                               curvatureCorrectionConfiguration: curvatureCorrectionConfiguration,
                                                               enhancementConfiguration: enhancementConfiguration,
                                                               rotationConfiguration: GSKRotationConfiguration.no(),
                                                               outputConfiguration: .default())
                processingResult = try GSKScanProcessor().processImage(scan.image, configuration: configuration)
            } catch {
                print("Error while processing scan: \(error)")
                return
            }
            
            DispatchQueue.main.async {
                self.reactOnImageCaptured?([
                    "imagePath": processingResult.processedImagePath
                ])
            }
        }
    }
    
//    override func cameraSessionIsSearchingQuadrangle(_ cameraSession: GSKCameraSession) {
//        super.cameraSessionIsSearchingQuadrangle(cameraSession)
//    }
//
//    override func cameraSessionIsAbout(toChooseQuadrangle cameraSession: GSKCameraSession) {
//        super.cameraSessionIsAbout(toChooseQuadrangle: cameraSession)
//    }
//
//    override func cameraSession(_ cameraSession: GSKCameraSession, willAutoTriggerWith quadrangle: GSKQuadrangle) {
//        super.cameraSession(cameraSession, willAutoTriggerWith: quadrangle)
//    }
    
    override func cameraSessionFailed(toFindQuadrangle cameraSession: GSKCameraSession) {
        super.cameraSessionFailed(toFindQuadrangle: cameraSession)
        DispatchQueue.main.async {
            self.reactOnEnableTakePicture?([
                "enable": false
            ])
        }
    }
    
    override func cameraSession(_ cameraSession: GSKCameraSession, didFind quadrangle: GSKQuadrangle) {
        super.cameraSession(cameraSession, didFind: quadrangle)
        DispatchQueue.main.async {
            self.reactOnEnableTakePicture?([
                "enable": true
            ])
        }
    }
    
    private func setupConstraints() {
        cameraView.translatesAutoresizingMaskIntoConstraints = false
        if #available(iOS 9.0, *) {
            NSLayoutConstraint.activate([
                cameraView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
                cameraView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
                cameraView.topAnchor.constraint(equalTo: view.topAnchor),
                cameraView.bottomAnchor.constraint(equalTo: view.bottomAnchor)
            ])
        } else {
            // Fallback on earlier versions
        }
    }
    
}


public class GeniusScanView : UIView {
    
    var configuration: GSKCameraSessionConfiguration?
    var cameraSession: GSKCameraSession?
    var controller: CustomCameraViewController?
    
    override public required init(frame:CGRect) {
        super.init(frame: frame)
        self.backgroundColor = UIColor.green
    }
    
    public required init (coder: NSCoder) {
        fatalError("not implemented")
    }
    
    @objc public override func layoutSubviews() {
          super.layoutSubviews()

          if controller == nil {
              embed()
          } else {
              controller?.view.frame = bounds
          }
      }
    
    func embed() {
        guard let parentVC = parentViewController else {
            return
        }
        
        let configurationLet = GSKCameraSessionConfiguration(documentDetection: GSKCameraSessionDocumentDetection.highlight)
        self.configuration = configurationLet
        let cameraSessionLet = GSKCameraSession(configuration: configurationLet)
        self.cameraSession = cameraSessionLet
        cameraSessionLet.flashStatus = .auto
        let vc = CustomCameraViewController(cameraSession: cameraSessionLet, reactOnEnableTakePicture: self.reactOnEnableTakePicture, reactOnImageCaptured: self.reactOnImageCaptured)

        parentVC.addChild(vc)
        addSubview(vc.view)
        vc.view.frame = bounds
        vc.didMove(toParent: parentVC)

        self.controller = vc
    }
    
    @objc func takePicture() {
        self.controller?.takePhoto()
    }
    
    var reactOnEnableTakePicture: RCTBubblingEventBlock?
    var reactOnImageCaptured: RCTBubblingEventBlock?
    
    @objc func setReactOnImageCaptured(_ value: @escaping RCTBubblingEventBlock) {
        self.reactOnImageCaptured = value
        self.controller?.reactOnImageCaptured = value
    }
    
    @objc func setReactOnEnableTakePicture(_ value: @escaping RCTBubblingEventBlock) {
        self.reactOnEnableTakePicture = value
        self.controller?.reactOnImageCaptured = value
    }
    
}

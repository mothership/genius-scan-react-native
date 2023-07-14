@objc(GeniusScanViewManager)
class GeniusScanViewManager: RCTViewManager {
    @objc override static func requiresMainQueueSetup() -> Bool {
        return true
    }

    func defaultFrame() -> CGRect {
        return UIScreen.main.bounds
    }

    override func view() -> (GeniusScanView) {
      return GeniusScanView(frame: self.defaultFrame())
    }
}

//extension GeniusScanViewManager {
//    func withGeniusScanView(
//        _ reactTag: NSNumber,
//        name: String,
//        rejecter: @escaping RCTPromiseRejectBlock,
//        fn: @escaping (_: GeniusScanView) -> Void) -> Void
//    {
//      self.bridge.uiManager.addUIBlock { (manager, viewRegistry) in
//        let view = viewRegistry![reactTag]
//
//        guard let view = view, let view = view as? GeniusScanView else {
//          print("Invalid react tag, could not find GeniusScanView");
//          rejecter(name, "Unknown find reactTag: \(reactTag)", nil)
//          return;
//        }
//
//        fn(view)
//      }
//    }
//}

// MARK: - react methods

extension GeniusScanViewManager {
    @objc
    func takePicture(_ reactTag: NSNumber) -> Void {
        DispatchQueue.main.async { [weak self] in
            if let view = self?.bridge.uiManager.view(forReactTag: reactTag), let view = view as? GeniusScanView {
                view.takePicture()
            }
        }
        //      withGeniusScanView(reactTag, name: "takePicture", rejecter: rejecter) { view in
        //        view.takePicture()
        //        resolver(nil)
        //      }
    }
}


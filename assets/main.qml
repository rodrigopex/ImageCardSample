import bb.cascades 1.2
import bb.system 1.2

Page {
    id: test
    titleBar: TitleBar {
        appearance: TitleBarAppearance.Plain
        title: "PreShare"
        dismissAction: ActionItem {
            title: "Cancel"
            onTriggered: {
                _controller.closeCard()
            }
        }
    }
    actions: [
        ActionItem {
            title: "Share"
            ActionBar.placement: ActionBarPlacement.OnBar
        },
        ActionItem {
            title: "Save"
            ActionBar.placement: ActionBarPlacement.OnBar
        },
        ActionItem {
            title: "Preview"
            ActionBar.placement: ActionBarPlacement.OnBar
        }
    ]
    Container {
        layout: DockLayout {
        }
        background: Color.create("#f8f8f8")
        Container {
            id: targetImage
            property int bytes: 0
            property int origWidth: 0
            property int origHeight: 0
            onCreationCompleted: {
                var ret = _controller.getImageMetadata("images/img.JPG")
                targetImage.bytes = ret["bytes"]
                targetImage.origWidth = ret["width"]
                targetImage.origWidth = ret["height"]
            }
            attachedObjects: [
                LayoutUpdateHandler {
                    id: targetImageFrame
                }
            ]
            ImageView {
                id: scaledImage
//                id: targetImage
                imageSource: "images/img.JPG" //_controller.imageSource
                scalingMethod: ScalingMethod.AspectFit
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                gestureHandlers: [
                    PinchHandler {
                        property bool pinchInProgress: false
                        property real previousPinchRatio: 0

                        onPinchStarted: {
                            pinchInProgress = true;
                        }
                        onPinchUpdated: {
                            if (pinchInProgress) {
                                // The total scale factor is the sum of the current pinch ratio
                                // and the accumulated pinching performed previously.
                                var totalScaleFactor = event.pinchRatio + previousPinchRatio;
                                targetImage.scaleX = totalScaleFactor;
                                targetImage.scaleY = totalScaleFactor;
                            }
                        }
                        onPinchEnded: {
                            if (pinchInProgress) {
                                // Save the current scaling of the image, so that the
                                // zoom factor can be adjusted for this during the next pinch session.
                                previousPinchRatio = targetImage.scaleX - 1.0;
                            } else {
                                previousPinchRatio = 0;
                            }
                            pinchInProgress = false
                        }
                    }
                ]
            }
        }
        BottomBar {
            barHeight: 130
            targetHeight: targetImage.origHeight
            targetWidth: targetImage.origWidth
        }
    }
}

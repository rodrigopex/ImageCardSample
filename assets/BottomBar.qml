import bb.cascades 1.2

Container {
    id: self
    property int targetWidth: 0
    property int targetHeight: 0
    rightPadding: 20
    leftPadding: 20
    bottomPadding: 10
    layout: DockLayout {
    }
    property alias barHeight: self.preferredHeight
    background: imgPaintDef.imagePaint
    verticalAlignment: VerticalAlignment.Bottom
    horizontalAlignment: HorizontalAlignment.Fill
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
        Label {
            textFormat: TextFormat.Html
            textFit.mode: LabelTextFitMode.FitToBounds
            text: "<html><b>" + targetWidth + "</b>x<b>" + targetHeight + "</b>px</html>"
            textStyle.base: SystemDefaults.TextStyles.BigText
            layoutProperties: StackLayoutProperties {
                spaceQuota: 20
            }
        }
        Label {
            textFit.mode: LabelTextFitMode.FitToBounds
            textFormat: TextFormat.Html
            text: "<html><b>50</b>KB</html>"
            textStyle.base: SystemDefaults.TextStyles.BigText
            horizontalAlignment: HorizontalAlignment.Right
        }
    }
    Label {
        text: "File size"
        verticalAlignment: VerticalAlignment.Bottom
        horizontalAlignment: HorizontalAlignment.Right
        textStyle.base: SystemDefaults.TextStyles.SubtitleText
    }
    Label {
        text: "Dimensions"
        verticalAlignment: VerticalAlignment.Bottom
        textStyle.base: SystemDefaults.TextStyles.SubtitleText
    }
    attachedObjects: [
        ImagePaintDefinition {
            id: imgPaintDef
            imageSource: "asset:///images/bottom_bar_bg.amd"
        },
        TextStyleDefinition {
            id: whiteTextStyleDef
            color: Color.create("#f8f8f8")

        }
    ]
}

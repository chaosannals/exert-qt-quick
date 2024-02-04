import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.Dialogs
import SegmentDemo 1.0

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("cppNqml")

    SegmentObject {
        id: segment
    }

    Column {
        id: column1
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        spacing: 5

        Text {
            id: tip
            text: segment.image_path
            font.pixelSize: 20
            // anchors 这个会干扰父级 column 的布局，确保 column 子元素不能有任何一个带这个属性。
//            anchors.centerIn: parent
        }

        Text {
            id: tip2
            text: segment.count.toString()
            font.pixelSize: 20
            // anchors 这个会干扰父级 column 的布局，确保 column 子元素不能有任何一个带这个属性。
//            anchors.centerIn: parent
        }

        Text {
            id: tip3
            text: globalDemo.timestamp.toString()
            font.pixelSize: 20
            // anchors 这个会干扰父级 column 的布局，确保 column 子元素不能有任何一个带这个属性。
//            anchors.centerIn: parent
        }

        Image {
            id: image1
            width: parent.width
            height: parent.width
//            Image.TileVertically
            fillMode: Image.PreserveAspectFit
//            fillMode: Image.PreserveAspectCrop
//            fillMode: Image.Pad
//            fillMode: Image.Stretch

            source: segment.image_path
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            console.log("ma click")
            segment.image_path = "主窗体"
            segment.count += 10
            fileDialog.open()
        }
    }

    FileDialog {
        id: fileDialog
        nameFilters: [ "Image Files(*.jpg *.png)", "All files(*)"]
        title: qsTr("pick file")
        currentFolder: shortcuts.home
        onAccepted: {
            console.log("fd pick: " + fileDialog.selectedFile)
            segment.image_path = fileDialog.selectedFile.toString()
        }
        onRejected: {
            console.log('fd cancel')
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}

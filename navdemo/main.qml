import QtQuick
import QtQuick.Controls
import "page"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    // Component 使得组件脱离渲染树，在必有的时候被 StackView 加入渲染树
    Component {
        id: homePage

        HomePage {
            // 自定义的 signal clickedTo
            onClickedTo: {
                navHost.push(confPage)
            }
        }
    }

    // Component 使得组件脱离渲染树，在必有的时候被 StackView 加入渲染树
    Component {
        id: confPage
        ConfPage {
            // 自定义的 signal clickedTo
            onClickedTo: {
                navHost.push(homePage)
            }
        }
    }

    Column {
        id: mainColumn
        anchors.fill: parent

        Row {
            id: navBar
            width: parent.width

            spacing: 10

            Button {
                text: "Home"
                onClicked: navHost.push(homePage)
            }

            Button {
                text: "Conf"
                onClicked: navHost.push(confPage)
            }

            Button {
                text: "Back"
                enabled: navHost.depth > 1
                onClicked: navHost.pop()
            }
            Text {
                text: navHost.depth.toString()
            }
        }

        StackView {
            id: navHost
            width: parent.width
            height: parent.height - navBar.height
            initialItem: homePage

            // 切换动画
            pushEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0
                    to:1
                    duration: 200
                }
            }
            pushExit: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 1
                    to:0
                    duration: 200
                }
            }
            popEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0
                    to:1
                    duration: 200
                }
            }
            popExit: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 1
                    to:0
                    duration: 200
                }
            }
        }
    }
}

import QtQuick
import QtWebView

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    // TODO
    // No WebView plug-in found!
    // 无法启用
    WebView {
        anchors.fill: parent
        url: "https://baidu.com"
    }
}

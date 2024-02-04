import QtQuick
import QtWebView

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

   // Windows 下 WebView 必须用 VC++ 编译， Mingw的 Qt 会被判定为 linux 导致无法找到 Webview
    // mingw 下会报 No WebView plug-in found!
    // 无法启用
    WebView {
        anchors.fill: parent
        url: "https://baidu.com"
    }
}

import QtQuick 2.0
import QtQuick.Controls

Column {
    id: confPageRoot

    // 外部是通过 onClickedTo ，名字约定是加 on 和首字母大写的固定形式。
    signal clickedTo(string route)

    Text {
        text: "Conf"
    }

    Button {
        text: "toHome"
        onClicked: {
            confPageRoot.clickedTo("home")
        }
    }
}

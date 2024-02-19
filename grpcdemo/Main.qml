import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("GRPC DEMO")

    Column {
        TextField {
            id: hostEdit
            placeholderText: qsTr("Host")
            text: grpcBook.host
        }
        TextField {
            id: idEdit
            placeholderText: qsTr("Id")
        }
        Text {
            id: resultText
            text: "结果"
        }

        Button {
            text: "登录"
            onClicked: {
                console.log("login");
                grpcBook.login();
            }
        }

        Button {
            text: "发送"
            onClicked: {
                const id = Number(idEdit.text);
                console.log("send", id);
                const r = grpcBook.find(id);
                console.log('r', r);
                resultText.text = r;
            }
        }
    }
}

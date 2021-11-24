import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.15

import QtQuick.Controls.Material 2.15

import "./MainWindow" as MainWindow


Window {
    id: mainWindow
    visible: true
    width: 1100
    height: 700
    title: qsTr("Chat")
    //flags: Qt.FramelessWindowHint | Qt.Window
    Connections {
        target: qmlApp

    }
    Component.onCompleted: {
        x = 1920/2 - width / 2
        y = 1080 / 2 - height / 2
    }

    Timer{

    }
  MainWindow.Header {
        id: header
        anchors.fill: parent
        anchors.bottomMargin: parent.height - 45
        width: parent.width
    }

    MainWindow.Body {
        id: body
        anchors.top: header.bottom
        anchors.left: header.left
        width: parent.width
        height: parent.height - header.height + 20
    }
}

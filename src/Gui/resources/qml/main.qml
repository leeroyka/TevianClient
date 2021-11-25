import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.15

import QtQuick.Controls.Material 2.15

import "./MainWindow" as MainWindow


Window {
    id: mainWindow
    visible: true
    width: 900
    height: 700
    minimumHeight: 400
    minimumWidth: 600
    title: qsTr("TevianClient")
    //flags: Qt.FramelessWindowHint | Qt.Window
    Connections {
        target: qmlApp
        onErrorRecived: {
          body.showErrorDialog(error);
        }
        onImagesProcessed: {
          header.lock();
          body.lock();
          footer.showProgressBar();
        }
        onImagesReady: {
          header.unlock();
          body.unlock();
          footer.showProgressBar();
        }
        onImageProcessed: {
          footer.updateProgressBar(images, maxImages)
          footer.updateInformation(images, maxImages)
        }
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
        width: parent.width
        anchors.top: header.bottom
        anchors.left: header.left
        height: parent.height - header.height + 20
    }
    MainWindow.Footer {
      id: footer
      height: 30
      width: parent.width
      anchors.bottom: body.bottom
      anchors.bottomMargin: 15
      anchors.left: body.left

    }
}

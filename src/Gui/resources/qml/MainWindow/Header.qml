import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Qt.labs.platform 1.0

Rectangle {
    function lock()
    {
      buttonDir.enabled = false;
      buttonImages.enabled = false;
      mouseArea.cursorShape = Qt.WaitCursor
    }
    function unlock()
    {
      buttonDir.enabled = false;
      buttonImages.enabled = false;
      mouseArea.cursorShape = Qt.ArrowCursor
    }

    property int previousX
    property int previousY
    anchors.fill: parent
    color: "#191919"

    FileDialog {
        id: fileDialogImages
        title: "Please choose a images"
        fileMode: FileDialog.OpenFiles
        nameFilters: [ "Image files (*.jpg *.png *.jpeg)"]
        onAccepted: {
            qmlApp.uploadImages(fileDialogImages.files)
        }
        onRejected: {
        }
    }
    FolderDialog {
        id: folderDialog
        title: "Please choose a directory"
        onAccepted: {
        }
    }

    MouseArea {
            id: mouseArea
            anchors.fill: parent
            onPressed: {
                previousX = mouseX
                previousY = mouseY
            }
            onMouseXChanged: {
                var dx = mouseX - previousX
                mainWindow.setX(mainWindow.x + dx)
            }
            onMouseYChanged: {
                var dy = mouseY - previousY
                mainWindow.setY(mainWindow.y + dy)
            }
        }
    Text {
        id: textLabelHeader
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.leftMargin: 15
        text: qsTr("TevianClient")
        font.pixelSize: 21
        font.bold: true
        color: "White"
     }
    ComboBox {
      currentIndex: 0
      model: ListModel {
        id: listImages
        ListElement { text: "aaaa"}
        ListElement { text: "Apple" }
        ListElement { text: "Coconut" } // delete
      }
      width: 200
      height: buttonImages.height
      anchors.top: parent.top
      anchors.right: buttonImages.left
      anchors.rightMargin: 5
      enabled: false
      onCurrentIndexChanged: {

      }
    }

    Button{
        id: buttonImages
        font.capitalization: Font.MixedCase
        font.bold: true
        anchors.top: parent.top
        anchors.right: buttonDir.left
        anchors.rightMargin: 5
        text: qsTr('Open Images')
        onClicked: fileDialogImages.open()
    }

    Button{
        id: buttonDir
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 5
        text: qsTr('Open Directory')
        font.capitalization: Font.MixedCase
        font.bold: true
        onClicked: folderDialog.open()
    }
}

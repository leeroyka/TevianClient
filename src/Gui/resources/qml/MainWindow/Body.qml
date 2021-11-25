import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs 1.2

Item{

  function showErrorDialog(error)
  {
      dialogError.textError = error;
      dialogError.open()
  }
  function lock()
  {
    mouseArea.cursorShape = Qt.WaitCursor
  }

  function unlock()
  {
    mouseArea.cursorShape = Qt.ArrowCursor
  }
  function setImage(path)
  {
    image.source = "file:///"+path
  }
  function setFaces(faces)
  {
    for(let face of faces)
    {
        console.debug(face[0],face[1],face[2],face[3],face[4],face[5])
    }

  }

  Component.onCompleted: {
      qmlApp.initialization()
  }
  Rectangle {
      anchors.fill: parent
      color: "#353535"
    Component.onCompleted: {

    }
    MouseArea {
      id: mouseArea
      anchors.fill: parent
    }
    Flickable {
        anchors.fill: parent

        contentWidth: Math.max(image.width * image.scale, mainWindow.width)
        contentHeight: Math.max(image.height * image.scale, mainWindow.height)
        clip: true

        Image {
            id: image

            property real zoom: 0.0
            property real zoomStep: 0.1

            asynchronous: true
            cache: false
            smooth: true
            antialiasing: true
            mipmap: true

            anchors.centerIn: parent
            transformOrigin: Item.Center
            scale: Math.min(mainWindow.width / width, mainWindow.height / height, 1) + zoom

            source: ""
            Rectangle {
                id: rect
                x: 10
                y: 10
                color: Qt.rgba(1,1,1,0);
                border.color: "green"
                opacity: 0.25
                border.width: 4/image.scale
                width: 80; height: 80
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: rect.opacity = 1
                    onExited: rect.opacity = 0.25
                }
            }
            TextArea{
                id: text
                x:10
                y:10 - (text.height/image.scale)
                color: "white"
                background: Rectangle {
                    anchors.fill: parent
                    color: "green"
                }
                text: "Age: 0\nGender: true "
                bottomPadding: -1
                topPadding: -1
                leftPadding: 2
                rightPadding: 2
                transformOrigin: Item.TopLeft
                font.pixelSize: 15
                scale: 1/image.scale
                onScaleChanged: {

                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton

        onWheel: {
            if (wheel.angleDelta.y > 0)
                image.zoom = Number((image.zoom + image.zoomStep).toFixed(1))
            else
                if (image.zoom > 0) image.zoom = Number((image.zoom - image.zoomStep).toFixed(1))

            wheel.accepted=true
        }
    }
    Dialog{
        id: dialogError
        title: "Error"
        standardButtons: Dialog.Ok
        property alias textError: labelError.text
        Label{
            id:labelError
            color: "#000000"
            text: qsTr('Error:')
        }
        onButtonClicked: Qt.quit()
    }
  }
}

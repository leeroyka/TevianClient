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
  property variant arrayFaces
  function setFaces(faces)
  {
    for(var i in arrayFaces)
      arrayFaces[i].destroy()
    arrayFaces = []
    for(let face of faces)
    {
      let rectFace = faceRectangle.createObject(image);
      rectFace.x      = face[0]
      rectFace.y      = face[1]
      rectFace.width  = face[2]
      rectFace.height = face[3]
      rectFace.text   = "Age: " + face[4] + "\nGender: " + face[5];
      arrayFaces.push(rectFace)
    }
  }

  Component.onCompleted: {
      qmlApp.initialization()
  }
  Component {
    id: faceRectangle

    Rectangle {
        x: 10
        y: 10
        property alias text: textArea.text
        color: Qt.rgba(1,1,1,0);
        border.color: "green"
        opacity: 0.45
        border.width: 3/image.scale
        width: 80; height: 80
        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {parent.opacity = 1; parent.color = Qt.rgba(0,1,0,0.12);}
            onExited: {parent.opacity = 0.45;  parent.color = Qt.rgba(0,1,0,0)}
        }
        TextArea{
            id:             textArea
            anchors.left:   parent.left
            anchors.bottom: parent.top
            color:          "white"
            background: Rectangle {
                anchors.fill: parent
                color: "green"
            }
            text:            "Age: 0\nGender: true "
            bottomPadding:   -1
            topPadding:      -1
            leftPadding:     2
            rightPadding:    2
            transformOrigin: Item.BottomLeft
            font.pixelSize:  15
            scale:           1/image.scale
        }
    }
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

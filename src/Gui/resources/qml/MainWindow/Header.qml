import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15


Rectangle {
    property int previousX
    property int previousY
    anchors.fill: parent
    color: "#191919"
    z: 101
    function changeChatType(type)
    {
      textLabelHeader.text = type
      if(type == "Server")
      {
        buttonShowSettings.visible = false
      }
      else
      {}
    }
    MouseArea {
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
    Button{
        id: buttonPrevious
        anchors.top: parent.top
        anchors.topMargin: (parent.height/2) - (buttonSave.height/2)
        anchors.right: buttonSave.left
        anchors.rightMargin: 10
        text: qsTr('File')
        onClicked: qmlApp.getHttpPost()
    }

    Button{
        id: buttonSave
        anchors.top: parent.top
        anchors.topMargin: (parent.height/2) - (buttonSave.height/2)
        anchors.right: buttonClose.left
        anchors.rightMargin: 10
        text: qsTr('Check')
        onClicked: qmlApp.testFunc()
    }
    Button{
        id: buttonClose
        width: 50
        anchors.top: buttonSave.top
        anchors.right: parent.right
        anchors.rightMargin: 10
        text: qsTr('x')
        onClicked: close()
    }
}

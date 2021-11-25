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

    Image {
        id: imageBackground
        anchors.left: parent.left
        anchors.top: parent.top
        z:0
        source: ""

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

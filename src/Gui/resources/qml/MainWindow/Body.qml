import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs 1.2

Item{

  property double scale: 0.75
    property int widthWindow: 1100
    property double delta: 2.5
    property double volume: 90
  function changeImageBackground(img)
  {
      imageBackground.source = img
      imageBackground.sourceSize.width = widthWindow
      mainWindow.setWidth(imageBackground.width)
      mainWindow.setHeight(imageBackground.height+header.height)
  }
  function changeImageCharacter(img, pos)
  {
      imageCharacter.source = img
      imageCharacter.sourceSize.height = mainWindow.height*8/9;
      if(pos<0 || pos>100)
          pos=25
      var curPosition = parseInt(pos)/100.
      imageCharacter.anchors.rightMargin = curPosition*mainWindow.width-(imageCharacter.width/2);
      if(imageCharacter.anchors.rightMargin<0)
          imageCharacter.anchors.rightMargin = 0;
      if(imageCharacter.anchors.rightMargin>mainWindow.width-(imageCharacter.width/2))
          imageCharacter.anchors.rightMargin = mainWindow.width-(imageCharacter.width/2)

  }
  function changeTextCharacter(text)
  {
    rectangleTextCharacter.text = text
    rectangleTextCharacter.width = rectangleTextCharacter.widthText + 20
    if(rectangleTextCharacter.width>(mainWindow.width/delta))
        rectangleTextCharacter.width = (mainWindow.width/delta)
    rectangleTextCharacter.widthText = (mainWindow.width/delta)-20
    rectangleTextCharacter.height = rectangleTextCharacter.heightText + 20
  }
  function changeTextPerson(text)
  {
      rectangleTextPerson.text = text
      rectangleTextPerson.width = rectangleTextPerson.widthText + 20
      if(rectangleTextPerson.width>(mainWindow.width/delta))
          rectangleTextPerson.width = (mainWindow.width/delta)
      rectangleTextPerson.widthText = (mainWindow.width/delta)-20
      rectangleTextPerson.height = rectangleTextPerson.heightText + 20
  }
  function showPrinter()
  {
      rectangleTextNameCharacter.visible=true;
      rectangleTextCharacter.visible=true;
      rectangleTextPerson.visible=true;
  }
  function hidePrinter()
  {
      rectangleTextNameCharacter.visible = false;
      rectangleTextCharacter.visible=false;
      rectangleTextPerson.visible=false;
  }

  function changeTextNameCharacter(text)
  {
      rectangleTextNameCharacter.text = text
      rectangleTextNameCharacter.width = rectangleTextNameCharacter.textWidth + 20
  }

  function showErrorDialog(error)
  {
      dialogError.textError = error;
      dialogError.open()
  }
  property variant arrayButtonArgs
  function showSelection(map)
  {
      rectBlackout.visible = true
      arrayButtonArgs = []
      var index = 0
      for(var key in map)
      {
          var answerBtn = buttonArg.createObject(layoutSelection, {
                                                 "text" : map[key],
                                                 "buttonId" : key});
          answerBtn.width = (mainWindow.width/delta)
          answerBtn.Layout.preferredWidth = (mainWindow.width/delta)
          arrayButtonArgs[index]=answerBtn
          index++
      }
  }

  function chooseAnswer(id)
  {
      console.log(id)
      rectBlackout.visible = false
      for(var i in arrayButtonArgs)
      {
        arrayButtonArgs[i].destroy();
      }
      qmlApp.jmp(id);
  }

  Rectangle {
      anchors.fill: parent
      color: "#353535"
    function sendMessage(msg)
    {
    }
    Component.onCompleted: {
      //updatemessages();
    }
    transitions: Transition {
        NumberAnimation { property: "opacity"; easing.type: Easing.InOutQuad; duration: 2500  }
    }

    Rectangle{
        id: rectBlackout
        anchors.fill: parent
        z: 99
        color: Qt.rgba(0,0,0,0.7)
        visible: false
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(!rectBlackout.visible)
                qmlApp.next();
        }
    }

    Component {
      id: buttonArg;
      Button {
        property string buttonId;
        Layout.preferredWidth: 400
        flat: true
        Material.background: Qt.rgba(0,0,0,0.8)
        Layout.alignment: Qt.AlignCenter

        onClicked: {
            chooseAnswer(buttonId)
        }
      }
    }
    ColumnLayout {
        id: layoutSelection
        anchors.left: parent.left
        anchors.top: parent.top
        spacing: 0
        z:100
        anchors.leftMargin: (parent.width/2) - (layoutSelection.width/2)
        anchors.topMargin: (parent.height/2) - (layoutSelection.height/2)
    }

    Image {
        id: imageBackground
        anchors.left: parent.left
        anchors.top: parent.top
        z:0
        source: ""

    }
    Image {
        id: imageCharacter
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 20
        source: ""
        NumberAnimation on opacity {
                id: createAnimationCharacter
                from: 0
                to: 1
                duration: 500
         }
        onSourceChanged: createAnimationCharacter.start()

    }
    Rectangle {
        id: rectangleTextCharacter
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.rightMargin: 20
        width: 100
        height: 120
        z: 98
        color: Qt.rgba(0,0,0,0.7)
        visible: false
        property alias text: textCharacter.text
        property alias widthText: textCharacter.width
        property alias heightText: textCharacter.height
        Text {
            id: textCharacter
            anchors.left: rectangleTextCharacter.left
            anchors.leftMargin: 10
            anchors.topMargin: 10
            anchors.top: rectangleTextCharacter.top
            color: "white"
            font.pointSize: 12
            wrapMode: Text.Wrap
        }

    }
    Rectangle {
        id: rectangleTextNameCharacter
        anchors.left: rectangleTextCharacter.left
        anchors.bottom: rectangleTextCharacter.top
        anchors.bottomMargin: 5
        height: 40
        width: 50
        z: 98
        color: Qt.rgba(0,0,0,0.7)
        visible: false
        property alias text: textNameCharacter.text
        property alias textWidth: textNameCharacter.width
        Text {
            id: textNameCharacter
            anchors.left: rectangleTextNameCharacter.left
            anchors.top: rectangleTextNameCharacter.top
            anchors.leftMargin: 10
            color: "white"
            font.pointSize: 12
            anchors.topMargin: 10
        }
    }
    Rectangle {
        id: rectangleTextPerson
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.leftMargin: 20
        width: 100
        height: 120
        z: 98
        color: Qt.rgba(0,0,0,0.7)
        visible: false
        property alias text: textPerson.text
        property alias widthText: textPerson.width
        property alias heightText: textPerson.height
        Text {
            id: textPerson
            anchors.left: rectangleTextPerson.left
            anchors.leftMargin: 10
            anchors.topMargin: 10
            anchors.top: rectangleTextPerson.top
            color: "white"
            font.pointSize: 12
            wrapMode: Text.Wrap
        }

    }
    Shortcut{
        sequence: "Ctrl+Return"
        onActivated: {
            footer.outText = ''
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
    }
  }
}

import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.15

Rectangle {
    function setProgressValue(value,max)
    {
      progressBar.value(value)
      progressBar.to(max)
    }
    function showProgressBar()
    {
      progressBar.visible = true;
      progressBar.value = 0;
    }
    function hideProgressBar()
    {
      progressBar.visible = false;
    }
    function updateProgressBar(images,maxImages)
    {
      progressBar.to = maxImages
      progressBar.value = images
    }
    function updateInformation(images,maxImages)
    {
      textImagesSelected.text = "Images processed (<b>"+images+"</b>); Images selected (<b>"+maxImages+"</b>)"
    }

    anchors.bottom: parent
    anchors.left: parent
    color: "#191919"
    z: 101
    width: parent.width
    height: parent.height
    Text {
        id: textImagesSelected
        anchors.fill: parent
        anchors.topMargin: 3
        anchors.leftMargin: 10
        font.pixelSize: 12
        text: qsTr("Images selected (<b>0</b>);")
        color: "White"
     }
    ProgressBar {
        id: progressBar
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 11
        anchors.rightMargin: 80
        scale: 4
        width: 50
        value: 0
        to: 2
        visible: false
    }
}

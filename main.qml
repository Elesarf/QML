import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0 as Controls
import com.cps.qmlcomponents 1.0

Window {
    id: window
    visible: true
    minimumWidth: 550
    minimumHeight: 550
    width: 800
    height: 600
    title: "PLK"

    property string fileName: "/tmp/notes.json"
    property string fileNamePins: "/tmp/pins.json"
    property int  szL: 2
    property int  szP: 32

    MyLabelController{
        id:myLabelModel
        Component.onCompleted: initDefault(szL);
        onSizeChanged: szL = size;
    }

    PinsController{
        id:myPins
        Component.onCompleted: initDefault(16,szP)
    }

    Rectangle{
        id: controller
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: pinsViewOut.width+ 40
        width: 250
        height: 450
        border.width: 3

        Text {
            id: text1
            text: qsTr("PLK")
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    MyLabel{
        id:ml
        height: parent.height - labelButtonRow.height
        anchors.top: labelButtonRow.bottom
        anchors.left: pinsViewOut.right
        anchors.leftMargin: 120
        anchors.right: parent.right
        dim : szL
        model:myLabelModel.modelData
    }

    Row{
        id:labelButtonRow
        anchors.top:parent.top
        anchors.right: parent.right
        Controls.Button{
            id:buttonSave
            text:"save"
            width: ml.width/3
            onClicked: myLabelModel.save(fileName);
        }
        Controls.Button{
            id: buttonLoad
            text: "load"
            width: ml.width/3
            onClicked: myLabelModel.load(fileName);
        }
        Controls.Button{
            id: buttonAdd
            text: "add"
            width: ml.width/3
            onClicked: {
                if (szL < 20)
                myLabelModel.add();
            }
        }
    }

    PinsView{
        id:pinsViewOut
        anchors.verticalCenter: controller.verticalCenter
        anchors.left: controller.right
        anchors.leftMargin: 10
        width: (szP/16) * 30
        height: controller.height
        model:myPins.modelDataOut
    }

    PinsView{
        id:pinsViewIn
        anchors.verticalCenter: controller.verticalCenter
        anchors.right: controller.left
        anchors.leftMargin: 10
        width: (szP/16) * 25
        height: controller.height
        model:myPins.modelDataIn
    }

    Row{
        anchors.bottom: controller.bottom
        anchors.bottomMargin: controller.border.width
        anchors.horizontalCenter: controller.horizontalCenter
        Controls.Button{
            id:buttonSavePin
            text:"save"
            width: controller.width/2 - controller.border.width
            onClicked: myPins.save(fileNamePins);
        }
        Controls.Button{
            id: buttonLoadPin
            text: "load"
            width: controller.width/2 - controller.border.width
            onClicked: myPins.load(fileNamePins);
        }
    }
}

import QtQuick 2.0

Column {

    id:modelItem1

    property var model

    Levitate{
        id:lvt
    }

    GridView{
        id: gri
        anchors.fill:parent
        model: modelItem1.model
        height: parent.height
        width: parent.width
        cellWidth: 30
        cellHeight: 28
        clip: true

        highlight: Rectangle {
            color: "skyblue"
            radius: 4
        }

        delegate: MyRingButton{
            width: 25
            height: 25
            group : model.group;

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onClicked: {
                    if(mouse.button === Qt.RightButton){
                        lvt.show = true;
                        lvt.x = mouseX + 50;
                        lvt.y = gri.cellHeight * index / 2 + 20;
                        lvt.show = true;
                        lvt.text = qsTr("%1").arg(group);
                    }
                }
            }
        }
    }
}

import QtQuick 2.0

Column {

    id:modelItem1

    property var model

    Levitate{
        id:lvt
    }

    GridView{
        anchors.fill:parent
        model: modelItem1.model
        height: parent.height
        width: parent.width
        cellWidth: 30
        cellHeight: 28

        delegate: MyRingButton{
            width: 25
            height: 25

            Component.onCompleted:  group = model.group;
            lev: lvt

            onGroupChanged: {
                model.group = group;
            }
        }
    }
}

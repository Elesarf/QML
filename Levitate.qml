import QtQuick 2.0
import QtQuick.Controls 2.0 as Controls

Rectangle{
    id:rect
    width: 150
    height: 120

    property bool show
    property string text
    opacity: 0
    border.width: 2
    border.color: "black"
    z:3

    Row{
        anchors.bottom: rect.bottom
        anchors.bottomMargin: rect.border.width
        anchors.left: rect.left
        anchors.leftMargin: rect.border.width
        Controls.Button{
            id: ok
            z:2
            text: "ok"
            width: rect.width/2 - rect.border.width
            onClicked: {
                rect.opacity = 0;
                show = false;
            }
        }
        Controls.Button{
            id: cancel
            z:2
            text: "cancel"
            width: rect.width/2 - rect.border.width
            onClicked: {
                rect.opacity = 0;
                show = false;
            }
        }
    }

    Text{
        text: rect.text
    }
}



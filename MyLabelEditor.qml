import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Extras 1.4

Item {
    id: labeledit
    width: parent.width
    height: parent.height

    property string text : ""
    property var model

    TextEdit{
        anchors.fill: parent
        text: parent.text
        font.pointSize: 12
        color: "black"
        wrapMode: TextEdit.WrapAnywhere
        onTextChanged:{
            if (text.length > 200) {
                var cursor = cursorPosition;
                text = labeledit.text;
                if (cursor > text.length) {
                    cursorPosition = text.length;
                } else {
                    cursorPosition = cursor-1;
                }
            }
            labeledit.text = text
        }
    }

    Button {
        id: button
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        text: qsTr("Ok")
        onClicked: {
            model.note = labeledit.text;
            parent.visible = false;
        }
    }
}

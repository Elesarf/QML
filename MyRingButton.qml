import QtQuick 2.5
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.0

Rectangle {
    id: circleButton

    width: parent.height
    height: width
    border.width: 0.5
    radius: width*0.5

    Component.onCompleted: circleButton.color = colors[group]

    readonly property variant colors :  ["red","lightgreen","lightseagreen","coral","mediumturquoise","violet", "lightsalmon", "chartreuse", "cornflowerblue", "darkcyan", "darkblue","darkorchid"
                                                                    ,"indigo", "yellow", "teal", "turquoise", "springgreen","sienna", "lightgoldenrodyellow", "orangered", "goldenrod"]
    property string text
    property int group : 0
    property bool onFocus: false

    states: State {
        name: "onFocus"; when: onFocus === true
        PropertyChanges { target: circleButton; border.width: 4}
        PropertyChanges { target: txt; opacity: 1 }
    }
    transitions: Transition {
        to: "onFocus"; reversible: true
        SequentialAnimation{
            PropertyAnimation{target: txt; property: "opacity"; duration: 800}
            PropertyAnimation{target: circleButton; property: "border.width"; duration: 400}
        }
    }

    PropertyAnimation{
        id: anim
        target: circleButton
        property: "border.width"
        duration: 400
    }

    PropertyAnimation{
        id: animT
        target: txt
        property: "opacity"
        duration: 400
    }

    Text {
        id: txt
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0
        text: qsTr("%1").arg(group)
    }

    MouseArea{
        id:mouseArea
        anchors.fill:parent
        hoverEnabled: true
        onClicked:{
            group = (group + 1)%20
        }

        onEntered: onFocus = true

        onExited: onFocus = false;
    }

    onGroupChanged:{
        if(group < colors.length)
        circleButton.color = colors[group]
    }
}

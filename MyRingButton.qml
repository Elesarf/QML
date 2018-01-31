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
    property var lev
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


    PropertyAnimation{
        id: animL
        target: lev
        property: "opacity"
        duration: 2000
    }

//    Levitate{
//        id:lev
//    }

    Text {
        id: txt
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0
        text: qsTr("%1").arg(group)
    }

    MouseArea{
        anchors.fill:parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked:{
            if(mouse.button === Qt.LeftButton)
            group = (group + 1)%20
            if(mouse.button === Qt.RightButton){
                lev.show = true;
                lev.opacity = 1;
                lev.text = qsTr("%1").arg(group);
                animL.stop();
            }
        }

        onEntered:{
            anim.stop();
            animT.stop();
            animL.stop();
            anim.to = 4;
            anim.start();

            animT.to = 1
            animT.start();

            if(!lev.show){
                animL.to = 1;
                animL.start();
            }
        }

        onMouseXChanged: {
            if(!lev.show)
            lev.x = mouseX + 10;
        }
        onMouseYChanged: {
            if(!lev.show)
            lev.y = mouseY + 10;
        }
        onExited: {
            anim.stop();
            animT.stop();
            animL.stop();
            anim.to = 0.5;
            anim.start();

            animT.to = 0
            animT.start();

            if(!lev.show){
                animL.duration = 300
                animL.to = 0;
                animL.start();
            }
        }
    }

    onGroupChanged:{
        if(group < colors.length)
        circleButton.color = colors[group]
    }
}

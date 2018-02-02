import QtQuick 2.0

Column {
    id: col1
    width: parent.width
    height: parent.height

    property var model
    property int dim
    property int giantHeight : height*0.6
    property real barbiHeight : (height - giantHeight ) / (dim - 1)
    property real normalHeight : height / dim

    MyLabelEditor{
        id: mle
        visible: false
    }

    PropertyAnimation{ id: animBarbie; property : "height"; duration: 400 }
    PropertyAnimation{ id: animGiant; property : "height"; duration: 400 }
    PropertyAnimation{ id: animNormal; property : "height"; duration: 200 }

    Repeater{
        id:repeat
        model: col1.model
        delegate: Rectangle{
            id:deleg
            width: parent.width
            height: normalHeight
            color: "lightgrey"
            border.width: 1
            border.color: "black"

            Binding{ target: deleg; property: "height"; value: normalHeight}

            Text{
                anchors.fill:parent
                id:txt
                visible: !mle.visible
                wrapMode: Text.WrapAnywhere
                text: qsTr("%1").arg( model.note)
            }

            MyRingButton{
                anchors.right: parent.right
                width: 15
                height: 15
                radius: 0
                group: model.group
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    if(!mle.visible){
                        var bList = [];
                        for(var i = 0; i < repeat.count; i+=1){
                            var item =  repeat.itemAt(i);
                            if(item !== parent){
                                bList.push(item);
                                } else {
                                animGiant.target = item;
                                animGiant.to = giantHeight;
                            }
                        }
                        animBarbie.targets = bList;
                        animBarbie.to = barbiHeight;
                        animBarbie.start();
                        animGiant.start();
                    }
                }
                onExited: {
                    animBarbie.stop();
                    animGiant.stop();
                    if(!mle.visible){
                        var bList = [];
                        for(var i = 0; i < repeat.count; i+=1){
                            var item =  repeat.itemAt(i);
                            bList.push(item);
                        }
                        animNormal.targets = bList;
                        animNormal.to = normalHeight;
                        animNormal.start();
                    }
                }
                onDoubleClicked: {
                    mle.parent = this;
                    mle.text = txt.text;
                    mle.model = model;
                    mle.visible = true;
                }
            }
        }
    }
}

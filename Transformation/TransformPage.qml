import QtQuick 2.0

Item {
    Rectangle {
        anchors.fill: parent;
        color: "#FFFFFF";
    }

    TransformCanvas {
        id: transformCanvas;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        width: parent.width * 0.9;
    }

    TransformInput {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: transformCanvas.right;
        anchors.right: parent.right;
        anchors.leftMargin: 10;
    }
}

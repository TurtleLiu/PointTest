import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "./Layout" as LAYOUT
import "./Transformation" as TRANS

ApplicationWindow {
    visible: true
    width: 1200
    height: width * 0.75;   //宽高比4：3
    title: qsTr("Agent Layout")

    SwipeView {
        id: swipeView
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: layoutList.top;
        anchors.bottomMargin: 10;
        currentIndex: tabBar.currentIndex

        LAYOUT.LayoutPage {

        }
        TRANS.TransformPage{

        }
    }

    LayoutList {
        id: layoutList;

        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Layout")
        }
        TabButton {
            text: qsTr("Transformation")
        }
    }
}

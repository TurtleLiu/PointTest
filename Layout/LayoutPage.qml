import QtQuick 2.4
import an.qt.ALPainter 1.0
import an.qt.Calculator 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import "../Layout"

LayoutPageForm {
    property int margin: 10;
    focus: true
    Keys.enabled: true
    Keys.onEscapePressed: Qt.quit();
    Keys.forwardTo: [alCanvas];
//    ALCanvas {
//        id: alCanvas;
//        anchors.top:parent.top;
//        height: parent.height/* * 0.778*/;
//        anchors.left: parent.left;
//        width: parent.width * 0.583;
//    }
    ScrollView {
        id:scrollview
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width*0.583;
        height: parent.height
        //contentWidth: parent.width*2; contentHeight: parent.height*2
        //clip: true
        //Image {id: image; source: "1.jpg"}
        ALPainter {
              id: alCanvas;
              //anchors.top:parent.top;
              height: scrollview.height*1/* * 0.778*/;
              //anchors.left: parent.left;
              width: scrollview.width*1
              fillColor: "#F0FFF0";
              Keys.enabled: true
              Keys.onPressed:{
                  switch (event.key){
                            case Qt.Key_D:
                                 alCanvas.deletePoints()
                                 //fillColor="#F0FFFF"
                                 break;
                            default:
                                return
                             }
                             event.accepted = true;
                         }
    //          onWidthChanged: {
    //              //painter.init()
    //              calculator.setWidth(width)
    //          }
    //          onHeightChanged: {
    //              //painter.init()
    //              calculator.setHeight(height)
    //          }
          }
    }



    Calculator{
        id:calculator
    }

    ImgCtrl {
        id: imgCtrl;
        anchors.leftMargin: margin;
        anchors.top:parent.top;
        height: parent.height * 0.429/*0.333*/;
        anchors.left: scrollview.right;
        anchors.right: parent.right;
    }

    InputCtrl {
        id:inputCtrl;
        anchors.leftMargin: margin;
        anchors.topMargin: margin;
        anchors.top:imgCtrl.bottom;
        height: parent.height * 0.571/*0.444*/ - margin;
        anchors.left: scrollview.right;
        anchors.right: parent.right;
    }
}

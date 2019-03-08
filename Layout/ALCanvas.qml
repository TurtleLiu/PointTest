import QtQuick 2.0
import an.qt.ALPainter 1.0
Item {
    Rectangle {
        id:canva
        anchors.fill: parent;
        color: "#F0FFF0";
    }

    ALPainter {
          id: painter;
          width: canva.width
          height: canva.height
//          onWidthChanged: {
//              //painter.init()
//          }
//          onHeightChanged: {
//             // painter.init()
//          }
      }


}

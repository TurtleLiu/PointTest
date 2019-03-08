import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import an.qt.ThresholdImg 1.0

Item {
    Rectangle {
        anchors.fill: parent;
        color: "#F0FFFF";
    }

    property int margin: 10;

    ThresholdImg{
        id:thresholdImg
    }

    Image {
        id: srcImg
        anchors.topMargin: margin;
        anchors.leftMargin: margin;
        anchors.top: parent.top;
        anchors.left: parent.left;
        width: (parent.width - margin * 3) / 2;
        height: width;
        fillMode: Image.PreserveAspectFit
        //source: "image://colors/origin"

        Rectangle {
            id: imgRec1;
            anchors.fill: parent;
            border.color: "black";
            border.width: 2;
            color: "#00000000";
        }
    }

    Image {
        id: thresImg;
        anchors.topMargin: margin;
        anchors.leftMargin: margin;
        anchors.top: parent.top;
        anchors.left: srcImg.right;
        height: (parent.width - margin * 3) / 2;
        width: height;
        //source: "image://colors/thres"
        fillMode: Image.PreserveAspectFit
        Rectangle {
            id: imgRec2;
            anchors.fill: parent;
            border.color: "black";
            border.width: 2;
            color: "#00000000";
        }
    }

    Button {
        id: open;
        anchors.left: srcImg.left;
        width: (srcImg - margin) / 2;
        anchors.topMargin: margin;
        anchors.top: srcImg.bottom;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: margin;
        Text {
            text:"打开图片"
            anchors.centerIn: parent;/*居中显示*/
            anchors.verticalCenterOffset: -1/*垂直居中偏移-1像素*/
            font.pixelSize: 16;
        }
        onClicked: {
            fileDialogOpenImg.selectedNameFilter = fileDialogOpenImg.nameFilters[0];
            fileDialogOpenImg.open();
        }
    }

    Button {
        id: reverse;
        anchors.leftMargin: margin;
        anchors.left: open.right;
        width: open.width;
        anchors.top: open.top;
        anchors.bottom: open.bottom;
        Text {
            text:"阈值反转"
            anchors.centerIn: parent;/*居中显示*/
            anchors.verticalCenterOffset: -1/*垂直居中偏移-1像素*/
            font.pixelSize: 16;
        }
        onClicked: {
            thresholdImg.thresholdReverse()
            thresImg.source=""
            thresImg.source = thresholdImg.reThreshold(Math.floor(thresValSlider.value))
        }
    }

    Text {
        id: threshold;
        text: qsTr("阈值：");
        anchors.left: thresImg.left;
        anchors.top: open.top;
        anchors.bottom: open.bottom;
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: 16;
    }

    Text {
        id: thresholdVal;
        text: qsTr("127");
        anchors.left: threshold.right;
        anchors.top: open.top;
        anchors.bottom: open.bottom;
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: 16;
    }

    Slider {
        id: thresValSlider;
        width: thresImg.width * 0.65;
        anchors.right: parent.right;
        anchors.rightMargin: margin;
        anchors.top: open.top;
        anchors.bottom: open.bottom;
        value: 127;
        from: 0;
        to: 255;
        onValueChanged: {
            thresholdVal.text = Math.floor(value);
            thresImg.source=""
            thresImg.source = thresholdImg.reThreshold(Math.floor(value));
        }
    }

    FileDialog {
        id: fileDialogOpenImg;
        title: qsTr("打开文件");
        nameFilters: ["Image Files (*.jpg *.png *.gif *.bmp *.ico *.jp2)"];
        onAccepted: {
            var filepath = this.fileUrl;
            srcImg.source = filepath;
            //threshold.text=thresholdImg.reThreshold(filepath);
            thresholdImg.setImg(filepath)
            thresImg.source=""
            thresImg.source = thresholdImg.reThreshold(Math.floor(thresValSlider.value))
            //cppImgCtrl.getUrl(filepath)
        }
    }
}

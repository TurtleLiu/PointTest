import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import an.qt.Calculator 1.0

Item {
    Rectangle {
        anchors.fill: parent;
        color: "#FFF8DC";
    }
    property int margin: 10;
    property int mode: 1;
    property double gapNum: 0;
    property int agtNum: 0;
    property bool ret;

//    CSVWriter不必与qml直接关联，由MVC模式，应由C层去调用
//    CSVWriter{
//        id:csvwriter
//    }

    Text {
        id: imgScale
        text: qsTr("显示比例")
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top: parent.top
        anchors.left: parent.left
        width:(parent.width-margin*4)/3/3*2
        height: (parent.height-margin*4)/3
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: 22;
    }

    Text {
        id: imgScaleVal
        text: qsTr("1.0")
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top:parent.top
        anchors.left: imgScale.right
        width:(parent.width-margin*4)/3/3
        height: (parent.height-margin*4)/3
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: 22;
    }

    Slider{
        id:imgScaleSlider
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top:parent.top
        anchors.left: imgScaleVal.right
        width:imgScaleVal.width*3
        height: (parent.height-margin*4)/3
        value: 0;
        from: -3;
        to: 3;
        stepSize: 1
        //BUG：小于1显示.99999
        onValueChanged: {
        //C1:增加滑条值变动时传参
            imgScaleVal.text = value*0.1+1;
        }
    }

    Button{
        id:modeSwitch
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top:parent.top
        anchors.left: imgScaleSlider.right
        width:imgScaleVal.width*3
        height: (parent.height-margin*4)/3
        Text {
            id:modeSwitchText
            text:"固定人数模式"
            anchors.centerIn: parent;/*居中显示*/
            anchors.verticalCenterOffset: -1/*垂直居中偏移-1像素*/
            font.pixelSize: 22;
        }
        onClicked: {
            //Finished!C2:添加模式切换接口,禁止文本框输入
            mode = 1 - mode;
            if (mode == 0) {
                modeSwitchText.text="固定间距模式"
                gapInput.readOnly = false
                agCntInput.readOnly = true
            }
            else {
                modeSwitchText.text="固定人数模式"
                gapInput.readOnly = true
                agCntInput.readOnly = false
            }
        }
    }

    Text {
        id: gap
        text: qsTr("间距")
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top: imgScale.bottom
        anchors.left: parent.left
        width:(parent.width-margin*4)/3
        height: (parent.height-margin*4)/3
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: 22;
    }

    TextField{
        id: gapInput
        //Q:占位字符不显示！！！！
        placeholderText: "请输入间距"
        font.pointSize: 22
        //textColor:"#313a4b"
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top: imgScale.bottom
        anchors.left: gap.right
        width:(parent.width-margin*4)/3
        height: (parent.height-margin*4)/3
        readOnly: true

    }



    Button{
        id:showPoints
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top:imgScale.bottom
        anchors.left: gapInput.right
        width:imgScaleVal.width*3
        height: (parent.height-margin*4)/3
        Text {
            text:"开始打点"
            anchors.centerIn: parent;/*居中显示*/
            anchors.verticalCenterOffset: -1/*垂直居中偏移-1像素*/
            font.pixelSize: 22;
        }
        onClicked: {
            //C3:需要补全的接口：取得参数，判断合法性，传递参数;找个合适位置取得打点后距离/人数
            if (mode == 0) {//固定间距
                gapNum = gapInput.text
                if (gapNum == 0) {
                    zeroGapWarning.open()
                }
                else if (gapNum > 70) {
                    overGapWarning.open()
                }
                else{
                    calculator.setWidth(alCanvas.width)
                    calculator.setHeight(alCanvas.height)
                    calculator.calcuLayout(imgScaleSlider.value*0.1+1,0,gapNum)
                    alCanvas.setAgentPos(calculator.drawPos)
                    alCanvas.draw()
                }

                }
                if (mode == 1) {//固定人数
                    agtNum = agCntInput.text
                    if (agtNum == 0) {
                        zeroAgCntWarning.open()
                    }
                    else{
                        calculator.setWidth(alCanvas.width)
                        calculator.setHeight(alCanvas.height)
                        calculator.calcuLayout(imgScaleSlider.value*0.1+1,1,agtNum)
                        alCanvas.setAgentPos(calculator.drawPos)
                        alCanvas.draw()
                    }

                }

        }
    }

    MessageDialog{
        id:zeroGapWarning
        title: "警告"
        icon: StandardIcon.Warning
        text:"输入间距不能为0!"
        onAccepted: {
            gapInput.text=""
        }
    }

    MessageDialog{
        id:overGapWarning
        title: "警告"
        icon: StandardIcon.Warning
        text:"输入距离超出坐标轴!"
        onAccepted: {
            gapInput.text=""
        }
    }

    MessageDialog{
        id:zeroAgCntWarning
        title: "警告"
        icon: StandardIcon.Warning
        text:"输入人数不能为0!"
        onAccepted: {
            agCntInput.text=""
        }
    }

    Text {
        id: agCnt
        text: qsTr("人数")
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top: gap.bottom
        anchors.left: parent.left
        width:(parent.width-margin*4)/3
        height: (parent.height-margin*4)/3
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: 22;
    }

    TextField{
        id: agCntInput
        placeholderText: "请输入人数"
        font.pointSize: 22
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top: gap.bottom
        anchors.left: agCnt.right
        width:(parent.width-margin*4)/3
        height: (parent.height-margin*4)/3
        readOnly: false
    }

    Button{
        id:writeFile
        anchors.topMargin: margin
        anchors.leftMargin: margin
        anchors.top:gap.bottom
        anchors.left: agCntInput.right
        width:imgScaleVal.width*3
        height: (parent.height-margin*4)/3
        Text {
            text:"输出坐标文件"
            anchors.centerIn: parent;/*居中显示*/
            anchors.verticalCenterOffset: -1/*垂直居中偏移-1像素*/
            font.pixelSize: 22;
        }
        onClicked: {
            //C4:需要的接口：传递打印命令
            ret=calculator.printAgtPos();
            if(ret==true)
                success.open()
            else
                fail.open()
        }
    }

    MessageDialog{
        id:success
        title: "提示"
        text:"CSV写入成功!"
    }

    MessageDialog{
        id:fail
        title: "提示"
        text: "CSV写入失败!"
        icon:StandardIcon.Critical
    }

    Connections{
       target: calculator
       onSetGap:{
           gapInput.text=Gap.toFixed(1);
       }
    }

    Connections{
        target: calculator
        onSetAgtNum:{
            agCntInput.text=AGtNum;
        }
    }

}

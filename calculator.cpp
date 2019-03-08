#include "calculator.h"

Calculator::Calculator(QObject *parent)
    :QObject (parent)
{
    m_calcudirect=new CalcuDirect();
    m_calcugap=new CalcuGap();
    m_calcuradio=new CalcuRadio();
    m_calculine=new CalcuLine();
    m_pointrotate=new PointRotate();
}

Calculator::~Calculator()
{

}

void Calculator::calcuLayout(float scale, int mode, double param)
{
    m_scale=scale;
    //C1:取得图片数据***************************************************
//    if (!m_imgShow->GetData(m_mat)) {
//        QMessageBox::warning(this, tr("警告！"), tr("请先打开图片进行阈值化获取图案"), QMessageBox::Yes);
//        return;
//    }
    m_mat=cv::imread("D:/threimg.jpg");
    cv::cvtColor(m_mat, m_mat, cv::COLOR_BGR2GRAY);//图像格式转换
    //cv::imshow("test",m_mat);
    //QVector<QPointF> agtPos;
    //C3:根据需求不同修改算法，根据不同需求封装为类***************************
    //固定间距
    if (mode == 0) {
//        m_rawAgtPos = m_calcudirect->ConstGapFunc(m_mat, param);
//        emit setAgtNum(m_calcudirect->getAgtNum());
        //m_rawAgtPos = m_calcugap->ConstGapFunc(m_mat, param);
        //m_rawAgtPos=m_calcuradio->ConstGapFunc(m_mat,param);
        //emit setAgtNum(m_calcuradio->getAgtNum());
        m_rawAgtPos=m_calculine->ConstGapFunc(m_mat,param);
        emit setAgtNum(m_calculine->getAgtNum());
    }
    //固定人数
    else {
        m_rawAgtPos = m_calcudirect->ConstNumFunc(m_mat, param);
        emit setGap(m_calcudirect->getGap());
//        m_rawAgtPos = m_calcugap->ConstNumFunc(m_mat, param);
//        emit setGap(m_calcugap->getGap());
    }
    coordinateManage(m_rawAgtPos);
    //rotateCoordinate(90);
}

void Calculator::rotateCoordinate(int angle){
    QVector<QPointF> agtPos;
    agtPos=m_pointrotate->pointRotate(m_rawAgtPos,angle);
    coordinateManage(agtPos);
}

void Calculator::coordinateManage(QVector<QPointF> &rawCoordinate){
    //坐标居中
    if (fabs(1.f * M_AREAWIDTH / M_AREAHEIGHT - 1.f * m_mat.cols / m_mat.rows) > 0.001f) {
        float wRate = 1.f * M_AREAWIDTH / m_mat.cols, hRate = 1.f * M_AREAHEIGHT / m_mat.rows;
        float rate = (hRate < wRate ? hRate : wRate);
        float width = m_mat.cols * rate, height = m_mat.rows * rate;

        for (auto& i : rawCoordinate) {
            i = i - QPointF(width / 2, height / 2) + QPointF(M_AREAWIDTH / 2, M_AREAHEIGHT / 2);
        }
    }

    m_agtPos = rawCoordinate;

    //乘缩放比例
    for (auto& i : rawCoordinate) {
        i = i * m_scale;
    }

    //中心点坐标统一
    QPoint oriCen(M_AREAWIDTH * m_scale / 2, M_AREAHEIGHT * m_scale / 2);
    QPoint CanvasCen(m_canvasWidth / 2, m_canvasHeight / 2);

    for (auto& i : rawCoordinate) {
        i = CanvasCen + (i - oriCen) * (oriCen.x() * 1.f / CanvasCen.x());
    }

    //QVector<QPoint> drawData;
    m_drawPos.clear();
    for (auto& i : rawCoordinate) {
        m_drawPos.push_back(QPoint(i.x(),i.y()));
    }
}

bool Calculator::printAgtPos(){
    bool ret = CSVWriter::GetInstance()->writeCSV("Output.csv",m_agtPos);
    return ret;
}

void Calculator::setWidth(int width){
    m_canvasWidth=width;
}

void Calculator::setHeight(int height){
    m_canvasHeight=height;
}
QVector<QPoint> Calculator::drawPos(){
    return m_drawPos;
}

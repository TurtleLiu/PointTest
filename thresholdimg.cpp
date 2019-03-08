#include "thresholdimg.h"
#include<QString>

ThresholdImg::ThresholdImg(QObject *parent)
    :QObject (parent)
    ,m_thresFlag(0)
{

}

ThresholdImg::~ThresholdImg()
{

}

void ThresholdImg::setImg(QString ImgPath)
{
    //脱壳
    std::string img_path=ImgPath.toStdString();
    img_path=img_path.substr(8);//file:///共8字符
    m_img=cv::imread(img_path);
    cv::cvtColor(m_img, m_img, cv::COLOR_BGR2GRAY);//图像格式转换
    //cv::imshow("test", m_img);
}

QString ThresholdImg::reThreshold(int value)
{
    //阈值化操作
    cv::threshold(m_img,m_imgThres, value, 255, m_thresFlag);
    m_desPath="D:/threimg.jpg";
    cv::imwrite(m_desPath.toStdString(),m_imgThres);
    //cv::imshow("test", m_img);
    return "file:///"+m_desPath;
}

void ThresholdImg::thresholdReverse()
{
    m_thresFlag = m_thresFlag == 0 ? 1 : 0;
}

#ifndef THRESHOLDIMG_H
#define THRESHOLDIMG_H
#include<QObject>
#include<QDebug>
#include <opencv2/opencv.hpp>
class ThresholdImg:
        public QObject
{
    Q_OBJECT
public:
    ThresholdImg(QObject *parent=0);
    ~ThresholdImg();

    Q_INVOKABLE void setImg(QString ImgPath);
    Q_INVOKABLE QString reThreshold(int value);
    Q_INVOKABLE void thresholdReverse();

private:
    int m_thresFlag;

    QString m_srcPath;
    QString m_desPath;

    cv::Mat m_img;
    cv::Mat m_imgThres;
};

#endif // THRESHOLDIMG_H

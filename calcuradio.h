#ifndef CALCURADIO_H
#define CALCURADIO_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <qvector.h>
#include <QPointF>

class CalcuRadio: public QObject
{
    Q_OBJECT
public:
    CalcuRadio(QObject *parent=0);
    ~CalcuRadio();
    QVector<QPointF> ConstGapFunc(cv::Mat& mat, float gap);
    QVector<QPointF> ConstNumFunc(cv::Mat& mat, int agtNum);

    int getAgtNum();
    float getGap();

private:
    static const int M_AREAWIDTH = 690;
    static const int M_AREAHEIGHT = 690;

    int m_agtNum;
    float m_gap;
};

#endif // CALCURADIO_H

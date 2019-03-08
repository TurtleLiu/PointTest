#ifndef CALCUDIRECT_H
#define CALCUDIRECT_H
#include <QObject>
#include <opencv2/opencv.hpp>
#include <qvector.h>
#include <QPointF>
class CalcuDirect:public QObject
{
    Q_OBJECT

public:
    CalcuDirect(QObject *parent=0);
    ~CalcuDirect();
    //距离、人数计算
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

#endif // CALCUDIRECT_H

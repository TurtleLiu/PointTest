#ifndef CALCULINE_H
#define CALCULINE_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <qvector.h>
#include <QPointF>

class CalcuLine:public QObject
{
    Q_OBJECT
public:
    CalcuLine(QObject *parent=0);
    ~CalcuLine();
    QVector<QPointF> ConstGapFunc(cv::Mat& mat, float gap);
    QVector<QPointF> ConstNumFunc(cv::Mat& mat, int agtNum);

    int getAgtNum();
    float getGap();
protected:
    int goPikachu(int x,int y);
private:
    static const int M_AREAWIDTH = 690;
    static const int M_AREAHEIGHT = 690;

    QVector<QPointF> m_rawPoint;
    cv::Mat m_mat;
    int m_agtNum;
    float m_gap;

};

#endif // CALCULINE_H

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <csvwriter.h>
#include <calcudirect.h>
#include <calcugap.h>
#include <pointrotate.h>
#include <calcuradio.h>
#include <calculine.h>
class Calculator:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<QPoint> drawPos READ drawPos)

public:
    Calculator(QObject *parent=0);
    ~Calculator();
    Q_INVOKABLE void calcuLayout(float scale, int mode, double param);
     void rotateCoordinate(int angle);
    Q_INVOKABLE bool printAgtPos();
    Q_INVOKABLE void setWidth(int width);
    Q_INVOKABLE void setHeight(int height);
    QVector<QPoint> drawPos();
    //Q_INVOKABLE void setDrawPos(QVector<QPoint> agentPos);
protected:
    void coordinateManage(QVector<QPointF> &rawCoordinate);
signals:
    void setGap(float Gap);
    void setAgtNum(int AGtNum);

private:
    QVector<QPointF> ConstGapFunc(cv::Mat& mat, float gap);
    QVector<QPointF> ConstNumFunc(cv::Mat& mat, int agtNum);
    //存储输出文件坐标
    QVector<QPointF> m_rawAgtPos;
    QVector<QPointF> m_agtPos;
    QVector<QPoint> m_drawPos;

    //输出文件坐标范围，TODO：可用配置文件设置
    static const int M_AREAWIDTH = 690;
    static const int M_AREAHEIGHT = 690;

    int m_canvasWidth;
    int m_canvasHeight;
    float m_scale;
    cv::Mat m_mat;
    //算法类
    CalcuDirect *m_calcudirect;
    CalcuGap *m_calcugap;
    CalcuRadio *m_calcuradio;
    CalcuLine *m_calculine;
    PointRotate *m_pointrotate;
};

#endif // CALCULATOR_H

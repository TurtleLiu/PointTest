#ifndef POINTROTATE_H
#define POINTROTATE_H

#include <QObject>
#include <qvector.h>
#include <QPointF>

class PointRotate: public QObject
{
    Q_OBJECT
public:
    PointRotate(QObject *parent=0);
    ~PointRotate();
    QVector<QPointF> pointRotate(QVector<QPointF> &agtPos,float angle);

protected:
    QPointF rotateAngle(QPointF &point);

private:
    QVector<QPointF> m_agtPos;
    double m_angle;
    //中心点坐标
    static const int M_CENTRALX = 345;
    static const int M_CENTRALY = 345;
};

#endif // POINTROTATE_H

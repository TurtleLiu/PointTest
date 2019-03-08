#include "pointrotate.h"
#include<cmath>
#include<qdebug.h>
PointRotate::PointRotate(QObject *parent)
    :QObject(parent)
{

}

PointRotate::~PointRotate(){

}

QVector<QPointF> PointRotate::pointRotate(QVector<QPointF> &agtPos,float angle){
    const double rad_to_ded=57.29577951;//1弧度=57.29577度
    //qDebug()<<angle<<endl;
    m_agtPos=agtPos;
    m_angle=angle/rad_to_ded;
    for (auto& i : m_agtPos) {
        i=rotateAngle(i);
    }
    return m_agtPos;
}

QPointF PointRotate::rotateAngle(QPointF &point){
    QPointF aPoint=point;
    float point_x=point.x()-M_CENTRALX;
    float point_y=point.y()-M_CENTRALY;
    double point_r=sqrt(point_x*point_x+point_y*point_y);
    double point_angle=atan2(point_y,point_x);
    point_angle+=m_angle;
    //qDebug()<<point_angle<<endl;
    point_x=point_r*cos(point_angle);
    point_y=point_r*sin(point_angle);
    aPoint.setX(point_x+M_CENTRALX);
    aPoint.setY(point_y+M_CENTRALY);
    return aPoint;
}

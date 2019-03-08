#ifndef ALPAINTER_H
#define ALPAINTER_H
#include <QQuickPaintedItem>
#include <QPainterPath>
#include <QPainter>
#include <QPointF>
#include <QImage>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <qvector.h>
#include <qevent.h>
#include <qpainter.h>
#include <qpen.h>
class ALPainter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVector<QPoint> agentPos READ agentPos WRITE setAgentPos)

public:
    ALPainter(QQuickItem *parent = 0);
    ~ALPainter();
    Q_INVOKABLE void draw();
    //删除选中的agent，返回剩余agent
    Q_INVOKABLE void deletePoints();
    void paint(QPainter *painter);
    QVector<QPoint> agentPos();
    Q_INVOKABLE void setAgentPos(QVector<QPoint> agentPos);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QVector<QPoint> m_agentPos;		//所有agent坐标
    QVector<QPoint> m_selectAgent;	//被选中的agent坐标（会从m_agentPos暂时移到本数组内）

    //实现框选逻辑
    bool m_isSelecting;
    QPoint m_startPos;
    QPoint m_movingPos;
};

#endif // ALPAINTER_H




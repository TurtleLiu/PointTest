#include "alpainter.h"
ALPainter::ALPainter(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_isSelecting(false)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

ALPainter::~ALPainter()
{
}
//const QVector<QPoint>& pos
void ALPainter::draw()
{
    //C1:找方法传入点数据****************
    //m_addToList->show();
    //m_agentPos = pos;
    update();
}

void ALPainter::paint(QPainter *painter)
{
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    pen.setWidth(2);
    painter->setPen(pen);
    //画未被选中的agent
    for (const auto& i : m_agentPos) {
        painter->drawPoint(i);
    }

    pen.setColor(QColor(0, 0, 255));
    painter->setPen(pen);

    //画被选中的agent
    for (const auto& i : m_selectAgent) {
        painter->drawPoint(i);
    }

    //画选择框
    if (m_isSelecting) {
        QPen recPen; //画笔
        recPen.setColor(QColor(0, 0, 255));
        recPen.setWidth(2);
        painter->setPen(recPen);
        painter->drawRect(QRect(m_startPos, m_movingPos));
    }
}

void ALPainter::deletePoints()
{
    //C2:补上键盘事件****************
    m_selectAgent.clear();
    update();
    //return m_agentPos;
}
//鼠标事件处理
void ALPainter::mousePressEvent(QMouseEvent *event)
{
//    if(!(event->button() & acceptedMouseButtons()))
//    {
//        QQuickPaintedItem::mousePressEvent(event);
//    }
//    else{
        m_startPos = event->pos();
        m_isSelecting = true;
//    }
}

void ALPainter::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isSelecting) {
            m_movingPos = event->pos();
            update();
//            QQuickPaintedItem::mouseMoveEvent(event);
        }
    //QQuickPaintedItem::mouseMoveEvent(event);
}

void ALPainter::mouseReleaseEvent(QMouseEvent *event)
{
//    if(!(event->button() & acceptedMouseButtons()))
//    {
//        QQuickPaintedItem::mousePressEvent(event);
//    }
//    else{
        if(m_isSelecting)
        {
            m_isSelecting = false;

            //先将上次选中没有删掉的的加回来
            m_agentPos.append(m_selectAgent);
            m_selectAgent.clear();

            //将选中的agent移入m_selectAgent
            QPoint leftTop(std::min(m_startPos.x(), event->x()), std::min(m_startPos.y(), event->y()));
            QPoint rightBottom(std::max(m_startPos.x(), event->x()), std::max(m_startPos.y(), event->y()));
            for (auto i = m_agentPos.begin(); i != m_agentPos.end();) {
                if (i->x() > leftTop.x() && i->x() < rightBottom.x() && i->y() > leftTop.y() && i->y() < rightBottom.y()) {
                    m_selectAgent.append(*i);
                    std::swap(*i, m_agentPos.back());
                    m_agentPos.pop_back();
                }
                else
                    i++;
            }

            update();
        }
//    }
}

QVector<QPoint> ALPainter::agentPos(){
    return m_agentPos;
}
void ALPainter::setAgentPos(QVector<QPoint> agentPos){
    m_agentPos=agentPos;
}

#include "cell.h"

Cell::Cell()
    : QGraphicsItem(),
      m_width(0),
      m_height(0),
      m_state(false)
{
}

QVariant Cell::state() const
{
    return m_state;
}

void Cell::setState(QVariant state_)
{
    m_state = state_.toBool();
    update();
}

QSizeF Cell::size() const
{
    return QSizeF(m_width, m_height);
}

void Cell::setSize(double width, double height)
{
    m_width = width;
    m_height = height;
}


QRectF Cell::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    if (m_state) {
        painter->setBrush(Qt::green);
    } else {
        painter->setBrush(Qt::white);
    }
    painter->drawRect(this->boundingRect());
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->scene()->property("pause").toBool()) {
        m_state = !m_state;
        update();
    }
    QGraphicsItem::mousePressEvent(event);
}

double Cell::width() const
{
    return m_width;
}

void Cell::setWidth(double width)
{
    m_width = width;
}

double Cell::height() const
{
    return m_height;
}

void Cell::setHeight(double height)
{
    m_height = height;
}

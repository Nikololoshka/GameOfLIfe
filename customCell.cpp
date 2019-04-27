#include "customCell.h"

CustomCell::CustomCell()
    : Cell ()
{
}

QVariant CustomCell::state() const
{
    return m_color;
}

void CustomCell::setState(QVariant state_)
{
    if(state_.type() == QVariant::Type::Bool) {
        switch (qrand() % 10) {
        case 0:
            m_color = QColor(Qt::red);
            break;
        case 1:
            m_color = QColor(Qt::blue);
            break;
        case 2:
            m_color = QColor(Qt::yellow);
            break;
        default:
            m_color = QColor(Qt::white);
            break;
        }
    } else {
        m_color = state_.value<QColor>();
    }

    this->update();
}

void CustomCell::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->setBrush(m_color);
    painter->drawRect(this->boundingRect());
}

void CustomCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->scene()->property("pause").toBool()) {
        update();
    }
    QGraphicsItem::mousePressEvent(event);
}

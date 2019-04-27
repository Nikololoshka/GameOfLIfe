#ifndef CELLCUSTOM_H
#define CELLCUSTOM_H

#include <QtWidgets>
#include "cell.h"

// Класс описывающий "клетку" на поле
// В отличии от своего предшествиника
// состоянием клетка является цвет, которым она
// в последствии о отображается на поле
class CustomCell : public Cell
{
public:
    CustomCell();

    QVariant state() const override;
    void setState(QVariant state_) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QColor m_color;
};

#endif // CELLCUSTOM_H

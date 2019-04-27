#ifndef CELL_H
#define CELL_H

#include <QtWidgets>

// Класс описывающий "клетку" на поле
class Cell : public QGraphicsItem
{
public:
    Cell();

    virtual QVariant state() const;
    virtual void setState(QVariant state_);

    QSizeF size() const;
    void setSize(double width, double height);

    double width() const;
    void setWidth(double width);

    double height() const;
    void setHeight(double height);

    QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    double m_width;
    double m_height;

private:
    bool m_state;
};

#endif // CELL_H

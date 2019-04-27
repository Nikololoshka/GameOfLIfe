#ifndef CUSTOMRULES_H
#define CUSTOMRULES_H

#include <QtWidgets>
#include "classicRules.h"

// Класс с собственными правилами
class CustomRules : public ClassicRules
{
public:
    CustomRules();

    // Метод для создания нового поколения
    // на основе текущего
    void newGeneration(QVector<QVector<Cell *> > &oldMap,
                       QVector<QVector<QVariant> > &newMap, int size) override;

    // Информация о данных правилах
    QString information() const override;
    // Используют ли данные правила иные "клетки" на поле
    bool isCustomCell() const override;

    // Проверка на окончание игры
    QString chechWinner(bool changeMap) const override;

protected:
    // Метод для подсчета соседий
    int neighbors(QVector<QVector<Cell *> > &map, int x, int y, int size) override;
    int colorNeighbors(QVector<QVector<Cell *> > &map, int x, int y, int size, QColor color);

    uint m_numberRedCells;
    uint m_numberBlueCells;
};

#endif // CUSTOMRULES_H

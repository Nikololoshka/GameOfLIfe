#ifndef CLASSICRULES_H
#define CLASSICRULES_H

#include <QtWidgets>
#include "cell.h"

// Классические правила игры "Жизнь"
class ClassicRules
{
public:
    ClassicRules();
    virtual ~ClassicRules();

    // Метод для создания нового поколения
    // на основе текущего
    virtual void newGeneration(QVector<QVector<Cell *>> &oldMap,
                               QVector<QVector<QVariant>> &newMap, int size);

    // Информация о данных правилах
    virtual QString information() const;
    // Используют ли данные правила иные "клетки" на поле
    virtual bool isCustomCell() const;

    // Проверка на окончание игры
    virtual QString chechWinner(bool changeMap) const;

    uint numberLivingCells() const;
    uint numberDeadCells() const;

protected:
    // Метод для подсчета соседий
    virtual int neighbors(QVector<QVector<Cell *> > &map, int x, int y, int size);

protected:
    uint m_numberLivingCells;
    uint m_numberDeadCells;
};

#endif // CLASSICRULES_H

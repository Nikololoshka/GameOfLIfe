#include "classicRules.h"

ClassicRules::ClassicRules()
    : m_numberLivingCells(0),
      m_numberDeadCells(0)
{}

ClassicRules::~ClassicRules()
{}

void ClassicRules::newGeneration(QVector<QVector<Cell *> > &oldMap,
                                 QVector<QVector<QVariant> > &newMap, int size)
{
    m_numberLivingCells = 0;
    m_numberDeadCells = 0;

    for (int i = 0; i < oldMap.size(); ++i) {
        for (int j = 0; j < oldMap[i].size(); ++j) {
            int countNeighbors = neighbors(oldMap, i, j, size);
            if (oldMap[i][j]->state().toBool()) {
                if (countNeighbors == 2 || countNeighbors == 3) {
                    newMap[i][j] = true;
                    ++m_numberLivingCells;
                } else {
                    ++m_numberDeadCells;
                }
            } else {
                if (countNeighbors == 3) {
                    newMap[i][j] = true;
                    ++m_numberLivingCells;
                }
            }
        }
    }
}

QString ClassicRules::information() const
{
    return QObject::tr("<p style=\"font-weight: bold\">Классические правила:</p>"
                       "<p align=justify>Распределение живых клеток в начале игры"
                       " производится случайным образом. Каждое следующее "
                       "поколение рассчитывается на основе предыдущего по таким правилам:<br>"
                       "1) в пустой (мёртвой) клетке, рядом с которой "
                       "ровно три живые клетки, зарождается жизнь;<br>"
                       "2) если у живой клетки есть две или три живые "
                       "соседки, то эта клетка продолжает жить;<br>"
                       "3) в противном случае, если соседей меньше "
                       "двух или больше трёх, клетка умирает "
                       "(«от одиночества» или «от перенаселённости»)</p>");
}

bool ClassicRules::isCustomCell() const
{
    return false;
}

QString ClassicRules::chechWinner(bool changeMap) const
{
    if (!changeMap) {
        return QObject::tr("При очередном шаге ни одна из клеток не меняет "
                           "своего состояния (складывается стабильная конфигурация)");
    }

    if (m_numberLivingCells == 0) {
        return QObject::tr("На поле не осталось ни одной живой клетки");
    }

    return "";
}

uint ClassicRules::numberLivingCells() const
{
    return m_numberLivingCells;
}

uint ClassicRules::numberDeadCells() const
{
    return m_numberDeadCells;
}

int ClassicRules::neighbors(QVector<QVector<Cell *> > &map, int x, int y, int size)
{
    int countNeighbors = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i != x || j != y)
                if (i >= 0 && j >= 0 && i < size && j < size)
                    if (map[i][j]->state().toBool())
                        countNeighbors++;
        }
    }
    return countNeighbors;
}

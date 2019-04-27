#include "customMazeRules.h"

CustomMazeRules::CustomMazeRules()
    : ClassicRules ()
{}

void CustomMazeRules::newGeneration(QVector<QVector<Cell *> > &oldMap,
                                    QVector<QVector<QVariant> > &newMap, int size)
{
    m_numberLivingCells = 0;
    m_numberDeadCells = 0;

    for (int i = 0; i < oldMap.size(); ++i) {
        for (int j = 0; j < oldMap[i].size(); ++j) {
            int countNeighbors = neighbors(oldMap, i, j, size);
            if (oldMap[i][j]->state().toBool()) {
                if (countNeighbors < 2) {
                    ++m_numberDeadCells;
                } else if (countNeighbors < 5) {
                    newMap[i][j] = true;
                    ++m_numberLivingCells;
                } else if (countNeighbors < 7) {
                    ++m_numberDeadCells;
                } else {
                    newMap[i][j] = true;
                    ++m_numberLivingCells;
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

QString CustomMazeRules::information() const
{
    return QObject::tr("<p style=\"font-weight: bold\">Правила для \"лабиринта\":</p>"
                       "<p align=justify>Распределение живых клеток в начале игры"
                       " производится случайным образом. Каждое следующее "
                       "поколение рассчитывается на основе предыдущего по таким правилам:<br>"
                       "1) в мёртвой клетке, рядом с которой ровно три живые клетки, зарождается жизнь;<br>"
                       "2) если у живой клетки менее 2 соседей, то эта клетка умерает;<br>"
                       "3) если у живой клетки от 2 до 5 соседей, то эта клетка остается живой;<br>"
                       "4) если у живой клетки от 5 до 7 соседей, то эта клетка умерает;<br>"
                       "5) если у живой клетки более 7 соседей, то эта клетка остается живой</p>");
}

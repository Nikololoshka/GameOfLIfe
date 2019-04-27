#include "customRules.h"

CustomRules::CustomRules()
    : ClassicRules ()
{  
}

void CustomRules::newGeneration(QVector<QVector<Cell *> > &oldMap,
                                QVector<QVector<QVariant> > &newMap, int size)
{
    m_numberLivingCells = 0;
    m_numberDeadCells = 0;

    m_numberRedCells = 0;
    m_numberBlueCells = 0;

    for (int i = 0; i < oldMap.size(); ++i) {
        for (int j = 0; j < oldMap[i].size(); ++j) {
            int countNeighbors = neighbors(oldMap, i, j, size);
            QColor color = oldMap[i][j]->state().value<QColor>();
            if (color != Qt::white) {
                if (countNeighbors > 2 && countNeighbors < 5) {
                    int red = colorNeighbors(oldMap, i, j, size, Qt::red);
                    int blue = colorNeighbors(oldMap, i, j, size, Qt::blue);
                    if (red && blue && color == Qt::yellow) {
                        if (red > blue) {
                            newMap[i][j] = QColor(Qt::red);
                            ++m_numberRedCells;
                        } else if (blue > red) {
                            newMap[i][j] = QColor(Qt::blue);
                            ++m_numberBlueCells;
                        } else {
                            newMap[i][j] = QColor(Qt::white);
                            ++m_numberDeadCells;
                            continue;
                        }
                    } else if (red > blue) {
                        newMap[i][j] = QColor(Qt::red);
                        ++m_numberRedCells;
                    } else if (blue > red){
                        newMap[i][j] = QColor(Qt::blue);
                        ++m_numberBlueCells;
                    } else {
                        newMap[i][j] = QColor(Qt::white);
                        ++m_numberDeadCells;
                        continue;
                    }
                    ++m_numberLivingCells;
                } else {
                    newMap[i][j] = QColor(Qt::white);
                    ++m_numberDeadCells;
                }
            } else {
                if (countNeighbors >= 3 && countNeighbors < 5) {
                    newMap[i][j] = QColor(Qt::yellow);
                    ++m_numberLivingCells;
                } else {
                    newMap[i][j] = QColor(Qt::white);
                }
            }
        }
    }
}

QString CustomRules::information() const
{
    return QObject::tr("<p style=\"font-weight: bold\">Модифицированные правила:</p>"
                       "<p align=justify>Распределение живых клеток в начале игры"
                       " производится случайным образом. Каждое следующее "
                       "поколение рассчитывается на основе предыдущего по таким правилам:<br>"
                       "1) в пустой (мёртвой) клетке, рядом с которой "
                       "ровно от 3 до 5 живых клетки, зарождается клетка желтого цвета (неопределившийся);<br>"
                       "Если у живой клетки от 2 до 5 живые соседки, то:"
                       "<ul>"
                       "<li>Если эта клетка желтого цвета и рядом много красных (синих) клеток,"
                       "то эта клетка становится красной (синей), иначе клетка становится белой (т.е. пустой);</li>"
                       "<li>Если клетка белого цвета и рядом много красных (синих) клеток,"
                       "то эта клетка становится красной (синей).</li>"
                       "</ul>"
                       "Признаком окончания игры является, помимо классических, является полное уничтожение"
                       "одного из \"вида\" клеток (красных или синих)."
                       "</p>");
}

bool CustomRules::isCustomCell() const
{
    return true;
}

QString CustomRules::chechWinner(bool changeMap) const
{
    if (!changeMap) {
        return QObject::tr("При очередном шаге ни одна из клеток не меняет "
                           "своего состояния (складывается стабильная конфигурация)");
    }

    if (m_numberLivingCells == 0) {
        return QObject::tr("На поле не осталось ни одной живой клетки");
    }

    if (m_numberRedCells == 0 || m_numberBlueCells == 0) {
        return QObject::tr("Победила одна из сторон");
    }

    return "";
}

int CustomRules::neighbors(QVector<QVector<Cell *> > &map, int x, int y, int size)
{
    int countNeighbors = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i != x || j != y)
                if (i >= 0 && j >= 0 && i < size && j < size)
                    if (map[i][j]->state().value<QColor>() != Qt::white)
                        countNeighbors++;
        }
    }
    return countNeighbors;
}

int CustomRules::colorNeighbors(QVector<QVector<Cell *> > &map, int x, int y, int size, QColor color)
{
    int countNeighbors = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i != x || j != y)
                if (i >= 0 && j >= 0 && i < size && j < size)
                    if (map[i][j]->state().value<QColor>() == color)
                        countNeighbors++;
        }
    }
    return countNeighbors;
}


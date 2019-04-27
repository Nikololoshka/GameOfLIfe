#ifndef CUSTOM_MAZE_RULES_H
#define CUSTOM_MAZE_RULES_H

#include <QtWidgets>
#include "classicRules.h"

class CustomMazeRules : public ClassicRules
{
public:
    CustomMazeRules();
    void newGeneration(QVector<QVector<Cell *> > &oldMap,
                       QVector<QVector<QVariant> > &newMap, int size) override;
    QString information() const override;
};

#endif // CUSTOM_MAZE_RULES_H

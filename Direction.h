#ifndef DIRECTION_H
#define DIRECTION_H

#include <QPoint>

enum class Direction {
    North,
    South,
    East,
    West,
    Undefinied
};

QPoint getDirectionPoint(Direction direction);
Direction getPointsDirection(QPoint first,QPoint last);
void printDirection(Direction direction);
Direction nextDirection(Direction direction);

#endif // DIRECTION_H

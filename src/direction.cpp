
#include "Direction.h"
#include <iostream>


Direction getPointsDirection(QPoint first,QPoint last){

    if(first.x()-last.x()==0){
        if(last.y()-first.y()>0){
            return Direction::South;
        }
        else if(last.y()-first.y()<0){
            return Direction::North;
        }
        else{
            return Direction::Undefinied;
        }
    }
    else if(first.y()-last.y()==0){
        if(last.x()-first.x()>0){
            return Direction::East;
        }
        else if(last.x()-first.x()<0){
            return Direction::West;
        }
    }
    return Direction::Undefinied;
}


QPoint getDirectionPoint(Direction direction) {
    switch (direction) {
    case Direction::North:
        return QPoint(0, -1);
    case Direction::South:
        return QPoint(0, 1);
    case Direction::East:
        return QPoint(1, 0);
    case Direction::West:
        return QPoint(-1, 0);
    default:
        return QPoint(0, 0);
    }
}


void printDirection(Direction direction){
    switch (direction) {
    case Direction::North:
        std::cout << "North"<<std::endl;
        break;
    case Direction::South:
        std::cout << "South"<<std::endl;
        break;
    case Direction::East:
        std::cout << "East"<<std::endl;
        break;
    case Direction::West:
        std::cout << "West"<<std::endl;
        break;

    case Direction::Undefinied:
        std::cout << "Other"<<std::endl;
        break;
    }
}


Direction nextDirection(Direction direction){
    switch (direction) {
    case Direction::North:
        return Direction::East;
    case Direction::South:
        return Direction::West;
    case Direction::East:
        return Direction::South;
    case Direction::West:
        return Direction::North;
    default:
        return Direction::Undefinied;
    }
}










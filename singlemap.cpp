#include "singlemap.h"
#include <QFile>
#include <QTextStream>

singleMap::singleMap(QObject *parent) : QObject(parent)
{
    this->mapBackground.load(":/image/map.png");
    this->scale = 5;
    this->createRoads();
    this->createHashSet();

}

bool singleMap::createHashSet()
{

}

bool singleMap::createRoads()
{

}

QHash<qlonglong, QPoint>*   singleMap::getMapHashSet()
{
    if(!mapHashSet.isEmpty())
        return &mapHashSet;
    else
        return NULL;

}

QLine*  singleMap::getMapRoads()
{
    return mapRoads;
}

QPixmap singleMap::getBackground()
{
    return this->mapBackground;
}

#include "map.h"
#include "ui_map.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QPainter>
Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);

    map = singleMap::getInstance();
}

Map::~Map(){
    delete ui;
}

void Map::paintEvent(QPaintEvent *)
{
    QPainter        painter(this);
    // QPoint          point(0, 0);
    QPoint          point(200, 200);
    QPoint          p0(0, 0);
    //car
    QPen            pen;
    QRect           rect;
    QPixmap         carPixmap;
    resize(700,700);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.drawPixmap(0, 0, width(), height(), map->getBackground());
    painter.scale(width()/1000.0, height()/1000.0);

    carPixmap.load(":/image/car.png");

    map->createHashSet();

    //获取小车当前坐标
  //  point = map->getMapHashSet()->value(info->getPosition());

    rect.setWidth(36);
    rect.setHeight(36);
    rect.moveCenter(point);
    painter.drawPixmap(rect, carPixmap);


}

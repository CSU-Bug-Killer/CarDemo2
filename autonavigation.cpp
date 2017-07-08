#include "autonavigation.h"
#include "ui_autonavigation.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QPainter>
#include "singlemap.h"
#include <QVariantMap>
#include "communicawidget.h"
#include "carmap.h"
#include <QDebug>

AutoNavigation::AutoNavigation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoNavigation)
{
    ui->setupUi(this);
    map = singleMap::getInstance();
    singleConnect = CommunicaWidget :: getInstance();
    connect(singleConnect,SIGNAL(signalReadMesg(QString)),
            this,SLOT(parseMsg(QString)));
    connect(this,SIGNAL(carMapUpdate(QString)),
            this,SLOT(updateCarmap(QString)));
}

AutoNavigation::~AutoNavigation()
{
    delete ui;
}

void AutoNavigation::updateAutomap(QString position){

   // point2 = map->getMapHashSet()->value(position.toLongLong());
}

void AutoNavigation::paintEvent(QPaintEvent *)
{
    QPainter        painter(this);
    QRect           rect;
    QPixmap         carPixmap;

    timer.start(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
   // painter.scale(width()/1000.0, height()/1000.0);
    painter.setRenderHints(QPainter::Antialiasing);

    painter.drawPixmap(0, 0, 700,700, map->getBackground());

    carPixmap.load(":/image/car.png");
//    rect.setWidth(31);
//    rect.setHeight(15);
//    rect.moveCenter(point);
//    painter.drawPixmap(rect, carPixmap);

}
void AutoNavigation::parseMsg(QString msg)
{

}

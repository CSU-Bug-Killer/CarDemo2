#include "carmap.h"
#include "ui_carmap.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QPainter>
#include "singlemap.h"

#include <QDebug>

CarMap::CarMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarMap)
{
    ui->setupUi(this);
    map = singleMap::getInstance();
    singleConnect = CommunicaWidget :: getInstance();
}

CarMap::~CarMap()
{
    delete ui;
}

void CarMap::paintEvent(QPaintEvent *)
{
    QPainter        painter(this);
    // QPoint          point(0, 0);
    QPoint          point(200, 200);
    QPoint          p0(0, 0);
    //car
    QPen            pen;
    QRect           rect;
    QPixmap         carPixmap;

    painter.setRenderHints(QPainter::Antialiasing);
    painter.drawPixmap(0, 0, width(), height(), map->getBackground());
    painter.scale(width()/1000.0, height()/1000.0);

    carPixmap.load(":/image/car.png");


    //获取小车当前坐标
  //  point = map->getMapHashSet()->value(info->getPosition());

    rect.setWidth(36);
    rect.setHeight(36);
    rect.moveCenter(point);
    painter.drawPixmap(rect, carPixmap);


}

void CarMap::parseMsg(QString msg)
{
    /*
        * msg = "{"
        */
       qDebug() << "di";
           QString json("{"
                        "\"message\":\"小车位置\","
                        "\"data\":{"
                        "\"returnType\":\"carPosition\","
                        "\"returnData\":{"
                        "\"device\":\"car1\","
                        "\"position\":\"36\""
                        "}"
                        "}"
                        "}"
                       );

           QJsonParseError error;
           QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toUtf8(),&error);
           if(error.error == QJsonParseError::NoError){
               if(jsonDocument.isObject()){
                   QVariantMap result = jsonDocument.toVariant().toMap();
                   qDebug() << "message:" << result["message"].toString();
       //            qDebug() << "plugins:";

       //            foreach(QVariant plugin,result["plug-ins"].toList()){
       //                qDebug() << "\t-" << plugin.toString();
       //            }

                   QVariantMap data = result["data"].toMap();
                   qDebug() << "returnType:" << data["returnType"];

                   if("carPosition"==data["returnType"]){

                   }
                   if("roadLights" == data["roadLights"]){

                   }

                   QVariantMap returnData = data["returnData"].toMap();
                   qDebug() << "device:" << returnData["device"].toString();
                   qDebug() << "position:" << returnData["position"];

       //            qDebug() << "length:" << nestedMap["length"].toInt();
       //            qDebug() << "use_space:" << nestedMap["use_space"].toBool();
               }
           }else{
               qFatal(error.errorString().toUtf8().constData());
               exit(1);
           }


}

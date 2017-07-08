#include "map.h"
#include "ui_map.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QPainter>
#include <QColor>
#include "singlemap.h"
#include "communicawidget.h"
#include <QDebug>
#include <QColor>

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{

    ui->setupUi(this);
    map = singleMap::getInstance();
    singleConnect = CommunicaWidget :: getInstance();
    connect(singleConnect,SIGNAL(signalReadMesg(QString)),
            this,SLOT(parseMsg(QString)));
    connect(this,SIGNAL(MapUpdate(QString,QString)),
              this,SLOT(updateMap(QString,QString)));

}


Map::~Map(){
    delete ui;

}

void Map::updateMap(QString s1,QString s2){

    light1 = s1;
    light2 = s2;

}

void Map::paintEvent(QPaintEvent *)
{
    QPainter        painter(this);
    QPen            pen;

    timer.start(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));

//  painter.scale(width()/1000.0, height()/1000.0);
    painter.setRenderHints(QPainter::Antialiasing);//抗锯齿
    painter.drawPixmap(0, 0, 700, 700, map->getBackground());//画地图

    pen.setCapStyle(Qt::RoundCap);

    //画出横向道路情况
    if("green" == light1){
         pen.setColor(Qt::green);
    }else if("red" == light1){
        pen.setColor(Qt::red);
    }else{
        pen.setColor(Qt::black);
    }
    pen.setWidth(20);
    painter.setPen(pen);

    //crossRoad2
    painter.drawPoint(380,349);
    //crossRoad4
    painter.drawPoint(315,349);

    pen.setWidth(8);
    painter.setPen(pen);

    painter.drawLine(150,340,260,340);//road5
    painter.drawLine(150,365,260,365);//road6

    painter.drawLine(440,340,550,340);//road7
    painter.drawLine(440,365,550,365);//road8

    //画出纵向道路情况
    if("green" == light2){
         pen.setColor(Qt::green);
    }else if("red" == light2){
        pen.setColor(Qt::red);
    }else{
        pen.setColor(Qt::black);
    }
    pen.setWidth(20);
    painter.setPen(pen);

    //crossRoad1
    painter.drawPoint(346,320);
    //crossRoad3
    painter.drawPoint(346,385);

    pen.setWidth(8);
    painter.setPen(pen);

    painter.drawLine(335,160,335,280);//road17
    painter.drawLine(360,160,360,280);//road18

    painter.drawLine(335,430,335,550);//road19
    painter.drawLine(360,430,360,550);//road20


    //画出常态畅通道路
    pen.setColor(Qt::green);
    pen.setWidth(8);
    painter.setPen(pen);

    QRectF rect1(50, 60, 625, 625); //x,y,w,h
    QRectF rect2(65, 90, 625, 625); //x,y,w,
    QRectF rect3(50, 50, 600, 700); //x,y,w,h
    QRectF rect4(75, 70, 600, 700); //x,y,w,h

    int startAngle1 = 110 * 16; //值为，实际角度 * 16
    int startAngle2 = 140 * 16; //值为，实际角度 * 16
    int spanAngle1 = 20 * 16;

    //三个参数：rect表示弧线所在的矩形，startAngle起始角度，spanAngle跨越角度

    painter.drawArc(rect1, startAngle1, spanAngle1);//road1
    painter.drawArc(rect2, startAngle1, spanAngle1);//road2

    painter.drawArc(rect3, startAngle2, spanAngle1);//road21
    painter.drawArc(rect4, startAngle2, spanAngle1);//road22

    painter.drawLine(440,70,550,70);//rode3
    painter.drawLine(440,95,550,95);//road4

    painter.drawLine(150,610,260,610);//road9
    painter.drawLine(150,635,260,635);//road10

    painter.drawLine(440,610,550,610);//road11
    painter.drawLine(440,635,550,635);//road12

    painter.drawLine(605,160,605,280);//road13
    painter.drawLine(630,160,630,280);//road14

    painter.drawLine(605,430,605,550);//road15
    painter.drawLine(630,430,630,550);//road16

    painter.drawLine(65,430,65,550);//road23
    painter.drawLine(90,430,90,550);//road24


}



void Map::parseMsg(QString msg)
{
    /*
        * msg = "{"
        */
  //  qDebug() << "sendSlot";
//           QString json("{"
//                        "\"message\":\"小车位置\","
//                        "\"data\":{"
//                        "\"returnType\":\"carPosition\","
//                        "\"returnData\":{"
//                        "\"device\":\"car1\","
//                        "\"position\":\"36\""
//                        "}"
//                        "}"
//                        "}"
//                       );
    QString json = msg;

           QJsonParseError error;
           QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toUtf8(),&error);
           if(error.error == QJsonParseError::NoError){
               if(jsonDocument.isObject()){
                   QVariantMap result = jsonDocument.toVariant().toMap();
         //          qDebug() << "message:" << result["message"].toString();
       //            qDebug() << "plugins:";

       //            foreach(QVariant plugin,result["plug-ins"].toList()){
       //                qDebug() << "\t-" << plugin.toString();
       //            }

                   QVariantMap data = result["data"].toMap();
                   //qDebug() << "returnType:" << data["returnType"];

                   if("carPosition"==data["returnType"]){
                       QVariantMap returnData = data["returnData"].toMap();

                   //    qDebug() << returnData["position"].toString();

                  //     emit carMapUpdate(returnData["position"].toString());

                   }
                  qDebug()<< data["returnType"].toString();
                   if("roadLights" == data["returnType"]){
                       QVariantMap returnData = data["returnData"].toMap();
                  //      qDebug()<<returnData;

                    //   qDebug() << returnData["status1"].toString();
//                       qDebug() << returnData["status2"].toString();

                       emit MapUpdate(returnData["status1"].toString(),returnData["status2"].toString());

                   }

//                   QVariantMap returnData = data["returnData"].toMap();
               //    qDebug() << "device:" << returnData["device"].toString();
//                   qDebug() << "position:" << returnData["position"];

       //            qDebug() << "length]]:" << nestedMap["length"].toInt();
       //            qDebug() << "use_space:" << nestedMap["use_space"].toBool();
               }
           }else{
               qFatal(error.errorString().toUtf8().constData());
               exit(1);
           }


}

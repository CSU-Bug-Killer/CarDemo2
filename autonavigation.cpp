#include "autonavigation.h"
#include "ui_autonavigation.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QPainter>
#include "singlemap.h"
#include <QVariantMap>
#include "communicawidget.h"
#include <QDebug>
#include "carmap.h"
#include <QtMath>
AutoNavigation::AutoNavigation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoNavigation)
{
    ui->setupUi(this);
    map = singleMap::getInstance();
    singleConnect = CommunicaWidget :: getInstance();
    point2 = QPoint(200, 200);
    connect(singleConnect,SIGNAL(signalReadMesg(QString)),
            this,SLOT(parseMsg(QString)));
    connect(this,SIGNAL(MapUpdate(QString)),
            this,SLOT(updateMap(QString)));
}

AutoNavigation::~AutoNavigation()
{
    delete ui;
}

void AutoNavigation::updateMap(QString position){

    point2 = map->getMapHashSet()->value(position.toLongLong());

}

void AutoNavigation::paintEvent(QPaintEvent *)
{
    QPainter        painter(this);
    QRect           rect;
    QPixmap         carPixmap;

    timer.start(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));

    qint32 side=qMin(width(),height());
    painter.scale(side/700.0,side/700.0);

    painter.setRenderHints(QPainter::Antialiasing);

    painter.drawPixmap(0, 0, 700,700, map->getBackground());

    QPoint m(point2.x(),point2.y());
    rect.moveCenter(m);

    carPixmap.load(":/image/car.png");
    rect.setWidth(31);
    rect.setHeight(15);

    painter.drawPixmap(rect, carPixmap);

}


void AutoNavigation::parseMsg(QString msg)
{
    /*
        * msg = "{"
        */
       qDebug() << "sendSlot";
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
     //       qDebug() << "message:" << result["message"].toString();
            //            qDebug() << "plugins:";

            //            foreach(QVariant plugin,result["plug-ins"].toList()){
            //                qDebug() << "\t-" << plugin.toString();
            //            }

            QVariantMap data = result["data"].toMap();
            qDebug() << "returnType:" << data["returnType"];

            if("carPosition"==data["returnType"]){
                QVariantMap returnData = data["returnData"].toMap();

                 qDebug() << returnData["position"].toString() << "auto";

                emit MapUpdate(returnData["position"].toString());

            }
//            if("roadLights" == data["roadLights"]){

//            }

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


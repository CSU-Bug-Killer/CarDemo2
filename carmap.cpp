#include "carmap.h"
#include "ui_carmap.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QPainter>
#include "singlemap.h"
#include <QVariantMap>
#include "communicawidget.h"
#include <QDebug>

CarMap::CarMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarMap)
{

    ui->setupUi(this);
    map = singleMap::getInstance();
    singleConnect = CommunicaWidget :: getInstance();
    point = QPoint(200, 200);
    connect(singleConnect,SIGNAL(signalReadMesg(QString)),
            this,SLOT(parseMsg(QString)));
    connect(this,SIGNAL(carMapUpdate(QString)),
            this,SLOT(updateCarmap(QString)));
}

void CarMap::updateCarmap(QString position){

    point = map->getMapHashSet()->value(position.toLongLong());
 // qDebug() << point;
  // qDebug() << position;
//  qDebug() <<map->getMapHashSet()->value(position.toLongLong());
//     this->update();
}

CarMap::~CarMap()
{
    delete ui;
}

void CarMap::paintEvent(QPaintEvent *)
{
    QPainter        painter(this);
    // QPoint          point(0, 0);
  //  QPoint          point(200, 200);
    QPoint          p0(0, 0);
    QPen            pen;
    QRect           rect;
    QPixmap         carPixmap;

    timer.start(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    painter.scale(width()/1000.0, height()/1000.0);

    painter.setRenderHints(QPainter::Antialiasing);

    painter.drawPixmap(0, 0,width(),height(), map->getBackground());
    qDebug()<<"width";
    qDebug()<<width();
    qDebug()<<"height";
    qDebug()<<height();

    carPixmap.load(":/image/car.png");
    rect.setWidth(31);
    rect.setHeight(15);
    rect.moveCenter(point);
    painter.drawPixmap(rect, carPixmap);

}

void CarMap::parseMsg(QString msg)
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

                 qDebug() << returnData["position"].toString() << "lllllllllll";

                emit carMapUpdate(returnData["position"].toString());

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

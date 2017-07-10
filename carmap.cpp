#include "carmap.h"
#include "ui_carmap.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QPainter>
#include "singlemap.h"
#include <QVariantMap>
#include "communicawidget.h"
#include <QDebug>
#include <QtMath>
#include <QPen>
#include <QColor>

CarMap::CarMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarMap)
{

    ui->setupUi(this);
    map = singleMap::getInstance();
    singleConnect = CommunicaWidget :: getInstance();
    point = QPoint(200.0, 200.0);
    connect(singleConnect,SIGNAL(signalReadMesg(QString)),
            this,SLOT(parseMsg(QString)));
    connect(this,SIGNAL(carMapUpdate(QString)),
            this,SLOT(updateCarmap(QString)));
//    qDebug()<<"height~~~~~~~~~~~~~~~~~~~~~";
//    qDebug()<<this->height();
}

void CarMap::updateCarmap(QString position){

    point = map->getMapHashSet()->value(position.toLongLong());
 // qDebug() << point;
  // qDebug() << position;

}

CarMap::~CarMap()
{
    delete ui;
}

void CarMap::paintEvent(QPaintEvent *)
{
    QPainter        painter(this);
    QPoint          p0(0, 0);
    QRect           rect;
    QPixmap         carPixmap;
    QPen            pen;


    timer.start(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));

    qint32 side=qMin(width(),height());

    painter.scale(side/700.0,side/700.0); // $$缩放

    painter.setRenderHints(QPainter::Antialiasing |QPainter::SmoothPixmapTransform);

    carPixmap.load(":/image/car.png");
    rect.setWidth(31);
    rect.setHeight(15);

    QPoint m(point.x(),point.y());
    rect.moveCenter(m);

    painter.drawPixmap(0, 0,700.0,700.0, map->getBackground());
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

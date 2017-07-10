#include "flowcount.h"
#include"ui_flowcount.h"
#include "database.h"
//#include "initsql.h"

#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QVariantMap>


QT_CHARTS_USE_NAMESPACE

FlowCount::FlowCount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlowCount)
{
    ui->setupUi(this);
    int day = QDate::currentDate().day();
//    qDebug()<<d.toString();
    dateMsg = tr("2017/07/%1;2017/07/0%2;2017/07/0%3;2017/07/0%4;2017/07/0%5").arg(day).arg(day-1).arg(day-2).arg(day-3).arg(day-4);
    qDebug()<<dateMsg;
    flowMsg = "5,5,5,5,5,5";

    conServer = CommunicaWidget::getInstance();
    connect(conServer,SIGNAL(signalReadMesg(QString)),
            this,SLOT(onReadMessageSave(QString)));

    d->createConn();
    d->queryAll();
    drawCharts();
//    this->resize(400,300);
}

//读取到信息则保存
void FlowCount::onReadMessageSave(QString msg){

    qDebug()<<"接受卡号:";
    QString json = msg;
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toUtf8(),&error);
    if(error.error == QJsonParseError::NoError){
        if(jsonDocument.isObject()){
            QVariantMap result = jsonDocument.toVariant().toMap();

            QVariantMap data = result["data"].toMap();
            qDebug() << "returnType:" << data["returnType"];

            if("carPosition"==data["returnType"]){
                QVariantMap returnData = data["returnData"].toMap();
                msg=returnData["position"].toString();
            }
        }
    }
    if(msg.toInt()%3==1){
        d->createConn();  //创建连接
        //将读到的卡写入到数据库中
        d->insertToCards(msg);
        drawCharts();
    }
    qDebug()<<msg;
}

void FlowCount::drawCharts(){

//    QHBoxLayout* l = new QHBoxLayout();
//    this->setLayout(l);
//    ui->setupUi();
    QStringList dateSeries=dateMsg.split(";");
    //有24条路，每条路显示近两天的车流量
    int firstDay[12];
    int secondDay[12];
    for (int i=0;i<12;i++)
    {
        int tmp=i*3+1;
        firstDay[i]=d->queryCountsAccordingCardNumAndTime(tr("%1").arg(tmp),dateSeries.at(0));
        secondDay[i]=d->queryCountsAccordingCardNumAndTime(tr("%1").arg(tmp),dateSeries.at(1));
    }


    //![1]
    //!
        QBarSet *set0 = new QBarSet(dateSeries.at(0));
        QBarSet *set1 = new QBarSet(dateSeries.at(1));

        //某一天各个道路的流量，今天，1，2，3，道路的流量分别为flow0,flow1,,,
        *set0 << firstDay[0] << firstDay[1] << firstDay[2] << firstDay[3] << firstDay[4] << firstDay[5] << firstDay[6] << firstDay[7] << firstDay[8] << firstDay[9] << firstDay[10] << firstDay[11] ;
        *set1 << secondDay[0] << secondDay[1] << secondDay[2] << secondDay[3] << secondDay[4] << secondDay[5] << secondDay[6] << secondDay[7] << secondDay[8] << secondDay[9] << secondDay[10] << secondDay[11] ;
    //![1]

    //![2]
        QBarSeries *series = new QBarSeries();
        series->append(set0);
        series->append(set1);

    //![2]

    //![3]
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Simple barchart example");
        chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
        QStringList categories;
        categories << "1" << "3" << "14" << "16" << "12" << "10" << "23" << "21" << "2" << "4" << "13"<< "15";
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);
    //![4]

    //![5]
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    //![6]



    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(chartView);
//    l->destroyed();
    this->setLayout(layout);
//    return layout;
}

FlowCount::~FlowCount(){
    delete ui;
}

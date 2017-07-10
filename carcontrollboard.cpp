/* ************************************************************
 * File:            carcontrollboard.cpp
 * Description:     小车控制面板源文件
 * Author：          刘莹莹
 * Date：            2017/07/05
 * Version：         v1.0
 * Copyright	(c) 2017-2018	Bug KillerAll Rights reserved.
 * ************************************************************/

#include "carcontrollboard.h"
#include "ui_carcontrollboard.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QString>

#include <QDebug>

CarControllBoard::CarControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarControllBoard)
{
    ui->setupUi(this);

    showCarPosition("21");

    //蜂鸣器开关按钮点击绑定事件
    connect(ui->beeSwitchBtn,SIGNAL(clicked(bool)),
            this,SLOT(switchChangeState()));

    //直行
    connect(ui->straightBtn,SIGNAL(clicked(bool)),
            this,SLOT(onStraightBtnClicked()));
    //左转
    connect(ui->leftBtn,SIGNAL(clicked(bool)),
            this,SLOT(onLeftBtnClicked()));
    //右转
    connect(ui->rightBtn,SIGNAL(clicked(bool)),
            this,SLOT(onRightBtnClicked()));
    //停止
    connect(ui->stopBtn,SIGNAL(clicked(bool)),
            this,SLOT(onStopBtnClicked()));
    //退格
    connect(ui->backBtn,SIGNAL(clicked(bool)),
            this,SLOT(onBackBtnClicked()));
    //清除重置
    connect(ui->resetBtn,SIGNAL(clicked(bool)),
            this,SLOT(onResetBtnClicked()));


    singleConnect = CommunicaWidget::getInstance();

    //车辆行为控制绑定
    connect(ui->actionControlBtn,SIGNAL(clicked(bool)),
            this,SLOT(onActionControlBtnClicked()));
    //车灯控制绑定
    connect(ui->carLightSetBtn,SIGNAL(clicked(bool)),
            this,SLOT(onCarLightSetBtnClicked()));
    connect(singleConnect,SIGNAL(signalReadMesg(QString)),
            this,SLOT(getSignal(QString)));

}

/********************************
* Function：         CARLED_Init
* Description：      初始化指定车灯
* Args				:NULL
* Return			:NULL
*********************************/
CarControllBoard::~CarControllBoard()
{
    delete ui;
}

void CarControllBoard::onActionControlBtnClicked()
{
    QString carAction = ui->lineEdit->text();
    singleConnect->controlDirection(this->carNum,carAction);

}

void CarControllBoard::onCarLightSetBtnClicked()
{
    QString headLeft = ui->leftCbx->isChecked()?"1":"0";
    QString headRight = ui->rightCbx->isChecked()?"1":"0";
    QString roofLeftRed = ui->roofRedCbx->isChecked()?"1":"0";
    QString roofRightBlue = ui->roofBlueCbx->isChecked()?"1":"0";
    singleConnect->controlLight(carNum,roofRightBlue,roofLeftRed,headRight,headLeft);

}

void CarControllBoard::getSignal(QString msg)
{
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
//    QPoint m(carmap->point.x(),carmap->point.y());
//    qDebug()<<m;
//    xAxis=m.x();
//    yAxis=m.y();

    showCarPosition(msg);
}

void CarControllBoard::switchChangeState()
{
    if(isOpen==true){
        ui->beeSwitchBtn->setText("关");
        ui->beeSwitchBtn->setStyleSheet("background-color:rgb(255,0,0);color:white;border-radius:5px;");
        singleConnect->controlSpeakers(this->carNum,"0");
    }
    else{
        ui->beeSwitchBtn->setText("开");
        ui->beeSwitchBtn->setStyleSheet("background-color:rgb(0,255,0);color:white;border-radius:5px;");
        singleConnect->controlSpeakers(this->carNum,"1");
    }
    isOpen=!isOpen;
}


void CarControllBoard::onStraightBtnClicked()
{
    QString ins="H";
    if(ui->lineEdit->text()==""){
        ui->lineEdit->setText(tr("D")+ins);
    }else{
        ui->lineEdit->setText(ui->lineEdit->text()+ins);
    }
}
void CarControllBoard::onLeftBtnClicked()
{
    QString ins="L";
    ui->lineEdit->setText(ui->lineEdit->text()+ins);
}
void CarControllBoard::onRightBtnClicked()
{
    QString ins="R";
    ui->lineEdit->setText(ui->lineEdit->text()+ins);
}
void CarControllBoard::onStopBtnClicked()
{
    QString ins="S";
    ui->lineEdit->setText(ui->lineEdit->text()+ins);
}
void CarControllBoard::onBackBtnClicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().left(ui->lineEdit->text().length()-1));
}
void CarControllBoard::onResetBtnClicked()
{
    QString ins="";
    ui->lineEdit->setText(ins);
}

//显示小车位置
void CarControllBoard::showCarPosition(QString msg){

    QString roadNum="1";
    QStringList roadList;
    roadList.append("1");
    roadList.append("3");
    roadList.append("14");
    roadList.append("16");
    roadList.append("12");
    roadList.append("10");
    roadList.append("23");
    roadList.append("21");
    roadList.append("2");
    roadList.append("4");
    roadList.append("13");
    roadList.append("15");
    roadList.append("11");
    roadList.append("9");
    roadList.append("24");
    roadList.append("22");
    roadList.append("17");
    roadList.append("19");
    roadList.append("18");
    roadList.append("20");
    roadList.append("5");
    roadList.append("7");
    roadList.append("6");
    roadList.append("8");



    //找到小车对应的卡号和路号
    QString cardNum=msg;
    if(cardNum.toInt()%3==0){
        roadNum=roadList.at(cardNum.toInt()/3);
    }
    if(roadNum=="1"||roadNum=="3"||roadNum=="14"||roadNum=="16"||roadNum=="70"||roadNum=="12"||roadNum=="10"||roadNum=="21"||roadNum=="23"){
        Direction="逆时针";
    }

//    ui->xAxisLbl->setText(ui->xAxisLbl->text().left(5)+tr("%1").arg(xAxis));
//    ui->yAxisLbl->setText(ui->yAxisLbl->text().left(5)+tr("%1").arg(yAxis));
    ui->roadNumberLbl->setText(ui->roadNumberLbl->text().left(3)+roadNum+tr("号路"));
    ui->directionLbl->setText(ui->directionLbl->text().left(3)+tr("%1").arg(Direction));
}


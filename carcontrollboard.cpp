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


#include <QDebug>

CarControllBoard::CarControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarControllBoard)
{
    ui->setupUi(this);

    showCarPosition();

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
void CarControllBoard::showCarPosition(){
    QString xAxis="130";
    QString yAxis="40";
    QString roadNum="1";
    ui->xAxisLbl->setText(ui->xAxisLbl->text().left(5)+xAxis);
    ui->yAxisLbl->setText(ui->yAxisLbl->text().left(5)+yAxis);
    ui->roadNumberLbl->setText(ui->roadNumberLbl->text().left(3)+roadNum+tr("号路"));
    if(roadNum.toInt()%2==0){
        ui->directionLbl->setText(ui->directionLbl->text().left(3)+tr("逆时针"));
    }else{
        ui->directionLbl->setText(ui->directionLbl->text().left(3)+tr("顺时针"));
    }
}


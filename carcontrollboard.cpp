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

    //蜂鸣器开关按钮点击绑定事件
    connect(ui->beeSwitchBtn,SIGNAL(clicked(bool)),
            this,SLOT(switchChangeState()));

    //直行
    connect(ui->straightBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_straightBtn_clicked()));
    //左转
    connect(ui->leftBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_leftBtn_clicked()));
    //右转
    connect(ui->rightBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_rightBtn_clicked()));
    //停止
    connect(ui->stopBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_stopBtn_clicked()));
    //退格
    connect(ui->backBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_backBtn_clicked()));
    //清除重置
    connect(ui->resetBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_resetBtn_clicked()));

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

void CarControllBoard::switchChangeState()
{
    if(isOpen==true){
        ui->beeSwitchBtn->setText("关");
        ui->beeSwitchBtn->setStyleSheet("background-color:rgb(255,0,0);color:white;border-radius:5px;");
    }
    else{
        ui->beeSwitchBtn->setText("开");
        ui->beeSwitchBtn->setStyleSheet("background-color:rgb(0,255,0);color:white;border-radius:5px;");
    }
    isOpen=!isOpen;
}


void CarControllBoard::on_straightBtn_clicked()
{
    QString ins="Z";
    if(ui->lineEdit->text()==""){
        ui->lineEdit->setText(tr("G")+ins);
    }else{
        ui->lineEdit->setText(ui->lineEdit->text()+ins);
    }
}
void CarControllBoard::on_leftBtn_clicked()
{
    QString ins="L";
    ui->lineEdit->setText(ui->lineEdit->text()+ins);
}
void CarControllBoard::on_rightBtn_clicked()
{
    QString ins="R";
    ui->lineEdit->setText(ui->lineEdit->text()+ins);
}
void CarControllBoard::on_stopBtn_clicked()
{
    QString ins="S";
    ui->lineEdit->setText(ui->lineEdit->text()+ins);
}
void CarControllBoard::on_backBtn_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().left(ui->lineEdit->text().length()-1));
}
void CarControllBoard::on_resetBtn_clicked()
{
    QString ins="";
    ui->lineEdit->setText(ins);
}

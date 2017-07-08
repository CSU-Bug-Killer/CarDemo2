#include "flowcount.h"
#include"ui_flowcount.h"

#include <QDebug>

FlowCount::FlowCount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlowCount)
{
    ui->setupUi(this);

    conServer = CommunicaWidget::getInstance();
    connect(conServer,SIGNAL(signalReadMesg(QString)),
            this,SLOT(onReadMessageSave(QString)));

}

//读取到信息则保存
void FlowCount::onReadMessageSave(QString msg){
    qDebug()<<"接受卡号";
    qDebug()<<msg;
}

FlowCount::~FlowCount(){
delete ui;
}

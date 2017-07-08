#include "flowcount.h"
#include"ui_flowcount.h"

FlowCount::FlowCount(QWidget *parent) :
    QWidget(parent),
    ui(Ui::FlowCount)
{
    ui->setupUi(this);

    conServer = CommunicaWidget::getInstance();
    connect(conServer,SIGNAL(signalReadMesg(QString)),
            this,SLOT(onReadMessageSave(QString)));

}

//读取到信息则保存
void FlowCount::onReadMessageSave(QString msg){

}

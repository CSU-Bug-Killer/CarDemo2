#include "setting.h"
#include "ui_setting.h"
#include <QDebug>
#include <QDialogButtonBox>

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    QRegExp rxPort("^[1-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-6][0-5][0-5][0-3][0-5]$)");
    QRegExp rxHost("^(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9])(.)(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9]|0)(.)(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9]|0)(.)(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[0-9])$");

    ui->hostAddrLdt->setValidator(new QRegExpValidator(rxHost));
    ui->hostPortLdt->setValidator(new QRegExpValidator(rxPort));

    connect(ui->buttonBox,SIGNAL(accepted()),
            this,SLOT(onButtonBoxAccepted()));

    connect(ui->buttonBox,SIGNAL(rejected()),
            this,SLOT(onButtonBoxRejected()));
    singleConnect = CommunicaWidget::getInstance();
}

Setting::~Setting(){
    delete ui;
}
QString Setting::getHostAddr()
{
    if(ui->hostAddrLdt->text()!=""){
        return ui->hostAddrLdt->text();
    }else{
        qDebug()<<"主机地址不能为空";
        return "127.0.0.1";
    }
}

QString Setting::getHostPort()
{
    if(ui->hostPortLdt->text()!=""){
         return ui->hostPortLdt->text();
    }else{
        qDebug()<<"主机端口不能为空";
        return tr("%1").arg(9527);
    }

}

void Setting::onButtonBoxAccepted()
{
    qDebug() << "click ok";
    if(ui->hostAddrLdt->text()==""){
        qDebug()<<"主机地址不能为空";
    }else if(ui->hostPortLdt->text()==""){
        qDebug()<<"主机端口不能为空";
    }else{
        QString host = ui->hostAddrLdt->text();
        QString port = ui->hostPortLdt->text();
        singleConnect->connectServer(host,port);
        qDebug()<<"setHostInfoSetting";
        this->close();
   }

}
void Setting::onButtonBoxRejected()
{
    this->close();
}





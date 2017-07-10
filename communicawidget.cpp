#include "communicawidget.h"

#include <QDebug>
#include <QJsonParseError>
#include <QTcpSocket>
#include <QByteArray>
#include <QVariant>


CommunicaWidget::CommunicaWidget(QWidget *parent) :
    QWidget(parent)
{

}

void CommunicaWidget::connectServer(QString host,QString port)
{
    qDebug() << "dd";
    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->abort();
    m_tcpSocket->connectToHost(host,port.toInt());
    connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(readMesg()));

    connect(m_tcpSocket,SIGNAL(disconnected()),
            this,SLOT(getDisConnectSignal()));
    connect(m_tcpSocket,SIGNAL(connected()),
            this,SLOT(getConnectedSignal()));
}

void CommunicaWidget::getDisConnectSignal(){
    emit disConToServer();
    qDebug()<<"signals:discontoserver()";
}
void CommunicaWidget::getConnectedSignal(){
    emit conToServer();
    qDebug()<<"signals:contoserver()";
}

void CommunicaWidget::disconnectServer()
{
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
//
}

void CommunicaWidget::readMesg() //读取信息
{
    QByteArray qba = m_tcpSocket->readAll();
    qDebug()<<qba;
    QString ss=QVariant(qba).toString();
    qDebug()<<"lyy:receive message:"<<ss;
    emit signalReadMesg(ss);
}

void CommunicaWidget::sendMesg(QString msg) //发送信息
{
    qDebug() << "sendMesg()";
    QString ss= msg;
    qDebug() << ss.toStdString().c_str();
    m_tcpSocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
}

void CommunicaWidget::controlDirection(QString car,QString control){
    qDebug() << "di";
    QString json("{"
                 "\"message\":\"行进方向指令串\","
                 "\"data\":{"
                 "\"sendType\":\"direction\","
                 "\"sendData\":{"
                 "\"device\":\""+car+"\","
                 "\"directionData\":\""+control+"\""
                 "}"
                 "}"
                 "}"
                );
    this->sendMesg(json);
}

void CommunicaWidget::controlLight(QString car,QString headLeft,QString headRight,QString roofLigntRed,QString roofLightBlue)
{
    QString json("{"
                 "\"message\":\"车灯控制\","
                 "\"data\":{"
                 "\"sendType\":\"carLights\","
                 "\"sendData\":{"
                 "\"device\":\""+car+"\","
                 "\"headLeft\":"+headLeft+","
                 "\"headRight\":"+headRight+","
                 "\"roofLigntRed\":"+roofLigntRed+","
                 "\"roofLightBlue\":"+roofLightBlue+""
                 "}"
                 "}"
                 "}"
                );
    this->sendMesg(json);
}

void CommunicaWidget::controlSpeakers(QString car,QString control)
{
    QString json("{"
                 "\"message\":\"蜂鸣器控制\","
                 "\"data\":{"
                 "\"sendType\":\"speakers\","
                 "\"sendData\":{"
                 "\"device\":\""+car+"\","
                 "\"control\":"+control+""
                 "}"
                 "}"
                 "}"
                );
    this->sendMesg(json);
}

void CommunicaWidget::controlRoadLight(QString roadLight1,QString control1,QString roadLight2,QString control2)
{
    QString json("{"
                 "\"message\":\"路灯控制\","
                 "\"data\":{"
                 "\"sendType\":\"roadLight\","
                 "\"sendData\":{"
                 "\"device1\":\""+roadLight1+"\","
                 "\"control\":\""+control1+"\","
                 "\"device2\":\""+roadLight2+"\","
                 "\"control2\":\""+control2+"\""
                 "}"
                 "}"
                 "}"
                );
    this->sendMesg(json);
}
void CommunicaWidget::controlAutoNav(QString car, QString target)
{
    QString json("{"
                 "\"message\":\"自动导航\","
                 "\"data\":{"
                 "\"sendType\":\"autoNav\","
                 "\"sendData\":{"
                 "\"device\":\""+car+"\","
                 "\"target\":\""+target+"\""
                 "}"
                 "}"
                 "}"
                 );
    this->sendMesg(json);
}



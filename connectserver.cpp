#include <QHostAddress>

#include "connectserver.h"

ConnectServer::ConnectServer()
{
    this->host = QHostAddress::LocalHost;
    this->port = 9527;
}

ConnectServer::~ConnectServer()
{

}

void ConnectServer::setHost(QHostAddress host)
{
    this->host = host;
}

void ConnectServer::setPort(qint16 port)
{
    this->port = port;
}

QHostAddress ConnectServer::getHost()
{
    return this->host;
}

qint16 ConnectServer::getPort()
{
    return this->port;
}

void ConnectServer::startRead()
{
    this->connectToHost(host,port);
    qDebug()<<"服务器连接";
}

void ConnectServer::stopRead()
{
    this->disconnectFromHost();
    qDebug()<<"服务器断开";
    this->close();
}


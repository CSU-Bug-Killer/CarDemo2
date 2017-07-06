#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

class ConnectServer : public QTcpSocket
{
    Q_OBJECT
public:
    ConnectServer();
    ~ConnectServer();

    void    setHost(QHostAddress host);
    void    setPort(qint16 port);
    QHostAddress    getHost(void);
    qint16  getPort(void);


signals:


private slots:
//    void connectServer();
//    void sendMesg();
//    void readMesg();

public slots:
    void startRead(void);
    void            stopRead(void);
    /*
    void            readData(void);
    void            sendData(QByteArray& frame);*/

private:
    QHostAddress    host;
    qint16          port;
};

#endif // CONNECTSERVER_H

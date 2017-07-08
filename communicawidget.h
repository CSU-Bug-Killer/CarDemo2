#ifndef COMMUNICAWIDGET_H
#define COMMUNICAWIDGET_H

#include <QWidget>
#include <QTcpSocket>
namespace Ui {
    class CommunicaWidget;
}

class CommunicaWidget : public QWidget
{
    Q_OBJECT
public:
    static CommunicaWidget*   getInstance()
    {
        static  CommunicaWidget*  instance = NULL;
        if(NULL == instance)
        {
            instance = new CommunicaWidget;
        }
        return instance;
    }

    void sendMesg(QString msg);
    void connectServer(QString host,QString port);
    void disconnectServer();
    void controlDirection(QString car,QString control);
    void controlLight(QString car,QString headLeft,QString headRight,QString roofLigntRed,QString roofLightBlue);
    void controlSpeakers(QString car,QString control);
    void controlRoadLight(QString roadLight1,QString control1,QString roadLight2,QString control2);
    void controlAutoNav(QString car,QString target);
//    QTcpSocket getTcpSocket();
//    QTcpSocket *m_tcpSocket;
private:
    CommunicaWidget(QWidget *parent = 0);
    Ui::CommunicaWidget *ui;
    QTcpSocket *m_tcpSocket;

signals:
//    void sendMesg(QString);
    void signalReadMesg(QString);
    void disConToServer();
    void conToServer();

public slots:
//    void connectServer();
//    void sendMesg();
    void readMesg();
    void getDisConnectSignal();
    void getConnectedSignal();




};

#endif // COMMUNICAWIDGET_H

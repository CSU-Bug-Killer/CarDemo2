#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QHostAddress>

//#include "connectserver.h"
#include "communicawidget.h"


namespace Ui {
class Setting;
}
class Setting : public QDialog
{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();

    QString getHostAddr(void);
    QString getHostPort(void);


signals:
//    void connOk();

private slots:
    void onButtonBoxAccepted();
    void onButtonBoxRejected();

private:
    Ui::Setting* ui;
//    ConnectServer* settingHost;
    CommunicaWidget *singleConnect;
};

#endif // CONNECT_H

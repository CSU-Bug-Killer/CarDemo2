#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QHostAddress>

#include "connectserver.h"

namespace Ui {
class Setting;
}
class Setting : public QDialog
{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();

    QHostAddress    getHostAddr(void);
    qint16          getHostPort(void);


private slots:
    void onButtonBoxAccepted();
    void onButtonBoxRejected();

private:
    Ui::Setting* ui;
    ConnectServer* settingHost;
};

#endif // CONNECT_H

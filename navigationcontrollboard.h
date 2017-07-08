#ifndef NAVIGATIONCONTROLLBOARD_H
#define NAVIGATIONCONTROLLBOARD_H

#include <QWidget>
#include "communicawidget.h"

namespace Ui {
class NavigationControllBoard;
}
class NavigationControllBoard : public QWidget
{
    Q_OBJECT
public:
    explicit NavigationControllBoard(QWidget *parent = 0);
    ~NavigationControllBoard();
signals:

public slots:

private slots:
    void AutoModelSwitchBtnClicked();
    void NavigateStartBtnClicked();

private:
    Ui::NavigationControllBoard* ui;
    CommunicaWidget* singleConnect;
    QString carNum="car1";
    bool isAutoModelOn = false;
};

#endif // NAVIGATIONCONTROLLBOARD_H

#ifndef CARCONTROLLBOARD_H
#define CARCONTROLLBOARD_H

#include <QWidget>
#include "communicawidget.h"
#include "carmap.h"

namespace Ui {
class CarControllBoard;
}
class CarControllBoard : public QWidget
{
    Q_OBJECT
public:
    explicit CarControllBoard(QWidget *parent = 0);
    ~CarControllBoard();
signals:

public slots:

private slots:

    void switchChangeState();

    void onStraightBtnClicked();
    void onLeftBtnClicked();
    void onRightBtnClicked();
    void onStopBtnClicked();
    void onBackBtnClicked();
    void onResetBtnClicked();

    void onActionControlBtnClicked();
    void onCarLightSetBtnClicked();

    void showCarPosition(QString msg);
    void getSignal(QString msg);


private:
    Ui::CarControllBoard* ui;
    CommunicaWidget* singleConnect;
    QString carNum="car1";
    bool isOpen=false;

    CarMap* carmap;
    int xAxis=0;
    int yAxis=0;
    QString Direction="顺时针";
};

#endif // CARCONTROLLBOARD_H

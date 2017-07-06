#ifndef LIGHTCONTROLLBOARD_H
#define LIGHTCONTROLLBOARD_H

#include <QWidget>
#include "communicawidget.h"


namespace Ui {
class LightControllBoard;
}
class LightControllBoard : public QWidget
{
    Q_OBJECT
public:
    explicit LightControllBoard(QWidget *parent = 0);
    ~LightControllBoard();
signals:

public slots:
    void setRoadLights();


private:
    Ui::LightControllBoard* ui;
    CommunicaWidget *singleConnect;

};

#endif // LIGHTCONTROLLBOARD_H

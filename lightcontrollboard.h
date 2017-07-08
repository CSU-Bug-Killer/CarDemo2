#ifndef LIGHTCONTROLLBOARD_H
#define LIGHTCONTROLLBOARD_H

#include <QWidget>
#include <QComboBox>
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
    void currentIndexChanged(int index);

public slots:
    void setRoadLights();
    void setRoadModel();
    void setTrafficLights();
//    void setAtuoNavigation();

//    void redOneChecked();
//    void greenOneChecked();
    void onCurrentIndexChanged();

private:
    Ui::LightControllBoard* ui;
    CommunicaWidget *singleConnect;

};

#endif // LIGHTCONTROLLBOARD_H

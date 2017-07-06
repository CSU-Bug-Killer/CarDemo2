#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "welcomepage.h"
#include "map.h"
#include "carcontrollboard.h"
#include "lightcontrollboard.h"
#include "carmap.h"
#include "autonavigation.h"
#include "navigationcontrollboard.h"
#include "setting.h"
#include "about.h"

#include "connectserver.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


public slots:

//    void    setHostInfo(void);

private slots:
    void onMainBtnClicked();

    void onWelcomeBtnClicked();

    void onCarMapBtnClicked();

    void onAutoNavigationBtnClicked();

    void onAboutBtnClicked();

    void onSettingBtnClicked();

    void onConnectBtnClicked();

private:
    Ui::Widget *ui;

    /*中央显示面板*/
    //欢迎界面
    WelcomePage* welWidget;

    //路况管控地图界面
    Map* mapWidget;

    //车辆管控界面
    CarMap* carMapWidget;

    /*右侧设置面板*/
    //车辆控制对应车辆行为控制、以及车辆位置等信息面板
    CarControllBoard* carcontrollBoard;

    //路况监控对应红绿灯控制面板
    LightControllBoard* lightcontrollBoard;

    //自动导航主页面
    AutoNavigation* autoNavigationWidget;
    //自动导航右侧控制面板
    NavigationControllBoard* navigationBoard;

    Setting* settingDialog;

    ConnectServer* socket;
//    About* aboutDialog;

    void updateQss(void);

};

#endif // WIDGET_H

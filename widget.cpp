#include "widget.h"
#include "ui_widget.h"

#include <QListWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <QDialogButtonBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    resize(1198,674);

    //引用样式文件
    updateQss();

    //初始化隐藏控制面板
    ui->controlBoardSkd->hide();

    //添加中央监控显示页面Widget
    this->mapWidget = new Map;
    ui->mapBoardSkd->addWidget(mapWidget);
    this->welWidget = new WelcomePage;
    ui->mapBoardSkd->addWidget(welWidget);
    this->carMapWidget = new CarMap;
    ui->mapBoardSkd->addWidget(carMapWidget);
    this->autoNavigationWidget = new AutoNavigation;
    ui->mapBoardSkd->addWidget(autoNavigationWidget);

    //

    //添加右侧控制面板widget
    this->carcontrollBoard = new CarControllBoard;
    ui->controlBoardSkd->addWidget(carcontrollBoard);
    this->lightcontrollBoard = new LightControllBoard;
    ui->controlBoardSkd->addWidget(lightcontrollBoard);
    this->navigationBoard = new NavigationControllBoard;
    ui->controlBoardSkd->addWidget(navigationBoard);


    //初始化页面菜单导航栏样式
    ui->welcomeBtn->setStyleSheet("QPushButton#welcomeBtn{background-color:red; color:white}");
    ui->mapBoardSkd->setCurrentWidget(this->welWidget);

    //连接菜单导航点击切换界面槽函数
    connect(ui->welcomeBtn,SIGNAL(clicked(bool)),
            this,SLOT(onWelcomeBtnClicked()));
    connect(ui->mainBtn,SIGNAL(clicked(bool)),
            this,SLOT(onMainBtnClicked()));
    connect(ui->carMapBtn,SIGNAL(clicked(bool)),
            this,SLOT(onCarMapBtnClicked()));
    connect(ui->aboutBtn,SIGNAL(clicked(bool)),
            this,SLOT(onAboutBtnClicked()));
    connect(ui->settingBtn,SIGNAL(clicked(bool)),
            this,SLOT(onSettingBtnClicked()));
    connect(ui->autoNavigationBtn,SIGNAL(clicked(bool)),
            this,SLOT(onAutoNavigationBtnClicked()));

    settingDialog = new Setting;

    conServer = CommunicaWidget::getInstance();

    connect(ui->connectBtn,SIGNAL(clicked(bool)),
            this,SLOT(onConnectBtnClicked()));

    //接收到连接成功的信号，改变右上角连接状态
    connect(conServer,SIGNAL(conToServer()),
            this,SLOT(updateConnectStatus()));
    //接收到连接失败的信号，改变右上角连接状态
    connect(conServer,SIGNAL(disConToServer()),
            this,SLOT(updateDisconnect()));

    //与服务器连接或断开，改变提示按钮样式
//    connect(conServer->m_tcpSocket,SIGNAL(connected()),
//            this,SLOT(updateConnectStatus()));

//    connect(conServer->m_tcpSocket,SIGNAL(disconnected()),
//            this,SLOT(updateDisconnect()));

    //设置端口和主机地址

}
Widget::~Widget()
{
    delete ui;
}

//设置样式
void Widget::updateQss(){
    //引用样式文件
    QString qss;
    QFile qssFile(":/qss/widget.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qDebug()<<"设置样式";
        qssFile.close();
    }
}

//切换菜单导航主页面显示欢迎页面
void Widget::onWelcomeBtnClicked()
{
    ui->mapBoardSkd->setCurrentWidget(this->welWidget);
    ui->controlBoardSkd->hide();
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);
    ui->autoNavigationBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);
    ui->settingBtn->setStyleSheet(setColor);

    ui->welcomeBtn->setStyleSheet(setOnlyColor);

//    updateQss();

}

//切换菜单导航主页面显示路况监控
void Widget::onMainBtnClicked()
{
    ui->mapBoardSkd->setCurrentWidget(this->mapWidget);
//    ui->controlBoardSkd->show();
    ui->controlBoardSkd->setCurrentWidget(this->lightcontrollBoard);

    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);
    ui->autoNavigationBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);
    ui->settingBtn->setStyleSheet(setColor);

    ui->mainBtn->setStyleSheet(setOnlyColor);
}

//切换菜单导航主页面显示车辆监控
void Widget::onCarMapBtnClicked()
{

    ui->mapBoardSkd->setCurrentWidget(this->carMapWidget);
//    ui->controlBoardSkd->show();
    ui->controlBoardSkd->setCurrentWidget(this->carcontrollBoard);

    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->autoNavigationBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);
    ui->settingBtn->setStyleSheet(setColor);

    ui->carMapBtn->setStyleSheet(setOnlyColor);
//    updateQss();
}

//切换菜单导航主页面显示自动导航
void Widget::onAutoNavigationBtnClicked()
{
    ui->mapBoardSkd->setCurrentWidget(this->autoNavigationWidget);
//    ui->controlBoardSkd->show();
    ui->controlBoardSkd->setCurrentWidget(this->navigationBoard);

    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);
    ui->settingBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);

    ui->autoNavigationBtn->setStyleSheet(setOnlyColor);
//    updateQss();
}



void Widget::onAboutBtnClicked()
{
//    ui->controlBoardSkd->hide();
    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);
    ui->autoNavigationBtn->setStyleSheet(setColor);
    ui->settingBtn->setStyleSheet(setColor);

    ui->aboutBtn->setStyleSheet(setOnlyColor);

//    aboutDialog->exec();

    QMessageBox::about(this, "智能交通综合系统",
                       "智能交通综合系统3.0\n\n"
                       "杰普软件科技有限公司版权所有\n\n"
                       "Copyright 2016-2020 The Briup Ltd. All rights reserved.");


    updateQss();
}

void Widget::onSettingBtnClicked()
{

    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);
    ui->autoNavigationBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);

    ui->settingBtn->setStyleSheet(setOnlyColor);

    settingDialog->exec();
}

void Widget::onConnectBtnClicked()
{
    if(ui->connectBtn->text()=="已连接"){
        conServer->disconnectServer();
//        ui->connectBtn->setStyleSheet("background-color:black;color:white;");
//        ui->connectBtn->setText("已断开");
        qDebug()<<"lyy:disconnect";

    } else {
        conServer->connectServer(settingDialog->getHostAddr(),settingDialog->getHostPort());
//        ui->connectBtn->setText("已连接");
//        ui->connectBtn->setStyleSheet("background-color:green;color:white;");
        qDebug()<<"lyy:connect";
    }
}

void Widget::updateConnectStatus()
{
    qDebug()<<"设置之后连接";
    ui->connectBtn->setText("已连接");
    ui->connectBtn->setStyleSheet("background-color:green;color:white;");

    ui->controlBoardSkd->show();
}
void Widget::updateDisconnect()
{
    qDebug()<<"连接断开";
    ui->connectBtn->setStyleSheet("background-color:black;color:white;");
    ui->connectBtn->setText("已断开");
    ui->controlBoardSkd->hide();
}



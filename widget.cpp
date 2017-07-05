#include "widget.h"
#include "ui_widget.h"

#include <QListWidgetItem>
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    resize(1198,674);

    //引用样式文件
    QString qss;
    QFile qssFile(":/qss/widget.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    //初始化页面菜单导航栏样式
//    ui->groupBox->setStyleSheet("QPushButton{background-color:black;color:#95a0aa}");
    ui->welcomeBtn->setStyleSheet("QPushButton#welcomeBtn{background-color:red; color:white}");
    ui->mapBoardSkd->setCurrentWidget(this->welWidget);
    ui->controlBoardSkd->hide();

    //添加中央监控显示页面Widget
    this->mapWidget = new Map;
    ui->mapBoardSkd->addWidget(mapWidget);
    this->welWidget = new WelcomePage;
    ui->mapBoardSkd->addWidget(welWidget);
    this->carMapWidget = new CarMap;
    ui->mapBoardSkd->addWidget(carMapWidget);
    //

    //添加右侧控制面板widget
    this->carcontrollBoard = new CarControllBoard;
    ui->controlBoardSkd->addWidget(carcontrollBoard);
    this->lightcontrollBoard = new LightControllBoard;
    ui->controlBoardSkd->addWidget(lightcontrollBoard);


    //连接菜单导航点击切换界面槽函数
    connect(ui->welcomeBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_welcomeBtn_clicked()));
    connect(ui->mainBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_mainBtn_clicked()));
    connect(ui->carMapBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_carMapBtn_clicked()));
    connect(ui->aboutBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_aboutBtn_clicked()));
    connect(ui->helpBtn,SIGNAL(clicked(bool)),
            this,SLOT(on_helpBtn_clicked()));



}
Widget::~Widget()
{
    delete ui;
}

//切换菜单导航主页面显示欢迎页面
void Widget::on_welcomeBtn_clicked()
{
    ui->mapBoardSkd->setCurrentWidget(this->welWidget);
    ui->controlBoardSkd->hide();

    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);
    ui->helpBtn->setStyleSheet(setColor);

    ui->welcomeBtn->setStyleSheet(setOnlyColor);
}

//切换菜单导航主页面显示路况监控
void Widget::on_mainBtn_clicked()
{
    ui->mapBoardSkd->setCurrentWidget(this->mapWidget);
    ui->controlBoardSkd->show();
    ui->controlBoardSkd->setCurrentWidget(this->lightcontrollBoard);

    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);
    ui->helpBtn->setStyleSheet(setColor);

    ui->mainBtn->setStyleSheet(setOnlyColor);
}

//切换菜单导航主页面显示车辆监控
void Widget::on_carMapBtn_clicked()
{
    ui->mapBoardSkd->setCurrentWidget(this->carMapWidget);
    ui->controlBoardSkd->show();
    ui->controlBoardSkd->setCurrentWidget(this->carcontrollBoard);

    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);
    ui->helpBtn->setStyleSheet(setColor);

    ui->carMapBtn->setStyleSheet(setOnlyColor);
}



void Widget::on_aboutBtn_clicked()
{
    ui->controlBoardSkd->hide();
    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);
    ui->helpBtn->setStyleSheet(setColor);

    ui->aboutBtn->setStyleSheet(setOnlyColor);
}

void Widget::on_helpBtn_clicked()
{

    ui->controlBoardSkd->hide();
    //颜色设置
    QString setColor="background-color:black;color:#95a0aa";
    QString setOnlyColor="background-color:red;color:white";
    ui->mainBtn->setStyleSheet(setColor);
    ui->welcomeBtn->setStyleSheet(setColor);
    ui->carMapBtn->setStyleSheet(setColor);
    ui->aboutBtn->setStyleSheet(setColor);

    ui->helpBtn->setStyleSheet(setOnlyColor);
}

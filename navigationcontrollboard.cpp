#include "navigationcontrollboard.h"
#include "ui_navigationcontrollboard.h"

NavigationControllBoard::NavigationControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationControllBoard)
{
    ui->setupUi(this);

    ui->destinationLbl->hide();
    ui->autoModelGbx->hide();
    //自动导航模式开关事件绑定
    connect(ui->autoModelSwitchBtn,SIGNAL(clicked(bool)),
            this,SLOT(AutoModelSwitchBtnClicked()));
}

NavigationControllBoard::~NavigationControllBoard()
{
    delete ui;
}


void NavigationControllBoard::AutoModelSwitchBtnClicked()
{
    if(isAutoModelOn==false){
        ui->autoModelGbx->show();
        ui->destinationLbl->show();
        ui->autoModelSwitchBtn->setText("开启");
        ui->autoModelSwitchBtn->setStyleSheet("background-color:green;color:white;");
    }else if(isAutoModelOn==true){
        ui->autoModelGbx->hide();
        ui->destinationLbl->hide();
        ui->autoModelSwitchBtn->setText("关闭");
        ui->autoModelSwitchBtn->setStyleSheet("background-color:black;color:white;");
    }
    isAutoModelOn= !isAutoModelOn;
}


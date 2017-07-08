#include "navigationcontrollboard.h"
#include "ui_navigationcontrollboard.h"

NavigationControllBoard::NavigationControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationControllBoard)
{
    ui->setupUi(this);

    ui->destinationLbl->hide();
    ui->autoModelGbx->hide();

    //初始化下拉框路号选项
    for(int i=1;i<25;i++){
        ui->roadChooseCbx->addItem(tr("%1").arg(i)+"号路");
    }

    singleConnect = CommunicaWidget::getInstance();

    //自动导航模式开关事件绑定
    connect(ui->autoModelSwitchBtn,SIGNAL(clicked(bool)),
            this,SLOT(AutoModelSwitchBtnClicked()));

    connect(ui->navigateStartBtn,SIGNAL(clicked(bool)),
            this,SLOT(NavigateStartBtnClicked()));
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
        ui->autoModelSwitchBtn->setText("点击关闭");
        ui->autoModelSwitchBtn->setStyleSheet("background-color:green;color:white;");
    }else if(isAutoModelOn==true){
        ui->autoModelGbx->hide();
        ui->destinationLbl->hide();
        ui->autoModelSwitchBtn->setText("点击开启");
        ui->autoModelSwitchBtn->setStyleSheet("background-color:black;color:white;");
    }
    isAutoModelOn= !isAutoModelOn;
}

void NavigationControllBoard::NavigateStartBtnClicked()
{
    QString target="30";
    singleConnect->controlAutoNav(carNum,target);
}




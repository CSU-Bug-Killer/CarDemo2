#include "navigationcontrollboard.h"
#include "ui_navigationcontrollboard.h"

NavigationControllBoard::NavigationControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationControllBoard)
{
    ui->setupUi(this);

//    ui->destinationLbl->hide();
//    ui->autoModelGbx->hide();
    //隐藏开关
    ui->autoModelSwitchBtn->hide();

    //初始化下拉框路号选项
    for(int i=1;i<25;i++){
        ui->roadChooseCbx->addItem(tr("%1").arg(i)+"号路");
    }

    singleConnect = CommunicaWidget::getInstance();
//    target= new QString;

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

    //根据路号和位置选择，判断目标地点卡号
    switch(ui->roadChooseCbx->currentIndex()){
    case 0:
        target="0";
        getALocation();
        break;
    case 1:
        target="24";
        getALocation();
        break;
    case 2:
        target="3";
        getALocation();
        break;
    case 3:
        target="27";
        getALocation();
        break;
    case 4:
        target="60";
        getALocation();
        break;
    case 5:
        target="66";
        getALocation();
        break;
    case 6:
        target="63";
        getALocation();
        break;
    case 7:
        target="69";
        getALocation();
        break;
    case 8:
        target="39";
        getAALocation();
        break;
    case 9:
        target="15";
        getAALocation();
        break;
    case 10:
        target="36";
        getAALocation();
        break;
    case 11:
        target="12";
        getAALocation();
        break;
    case 12:
        target="30";
        getALocation();
        break;
    case 13:
        target="6";
        getALocation();
        break;
    case 14:
        target="33";
        getALocation();
        break;
    case 15:
        target="9";
        getALocation();
        break;
    case 16:
        target="48";
        getALocation();
        break;
    case 17:
        target="54";
        getALocation();
        break;
    case 18:
        target="51";
        getALocation();
        break;
    case 19:
        target="57";
        getALocation();
        break;
    case 20:
        target="21";
        getAALocation();
        break;
    case 21:
        target="45";
        getAALocation();
        break;
    case 22:
        target="18";
        getAALocation();
        break;
    case 23:
        target="42";
        getAALocation();
        break;
    }

    singleConnect->controlAutoNav(carNum,target);
    target="0";
}

void NavigationControllBoard::getALocation(){
    switch (ui->locationCbx->currentIndex()) {
    case 0:
        target=tr("%1").arg(target.toInt());
        break;
    case 1:
        target=tr("%1").arg(target.toInt()+1);
    case 2:
        target=tr("%1").arg(target.toInt()+2);
    default:
        break;
    }
}
void NavigationControllBoard::getAALocation(){
    switch (ui->locationCbx->currentIndex()) {
    case 0:
        target=tr("%1").arg(target.toInt()+2);
        break;
    case 1:
        target=tr("%1").arg(target.toInt()+1);
    case 2:
        target=tr("%1").arg(target.toInt());
    default:
        break;
    }
}




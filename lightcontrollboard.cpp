#include "lightcontrollboard.h"
#include "ui_lightcontrollboard.h"

#include <QMessageBox>
#include <QComboBox>

LightControllBoard::LightControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightControllBoard)
{
    ui->setupUi(this);

    ui->destinationLbl->hide();
    ui->autoModelGbx->hide();
    ui->roadCmb->setEnabled(false);


    //道路模式选择绑定
    connect(ui->roadModelCmb,SIGNAL(currentIndexChanged(int)),
            this,SLOT(onCurrentIndexChanged()));
    //道路模式设置绑定
    connect(ui->setTrafficModelBtn,SIGNAL(clicked(bool)),
            this,SLOT(setRoadModel()));


    //红绿灯设置绑定
    connect(ui->applyLightBtn,SIGNAL(clicked(bool)),
            this,SLOT(setTrafficLights()));

    singleConnect = CommunicaWidget::getInstance();

}

LightControllBoard::~LightControllBoard()
{
    delete ui;
}

void LightControllBoard::setRoadLights()
{
    qDebug() << "setRoadLights";
}

//设置道路通行控制模式
void LightControllBoard::setRoadModel()
{
    switch (ui->roadModelCmb->currentIndex()){
    case 0:                                    //未选中任何模式,显示警告
        QMessageBox::warning(this,tr("通行模式控制"),tr("未选择模式"),QMessageBox::Ok);
        break;
    case 1:                                    //畅通模式
        switch (ui->roadCmb->currentIndex()) {
        case 0:                                //东西向路畅通，南北保持默认的，将1号交通灯设置为红色，2号为绿色,将永远为此颜色
            singleConnect->controlRoadLight("roadLight1","red","roadLight2","green");
            break;
        case 1:                                //南北向路畅通，东西保持默认，将2号交通灯设置为红色,1号为绿色
            singleConnect->controlRoadLight("roadLight1","green","roadLight2","red");
            break;
        case 2:                                //十字路口全方位
            singleConnect->controlRoadLight("roadLight1","green","roadLight2","green");
            break;
        default:
            break;
        }
        break;
    case 2:                                    //禁行模式
        switch (ui->roadCmb->currentIndex()) {
        case 0:                                //东西向路禁行，南北畅通，将1号交通灯设置为红色，2号为绿色,将永远为此颜色
            singleConnect->controlRoadLight("roadLight1","green","roadLight2","red");
            break;
        case 1:                                //南北向路禁行，东西畅通，将2号交通灯设置为红色,1号为绿色
            singleConnect->controlRoadLight("roadLight1","red","roadLight2","green");
        case 2:                                //十字路口全方位禁行
            singleConnect->controlRoadLight("roadLight1","red","roadLight2","red");
        default:
            break;
        }
        break;
    }

}

//通行模式改变时
void LightControllBoard::onCurrentIndexChanged()
{

    ui->roadCmb->setEnabled(false);
    qDebug()<<ui->roadModelCmb->currentIndex();
    switch (ui->roadModelCmb->currentIndex())
    {
    case 0:                                    //未选择任何模式和选择畅通模式，允许设置红绿灯
        ui->roadCmb->setEnabled(false);        //路号不可选
        ui->redBtn1->setEnabled(true);         //红绿灯允许设置
        ui->greenBtn1->setEnabled(true);
        ui->redBtn2->setEnabled(true);
        ui->greenBtn2->setEnabled(true);
        ui->applyLightBtn->setStyleSheet("background-color:black;");
        ui->applyLightBtn->setEnabled(true);
        break;
    case 1:
    case 2:                                    //选择禁行模式，则不允许再进行红绿灯设置,应用按钮设为不可点击
        ui->roadCmb->setEnabled(true);         //路号可选
        ui->redBtn1->setEnabled(false);
        ui->greenBtn1->setEnabled(false);
        ui->redBtn2->setEnabled(false);
        ui->greenBtn2->setEnabled(false);
        ui->applyLightBtn->setStyleSheet("background-color:gray;");
        ui->applyLightBtn->setEnabled(false);  //不允许红绿灯设置

        break;
    default:
        break;
    }
}

//红绿灯控制
void LightControllBoard::setTrafficLights()
{

    QString light1Status="";                    //1号红绿灯状态
    QString light2Status="";                    //2号红绿灯状态
    if((!ui->redBtn1->isChecked()&&!ui->greenBtn1->isChecked())||(!ui->redBtn1->isChecked()&&!ui->greenBtn1->isChecked())){
        QMessageBox::warning(this,tr("模式错误"),tr("您未进行设置"),QMessageBox::Ok);
    }else{
        if(ui->redBtn1->isChecked()){
            light1Status="red";
        }else if(ui->greenBtn1->isChecked()){
            light1Status="green";
        }

        if(ui->redBtn2->isChecked()){
            light2Status="red";
        }
        else if(ui->greenBtn2->isChecked()){
            light2Status="green";
        }
    }
    singleConnect->controlRoadLight("roadlight1",light1Status,"roadlight2",light2Status);
}




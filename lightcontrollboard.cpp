#include "lightcontrollboard.h"
#include "ui_lightcontrollboard.h"

LightControllBoard::LightControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightControllBoard)
{
    ui->setupUi(this);

    ui->destinationLbl->hide();
    ui->autoModelGbx->hide();

    connect(ui->applyBtn,SIGNAL(clicked()),
            this,SLOT(setRoadLights()));
    connect(ui->testSend,SIGNAL(clicked()),
            this,SLOT(setRoadLights()));


    singleConnect = CommunicaWidget::getInstance();

}

void LightControllBoard::setRoadLights()
{
    qDebug() << "setRoadLights";
    singleConnect->controlRoadLight("roadLight1","1");
}


LightControllBoard::~LightControllBoard()
{
    delete ui;
}




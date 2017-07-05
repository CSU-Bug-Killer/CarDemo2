#include "lightcontrollboard.h"
#include "ui_lightcontrollboard.h"

LightControllBoard::LightControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightControllBoard)
{
    ui->setupUi(this);
}

LightControllBoard::~LightControllBoard()
{
    delete ui;
}

#include "carcontrollboard.h"
#include "ui_carcontrollboard.h"

CarControllBoard::CarControllBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarControllBoard)
{
    ui->setupUi(this);
}

CarControllBoard::~CarControllBoard()
{
    delete ui;
}

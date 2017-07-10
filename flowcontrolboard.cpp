#include "flowcontrolboard.h"
#include "ui_flowcontrolboard.h"

FlowControlBoard::FlowControlBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlowControlBoard)
{
    ui->setupUi(this);
}

FlowControlBoard::~FlowControlBoard()
{
    delete ui;
}

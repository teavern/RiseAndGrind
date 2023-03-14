#include "talitool.h"
#include "ui_talitool.h"

TaliTool::TaliTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TaliTool)
{
    ui->setupUi(this);
}

TaliTool::~TaliTool()
{
    delete ui;
}


#include "viewapplication.h"
#include "ui_viewapplication.h"

ViewApplication::ViewApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewApplication)
{
    ui->setupUi(this);
}

ViewApplication::~ViewApplication()
{
    delete ui;
}

#include "ErrorDialog.h"

#include "ui_ErrorDialog.h"

ErrorDialog::ErrorDialog(const std::exception& error, QWidget* parent)
: QDialog(parent), ui(new Ui::ErrorDialog) {
    ui->setupUi(this);
    ui->errorText->setText(error.what());
}

ErrorDialog::~ErrorDialog() { delete ui; }

#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller* c, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ctrl(c) {
  ui->setupUi(this);
  ui->drawArea->setWindow(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::normalizePic(const QImage& pic) {
  s21::Image image;
  int count = 0;
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      QRgb colour = pic.pixel(i * 280 / 28 + 7, j * 280 / 28 + 7);
      image.setValue(count, 255 - (colour & 0x000000ff));
      count++;
    }
  }
  std::string answer;
  answer += ctrl->getPredict(image);
  ui->lineAnswer->setText(QString::fromStdString(answer));
}

void MainWindow::getPredictDrawing() {
  normalizePic(ui->drawArea->getPicture());
}

void MainWindow::on_clearButton_2_clicked() { ui->drawArea->clearImage(); }

void MainWindow::on_LoadButton_clicked() {
  try {
    if (ui->graphButton->isChecked()) {
      ctrl->loadNetworkWeights(0, ui->layerBox->value());
    } else {
      ctrl->loadNetworkWeights(1, ui->layerBox->value());
    }
  } catch (std::exception& error) {
    ErrorDialog errorWindow(error);
    errorWindow.setModal(true);
    errorWindow.exec();
  }
}

void MainWindow::on_TrainButton_clicked() {
  try {
    if (ui->checkCrossValBox->isChecked()) {
      ctrl->crossValNetwork(ui->crossValBox->text().toInt());
    } else {
      ctrl->trainNetwork(0.1, ui->epochsBox->text().toInt());
    }
    std::vector<double> coord = ctrl->getHistory();
    ui->PlotWidget->drawPlot(coord);
  } catch (std::exception& error) {
    ErrorDialog errorWindow(error);
    errorWindow.setModal(true);
    errorWindow.exec();
  }
}

void MainWindow::on_SaveButton_clicked() {
  try {
    ctrl->saveNetworkWeights();
  } catch (std::exception& error) {
    ErrorDialog errorWindow(error);
    errorWindow.setModal(true);
    errorWindow.exec();
  }
}

void MainWindow::on_matrixButton_clicked() {
  try {
    ctrl->setMatrixNetwork(ui->layerBox->text().toInt());
  } catch (std::exception& error) {
    ErrorDialog errorWindow(error);
    errorWindow.setModal(true);
    errorWindow.exec();
  }
}

void MainWindow::on_graphButton_clicked() {
  try {
    ctrl->setGraphNetwork(ui->layerBox->text().toInt());
  } catch (std::exception& error) {
    ErrorDialog errorWindow(error);
    errorWindow.setModal(true);
    errorWindow.exec();
  }
}

void MainWindow::on_SavePhotoButton_clicked() {
  ui->drawArea->getPicture().save(QFileDialog::getSaveFileName());
}

void MainWindow::on_LoadPhotoButton_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Выбрать файл", "", "Файлы изображений (* .bmp )");
  if (fileName != "") {
    QImage img(fileName);
    try {
      if (!img.isNull()) {
        ui->drawArea->setPicture(img);
        normalizePic(img);
      }
    } catch (std::exception& error) {
      ErrorDialog errorWindow(error);
      errorWindow.setModal(true);
      errorWindow.exec();
    }
  }
}

void MainWindow::on_TestButton_clicked() {
  try {
    ctrl->testProgram(ui->testBox->value());
    ui->time->setText(
        QString::fromStdString(std::to_string(ctrl->getMetrics().seconds)));
    ui->precision->setText(
        QString::fromStdString(std::to_string(ctrl->getMetrics().precision)));
    ui->recall->setText(
        QString::fromStdString(std::to_string(ctrl->getMetrics().recall)));
    ui->accuracy->setText(
        QString::fromStdString(std::to_string(ctrl->getMetrics().accuracy)));
    ui->fMeasure->setText(
        QString::fromStdString(std::to_string(ctrl->getMetrics().fMeasure)));
  } catch (std::exception& error) {
    ErrorDialog errorWindow(error);
    errorWindow.setModal(true);
    errorWindow.exec();
  }
}

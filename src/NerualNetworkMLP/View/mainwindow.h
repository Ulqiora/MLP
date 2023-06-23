#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QColor>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QRgb>
#include <chrono>

#include "../Controller/Controller.h"
#include "../Model/Dataset.h"
#include "../Model/GNN/GNN.h"
#include "../Model/MNN/MNN.h"
#include "../View/ErrorDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(s21::Controller* c, QWidget* parent = nullptr);
    ~MainWindow();
    void getPredictDrawing();

 private:
    void normalizePic(const QImage& pic);

 private slots:

    void on_clearButton_2_clicked();

    void on_LoadButton_clicked();

    void on_TrainButton_clicked();

    void on_SaveButton_clicked();

    void on_matrixButton_clicked();

    void on_graphButton_clicked();

    void on_SavePhotoButton_clicked();

    void on_LoadPhotoButton_clicked();

    void on_TestButton_clicked();

 private:
    Ui::MainWindow* ui;
    s21::Controller* ctrl;
};
#endif  // MAINWINDOW_H

#include <QApplication>
#include <QFileDialog>
#include <chrono>

#include "Controller/Controller.h"
#include "Model/Dataset.h"
#include "Model/GNN/GNN.h"
#include "Model/MNN/MNN.h"
#include "View/mainwindow.h"
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Controller myCtrl;
  MainWindow w(&myCtrl);
  w.show();
  return a.exec();
}

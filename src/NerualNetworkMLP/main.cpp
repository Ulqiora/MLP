#include "Model/Dataset.h"
#include "Model/GNN/GNN.h"
#include <QApplication>
#include <QFileDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string str=QFileDialog::getOpenFileName().toStdString();
    s21::Dataset date;
    try {
        date.setDate(str);
    }  catch (std::exception& e) {
        qDebug()<<e.what();
    }
    s21::GraphNerualNetwork gnn(2);
    qDebug()<<"train start";
    gnn.train(date,4);
    qDebug()<<gnn.getAccuracyHistory();
    return a.exec();
}

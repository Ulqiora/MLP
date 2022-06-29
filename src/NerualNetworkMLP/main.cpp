#include "Model/Dataset.h"
#include "Model/GNN/GNN.h"
#include <QApplication>
#include <QFileDialog>
#include <chrono>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string str=QFileDialog::getOpenFileName().toStdString();
//    std::string str1=QFileDialog::getOpenFileName().toStdString();
    s21::Dataset date/*,dateTest*/;
    try {
        date.setDate(str);
    }  catch (std::exception& e) {
        qDebug()<<e.what();
    }
//    try {
//        dateTest.setDate(str1);
//    }  catch (std::exception& e) {
//        qDebug()<<e.what();
//    }
    s21::GraphNerualNetwork gnn(2);
    qDebug()<<"train start";
    auto begin = std::chrono::steady_clock::now();
    gnn.train(date,1);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::minutes>(end - begin);
    qDebug() << "The time: " << elapsed_ms.count() << " ms\n";
//    qDebug()<<"test start";
//    gnn.test(dateTest);
    return a.exec();
}

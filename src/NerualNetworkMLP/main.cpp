#include "Model/Dataset.h"
#include "Model/GNN/GNN.h"
#include <QApplication>
#include <QFileDialog>
#include <chrono>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string str=QFileDialog::getOpenFileName().toStdString();
    std::string str1=QFileDialog::getOpenFileName().toStdString();
    s21::Dataset date,dateTest;
    try {
        date.setDate(str);
    }  catch (std::exception& e) {
        qDebug()<<e.what();
    }
//    std::vector<int> answers(26);
//    for(int i=0;i<date.getSize();++i){
//        answers[date.getAnswer(i)]++;
//    }
    qDebug()<<QString::fromStdString(str);
    qDebug()<<QString::fromStdString(str1);
    try {
        dateTest.setDate(str1);
    }  catch (std::exception& e) {
        qDebug()<<e.what();
    }
    s21::GraphNerualNetwork gnn(2);
    qDebug()<<"train start";
    auto begin = std::chrono::steady_clock::now();
    gnn.train(date,dateTest,20);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    qDebug() << "All time: " << elapsed_ms.count() << " s\n";
    return a.exec();
}

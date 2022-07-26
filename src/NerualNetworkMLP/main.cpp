#include "Model/Dataset.h"
#include "Model/GNN/GNN.h"
#include "Model/MNN/MNN.h"
#include <QApplication>
#include <QFileDialog>
#include <chrono>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string str=QFileDialog::getOpenFileName().toStdString();
    std::string str1=QFileDialog::getOpenFileName().toStdString();
    std::string w=QFileDialog::getOpenFileName().toStdString();
    s21::Dataset date,dateTest;
    try {
        date.setDate(str);
        dateTest.setDate(str1);
    }  catch (std::exception& e) {
        qDebug()<<e.what();
    }

    qDebug()<<"train start";
    auto begin = std::chrono::steady_clock::now();
    s21::MatrixNerualNetwork gnn(2);
    gnn.loadWeights(w);
    gnn.train(date,dateTest,1,5);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    qDebug() << "All time: " << elapsed_ms.count() << " s\n";
    qDebug()<<gnn.getAccuracyHistory();
    return a.exec();
}

//std::string str=QFileDialog::getOpenFileName().toStdString();
//std::string str1=QFileDialog::getOpenFileName().toStdString();
//s21::Dataset date,dateTest;
//try {
//    date.setDate(str);
//}  catch (std::exception& e) {
//    qDebug()<<e.what();
//}
//try {
//    dateTest.setDate(str1);
//}  catch (std::exception& e) {
//    qDebug()<<e.what();
//}
//s21::GraphNerualNetwork gnn(2);
//qDebug()<<"train start";
//auto begin = std::chrono::steady_clock::now();
//gnn.train(date,dateTest,0.50,10);
//auto end = std::chrono::steady_clock::now();
//auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
//qDebug() << "All time: " << elapsed_ms.count() << " s\n";
//gnn.saveWeights(QFileDialog::getSaveFileName().toStdString());
//std::string weightsFile=QFileDialog::getOpenFileName().toStdString();
//gnn.loadWeights(weightsFile);
//gnn.test(dateTest,1.0);

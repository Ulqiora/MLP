//#include "Model/Dataset.h"
//#include "Model/GNN/GNN.h"
#include "View/viewapplication.h"
#include <QApplication>
#include <QFileDialog>
#include <chrono>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewApplication app;
    app.show();
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
//gnn.train(date,dateTest,10);
//auto end = std::chrono::steady_clock::now();
//auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
//qDebug() << "All time: " << elapsed_ms.count() << " s\n";
//gnn.saveWeights(QFileDialog::getSaveFileName().toStdString());
//std::string weightsFile=QFileDialog::getOpenFileName().toStdString();
//gnn.loadWeights(weightsFile);
//gnn.test(dateTest);

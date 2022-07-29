//#include "Model/Dataset.h"
#include "Model/GNN/GNN.h"
#include "Model/MNN/MNN.h"
#include <iostream>
#include <string>
//#include <QApplication>
//#include <QFileDialog>
#include <chrono>
int main(/*int argc, char *argv[]*/)
{
    std::cout<<"start data train parse"<<'\n';
    std::string str1="/Users/jcraster/MLP/datasets/emnist-letters-train.csv";
    std::string str2="/Users/jcraster/MLP/datasets/emnist-letters-test.csv";
//    std::string str1="/Users/jcraster/MLP/datasets/train.txt";
std::string weights="/Users/jcraster/MLP/src/NerualNetworkMLP/weights/weight_l2_2epoch_78_2703.txt";
    s21::Dataset data1(str1);
    std::cout<<"start data test parse"<<'\n';
    s21::Dataset data2(str2);
    std::cout<<str2<<'\n';
    s21::GraphNerualNetwork gnn(2);
    gnn.loadWeights(weights);
    std::cout<<"train start"<<'\n';
    auto begin = std::chrono::steady_clock::now();
    gnn.train(data1,data2,1,50);
    gnn.saveWeights("/Users/jcraster/MLP/src/NerualNetworkMLP/weights/random2.txt");
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    std::cout << "All time: " << elapsed_ms.count() << " s\n";
    return 0;
//    std::string str2="/Users/jcraster/MLP/datasets/emnist-letters-test.csv";
//    std::string str1="/Users/jcraster/MLP/datasets/train.txt";
//    QApplication a(argc, argv);
//    std::string str=QFileDialog::getOpenFileName().toStdString();
//    std::string str1=QFileDialog::getOpenFileName().toStdString();
//    std::string w=QFileDialog::getOpenFileName().toStdString();
//    s21::Dataset date,dateTest;
//    try {
//        date.setDate(str);
//        dateTest.setDate(str1);
//    }  catch (std::exception& e) {
//        qDebug()<<e.what();
//    }
//    qDebug()<<"train start";
//    auto begin = std::chrono::steady_clock::now();
//    s21::GraphNerualNetwork gnn(2);
//    gnn.loadWeights(w);
//    gnn.train(date,dateTest,1,50);
//    auto end = std::chrono::steady_clock::now();
//    auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
//    qDebug() << "All time: " << elapsed_ms.count() << " s\n";
//    qDebug()<<gnn.getAccuracyHistory();
//    qDebug()<<"recall"<<gnn.metrics().recall;
//    qDebug()<<"accuracy"<<gnn.metrics().accuracy;
//    qDebug()<<"f-measure"<<gnn.metrics().fMeasure;
//    qDebug()<<"presition"<<gnn.metrics().precision;
//    gnn.saveWeights(w);
//    return a.exec();
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

#include "Model/Dataset.h"
#include "Model/GNN/GNN.h"
//#include <QApplication>
//#include <QFileDialog>
int main(/*int argc, char *argv[]*/)
{
//    QApplication a(argc, argv);
//    std::string str=QFileDialog::getOpenFileName().toStdString();
    s21::GraphNerualNetwork gnn(2);
    qDebug()<<gnn.getLayer(3).getNumOfNeurons();
    return 0;
}

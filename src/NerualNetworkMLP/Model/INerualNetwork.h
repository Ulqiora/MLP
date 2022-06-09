#ifndef INERUALNETWORK_H
#define INERUALNETWORK_H
#include "Matrix.h"
#include <vector>
#include <QFile>
namespace s21{

enum TypeLayer{OUTPUT=26,INPUT=784,HIDDEN=200};

class INerualNetwork
{
public:
    char predict();

    void loadWeight();
    void saveWeight();
};

class NerualNetworkMatrix{
public:
    explicit NerualNetworkMatrix(unsigned int numHiddenLayers);
    void loadWeight(const QFile& filename);
    void saveWeight(const QFile& filename);
private:
    unsigned int _hiddenLayers;
    std::vector<Matrix> _neuronWeightMat;
    std::vector<Matrix> _biosWeightMat;
    std::vector<Matrix> _errorMatrix;
private:
    void setWeightMatrix();
    void setBiosMatrix();
};


}    //    namespace s21
#endif // INERUALNETWORK_H

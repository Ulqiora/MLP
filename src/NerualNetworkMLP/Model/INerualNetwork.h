#ifndef INERUALNETWORK_H
#define INERUALNETWORK_H
#include "Matrix.h"
#include "ActicateFunction.h"
#include "Dataset.h"
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
protected:
};

class NerualNetworkMatrix{
public:
    explicit NerualNetworkMatrix(unsigned int numHiddenLayers);
    void loadWeight(const QFile& filename);
    void saveWeight(const QFile& filename);

    void train(int epoch,Dataset& data);
    void trainCrossValidation(int numOfGroup,Dataset& data);

private:
    ActicateFunction _func;
    unsigned int _hiddenLayers;
    std::vector<Matrix> _neuronWeightMat;
    std::vector<Matrix> _biosWeightMat;
    std::vector<Matrix> _errorMatrix;
    double _currentError;

private:
    void setWeightMatrix();
    void setBiosMatrix();
    int forwardPropagation(double* pixels,int answer=0);
    void backPropagation();
    void addErrorToCurrent(Matrix& outputNeruals);
    int getPredict(Matrix& outputNeruals);
};


}    //    namespace s21
#endif // INERUALNETWORK_H

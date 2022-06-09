#include "INerualNetwork.h"
namespace s21{
NerualNetworkMatrix::NerualNetworkMatrix(unsigned int numHiddenLayers):
    _neuronWeightMat(0),_biosWeightMat(0),_errorMatrix(0)
{
    _hiddenLayers=numHiddenLayers;
    setWeightMatrix();
    setBiosMatrix();
}

void NerualNetworkMatrix::setWeightMatrix(){
    Matrix inputLayer(HIDDEN,INPUT);
    inputLayer.setRandom();
    _neuronWeightMat.push_back(inputLayer);
    for(unsigned int i=0;i<_hiddenLayers-1;i++){
        Matrix hiddenLayer(HIDDEN,HIDDEN);
        hiddenLayer.setRandom();
        _neuronWeightMat.push_back(inputLayer);
    }
    Matrix hiddenLayer(OUTPUT,HIDDEN);
    hiddenLayer.setRandom();
    _neuronWeightMat.push_back(inputLayer);
}

void NerualNetworkMatrix::setBiosMatrix(){
    for(unsigned int i=0;i<_hiddenLayers;i++){
        Matrix weightBios_i(HIDDEN,1);
        weightBios_i.setRandom();
        _biosWeightMat.push_back(weightBios_i);
    }
    Matrix weightBios_last(OUTPUT,1);
    weightBios_last.setRandom();
    _biosWeightMat.push_back(weightBios_last);
}



}

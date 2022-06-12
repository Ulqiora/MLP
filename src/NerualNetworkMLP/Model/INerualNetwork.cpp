#include "INerualNetwork.h"
namespace s21{
NerualNetworkMatrix::NerualNetworkMatrix(unsigned int numHiddenLayers):
    _func(typeFunction::SIGMOIND),_neuronWeightMat(0),_biosWeightMat(0),_errorMatrix(0)
{
    _hiddenLayers=numHiddenLayers;
    setWeightMatrix();
    setBiosMatrix();
}

int NerualNetworkMatrix::forwardPropagation(Image& currrentImage){
    Matrix neruals(currrentImage._pixels,NUM_OF_PIXELS);
    for(unsigned int i=0;i<=_hiddenLayers;++i){
        neruals=_neuronWeightMat[i]*neruals+_biosWeightMat[i];
        neruals=_func.use(neruals);
    }
    addErrorToCurrent(neruals);
    return getPredict(neruals);
}

int NerualNetworkMatrix::getPredict(Matrix& outputNeruals){
    int max=0;
    for(int i=1;i<TypeLayer::OUTPUT;i++){
        if(outputNeruals(i,0)>outputNeruals(max,0)){
            max=i;
        }
    }
    return max;
}

void NerualNetworkMatrix::addErrorToCurrent(Matrix& outputNeruals){

}


void NerualNetworkMatrix::train(int epoch,Dataset& data){
    unsigned int datasetSize=data._data.size();

    for(int i=0;i<epoch;i++){
        forwardPropagation(data._data[i]);
    }
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

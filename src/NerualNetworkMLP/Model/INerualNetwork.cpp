#include "INerualNetwork.h"
namespace s21{
NerualNetworkMatrix::NerualNetworkMatrix(unsigned int numHiddenLayers):
    _func(typeFunction::SIGMOIND),_neuronWeightMat(0),_biosWeightMat(0),_valueNeruals(numHiddenLayers+1),_valueErrors(numHiddenLayers+1)
{
    _hiddenLayers=numHiddenLayers;
    setWeightMatrix();
    setBiosMatrix();
}
//    инициализация матриц весов
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
//     инициализация матриц весов для нейронов смещения
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
//    вычисляет значения выходного слоя для набора пикселей
void NerualNetworkMatrix::forwardPropagation(double* currrentImage){
    _valueNeruals.front() = Matrix (currrentImage,NUM_OF_PIXELS);
    for(unsigned int i=1;i<=_hiddenLayers+1;++i){
        _valueNeruals[i]=_neuronWeightMat[i]*_valueNeruals[i]+_biosWeightMat[i];
        _valueNeruals[i]=_func.use(_valueNeruals[i]);
    }
}
//    после прохождения forwardPropagation находит максимум среди выходного слоя
int NerualNetworkMatrix::getPredict(){
    int max=0;
    for(int i=1;i<TypeLayer::OUTPUT;i++){
        if(_valueNeruals.back()(i,0)>_valueNeruals.back()(max,0)){
            max=i;
        }
    }
    return max;
}

//    answer-ответ текущего набора пикселей(приведен к элементам массива)
void NerualNetworkMatrix::calcError(unsigned int answer){
    Matrix errors(OUTPUT,0);
    for(unsigned int i=0;i<TypeLayer::OUTPUT ;i++){
        if(i != answer){
            errors(i,0)=-_valueNeruals.back()(i,0)*_func.useDerivative(_valueNeruals.back()(i,0));
        } else {
            errors(i,0)=(1.0-_valueNeruals.back()(i,0))*_func.useDerivative(_valueNeruals.back()(i,0));
        }
    }
    _valueErrors.back()=errors;
    for(unsigned int i=_hiddenLayers-1;i>=0;--i){
        errors=_neuronWeightMat[i]*_valueErrors[i+1];
        for(int j=0;j<TypeLayer::HIDDEN;j++){
            errors(j,0)*=_func.useDerivative(_valueNeruals[i+1](j,0));
        }
//        _valueErrors[i]=
    }
}

void NerualNetworkMatrix::updateWeight(){

}

//    обучение нейросети с указанием числа эпох
void NerualNetworkMatrix::train(unsigned int epoch,Dataset& data){
    unsigned int datasetSize=data._data.size();

    for(unsigned int i=0;i<epoch;i++){
        for(unsigned int j=0;j<datasetSize;j++){
            forwardPropagation(data._data[i]._pixels);
            calcError(data._data[i]._numOfSymbol-1);

        }


    }
}

void NerualNetworkMatrix::backPropagation(){

}
}

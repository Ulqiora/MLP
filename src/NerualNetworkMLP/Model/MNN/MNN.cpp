#include "MNN.h"

namespace s21 {

MatrixNerualNetwork::MatrixNerualNetwork(unsigned int numHiddenLayers):
    _func(typeFunction::SIGMOIND),_neuronWeightMat(0),_biosWeightMat(0),_valueNeruals(numHiddenLayers+1),_valueErrors(numHiddenLayers)
{
    _numOfHiddenLayers=numHiddenLayers;
    setWeightMatrix();
    setBiosMatrix();
}

void MatrixNerualNetwork::setWeightMatrix() {
    Matrix inputLayer(static_cast<int>(TypeLayer::HIDDEN),static_cast<int>(TypeLayer::INPUT));
    inputLayer.setRandom();
    _neuronWeightMat.push_back(inputLayer);
    for(unsigned int i=0;i<_numOfHiddenLayers-1;i++){
        Matrix hiddenLayer(static_cast<int>(TypeLayer::HIDDEN),static_cast<int>(TypeLayer::HIDDEN));
        hiddenLayer.setRandom();
        _neuronWeightMat.push_back(inputLayer);
    }
    Matrix hiddenLayer(static_cast<int>(TypeLayer::OUTPUT),static_cast<int>(TypeLayer::HIDDEN));
    hiddenLayer.setRandom();
    _neuronWeightMat.push_back(inputLayer);
}

void MatrixNerualNetwork::setBiosMatrix(){
    for(unsigned int i=0;i<_numOfHiddenLayers;i++){
        Matrix weightBios_i(static_cast<int>(TypeLayer::HIDDEN),1);
        weightBios_i.setRandom();
        _biosWeightMat.push_back(weightBios_i);
    }
    Matrix weightBios_last(static_cast<int>(TypeLayer::OUTPUT),1);
    weightBios_last.setRandom();
    _biosWeightMat.push_back(weightBios_last);
}

void MatrixNerualNetwork::forwardPropagation(const Image& image){
    _valueNeruals.front()=Matrix(image);
    for(unsigned int i=1;i<=_numOfHiddenLayers+1;++i){
        _valueNeruals[i]=_neuronWeightMat[i]*_valueNeruals[i]+_biosWeightMat[i];
        _valueNeruals[i]=_func.use(_valueNeruals[i]);
    }
}

void MatrixNerualNetwork::backPropagation(int answer){
    Matrix errors(static_cast<int>(TypeLayer::OUTPUT),0);
    for(int i=0;i<errors.getRows() ;i++){
        if(i != answer){
            errors.setValue(i,0,-_valueNeruals.back()(i,0)*_func.useDerivative(_valueNeruals.back()(i,0)));
        } else {
            errors.setValue(i,0,1.0-_valueNeruals.back()(i,0)*_func.useDerivative(_valueNeruals.back()(i,0)));
        }
    }
    _valueErrors.back()=errors;
    for(unsigned int i=_numOfHiddenLayers-1;i>0;--i){
        _valueErrors[i]=_neuronWeightMat[i+1].transpose()*_valueErrors[i+1];
        for(int j=0;i<_valueErrors[i].getRows();++j){
            _valueErrors[i]*=_func.useDerivative(_valueNeruals[i+1]);
        }
    }
}

void MatrixNerualNetwork::updateWeight(int numOfEpoch)
{
    for(unsigned int i=0;i<_neuronWeightMat.size();++i){
        for(int j=0;j<_neuronWeightMat[i].getRows();++j){
            for(int k=0;k<_neuronWeightMat[i].getCols();++k){
                _neuronWeightMat[i].setValue(j,k,_neuronWeightMat[i](j,k)-(lr/numOfEpoch)*_valueNeruals[i](k,0)*_valueErrors[i+1](j,0));
            }
            _biosWeightMat[i].setValue(j,0,_biosWeightMat[i](j,0)-(lr/numOfEpoch)*_valueErrors[i+1](j,0));
        }
    }
}


void MatrixNerualNetwork::train(Dataset& data,Dataset&  dataTest, double percentTestData,int numOfEpoch)
{
    _accuracyHistory.clear();
    for (int i = 0; i < numOfEpoch; i++) {
        int dataSize = data.getSize();
        for (int j = 0; j < dataSize; ++j) {
            forwardPropagation(data.getImage(j));
            backPropagation(data.getAnswer(j));
            updateWeight(i+1);
        }
        test(dataTest,percentTestData);
    }
}

Metrics MatrixNerualNetwork::test(Dataset &data, double percentTestData)
{
    Metrics metrics;
    metrics.reset();
    int accuracy=0;
    int dataSize=data.getSize()*percentTestData;
    for (int j = 0; j < dataSize; ++j) {
        forwardPropagation(data.getImage(j));
        accuracy+=isCorrectPrediction(data.getAnswer(j));
        calcSolutions(metrics,data.getAnswer(j));
    }

    metrics.accuracy =static_cast<double>(accuracy) / data.getSize() * 100.0;
    metrics.precision=metrics.solutions.tp/(metrics.solutions.tp+metrics.solutions.fp);
    metrics.recall=metrics.solutions.tp/(metrics.solutions.tp+metrics.solutions.fn);
    metrics.fMeasure=2*(metrics.precision*metrics.recall)/(metrics.precision*metrics.recall);
    return metrics;
}
void MatrixNerualNetwork::calcSolutions(Metrics& metrics,int answer){
    for(int i=0;i<static_cast<int>(TypeLayer::OUTPUT);++i){
        if(isCorrectPrediction(answer)){
            if(i==answer){
                metrics.solutions.tp++;
            } else {
                metrics.solutions.fp++;
            }
        } else {
            if(i==answer){
                metrics.solutions.fn++;
            } else {
                metrics.solutions.tn++;
            }
        }
    }
}

bool MatrixNerualNetwork::isCorrectPrediction(int answer)
{
    int indexMax=0;
    for(int i=1;i<static_cast<int>(TypeLayer::OUTPUT);i++){
        if(_valueNeruals.back()(i,0)>_valueNeruals.back()(indexMax,0)){
            indexMax=i;
        }
    }
    return indexMax==answer;
}


}  // namespace s21P

#include "MNN.h"

namespace s21 {

MatrixNerualNetwork::MatrixNerualNetwork(unsigned int numHiddenLayers):
    _func(typeFunction::SIGMOIND),_neuronWeightMat(0),_biosWeightMat(0),_valueNeruals(numHiddenLayers+2),_valueErrors(numHiddenLayers+1)
{
    _numOfHiddenLayers=numHiddenLayers;
    setWeightMatrix();
    setBiosMatrix();
}

void MatrixNerualNetwork::setWeightMatrix() {
    Matrix inputLayer(static_cast<int>(TypeLayer::HIDDEN),static_cast<int>(TypeLayer::INPUT));
//    inputLayer.setRandom();
    _neuronWeightMat.push_back(inputLayer);
    for(unsigned int i=0;i<_numOfHiddenLayers-1;i++){
        Matrix hiddenLayer(static_cast<int>(TypeLayer::HIDDEN),static_cast<int>(TypeLayer::HIDDEN));
//        hiddenLayer.setRandom();
        _neuronWeightMat.push_back(hiddenLayer);
    }
    Matrix hiddenLayer(static_cast<int>(TypeLayer::OUTPUT),static_cast<int>(TypeLayer::HIDDEN));
//    hiddenLayer.setRandom();
    _neuronWeightMat.push_back(hiddenLayer);
}

void MatrixNerualNetwork::setBiosMatrix(){
    for(unsigned int i=0;i<_numOfHiddenLayers;i++){
        Matrix weightBios_i(static_cast<int>(TypeLayer::HIDDEN),1);
//        weightBios_i.setRandom();
        _biosWeightMat.push_back(weightBios_i);
    }
    Matrix weightBios_last(static_cast<int>(TypeLayer::OUTPUT),1);
//    weightBios_last.setRandom();
    _biosWeightMat.push_back(weightBios_last);
}

void MatrixNerualNetwork::forwardPropagation(const Image& image){
    _valueNeruals.front()=Matrix(image);
    for(unsigned int i=1;i<=_numOfHiddenLayers+1;++i){
        _valueNeruals[i]=_neuronWeightMat[i-1]*_valueNeruals[i-1]+_biosWeightMat[i-1];
        _valueNeruals[i]=_func.use(_valueNeruals[i]);
    }
}

void MatrixNerualNetwork::backPropagation(int answer){
    Matrix errors(static_cast<int>(TypeLayer::OUTPUT),1);
    for(int i=0;i<errors.getRows() ;i++){
        double res= (_valueNeruals.back()(i,0)-(i==answer));
        errors.setValue(i,0,res);
    }
    _valueErrors.back()=errors;
    for(int i=_numOfHiddenLayers-1;i>=0;--i){
        _valueErrors[i]=_neuronWeightMat[i+1].transpose()*_valueErrors[i+1];
    }
}

void MatrixNerualNetwork::updateWeight(int numOfEpoch)
{
    for(unsigned int i=0;i<_numOfHiddenLayers+1;++i){
        for(int j=0;j<_neuronWeightMat[i].getRows();++j){
            for(int k=0;k<_neuronWeightMat[i].getCols();++k){
                qDebug()<<-lr*_valueNeruals[i](k,0)*_valueErrors[i](j,0)*_func.useDerivative(_valueNeruals[i+1](j,0));
                _neuronWeightMat[i].setValue(j,k,
                   _neuronWeightMat[i](j,k)-lr*_valueNeruals[i](k,0)*_valueErrors[i](j,0)*_func.useDerivative(_valueNeruals[i+1](j,0)));
            }
            qDebug()<<-lr*_valueErrors[i](j,0)*_func.useDerivative(_valueNeruals[i+1](j,0));
            _biosWeightMat[i].setValue(j,0,_biosWeightMat[i](j,0)-lr*_valueErrors[i](j,0)*_func.useDerivative(_valueNeruals[i+1](j,0)));
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
        _accuracyHistory.push_back(test(dataTest,percentTestData));
    }
    _metrics.accuracy =(_metrics.solutions.tp+_metrics.solutions.tn);
    _metrics.accuracy/=(_metrics.solutions.tp+_metrics.solutions.tn+_metrics.solutions.fp+_metrics.solutions.fn);
    _metrics.precision=_metrics.solutions.tp/(_metrics.solutions.tp+_metrics.solutions.fp);
    _metrics.recall=_metrics.solutions.tp/(_metrics.solutions.tp+_metrics.solutions.fn);
    _metrics.fMeasure=2*(_metrics.precision*_metrics.recall)/(_metrics.precision*_metrics.recall);
}

double MatrixNerualNetwork::test(Dataset &data, double percentTestData)
{
    int accuracy=0;
    int dataSize=data.getSize()*percentTestData;
    for (int j = 0; j < dataSize; ++j) {
        forwardPropagation(data.getImage(j));
        accuracy+=isCorrectPrediction(data.getAnswer(j));
        calcSolutions(_metrics,data.getAnswer(j));
        qDebug()<<accuracy;
    }
    return static_cast<double>(accuracy)/dataSize;
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

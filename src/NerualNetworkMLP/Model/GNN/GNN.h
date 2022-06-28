#pragma once
#include "Layer.h"
#include "../Dataset.h"
#include "../ActivateFunction.h"
namespace s21
{
class GraphNerualNetwork{
private:
    std::vector<Layer> _layers;
    unsigned int _hiddenLayers;
    std::vector<double> _accuracyHistory;
    ActivateFunction _func;
private:
    bool isCorrectPrediction(int answer){
        int indexMax=0;
        for(int i=1;i<_layers.back().getNumOfNeurons();i++){
            if(_layers.back()(i)->getValue() >
               _layers.back()(indexMax)->getValue()) {
                indexMax=i;
            }
        }
//        qDebug()<<answer<<"     "<< indexMax;
        return answer==(indexMax);
    }

    void forwardPropagation(Image& image){
        for(int i=0;i<_layers[0].getNumOfNeurons();i++){
            _layers[0](i)->getValue()=0.0;
            for(int j=0;j<_layers[0](i)->getNumOfWeights();j++){
                _layers[0](i)->getValue()+=(*_layers[0](i))(j)*image(j);
            }
            _layers[0](i)->getValue()=_func.use(_layers[0](i)->getValue());
        }
        for(unsigned int i=1;i<=_hiddenLayers;++i){
            _layers[i].calcForForwardPropagation(_layers[i-1],_func);
        }
    }

    void backPropagation(int answer){
        _layers.back().setErrorNeuronsWithAnswer(answer,_func);
        for(int i=_hiddenLayers-1;i>=0;--i){
            _layers[i].calcForBackPropagation(_layers[i+1],_func);
        }
    }

    void updateWeight(Image& image){
        for(unsigned int i=_hiddenLayers;i>0;i--){
            _layers[i].updateWeightNeurons(_layers[i-1]);
        }
        for(Neuron* neuron:_layers[0]){
            for(int i=0;i<neuron->getNumOfWeights();i++){
                (*neuron)(i)+=image(i)*neuron->getError();
            }
        }
    }
public:
    GraphNerualNetwork(unsigned int numHiddenLayers):_hiddenLayers(numHiddenLayers),_func(){
        _layers.push_back(Layer(TypeLayer::HIDDEN,TypeLayer::INPUT));
        for(unsigned int i=0;i<_hiddenLayers-1;++i){
            _layers.push_back(Layer(TypeLayer::HIDDEN,TypeLayer::HIDDEN));
        }
        _layers.push_back(Layer(TypeLayer::OUTPUT,TypeLayer::HIDDEN));
    }

    void train(Dataset& date,int epoch){
        _accuracyHistory.clear();
        for(int i=0;i<epoch;i++){
            int accuracy=0,dataSize=date.getSize();
            for(int j=0;j<dataSize;++j){
                forwardPropagation(date.getImage(j));
                if (isCorrectPrediction(date.getAnswer(j))) {
//                    qDebug()<<j<<":  1";
                    ++accuracy;
                } else {
//                    qDebug()<<j<<":  0";
                }
                backPropagation(date.getAnswer(j));
                updateWeight(date.getImage(j));
            }
            double percent=static_cast<double>(accuracy)/date.getSize()*100.0;
            _accuracyHistory.push_back(percent);
            qDebug()<< i+1 << "     " << accuracy;
        }
        qDebug()<<getAccuracyHistory();
    }

    void test(Dataset& date){
        int accuracy=0;
        for(int j=0;j<date.getSize();++j){
            forwardPropagation(date.getImage(j));
            if (isCorrectPrediction(date.getAnswer(j))) {
                ++accuracy;
//                    qDebug()<< j <<"   1";
            } else {
//                    qDebug()<< j <<"   0";
            }
        }
        double percent=static_cast<double>(accuracy)/date.getSize()*100.0;
        qDebug() << "test: accuracy=" << percent;
    }

    Layer& getLayer(int i){
        return _layers[i];
    }

    std::vector<double>& getAccuracyHistory(){
        return _accuracyHistory;
    }
};
} // namespace s21

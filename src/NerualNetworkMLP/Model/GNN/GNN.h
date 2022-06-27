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
    bool isCorrectPrediction(int& answer){
        int indexMax=0;
        for(int i=1;i<_layers.back().getNumOfNeurons();i++){
            if(_layers.back()(i).getValue() >
               _layers.back()(indexMax).getValue()) {
                indexMax=i;
            }
        }
        return answer==(indexMax+1);
    }
    void forwardPropagation(Image& image){
        setImageToInputNeurons(image);
        for(unsigned int i=0;i<_hiddenLayers+1;++i){
            _layers[i+1].calcForForwardPropagation(_layers[i],_func);
        }
    }

    void setImageToInputNeurons(Image& image){
        for(int i=0;i<NUM_OF_PIXELS;i++){
            _layers[0](i).getValue()=image(i);
        }
    }

    void setErrorForOutputLayers(int answer){
        for(int i=0;i<_layers.back().getNumOfNeurons();i++){
            if(i==answer-1){
                _layers.back()(i).getError() = (1.0-_layers.back()(i).getValue())*
                        _func.useDerivative(_layers.back()(i).getValue());
            } else {
                _layers.back()(i).getError() = (-_layers.back()(i).getValue())*
                        _func.useDerivative(_layers.back()(i).getValue());
            }
        }
    }

    void backPropagation(){
        for(int i=_hiddenLayers;i>=0;--i){
            for(int j=0;j<_layers[i].getNumOfNeurons();++j){
                double sum=0.0;
                for(int k=0; k < _layers[i+1].getNumOfNeurons(); ++k){
                    sum+=(_layers[i+1](k).getError()*_layers[i+1](k).getWeight(j));
                }
                _layers[i](j).getError()=sum;
                _layers[i](j).getError()*=_func.useDerivative(_layers[i](j).getValue());
            }
        }
    }
    void updateWeight(){
        for(unsigned int i=1;i<=_hiddenLayers+1;i++){
            for(int j=0;j<_layers[i].getNumOfNeurons();j++){
                for(int k=0;k<_layers[i](j).getNumOfWeights();++k){
                    _layers[i](j).getWeight(k)-=(_layers[i-1](j).getValue()*_layers[i](j).getError());
                }
            }
        }
    }
public:
    GraphNerualNetwork(unsigned int numHiddenLayers):_hiddenLayers(numHiddenLayers),_func(){
        _layers.push_back(Layer(TypeLayer::INPUT,TypeLayer::NA));
        _layers.push_back(Layer(TypeLayer::HIDDEN,TypeLayer::INPUT));
        for(unsigned int i=0;i<_hiddenLayers-1;++i){
            _layers.push_back(Layer(TypeLayer::HIDDEN,TypeLayer::HIDDEN));
        }
        _layers.push_back(Layer(TypeLayer::OUTPUT,TypeLayer::HIDDEN));
    }

    void train(Dataset& date,int epoch){
        _accuracyHistory.clear();
        for(int i=0;i<epoch;i++){
            int accuracy=0;
            for(int j=0;j<date.getSize();++j){
                forwardPropagation(date.getImage(i));
                if (isCorrectPrediction(date.getAnswer(i))) {
                    ++accuracy;
                    qDebug()<< j <<"   1";
                } else {
                    qDebug()<< j <<"   0";
                }
                setErrorForOutputLayers(date.getAnswer(i));
                backPropagation();
                updateWeight();
            }
            double percent=static_cast<double>(accuracy)/date.getSize()*100.0;
            _accuracyHistory.push_back(percent);
            qDebug()<< i+1 << "     " << percent;
        }
    }

    int getNumOfLayers(){
        return 2+_hiddenLayers;
    }
    Layer& getLayer(int i){
        return _layers[i];
    }

    std::vector<double>& getAccuracyHistory(){
        return _accuracyHistory;
    }
};
} // namespace s21

#pragma once
#include "Layer.h"
#include "../Dataset.h"
#include "../ActicateFunction.h"
namespace s21
{
class GraphNerualNetwork{
private:
    std::vector<Layer> _layers;
    unsigned int _hiddenLayers;
    std::vector<double> _valueError;
    ActivateFunction _func;
private:
    bool isCorrectPrediction(int answer){
        return answer==0;
    }
    void forwardPropagation(Image& image){
        setImageToInputNeurons(image);
        for(unsigned int i=0;i<_hiddenLayers+1;++i){
            _layers[i+1].calcForForwardPropagation(_layers[i],_func);
        }
    }

    void setImageToInputNeurons(Image& image){
        for(int i=0;i<NUM_OF_PIXELS;i++){
            _layers[0].getNeuron(i).setValue(image(i));
        }
    }

    void backPropagation();
    void updateWeight();
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
        _valueError.clear();
        for(int i=0;i<epoch;i++){
            int accuracy=0.0;
            for(int j=0;j<date.getSize();++j){
                forwardPropagation(date.getImage(i));
                if (isCorrectPrediction(date.getAnswer(i))) {
                    ++accuracy;
                }
                backPropagation();
                updateWeight();
            }

        }
    }

    int getNumOfLayers(){
        return 2+_hiddenLayers;
    }
    Layer& getLayer(int i){
        return _layers[i];
    }
};
} // namespace s21

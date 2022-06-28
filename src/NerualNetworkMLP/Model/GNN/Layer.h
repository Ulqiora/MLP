#pragma once
#include "Neuron.h"
#include "../Dataset.h"
#include "../ActivateFunction.h"
namespace s21
{
class Layer{
private:
    std::vector<Neuron*> _neurons;
    TypeLayer _type;

public:
    Layer(TypeLayer thisLayer, TypeLayer previousLayer):_neurons(0),_type(thisLayer){
        int numOfNeurons=static_cast<int>(_type);
        Neuron* neuron=nullptr;
        for(int i=0;i<numOfNeurons;i++){
            neuron=new Neuron(previousLayer);
            _neurons.push_back(neuron);
        }
    }

    void calcForForwardPropagation(Layer& layer,ActivateFunction& _func){
        for(int i=0;i<getNumOfNeurons();++i){
            double sum=0.0;
            for(int j=0;j<layer.getNumOfNeurons();++j){
                sum+=((layer(j)).getValue()*(*_neurons[i])(j));
            }
            _neurons[i]->getValue()=_func.use(sum);
        }
    }

    void setNeuronsWithPixels(Image& image){
        if(_type!=TypeLayer::INPUT)
            throw std::invalid_argument("Error layer, this layer is not input");
        for(int i=0;i<getNumOfNeurons();++i){
            _neurons[i]->getValue()=image(i);
        }
    }

    void setErrorNeuronsWithAnswer(int answer,ActivateFunction func){
        if(_type!=TypeLayer::OUTPUT)
            throw std::invalid_argument("Error layer, this layer is not output");
        for(int i=0;i<getNumOfNeurons();i++){
            if(i==answer-1){
                _neurons[i]->getError() = (1.0-_neurons[i]->getValue())*
                        func.useDerivative(_neurons[i]->getValue());
            } else {
                _neurons[i]->getError() = (-_neurons[i]->getValue())*
                        func.useDerivative(_neurons[i]->getValue());
            }
        }
    }

    int getNumOfNeurons(){
        return _neurons.size();
    }
    Neuron& operator()(int i){
        return *(_neurons[i]);
    }

};



} // namespace s21

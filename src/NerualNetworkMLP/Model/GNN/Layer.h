#pragma once
#include "Neuron.h"
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
                sum+=(layer._neurons[j]->getValue()*_neurons[i]->getWeight(j));
            }
            _neurons[i]->getValue()=_func.use(sum);
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

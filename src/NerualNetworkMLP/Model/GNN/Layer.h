#pragma once
#include "Neuron.h"
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
    
};



} // namespace s21

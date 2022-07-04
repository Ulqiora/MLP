#pragma once
#include <memory>
//#include <omp.h>
#include "Neuron.h"
#include "../Dataset.h"
#include "../ActivateFunction.h"
namespace s21
{
class Layer{
private:
    std::vector<Neuron> _neurons;
    TypeLayer _type;

public:
    Layer(TypeLayer thisLayer, TypeLayer previousLayer);
    void setNeuronsByImagePixels(const Image& image);
    int getIndexOfMaxValueNeuron();
    void calcForForwardPropagation(Layer& layer);
    void calcForBackPropagation(Layer& layerPrev);
    void calcForBackPropagation(const int answer);
    void updateWeightNeurons(Layer& layerPrev,double lr);
    int getNumOfNeurons();
    Neuron operator ()(int i)const;
    void printLayer(std::ofstream& file){
        for(auto& neuron:_neurons){
            neuron.printNeuron(file);
        }
    }
    void loadWeights(std::ifstream& file){
        for(auto& neuron:_neurons){
            neuron.loadWeights(file);
        }
    }
};



} // namespace s21

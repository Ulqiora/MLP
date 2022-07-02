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

    void updateWeightNeurons(Layer& layerPrev);
    int getNumOfNeurons();
    Neuron operator ()(int i)const;
    std::vector<Neuron>::iterator begin();
    std::vector<Neuron>::iterator end();
    std::vector<Neuron>::const_iterator cbegin();
    std::vector<Neuron>::const_iterator cend();
};



} // namespace s21

#pragma once
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <QRandomGenerator>
#include "vector"
#include "../constantValues.h"
#include "../ActivateFunction.h"

namespace s21{
class Neuron{
private:
    double _value;
    double _error;
    double _bios;
    std::vector<double> _weights;
public:
    ActivateFunction _func;
    explicit Neuron(TypeLayer numOfWeights,typeFunction type=typeFunction::SIGMOIND);
    void forwardPropagation(const std::vector<Neuron>& inputNeurons);
    void forwardPropagation(int i=0);
    void backPropagation(const std::vector<Neuron>& inputNeurons);
    void backPropagation(int answer);
    int getNumOfWeights();
    double value()const;
    void setValue(double other);
    double error()const;
    void setError(double other);
    double bios();
    void addToBios(double other);
    double weight(int i)const;
    void addToWeight(double other,int i);
};

}    //    namespace s21

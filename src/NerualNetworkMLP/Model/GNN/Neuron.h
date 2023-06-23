#pragma once
#include <exception>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../ActivateFunction.h"
#include "../constantValues.h"

namespace s21 {
class Neuron {
 private:
    double _value;
    double _sum;
    double _error;
    double _bias;
    std::vector<double> _weights;

 public:
    ActivateFunction _func;
    explicit Neuron(TypeLayer numOfWeights, typeFunction type = typeFunction::SIGMOIND);
    void forwardPropagation(const std::vector<Neuron>& inputNeurons);
    void forwardPropagation(int i = 0);
    void backPropagation(const std::vector<Neuron>& inputNeurons);
    void backPropagation(int answer);
    int getNumOfWeights();
    double value() const;
    void setValue(double other);
    double sum() const;
    double error() const;
    void setError(double other);
    double bios();
    void calcToEditBias(double lr);
    double weight(int i) const;
    void calcToEditWeight(double index, double lr, double valueNeuronOfPrevLayer);
    void printNeuron(std::ofstream& file) {
        file << _bias << ' ';
        for (const auto& i : _weights) {
            file << i << ' ';
        }
        file << '\n';
    }
    void loadWeights(std::ifstream& file) {
        file >> _bias;
        if (file.peek() == ' ') file.ignore();
        for (auto& i : _weights) {
            file >> i;
            if (file.peek() == ' ') file.ignore();
        }
        file.ignore();
    }
};

}  //    namespace s21

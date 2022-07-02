#pragma once
#include "Layer.h"
#include "../Dataset.h"
#include "../ActivateFunction.h"
namespace s21
{
class GraphNerualNetwork{
private:
    std::vector<Layer> _layers;
    unsigned int _numOfHiddenLayers;
    std::vector<double> _accuracyHistory;
private:
    bool isCorrectPrediction(int answer);
    void forwardPropagation(const Image& image);
    void backPropagation(int answer);
    void updateWeight();
    void test(Dataset& date);
public:
    GraphNerualNetwork(unsigned int numHiddenLayers);
    void train(Dataset& date,Dataset&  dateTest,int epoch);

};
} // namespace s21

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
public:
    GraphNerualNetwork(unsigned int numHiddenLayers);
    void train(Dataset& date,Dataset&  dateTest,int epoch);
    void test(Dataset& date);
    Layer& getLayer(int i);
    std::vector<double>& getAccuracyHistory();
};
} // namespace s21

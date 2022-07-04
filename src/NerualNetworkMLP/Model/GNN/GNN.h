#pragma once
#include <ostream>
#include "Layer.h"
#include "../Dataset.h"
#include "../ActivateFunction.h"
namespace s21
{
class GraphNerualNetwork{
private:
    double lr=0.25;
    std::vector<Layer> _layers;
    unsigned int _numOfHiddenLayers;
    std::vector<double> _accuracyHistory;
private:
    bool isCorrectPrediction(int answer);
    void forwardPropagation(const Image& image);
    void backPropagation(int answer);
    void updateWeight(int epoch);
public:
    GraphNerualNetwork(unsigned int numHiddenLayers);
    void train(Dataset& date,Dataset&  dateTest,int epoch);
    void test(Dataset& date);
    void saveWeights(std::string filename);
    void loadWeights(std::string filename);
};
} // namespace s21

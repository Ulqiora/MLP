#pragma once
#include <ostream>
#include "Layer.h"
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
    void train(Dataset& data,Dataset&  dataTest, double percentTestData,int numOfEpoch);
    Metrics test(Dataset& data, double percentTestData);
    void saveWeights(std::string filename);
    void loadWeights(std::string filename);
    void crossValidate(Dataset& dateTrain,int k);
    void setLearningRate(double value);
};
} // namespace s21

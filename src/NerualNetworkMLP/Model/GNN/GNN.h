#pragma once
#include <ostream>
#include "Layer.h"
#include "../INerualNetwork.h"
namespace s21
{
class GraphNerualNetwork:public INerualNetwork{
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
    void train(Dataset& data,Dataset&  dataTest, double percentTestData,int numOfEpoch)override;
    Metrics test(Dataset& data, double percentTestData)override;
    void saveWeights(std::string filename)override;
    void loadWeights(std::string filename)override;
    void crossValidate(Dataset& dateTrain,int k)override;
    void setLearningRate(double value)override;
};
} // namespace s21

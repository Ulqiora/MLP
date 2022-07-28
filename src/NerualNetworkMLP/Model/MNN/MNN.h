#pragma once
#include "../ActivateFunction.h"
#include "../INerualNetwork.h"
#include "../Dataset.h"

namespace s21 {
class MatrixNerualNetwork : public INerualNetwork {
 private:
    double lr = 0.25;
    unsigned int _numOfHiddenLayers;
    ActivateFunction _func;
    std::vector<Matrix> _neuronWeightMat;
    std::vector<Matrix> _biosWeightMat;
    std::vector<Matrix> _biosErrors;
    std::vector<Matrix> _valueNeruals;
    std::vector<Matrix> _valueErrors;
    std::vector<double> _accuracyHistory;
    Metrics _metrics;

 private:
    void setWeightMatrix();
    void setBiosMatrix();
    void forwardPropagation(const Image& image);
    void backPropagation(int answer);
    void updateWeight(int numOfEpoch);
    void calcSolutions(Metrics& metrics,int answer);
    bool isCorrectPrediction(int answer);
    int findMaxIndex(){
        int indexMax=0;
        for(int i=1;i<static_cast<int>(TypeLayer::OUTPUT);i++){
            if(_valueNeruals.back()(i,0)>_valueNeruals.back()(indexMax,0)){
                indexMax=i;
            }
        }
        return indexMax;
    }
 public:
    MatrixNerualNetwork(unsigned int numHiddenLayers);
    void train(Dataset& data, Dataset& dataTest, double percentTestData, int numOfEpoch) override;
    double test(Dataset& data, double percentTestData) override;
    void saveWeights(std::string filename) override;
    void loadWeights(std::string filename) override;
    void crossValidate(Dataset& dateTrain, int k) override;
    void setLearningRate(double value) override{
        lr=value;
    }
    Metrics metrics()override{
        return _metrics;
    }
    virtual std::vector<double> getAccuracyHistory() override{
        return _accuracyHistory;
    }
    virtual int predict(const Image& image)override{
        forwardPropagation(image);
        return findMaxIndex();
    }
};
}  // namespace s21

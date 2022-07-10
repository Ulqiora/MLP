#pragma once 
#include "Dataset.h"
#include "Metrics.h"
namespace s21{
class INerualNetwork{
public:
    virtual void train(Dataset& data,Dataset&  dataTest, double percentTestData,int numOfEpoch) = 0;
    virtual double test(Dataset& data, double percentTestData) = 0;
    virtual void saveWeights(std::string filename) = 0;
    virtual void loadWeights(std::string filename) = 0;
    virtual void crossValidate(Dataset& dateTrain,int k) = 0;
    virtual void setLearningRate(double value) = 0;
    virtual std::vector<double> getAccuracyHistory()=0;
    virtual Metrics metrics() = 0;
};
}

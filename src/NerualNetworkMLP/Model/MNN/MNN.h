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
 public:
    MatrixNerualNetwork(unsigned int numHiddenLayers);
    void train(Dataset& data, Dataset& dataTest, double percentTestData, int numOfEpoch) override;
    double test(Dataset& data, double percentTestData) override;
    void saveWeights(std::string filename) override{
        std::ofstream file(filename);
        if(!file.is_open())
            throw std::invalid_argument("This file can't be opened!");
        file<<_numOfHiddenLayers<<'\n';
        auto biosWeightsMat=_biosWeightMat.begin();
        for(auto& weightsMat:_neuronWeightMat){
            for(int j=0;j<weightsMat.getRows();j++){
                file<<(*biosWeightsMat)(j,0)<<' ';
                for(int k=0;k<weightsMat.getCols();k++){
                    file<<weightsMat(j,k)<<' ';
                }
                file<<'\n';
            }
        }
    }
    void loadWeights(std::string filename) override{
        std::ifstream file(filename);
        unsigned int numOflayers=0;
        if(!file.is_open()){
            throw std::invalid_argument("This file can't be opened!");
        }
        file>>numOflayers;
        if(numOflayers!=_numOfHiddenLayers)
            throw std::invalid_argument("This file is not for nerual network for!");
        if(file.peek()=='\n') file.ignore();
        double temp=0.0;
        for(int i=0;i<static_cast<int>(_neuronWeightMat.size());i++){
            for(int j=0;j<_neuronWeightMat[i].getRows();j++){
                file>>temp;
                _biosWeightMat[i].setValue(j,0,temp);
                if (file.peek()==' ')file.ignore();
                for(int k=0;k<_neuronWeightMat[i].getCols();++k){
                    file>>temp;
                    _neuronWeightMat[i].setValue(j,k,temp);
                    if(file.peek()==' ') file.ignore();
                }
                file.ignore();
            }
        }
    }
    void crossValidate(Dataset& dateTrain, int k) override{}
    void setLearningRate(double value) override{}
    Metrics metrics()override{
        return _metrics;
    }
    virtual std::vector<double> getAccuracyHistory() override{
        return _accuracyHistory;
    }
    virtual int predict(const Image& image)override{}
};
}  // namespace s21

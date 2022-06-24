#pragma once
#include "vector"
#include "../ConstantValues.h"
namespace s21{
class Neuron{
private:
    double _value;
    std::vector<double> _weights;

public:
    Neuron(TypeLayer numOfWeights):_value(0),_weights(static_cast<int>(numOfWeights)){
        int numOfWeightsInt=static_cast<int>(numOfWeights);
        for(int i=0;i<numOfWeightsInt;++i){
            _weights[i]=arc4random_uniform(100)/100;
        }
    }
    double getValue();
    void setValue(const double& other);
    void updateWeight();
};

}    //    namespace s21

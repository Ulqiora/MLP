#pragma once
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <QRandomGenerator>
#include "vector"
#include "../constantValues.h"
namespace s21{
class Neuron{
private:
    double _value;
    double _error;
    std::vector<double> _weights;

public:
    Neuron(TypeLayer numOfWeights):_value(0),_weights(static_cast<int>(numOfWeights)){
        int numOfWeightsInt=static_cast<int>(numOfWeights);
        for(int i=0;i<numOfWeightsInt;++i){
            _weights[i]=QRandomGenerator::global()->bounded(0,100)/100.0;
        }
    }
    int getNumOfWeights(){
        return _weights.size();
    }
    double& getValue(){
        return _value;
    }
    double& getWeight(int i){
        return _weights[i];
    }
    double& getError(){
        return _error;
    }
};

}    //    namespace s21

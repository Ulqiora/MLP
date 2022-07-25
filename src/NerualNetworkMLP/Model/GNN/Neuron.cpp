#include "Neuron.h"
namespace s21 {
Neuron::Neuron(TypeLayer numOfWeights,typeFunction type) : _value(0), _weights(static_cast<int>(numOfWeights)),_func(type) {
    for (auto& i : _weights) {
//        i = QRandomGenerator::global()->bounded(-100, 100) / 100.0;
        i=0;
    }
}

void Neuron::forwardPropagation(const std::vector<Neuron> &inputNeurons)
{
    _sum=_bias;
    auto weightIterator=_weights.cbegin();
    for(const auto& neuron:inputNeurons){
        _sum+=neuron._value*(*weightIterator);
        ++weightIterator;
    }
    _value=_func.use(_sum);
}

void Neuron::backPropagation(int answer)
{
    _error=(_value-answer);

}

int Neuron::getNumOfWeights() { return _weights.size(); }

double Neuron::value() const { return _value; }

void Neuron::setValue(double value)
{
    _value=value;
}

double Neuron::sum()const {
    return _sum;
}

double Neuron::error() const { return _error; }

void Neuron::setError(double sumError)
{
    _error=sumError;
}

double Neuron::bios(){
    return _bias;
}
void Neuron::calcToEditBias(double lr){
    qDebug()<<-_error*_func.useDerivative(_value)*lr;
    _bias-=_error*_func.useDerivative(_value)*lr;
}

double Neuron::weight(int i)const{
    return _weights[i];
}
void Neuron::calcToEditWeight(double index,double lr,double valueNeuronOfPrevLayer){
    qDebug()<<-lr*valueNeuronOfPrevLayer*_func.useDerivative(_value)*_error;
    _weights[index]-=lr*valueNeuronOfPrevLayer*_func.useDerivative(_value)*_error;
}

}  // namespace s21

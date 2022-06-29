#include "Neuron.h"
namespace s21 {
Neuron::Neuron(TypeLayer numOfWeights,typeFunction type) : _value(0), _weights(static_cast<int>(numOfWeights)),_func(type) {
    for (auto& i : _weights) {
        i = QRandomGenerator::global()->bounded(0, 100) / 100.0;
    }
}

void Neuron::forwardPropagation(const std::vector<Neuron> &inputNeurons)
{
    double sum=0.0;
    auto weightIterator=_weights.cbegin();
    for(auto& neuron:inputNeurons){
        sum+=neuron._value*(*weightIterator);
        ++weightIterator;
    }
    _value=_func.use(sum);
}

void Neuron::backPropagation(int answer)
{
        _error=(answer-_value)*_func.useDerivative(_value);
}

int Neuron::getNumOfWeights() { return _weights.size(); }

double Neuron::value() const { return _value; }

void Neuron::setValue(double other)
{
    _value=other;
}

double Neuron::error() const { return _error; }

void Neuron::setError(double sumError)
{
    _error=sumError;
}
double Neuron::weight(int i)const{
    return  _weights[i];
}
void Neuron::setWeight(double other,int i){
    _weights[i]=other;
}

}  // namespace s21

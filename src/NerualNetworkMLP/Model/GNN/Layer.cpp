#include "Layer.h"

namespace s21 {
Layer::Layer(TypeLayer thisLayer, TypeLayer previousLayer) : _type(thisLayer) {
    int numOfNeurons = static_cast<int>(_type);
    for (int i = 0; i < numOfNeurons; i++) {
        _neurons.push_back(Neuron(previousLayer));
    }
}

void Layer::calcSolutions(Metrics& metrics, int answer) {
    if (_type != TypeLayer::OUTPUT) throw std::invalid_argument("This layer is not output!");
    if (answer == 0) {
        if (getIndexOfMaxValueNeuron() == 0) {
            metrics.solutions.tp++;
        } else {
            metrics.solutions.fp++;
        }
    } else {
        if (getIndexOfMaxValueNeuron() != 0) {
            metrics.solutions.tn++;
        } else {
            metrics.solutions.fn++;
        }
    }
}

void Layer::setNeuronsByImagePixels(const Image& image) {
    if (_type != TypeLayer::INPUT) throw std::invalid_argument("Error, It is not input layer");
    auto imageIterator = image.cbegin();
    for (auto& neuron : _neurons) {
        neuron.setValue(*imageIterator);
        ++imageIterator;
    }
}

int Layer::getIndexOfMaxValueNeuron() {
    int numOfNeurons = _neurons.size();
    int indexMax = 0;
    for (int i = 0; i < numOfNeurons; i++) {
        if (_neurons[i].value() > _neurons[indexMax].value()) {
            indexMax = i;
        }
    }
    return indexMax;
}

void Layer::calcForForwardPropagation(const Layer& layerPrev) {
    for (Neuron& neuron : _neurons) {
        neuron.forwardPropagation(layerPrev._neurons);
    }
}

void Layer::calcForBackPropagation(const Layer& layerPrev) {
    int numOfNeurons = getNumOfNeurons();
    for (int i = 0; i < numOfNeurons; i++) {
        double sum = 0.0;
        for (const auto& neuron : layerPrev._neurons) {
            sum += (neuron.error() * neuron.weight(i));
        }
        _neurons[i].setError(sum);
    }
}

void Layer::calcForBackPropagation(const int answer) {
    if (_type != TypeLayer::OUTPUT) throw std::invalid_argument("Error layer, this layer is not output");
    int i = 0;
    for (auto neuron = _neurons.begin(); neuron != _neurons.end(); ++neuron) {
        neuron->backPropagation(i == answer);
        ++i;
    }
}

void Layer::updateWeightNeurons(const Layer& layerPrev, double lr) {
    for (auto& neuron : _neurons) {
        int j = 0;
        for (auto& neuronPrevLayer : layerPrev._neurons) {
            neuron.calcToEditWeight(j, lr, neuronPrevLayer.value());
            ++j;
        }
        neuron.calcToEditBias(lr);
    }
}

int Layer::getNumOfNeurons() { return _neurons.size(); }
};  // namespace s21

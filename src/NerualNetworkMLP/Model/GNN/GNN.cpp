#include "GNN.h"

namespace s21 {
bool GraphNerualNetwork::isCorrectPrediction(int answer) {
    return answer == _layers.back().getIndexOfMaxValueNeuron();
}

void GraphNerualNetwork::forwardPropagation(const Image& image) {
    _layers.front().setNeuronsByImagePixels(image);
    for(unsigned int i=1;i<_numOfHiddenLayers+2;++i){
        _layers[i].calcForForwardPropagation(_layers[i-1]);
    }
}

void GraphNerualNetwork::backPropagation(int answer) {
    _layers.back().calcForBackPropagation(answer);
    for(unsigned int i=_numOfHiddenLayers;i>0;--i){
        _layers[i].calcForBackPropagation(_layers[i+1]);
    }
}

void GraphNerualNetwork::updateWeight() {
    for(int i=_numOfHiddenLayers+1;i>0;--i){
        _layers[i].updateWeightNeurons(_layers[i-1]);
    }
}

GraphNerualNetwork::GraphNerualNetwork(unsigned int numHiddenLayers) : _numOfHiddenLayers(numHiddenLayers){
    _layers.push_back(Layer(TypeLayer::INPUT, TypeLayer::NA));
    _layers.push_back(Layer(TypeLayer::HIDDEN, TypeLayer::INPUT));
    for (unsigned int i = 0; i < _numOfHiddenLayers - 1; ++i) {
        _layers.push_back(Layer(TypeLayer::HIDDEN, TypeLayer::HIDDEN));
    }
    _layers.push_back(Layer(TypeLayer::OUTPUT, TypeLayer::HIDDEN));
}

void GraphNerualNetwork::train(Dataset& date, int epoch) {
    _accuracyHistory.clear();
    for (int i = 0; i < epoch; i++) {
        int accuracy = 0, dataSize = date.getSize();
        for (int j = 0; j < dataSize; ++j) {
            forwardPropagation(date.getImage(j));
            if (isCorrectPrediction(date.getAnswer(j))) {
                                    qDebug()<<j<<":  1";
                ++accuracy;
            } else {
                                    qDebug()<<j<<":  0";
            }
            backPropagation(date.getAnswer(j));
            updateWeight();
        }
        double percent = static_cast<double>(accuracy) / date.getSize() * 100.0;
        _accuracyHistory.push_back(percent);
        qDebug() << i + 1 << "     " << accuracy;
    }
    qDebug() << getAccuracyHistory();
}

void GraphNerualNetwork::test(Dataset& date) {
    int accuracy = 0;
    for (int j = 0; j < date.getSize(); ++j) {
        forwardPropagation(date.getImage(j));
        if (isCorrectPrediction(date.getAnswer(j))) {
            ++accuracy;
            //                    qDebug()<< j <<"   1";
        } else {
            //                    qDebug()<< j <<"   0";
        }
    }
    double percent = static_cast<double>(accuracy) / date.getSize() * 100.0;
    qDebug() << "test: accuracy=" << percent;
}

Layer& GraphNerualNetwork::getLayer(int i) { return _layers[i]; }

std::vector<double>& GraphNerualNetwork::getAccuracyHistory() { return _accuracyHistory; }
}  // namespace s21

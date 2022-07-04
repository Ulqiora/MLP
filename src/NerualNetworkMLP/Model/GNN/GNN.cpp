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

void GraphNerualNetwork::updateWeight(int epoch) {
//    qDebug()<<"LR="<<lr/epoch;
    for(int i=_numOfHiddenLayers+1;i>0;--i){
        _layers[i].updateWeightNeurons(_layers[i-1],lr/epoch);
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

void GraphNerualNetwork::train(Dataset& date,Dataset&  dateTest, int epoch) {
    for (int i = 0; i < epoch; i++) {
        qDebug() << i + 1 <<"epoch";
        qDebug()<<"LR ="<<lr/epoch;
        auto begin = std::chrono::steady_clock::now();
        int dataSize = date.getSize();
        for (int j = 0; j < dataSize; ++j) {
            forwardPropagation(date.getImage(j));
//            qDebug() <<"forwardPropagation-yes";
            backPropagation(date.getAnswer(j));
//            qDebug() <<"backPropagation-yes";
            updateWeight(i+1);
//            qDebug() <<"updateWeight-yes";
//            qDebug() << "weight" << _layers[3].begin()->weight(0);
//            qDebug() << "error" << _layers[3].begin()->error();
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
        qDebug() <<"Train runtime=" << elapsed_ms.count() << " s\n";
        test(dateTest);
        auto end2 = std::chrono::steady_clock::now();
        auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::seconds>(end2 - end);
        qDebug() <<"Test runtime=" << elapsed_ms2.count() << " s\n";
    }
}

void GraphNerualNetwork::test(Dataset& date) {
    int accuracy = 0;
    for (int j = 0; j < date.getSize(); ++j) {
        forwardPropagation(date.getImage(j));
        accuracy+=isCorrectPrediction(date.getAnswer(j));
    }
    double percent = static_cast<double>(accuracy) / date.getSize() * 100.0;
    qDebug() << "test: percent  =" << percent;
    qDebug() << "      accuracy =" << accuracy;
}

void GraphNerualNetwork::saveWeights(std::string filename){
    std::ofstream file(filename);
    if(!file.is_open())
        throw std::invalid_argument("This file can't be opened!");
    file<<_numOfHiddenLayers<<'\n';
    for(unsigned int i=1;i<=_numOfHiddenLayers+1;++i){
        _layers[i].printLayer(file);
    }
    file.close();
}

void GraphNerualNetwork::loadWeights(std::string filename){
    std::ifstream file(filename);
    unsigned int numOflayers=0;
    if(!file.is_open()){
        throw std::invalid_argument("This file can't be opened!");
    }
    file>>numOflayers;
    if(numOflayers!=_numOfHiddenLayers)
        throw std::invalid_argument("This file is not for nerual network for!");
    if(file.peek()=='\n') file.ignore();
    for(unsigned int i=1;i<=_numOfHiddenLayers+1;++i){
        _layers[i].loadWeights(file);
    }
}

}  // namespace s21

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

void GraphNerualNetwork::train(Dataset& data,Dataset&  dataTest, double percentTestData,int epoch) {
    _accuracyHistory.clear();
    for (int i = 0; i < epoch; i++) {
        int dataSize = data.getSize();
        for (int j = 0; j < dataSize; ++j) {
            forwardPropagation(data.getImage(j));
            backPropagation(data.getAnswer(j));
            updateWeight(i+1);
        }
        test(dataTest,percentTestData);
    }
}

Metrics GraphNerualNetwork::test(Dataset& date, double percentTestData) {
    Metrics metrics;
    int accuracy=0;
    int dataSize=date.getSize()*percentTestData;
    for (int j = 0; j < dataSize; ++j) {
        forwardPropagation(date.getImage(j));
        accuracy+=isCorrectPrediction(date.getAnswer(j));
        _layers.back().calcSolutions(metrics,date.getAnswer(j));
    }
    metrics.accuracy =static_cast<double>(accuracy) / date.getSize() * 100.0;
    metrics.precision=metrics.solutions.tp/(metrics.solutions.tp+metrics.solutions.fp);
    metrics.recall=metrics.solutions.tp/(metrics.solutions.tp+metrics.solutions.fn);
    metrics.fMeasure=2*(metrics.precision*metrics.recall)/(metrics.precision*metrics.recall);
    return metrics;
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

void GraphNerualNetwork::crossValidate(Dataset& dataTrain,int k)
{
    _accuracyHistory.clear();
    int sizeDataTrain=dataTrain.getSize();
    int stepByFor=sizeDataTrain/k;
    for(int i=0;i<k;++k){
        int start=stepByFor*i;
        int end=stepByFor*(i+1);
        for(int indexForData=start;indexForData<end;++indexForData){
            forwardPropagation(dataTrain.getImage(indexForData));
            backPropagation(dataTrain.getAnswer(indexForData));
            updateWeight(1);
        }
        int accuracy=0;
        for(int indexForData=0;indexForData<start;++indexForData){
            forwardPropagation(dataTrain.getImage(indexForData));
            accuracy+=isCorrectPrediction(dataTrain.getAnswer(indexForData));
        }
        for(int indexForData=end;indexForData<sizeDataTrain;++indexForData){
            forwardPropagation(dataTrain.getImage(indexForData));
            accuracy+=isCorrectPrediction(dataTrain.getAnswer(indexForData));
        }
        _accuracyHistory.push_back(accuracy/(sizeDataTrain-stepByFor));
    }
}

}  // namespace s21

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
        _layers[i].updateWeightNeurons(_layers[i-1],lr/sqrt(epoch));
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
    _metrics.reset();
    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < epoch; i++) {
        int dataSize = data.getSize();
        for (int j = 0; j < dataSize; ++j) {
            // std::cout<<j<<'\n';
            forwardPropagation(data.getImage(j));
            backPropagation(data.getAnswer(j));
            updateWeight(i+1);
        }
        _accuracyHistory.push_back(test(dataTest,percentTestData));
        std::cout<<_accuracyHistory.back()<<'\n';
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    _metrics.seconds=elapsed_ms.count();
    _metrics.accuracy =(_metrics.solutions.tp+_metrics.solutions.tn)/(data.getSize()*epoch);
    _metrics.precision=_metrics.solutions.tp/(_metrics.solutions.tp+_metrics.solutions.fp);
    _metrics.recall=_metrics.solutions.tp/(_metrics.solutions.tp+_metrics.solutions.fn);
    _metrics.fMeasure=2*(_metrics.precision*_metrics.recall)/(_metrics.precision*_metrics.recall);
}

double GraphNerualNetwork::test(Dataset& data, double percentTestData) {
    int dataSize=data.getSize()*percentTestData;
    int accuracy=0;
    for (int j = 0; j < dataSize; ++j) {
        // std::cout<<j<<'\n';
        forwardPropagation(data.getImage(j));
        accuracy+=isCorrectPrediction(data.getAnswer(j));
        _layers.back().calcSolutions(_metrics,data.getAnswer(j));
    }
    return static_cast<double>(accuracy)/dataSize;
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

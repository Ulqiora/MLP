#pragma once
#include "Layer.h"
namespace s21
{
class GraphNerualNetwork{
private:
    std::vector<Layer> _layers;
    unsigned int _hiddenLayers;
public:
    GraphNerualNetwork(unsigned int numHiddenLayers):_layers(0),_hiddenLayers(numHiddenLayers){
        _layers.push_back(Layer(TypeLayer::INPUT,TypeLayer::NA));
        _layers.push_back(Layer(TypeLayer::HIDDEN,TypeLayer::INPUT));
        for(unsigned int i=0;i<_hiddenLayers-1;++i){
            _layers.push_back(Layer(TypeLayer::HIDDEN,TypeLayer::HIDDEN));
        }
        _layers.push_back(Layer(TypeLayer::OUTPUT,TypeLayer::HIDDEN));
    }
};
} // namespace s21

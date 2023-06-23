#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once
#include <QFileDialog>
#include <vector>

#include "../Model/Dataset.h"
#include "../Model/GNN/GNN.h"
#include "../Model/MNN/MNN.h"

namespace s21 {
class Controller {
 public:
    Controller();
    ~Controller();
    s21::Dataset& getDate();
    s21::Dataset& getDateTest();
    void setMatrixNetwork(int layers);
    void setGraphNetwork(int layers);
    void trainNetwork(float percentage, int epoch);
    void crossValNetwork(int crossCoef);
    void saveNetworkWeights();
    void loadNetworkWeights(int networkType, int layers);
    void testProgram(double percent);
    char getPredict(const Image& image);
    std::vector<double> getHistory();
    Metrics getMetrics();
    Controller(const Controller& other) = delete;
    void operator=(const Controller& other) = delete;

 private:
    s21::Dataset date, dateTest;
    s21::INerualNetwork* nerualNetwork;
};
}  // namespace s21

#endif  // CONTROLLER_H

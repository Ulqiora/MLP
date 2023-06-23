#include "Controller.h"

namespace s21 {
Controller::Controller() : nerualNetwork(new s21::GraphNerualNetwork(2)) {}

Controller::~Controller() {}

s21::Dataset& Controller::getDate() { return date; }

s21::Dataset& Controller::getDateTest() { return dateTest; }

void Controller::setMatrixNetwork(int layers) {
    if (layers > 0) {
        delete nerualNetwork;
        nerualNetwork = new s21::MatrixNerualNetwork(layers);
    }
}

void Controller::setGraphNetwork(int layers) {
    if (layers > 0) {
        delete nerualNetwork;
        nerualNetwork = new s21::GraphNerualNetwork(layers);
    }
}

void Controller::trainNetwork(float percentage, int epoch) {
    try {
        std::string str = QFileDialog::getOpenFileName().toStdString();
        std::string str1 = QFileDialog::getOpenFileName().toStdString();
        if (str != "" && str1 != "") {
            date.setDate(str);
            dateTest.setDate(str1);
            if (date.getSize() > 0) {
                nerualNetwork->train(date, dateTest, percentage, epoch);
            }
        }
    } catch (const std::exception& e) {
        throw e;
    }
}

void Controller::crossValNetwork(int crossCoef) {
    try {
        std::string str = QFileDialog::getOpenFileName().toStdString();
        if (str != "") {
            date.setDate(str);
            if (date.getSize() > 0) {
                nerualNetwork->crossValidate(date, crossCoef);
            }
        }
    } catch (const std::exception& e) {
        throw e;
    }
}

void Controller::saveNetworkWeights() {
    try {
        std::string str = QFileDialog::getSaveFileName().toStdString();
        if (str != "") {
            nerualNetwork->saveWeights(str);
        }
    } catch (const std::exception& e) {
        throw e;
    }
}

void Controller::loadNetworkWeights(int networkType, int layers) {
    try {
        delete nerualNetwork;
        if (networkType == 0) {
            nerualNetwork = new s21::GraphNerualNetwork(layers);
        } else {
            nerualNetwork = new s21::MatrixNerualNetwork(layers);
        }
        std::string str = QFileDialog::getOpenFileName().toStdString();
        if (str != "") {
            nerualNetwork->loadWeights(str);
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("Error file");
    }
}

void Controller::testProgram(double percent) {
    std::string str = QFileDialog::getOpenFileName().toStdString();
    if (str != "") {
        dateTest.setDate(str);
        nerualNetwork->test(dateTest, percent);
    }
}

char Controller::getPredict(const Image& image) { return nerualNetwork->predict(image) + 'A'; }

std::vector<double> Controller::getHistory() { return nerualNetwork->getAccuracyHistory(); }

Metrics Controller::getMetrics() { return nerualNetwork->metrics(); }

}  // namespace s21

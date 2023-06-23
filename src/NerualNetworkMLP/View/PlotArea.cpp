#include "PlotArea.h"

#include "ui_PlotArea.h"

PlotArea::PlotArea(QWidget* parent) : QWidget(parent), ui(new Ui::PlotArea) {
    ui->setupUi(this);
    ui->widget->xAxis->setRange(0, 5);
    ui->widget->yAxis->setRange(-0.6, 1);
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

void PlotArea::drawPlot(const std::vector<double>& plotCoord) {
    QVector<double> coord = QVector<double>(plotCoord.begin(), plotCoord.end());
    QVector<double> errors;
    QVector<double> indexes;
    for (unsigned int j = 0; j < plotCoord.size(); j++) {
        errors.push_back(1.0 - plotCoord.data()[j]);
    }
    for (unsigned int i = 1; i <= plotCoord.size(); i++) {
        indexes.push_back(i);
    }
    ui->widget->xAxis->setRange(0, 5);
    ui->widget->yAxis->setRange(-0.6, 1);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(indexes, coord);
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QColorConstants::Red);
    ui->widget->graph(1)->addData(indexes, errors);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

PlotArea::~PlotArea() { delete ui; }

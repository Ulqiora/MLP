
#pragma once
#include <QWidget>

namespace Ui {
class PlotArea;
}

class PlotArea : public QWidget {
  Q_OBJECT

 public:
  explicit PlotArea(QWidget *parent = nullptr);
  ~PlotArea();
  void drawPlot(const std::vector<double> &plotCoord);

 private:
  Ui::PlotArea *ui;
};

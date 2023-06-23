#pragma once
#include <QDebug>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include <vector>

#include "mainwindow.h"

class DrawScene : public QWidget {
    Q_OBJECT
 public:
    explicit DrawScene(QWidget* parent = nullptr);
    void clearImage();
    QImage getPicture();
    void setPicture(const QImage& img);
    void setWindow(MainWindow* w) { window = w; }

 protected:
    void paintEvent(QPaintEvent* event) override;

 private:
    QImage picture;
    QPoint mousePos;
    Qt::MouseButton mButton;
    MainWindow* window;

 private:
    void mousePressEvent(QMouseEvent* mEvent) override;
    void mouseMoveEvent(QMouseEvent* mEvent) override;
    void mouseReleaseEvent(QMouseEvent* mEvent) override;
    void drawLine(const QPoint& end);
};

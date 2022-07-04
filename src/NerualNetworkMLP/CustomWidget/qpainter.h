#ifndef QPAINTER_H
#define QPAINTER_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QMouseEvent>

class QPainter : public QWidget
{
    Q_OBJECT

public:
    explicit QPainter(QWidget *parent = nullptr);

private:

private:
    void resizeEvent(QResizeEvent * event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};
#endif // QPAINTER_H

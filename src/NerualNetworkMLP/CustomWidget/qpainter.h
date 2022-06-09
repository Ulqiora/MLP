#ifndef QPAINTER_H
#define QPAINTER_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QMouseEvent>

class QPainter : public QWidget
{
    Q_OBJECT

//    int size = 1;
//    int w = 28*size;
//    int h = 28*size;
//    int scale = 20/size;

public:
    explicit QPainter(QWidget *parent = nullptr);

private:

//    QImage image_size;

//    float inputs[28*28];
//    float result[10];

//    float mx,my;
//    int mousePressed;


private:
    /* Переопределяем событие изменения размера окна
     * для пересчёта размеров графической сцены
     * */
//    void resizeEvent(QResizeEvent * event);

    // Для рисования используем события мыши
//    void mousePressEvent(QMouseEvent *e);
//    void mouseMoveEvent(QMouseEvent *e);
};
#endif // QPAINTER_H

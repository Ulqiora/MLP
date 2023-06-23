#ifndef SRC_NERUALNETWORKMLP_CUSTOMWIDGET_QPAINTER_H_
#define SRC_NERUALNETWORKMLP_CUSTOMWIDGET_QPAINTER_H_

#include <QMouseEvent>
#include <QResizeEvent>
#include <QTimer>
#include <QWidget>

class QPainter : public QWidget {
    Q_OBJECT

 public:
    explicit QPainter(QWidget *parent = nullptr);

 private:
 private:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};
#endif  // SRC_NERUALNETWORKMLP_CUSTOMWIDGET_QPAINTER_H_

#include "qpainter.h"

QPainter::QPainter(QWidget *parent): QWidget(parent)
{

}

//void QPainter::mousePressEvent(QMouseEvent *e)
//{
//    int key = 0;
//    if(e->buttons() == Qt::LeftButton) key = 1;
//    if(e->buttons() == Qt::RightButton) key = 2;
//    mx = e->position().x()/scale;
//    my = e->position().y()/scale;
//    mousePressed=key;
//}

#include "DrawScene.h"

DrawScene::DrawScene(QWidget* parent)
: QWidget{parent},
picture(QImage(QSize(280, 280), QImage::Format_RGB16)) {
    clearImage();
}

void DrawScene::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter myPainter(this);
    myPainter.drawImage(picture.rect(), picture);
}

void DrawScene::mousePressEvent(QMouseEvent* mEvent) {
    mButton = mEvent->button();
    if (mButton == Qt::LeftButton) {
        mousePos = mEvent->pos();
    }
}

void DrawScene::mouseMoveEvent(QMouseEvent* mEvent) {
    if (mButton == Qt::LeftButton) {
        drawLine(mEvent->pos());
    }
}

void DrawScene::mouseReleaseEvent(QMouseEvent* mEvent) {
    if (mEvent->button() == Qt::LeftButton) {
        window->getPredictDrawing();
    }
}

void DrawScene::drawLine(const QPoint& end) {
    QPainter linePainter(&picture);
    linePainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    linePainter.setRenderHint(QPainter::Antialiasing, true);
    linePainter.setPen(QPen(Qt::black, 30, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    linePainter.drawLine(mousePos, end);

    int corr = (30 / 2) + 2;
    update(QRect(mousePos, end).normalized().adjusted(-1 * corr, -1 * corr, corr, corr));

    mousePos = end;
}

void DrawScene::clearImage() {
    picture.fill(qRgb(255, 255, 255));
    update();
}

QImage DrawScene::getPicture() { return picture; }

void DrawScene::setPicture(const QImage& img) {
    picture = img;
    update();
}

#include "qothelloview.h"

QOthelloView::QOthelloView(QWidget* parent)
    : QGraphicsView(parent)
{
}

QOthelloView::QOthelloView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
{
}

void QOthelloView::mousePressEvent(QMouseEvent* event)
{
    QPoint point = event->pos();
    emit set_piece(&point);
}

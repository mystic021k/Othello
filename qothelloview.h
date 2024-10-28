#pragma once
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsView>

class QOthelloView :
    public QGraphicsView
{
    Q_OBJECT
signals:
    void set_piece(QPoint* pos);
public:
    QOthelloView(QWidget* parent);
    QOthelloView(QGraphicsScene* scene, QWidget* parent);
    void mousePressEvent(QMouseEvent* event);
};


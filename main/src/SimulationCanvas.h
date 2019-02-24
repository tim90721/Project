#ifndef SCANVAS
#define SCANVAS

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "Model.h"
#include "IPaintObservor.h"

class SimulationCanvas : public QWidget, IPaintObservor{
    Q_OBJECT

public:
    SimulationCanvas(QWidget *parent = 0, Model *model = 0);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void updateCanvas();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Model *model;
};

#endif

#include "SimulationCanvas.h"
//#include "Cell.h"
//#include "MacroCell.h"

// Constructor
// A canvas for painting
// parent: parent QWidget
// model: model for handle all things
SimulationCanvas::SimulationCanvas(QWidget *parent, Model *model) : 
    QWidget(parent){
    setStyleSheet("QWidget{background : white;}");
    setMouseTracking(true);
    this->model = model;
    model->registerPaintObservor(this);
}

// Mouse moving event
void SimulationCanvas::mouseMoveEvent(QMouseEvent *event){
    model->setMouseXY(event->x(), event->y());
}

// Mouse press event
void SimulationCanvas::mousePressEvent(QMouseEvent *event){
    model->setMousePressed(true);
    model->setMouseXY(event->x(), event->y());
}

// Mouse release event
void SimulationCanvas::mouseReleaseEvent(QMouseEvent *event){
    model->setMousePressed(false);
}

// Canvas painting event
void SimulationCanvas::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QWidget::paintEvent(event);

    painter.setBrush(QBrush(QColor(128, 128, 255, 128), Qt::SolidPattern));
    model->draw(painter);
}

// IPaintSubject notify IPaintObservor update canvas
void SimulationCanvas::updateCanvas(){
    update();
}

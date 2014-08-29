#include "drawarea.h"

DrawArea::DrawArea(QWidget* parent) :
    QWidget(parent)
{
    //Make the background white
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    //Start the line size at 0
    lineXSize = lineYSize = 0;
}

DrawArea::~DrawArea()
{
}

QSize DrawArea::minimumSizeHint() const
{
    return QSize(WIDTH, HEIGHT);
}

QSize DrawArea::sizeHint() const
{
    return QSize(WIDTH, HEIGHT);
}

void DrawArea::draw(int size)
{
    lineXSize = lineYSize = size;
    this->update();
}

void DrawArea::paintEvent(QPaintEvent * /*event*/)
{
    //Create the painter
    QPainter painter(this);
    //Set up the pen for the painter
    QPen pen(Qt::black, 3);
    painter.setPen(pen);
    //Enable antialiasing
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawLine(QPoint(0, 0), QPoint(lineXSize, lineYSize));
}

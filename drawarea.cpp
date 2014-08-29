#include "drawarea.h"

DrawArea::DrawArea(QWidget* parent) :
    QWidget(parent)
{
    //Make the background white
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    //Set the size of the draw area
    this->setMinimumSize(WIDTH, HEIGHT);
    this->setMaximumSize(WIDTH, HEIGHT);

    //Set endOfLastLine and endOfNewLine to (WIDTH/2), (HEIGHT/2) so it starts drawing from the middle of the draw area
    endOfLastLine = QPoint((WIDTH/2), (HEIGHT/2));
    endOfNewLine = QPoint((WIDTH/2), (HEIGHT/2));
}

DrawArea::~DrawArea()
{
}

void DrawArea::draw(int direction, int distance)
{
    //Change the angle so that if the user entered 0 degrees, the line would go straight ahead.
    direction -= 90;
    //Convert the direction from degrees to radians
    float dirInRad = (direction * (PI / 180));
    //Find the distance the line needs to travel horizontally
    int horDist = (distance * cos(dirInRad));
    //Find the distance the line needs to travel vertically
    int verDist = (distance * sin(dirInRad));

    qDebug() << dirInRad << horDist << verDist;

    //The x of the new line will be the horizontal distance traveled plus the x of the end of the last line
    endOfNewLine.setX(horDist + endOfLastLine.x());
    //The y of the new line will be the vertical distance traveled plus the y of the end of the last line
    endOfNewLine.setY(verDist + endOfLastLine.y());

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

    //The end of the last line will be the beggining of the new line
    painter.drawLine(endOfLastLine, endOfNewLine);
}

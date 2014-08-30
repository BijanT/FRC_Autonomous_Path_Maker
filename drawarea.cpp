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

    //Make the first "line" in the lines vector a point in the middle of the draw area
    lines.push_back(PathLine(QPoint(WIDTH/2, HEIGHT/2), QPoint(WIDTH/2, HEIGHT/2)));

}

DrawArea::~DrawArea()
{
    lines.clear();
}

void DrawArea::draw(int direction, int distance)
{
    //Initialize all the variables used in this function
    float dirInRad;
    int horDist, verDist;
    PathLine lastLine;
    PathLine newLine;
    QPoint start, end;

    //Change the angle so that if the user entered 0 degrees, the line would go straight ahead.
    direction -= 90;
    //Convert the direction from degrees to radians
    dirInRad = (direction * (PI / 180));
    //Find the distance the line needs to travel horizontally
    horDist = (distance * cos(dirInRad));
    //Find the distance the line needs to travel vertically
    verDist = (distance * sin(dirInRad));

    qDebug() << dirInRad << horDist << verDist;

    //The beggining if the new line is the end of the last line
    lastLine = lines.back();
    start = lastLine.lineEnd;
    //The end of the new line is the horizantal and vertical distance traveled added to the end of last line's x and y value respectively
    end;
    end.setX(lastLine.lineEnd.x() + horDist);
    end.setY(lastLine.lineEnd.y() + verDist);
    //Put the start and end values in newLine
    newLine.lineEnd = end;
    newLine.lineStart = start;

    //Add the new line to the lines vector
    lines.push_back(newLine);

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

    //Paint all of the PathLines in the lines vector
    for(auto iter = lines.begin(); iter != lines.end(); iter++)
    {
        painter.drawLine((*iter).lineStart, (*iter).lineEnd);
    }
}

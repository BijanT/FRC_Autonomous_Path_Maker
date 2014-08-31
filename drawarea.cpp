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
    instructions.clear();
}

void DrawArea::draw(int direction, int distance)
{
    //Initialize all the variables used in this function
    float dirInRad;
    int horDist, verDist;
    PathLine lastLine;
    PathLine newLine;
    QPoint start, end;

    //Save the direction and distance in the instructions vector
    instructions.push_back(PathInstruction(direction, distance));

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

void DrawArea::clearScreen()
{
    //Clear both the lines and instructions vector
    lines.clear();
    instructions.clear();

    //Put a "line" that is a dot in the center of the draw area as a point of reference to the user
    lines.push_back(PathLine(QPoint(WIDTH/2, HEIGHT/2), QPoint(WIDTH/2, HEIGHT/2)));

    //Update the draw area
    this->update();
}

void DrawArea::removeLastLine()
{
    //Remove the last elements of the lines and instructions vector after checking if they are occupied
    if((lines.size() > 0) && (instructions.size() > 0))
    {
        lines.erase(lines.end()-1);
        instructions.erase(instructions.end()-1);

        //After removing the last line, update the draw area
        this->update();
    }
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

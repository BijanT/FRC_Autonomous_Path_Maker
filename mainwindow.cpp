#include "mainwindow.h"

MainWindow::MainWindow()
{
    //Initialize the widgets
    drawArea  = new DrawArea(this);
    drawButton = new QPushButton(tr("Press Me"), this);

    //Set up the Signal/Slot relationships for the widgets
    connect(drawButton, SIGNAL(clicked(bool)), this, SLOT(updateDrawArea()));

    //Put the widgets in the main window
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(drawButton, 0, 0);
    layout->addWidget(drawArea, 1, 0);
}

MainWindow::~MainWindow()
{
    delete drawArea;
    delete drawButton;
}

void MainWindow::updateDrawArea()
{
    drawArea->draw(100);
}

QSize MainWindow::minimumSizeHint() const
{
    return QSize(WIDTH, HEIGHT);
}

QSize MainWindow::sizeHint() const
{
    return QSize(WIDTH, HEIGHT);
}

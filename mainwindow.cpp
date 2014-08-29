#include "mainwindow.h"

MainWindow::MainWindow()
{
    //Set the size for the windows
    this->setMinimumSize(WIDTH, HEIGHT);
    this->setMaximumSize(WIDTH, HEIGHT);

    //Initialize the widgets
    drawArea  = new DrawArea(this);
    drawButton = new QPushButton(tr("Add Motion"), this);
    direction = new QLineEdit(this);
    distance = new QLineEdit(this);
    directionLabel = new QLabel(tr("Direction (degrees):"), this);
    distanceLabel = new QLabel(tr("Distance (inches):"), this);

    //Set up the Signal/Slot relationships for the widgets
    connect(drawButton, SIGNAL(clicked(bool)), this, SLOT(updateDrawArea()));

    //Create layouts to organize the widgets
    QGridLayout* mainLayout = new QGridLayout(this);
    QGridLayout* userInputLayout = new QGridLayout();

    //Put the widgets used for user input in the user input layout
    userInputLayout->addWidget(directionLabel, 0, 0);
    userInputLayout->addWidget(distanceLabel, 0, 1);
    userInputLayout->addWidget(direction, 1, 0);
    userInputLayout->addWidget(distance, 1, 1);
    userInputLayout->addWidget(drawButton, 2, 0, 1, 2);

    //Put the widgets in the main window
    mainLayout->addLayout(userInputLayout, 0, 0);
    mainLayout->addWidget(drawArea, 0, 1, 5, 1);//Have drawArea span five rows to make the widgets of the user input layout closer together
}

MainWindow::~MainWindow()
{
    delete drawArea;
    delete drawButton;
    delete direction;
    delete distance;
    delete directionLabel;
    delete distanceLabel;
}

void MainWindow::updateDrawArea()
{

    drawArea->draw(-45, 60);
}

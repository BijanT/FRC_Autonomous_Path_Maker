#include "mainwindow.h"

MainWindow::MainWindow()
{
    //Set the size for the windows
    this->setMinimumSize(WIDTH, HEIGHT);
    this->setMaximumSize(WIDTH, HEIGHT);

    //Initialize the widgets
    drawArea  = new DrawArea(this);
    drawButton = new QPushButton(tr("Add Motion"), this);
    saveButton = new QPushButton(tr("Save"), this);
    clearButton = new QPushButton(tr("Clear Path"), this);
    removeLastButton = new QPushButton(tr("Remove Last Line"), this);
    direction = new QLineEdit(this);
    distance = new QLineEdit(this);
    directionLabel = new QLabel(tr("Direction (degrees):"), this);
    distanceLabel = new QLabel(tr("Distance (inches):"), this);

    //Set up the Signal/Slot relationships for the widgets
    connect(drawButton, SIGNAL(clicked(bool)), this, SLOT(updateDrawArea()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(savePath()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clearScreen()));
    connect(removeLastButton, SIGNAL(clicked(bool)), this, SLOT(removeLastLine()));

    //Create layouts to organize the widgets
    QGridLayout* mainLayout = new QGridLayout(this);
    QGridLayout* userInputLayout = new QGridLayout();

    //Put the widgets used for user input in the user input layout
    userInputLayout->addWidget(directionLabel, 0, 0);
    userInputLayout->addWidget(distanceLabel, 0, 1);
    userInputLayout->addWidget(direction, 1, 0);
    userInputLayout->addWidget(distance, 1, 1);
    userInputLayout->addWidget(drawButton, 2, 0, 1, 2);
    userInputLayout->addWidget(clearButton, 3, 0);
    userInputLayout->addWidget(removeLastButton, 3, 1);
    userInputLayout->addWidget(saveButton, 4, 0, 1, 2);

    //Put the widgets in the main window
    mainLayout->addLayout(userInputLayout, 0, 0);
    mainLayout->addWidget(drawArea, 0, 1, 5, 1);//Have drawArea span five rows to make the widgets of the user input layout closer together
}

MainWindow::~MainWindow()
{
    delete drawArea;
    delete drawButton;
    delete saveButton;
    delete clearButton;
    delete removeLastButton;
    delete direction;
    delete distance;
    delete directionLabel;
    delete distanceLabel;
}

//This function is called when drawButton is pressed
void MainWindow::updateDrawArea()
{
    //Initialize the variables used in this function
    int directionInt, distanceInt;
    bool conversionSuccessful;
    //Convert the direction and distance text boxes from QStrings to ints and make sure the conversion occured correctly
    directionInt = direction->text().toInt(&conversionSuccessful);
    if(!conversionSuccessful)
    {
        //If the conversion failed, display a message and exit the function
        QMessageBox::critical(this, tr("Error!"), tr("Error converting the direction from a string to an integer"));
        return;
    }
    distanceInt = distance->text().toInt(&conversionSuccessful);
    if(!conversionSuccessful)
    {
        //If the conversion failed, display a message and exit the function
        QMessageBox::critical(this, tr("Error!"), tr("Error converting the distance from a string to an integer"));
        return;
    }

    //If the conversions were succesful, draw a new line with the requested distance and direction
    drawArea->draw(directionInt, distanceInt);
}

//This function handles saving a .path file that holds the instruction for the path
//Called when the save button is pressed
void MainWindow::savePath()
{
    //Get a copy of the instructions from drawArea
    std::vector< PathInstruction > instructions = drawArea->getInstructions();

    //Get the file name the user wants to save to
    QString fileName = QFileDialog::getSaveFileName(this, tr("Where do you want to save the path file?"), QString(), tr("Path files (*.path)"));

    //Check if the fileName string is not empty (i.e. the user chose a file name to save to)
    if(!fileName.isEmpty())
    {
        //Create an instance of the file and make sure it opens correctly
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not save to the requested file."));
            return;
        }
        QTextStream out(&file);

        //loop trough all of the instructions and save them into the file
        for(auto iter = instructions.begin(); iter != instructions.end(); iter++)
        {
            out << (*iter).direction << " " << (*iter).distance <<"\n";
        }

        file.close();
    }
}

void MainWindow::clearScreen()
{
    drawArea->clearScreen();
}

void MainWindow::removeLastLine()
{
    drawArea->removeLastLine();
}

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
    openButton = new QPushButton(tr("Open"), this);
    clearButton = new QPushButton(tr("Clear Path"), this);
    removeLastButton = new QPushButton(tr("Remove Last Line"), this);
    direction = new QLineEdit(this);
    distance = new QLineEdit(this);
    speed = new QLineEdit(this);
    directionLabel = new QLabel(tr("Direction (degrees):"), this);
    distanceLabel = new QLabel(tr("Distance (inches):"), this);
    speedLabel = new QLabel(tr("Speed"), this);

    //Set up the Signal/Slot relationships for the widgets
    connect(drawButton, SIGNAL(clicked(bool)), this, SLOT(updateDrawArea()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(savePath()));
    connect(openButton, SIGNAL(clicked(bool)), this, SLOT(openPath()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clearScreen()));
    connect(removeLastButton, SIGNAL(clicked(bool)), this, SLOT(removeLastLine()));

    //Create layouts to organize the widgets
    QGridLayout* mainLayout = new QGridLayout(this);
    QGridLayout* userInputLayout = new QGridLayout();

    //Put the widgets used for user input in the user input layout
    userInputLayout->addWidget(directionLabel, 0, 0);
    userInputLayout->addWidget(distanceLabel, 0, 1);
    userInputLayout->addWidget(speedLabel, 0, 2);
    userInputLayout->addWidget(direction, 1, 0);
    userInputLayout->addWidget(distance, 1, 1);
    userInputLayout->addWidget(speed, 1, 2);
    userInputLayout->addWidget(drawButton, 2, 0, 1, 3);//Have the button span three collumns
    userInputLayout->addWidget(clearButton, 3, 0);
    userInputLayout->addWidget(removeLastButton, 3, 1);
    userInputLayout->addWidget(saveButton, 4, 0);
    userInputLayout->addWidget(openButton, 4, 1);

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
    delete speed;
    delete directionLabel;
    delete distanceLabel;
    delete speedLabel;
}

//This function is called when drawButton is pressed
void MainWindow::updateDrawArea()
{
    //Initialize the variables used in this function
    int directionInt, distanceInt, speedInt;
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
    //Conver the speed from a QString into an integer
    speedInt = speed->text().toInt(&conversionSuccessful);
    if(!conversionSuccessful)
    {
        //If the conversion failed, display a message and exit the function
        QMessageBox::critical(this, tr("Error!"), tr("Error converting the speed from a string to an integer"));
        return;
    }

    //If the conversions were succesful, draw a new line with the requested distance, direction, and speed through
    drawArea->draw(directionInt, distanceInt, speedInt);
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
            out << (*iter).direction << " " << (*iter).distance << " " << (*iter).speed << "\n";
        }

        file.close();
    }
}

//This function handles opening a .path file
//Called whenever the open button is pressed
void MainWindow::openPath()
{
    //Get the name of the file to open
    QString fileName = QFileDialog::getOpenFileName(this, tr("Which file do you want to open?"), QString(), tr("Path files (*.path)"));

    //Check if the fileName string is not empty (i.e. the user chose a file name to open)
    if(!fileName.isEmpty())
    {
        //Clear the screen for the new path to be opened
        drawArea->clearScreen();
        QFile file(fileName);
        //Open the file and make sure it is opened correctly
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open requested file."));
            return;
        }
        QTextStream in(&file);

        //Read the file line by line until the file ends
        while(!in.atEnd())
        {
            int directionInt, distanceInt, speedInt;
            bool conversionSuccessful;
            QString input, direction, distance, speed;
            QStringList splitString;

            //Read one line from the file
            input = in.readLine();

            //Split the input into the direction and distance
            splitString = input.split(QRegExp(" "));
            direction = splitString.at(0);
            distance = splitString.at(1);
            speed = splitString.at(2);

            //Convert the strings to integers and check if they were converted correctly
            directionInt = direction.toInt(&conversionSuccessful);
            if(!conversionSuccessful)
            {
                QMessageBox::critical(this, tr("Error"), tr("There was an error opening the file. The file may not be the correct format/type"));
                return;
            }
            distanceInt = distance.toInt(&conversionSuccessful);
            if(!conversionSuccessful)
            {
                QMessageBox::critical(this, tr("Error"), tr("There was an error opening the file. The file may not be the correct format/type"));
                return;
            }
            speedInt = speed.toInt(&conversionSuccessful);
            if(!conversionSuccessful)
            {
                QMessageBox::critical(this, tr("Error"), tr("There was an error opening the file. The file may not be the correct format/type"));
                return;
            }

            //Draw a path with the newly aquired instructions
            drawArea->draw(directionInt, distanceInt, speedInt);
        }
    }
}

void MainWindow::clearScreen()
{
    //Check if the user is sure before clearing the draw area
    if(userIsSure() == QMessageBox::Yes)
    {
        drawArea->clearScreen();
    }
}

void MainWindow::removeLastLine()
{
    //Check if the user is sure before removing the last line
    if(userIsSure() == QMessageBox::Yes)
    {
        drawArea->removeLastLine();
    }
}

QMessageBox::StandardButton MainWindow::userIsSure()
{
    return QMessageBox::question(this, tr("Are you sure?"), tr("Are you sure you want to do this? It cannot be undone."));
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <vector>
#include "drawarea.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    //The width and height of the widget
    const int WIDTH = 930;
    const int HEIGHT = 480;

    //The widgets we will use for this program
    DrawArea* drawArea;
    QPushButton* drawButton;
    QPushButton* saveButton;
    QPushButton* openButton;
    QPushButton* clearButton;
    QPushButton* removeLastButton;
    QLineEdit* direction;
    QLineEdit* distance;
    QLineEdit* speed;
    QLabel* directionLabel;
    QLabel* distanceLabel;
    QLabel* speedLabel;

    QMessageBox::StandardButton userIsSure();

private slots:
    void updateDrawArea();
    void savePath();
    void openPath();
    void clearScreen();
    void removeLastLine();
};

#endif // MAINWINDOW_H

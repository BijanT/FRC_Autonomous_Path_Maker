#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
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
    QLineEdit* direction;
    QLineEdit* distance;
    QLabel* directionLabel;
    QLabel* distanceLabel;

private slots:
    void updateDrawArea();
};

#endif // MAINWINDOW_H

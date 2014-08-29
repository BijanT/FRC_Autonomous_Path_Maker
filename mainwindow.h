#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include "drawarea.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    //Functions that determine the widget's size
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    //The width and height of the widget
    const int WIDTH = 620;
    const int HEIGHT = 480;

    //The widgets we will use for this program
    DrawArea* drawArea;
    QPushButton* drawButton;

private slots:
    void updateDrawArea();
};

#endif // MAINWINDOW_H

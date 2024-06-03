#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QRadioButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <vector>
#include "Painter.h"
#include <QMouseEvent>
#include "Matrix.h"

enum M_PAINTING_MODE
{
    PAINT_ADD,
    PAINT_REMOVE
};

enum S_OBJECT
{
    VERTICLE,
    EDGE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    M_PAINTING_MODE PAINTING_MODE;
    S_OBJECT PAINTING_SHAPE;
    std::vector<verticle> verticles;
    Matrix matrix;
    int holdVerticleIndex;

    void setDockWidget();


    QDockWidget *dockWidget;

    QRadioButton *radioBtn1;
    QRadioButton *radioBtn2;
    QRadioButton *radioBtn3;
    QRadioButton *radioBtn4;

    QButtonGroup *btnGroup1;
    QButtonGroup *btnGroup2;

    QHBoxLayout *hLayout1;
    QHBoxLayout *hLayout2;

    QPushButton *pushBtn;

    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QLabel *label;

    QVBoxLayout *vLayout;


private slots:
    void slot_operation();
    void slot_shape();
    void slot_compute();

};
#endif // MAINWINDOW_H

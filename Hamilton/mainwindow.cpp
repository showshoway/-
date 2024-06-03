#include "mainwindow.h"
#include <QPainterPath>
#include <QPainter>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPalette>
#include <QPushButton>
#include <QLineEdit>
#include <QCursor>
#include "Painter.h"
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(1200, 800);
    this->setDockNestingEnabled(true);
    setDockWidget();
    this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    holdVerticleIndex = -1;

    connect(this->radioBtn1, SIGNAL(clicked(bool))
            ,this, SLOT(slot_shape()));
    connect(this->radioBtn2, SIGNAL(clicked(bool))
            ,this, SLOT(slot_shape()));
    connect(this->radioBtn3, SIGNAL(clicked(bool))
            ,this, SLOT(slot_operation()));
    connect(this->radioBtn4, SIGNAL(clicked(bool))
            ,this, SLOT(slot_operation()));
    connect(this->pushBtn, SIGNAL(clicked(bool))
            ,this, SLOT(slot_compute()));
}

MainWindow::~MainWindow() {}


//绘图
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制所有节点以及边
    paintVerticle(verticles, this, 10);
    update();

}


void MainWindow::slot_shape()
{
    switch (btnGroup1->checkedId()) {
    case 0:
        PAINTING_SHAPE = VERTICLE;
        holdVerticleIndex = -1;
        break;
    case 1:
        PAINTING_SHAPE = EDGE;
        holdVerticleIndex = -1;
        break;

    }
}

void MainWindow::slot_operation()
{
    switch (btnGroup2->checkedId()) {
    case 0:
        PAINTING_MODE = PAINT_ADD;
        break;
    case 1:
        PAINTING_MODE = PAINT_REMOVE;
        holdVerticleIndex = -1;
        break;

    }

}

//计算汉密尔顿路并显示
void MainWindow::slot_compute()
{
    this->label->setText("clicked");
    Hamilton *hamiltonGraph;
    matrix.addWeightValue(verticles);
    hamiltonGraph = matrix.findHamilton();

    if(hamiltonGraph == nullptr)
    {
        label->setText("无汉密尔顿路");
        return;
    }

    QString result = "汉密尔顿路总长：" + QString::number(hamiltonGraph->weightValue) + "\n";
    result.append("汉密尔顿路径：");

    result.append(verticles[hamiltonGraph->order[0]].name);
    for(int i = 1; i < verticles.size(); i++)
    {
        result.append("->" + verticles[hamiltonGraph->order[i]].name + "\n");
    }
    label->setText(result);
    label->adjustSize();
}




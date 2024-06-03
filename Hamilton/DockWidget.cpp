#include "mainwindow.h"

#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPalette>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QValidator>

void MainWindow::setDockWidget()
{
    dockWidget = new QDockWidget("设置");
    dockWidget->setFixedSize(200, 800);
    dockWidget->setGeometry(0, 0, 300, 100);
    QColor color(125, 125, 130);
    QPalette pal(color);
    dockWidget->setPalette(pal);
    dockWidget->setAutoFillBackground(true);
    dockWidget->show();

    QWidget *currentWidget = new QWidget();

    radioBtn1 = new QRadioButton();
    radioBtn2 = new QRadioButton();
    radioBtn3 = new QRadioButton();
    radioBtn4 = new QRadioButton();

    radioBtn1->setText("节点");
    radioBtn2->setText("边");
    radioBtn3->setText("添加");
    radioBtn4->setText("删除");

    btnGroup1 = new QButtonGroup();
    btnGroup1->addButton(radioBtn1, 0);
    radioBtn1->setChecked(true);
    btnGroup1->addButton(radioBtn2, 1);
    btnGroup2 = new QButtonGroup();
    btnGroup2->addButton(radioBtn3, 0);
    radioBtn3->setChecked(true);
    btnGroup2->addButton(radioBtn4, 1);


    hLayout1 = new QHBoxLayout();
    hLayout2 = new QHBoxLayout();

    hLayout1->addWidget(radioBtn1);
    hLayout1->addWidget(radioBtn2);
    hLayout2->addWidget(radioBtn3);
    hLayout2->addWidget(radioBtn4);

    pushBtn = new QPushButton();
    pushBtn->setText("计算");

    lineEdit2 = new QLineEdit();
    lineEdit2->setText("输入节点名");

    lineEdit1 = new QLineEdit();
    lineEdit1->setText("输入步长");
    lineEdit1->setValidator(new QIntValidator(1, 9999999, this));

    label = new QLabel();
    label->adjustSize();
    label->setText("路径：");

    vLayout = new QVBoxLayout();

    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addWidget(lineEdit2);
    vLayout->addWidget(lineEdit1);
    vLayout->addWidget(label);
    vLayout->addWidget(pushBtn);

    currentWidget->setLayout(vLayout);

    dockWidget->setWidget(currentWidget);

    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}

#ifndef PAINTER_H
#define PAINTER_H
#include <vector>
#include <string>
#include <QMainWindow>
#include <QString>
struct Edge
{
    int i;//所连节点的索引
    int weightValue;//权值
};

struct verticle
{
    QString name;
    //屏幕上的坐标
    int x;
    int y;
    std::vector<Edge> edges;
};

void paintVerticle(std::vector<verticle> verticles, QMainWindow *mainwindow, int r);




#endif // PAINTER_H

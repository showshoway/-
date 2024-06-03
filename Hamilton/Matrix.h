#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include "Painter.h"

struct Hamilton
{
    std::vector<int> order;//顺序
    int weightValue;//总权值
};

class Matrix
{
public:
    Matrix();
    Hamilton* findHamilton();
    void addPoint();
    void removePoint(int index);
    void addWeightValue(const std::vector<verticle> verticles);
    ~Matrix();
private:
    bool isConnectivity();//判断连通性

    void Dijkstra();
    std::vector<std::vector<int>> *matrix;//矩阵第i行j列意味着第i与j个节点间的最短距离

};

int min(int a, int b);


#endif // MATRIX_H

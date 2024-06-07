#include "Matrix.h"
#include <vector>
#include "Painter.h"
#include <iterator>
#include <list>
#include <algorithm>



int min(int a, int b)
{
    return a > b ? b : a;
}

Matrix::Matrix()
{
    matrix = new std::vector<std::vector<int>>();
}

Matrix::~Matrix()
{
    delete matrix;
}

//添加节点
void Matrix::addPoint()
{
    std::vector<int> list1;

    for(int i = 0; i < matrix->size(); i++)
    {
        (*matrix)[i].push_back(-1);
    }
    for(int i = 0; i < matrix->size() + 1 ; i++ )
    {
        list1.push_back(-1);
    }
    matrix->push_back(list1);

}

void Matrix::removePoint(int index)
{
    matrix->erase(matrix->begin() + index);
    for(int i = 0; i < matrix->size(); i++)
    {
        (*matrix)[i].erase((*matrix)[i].begin() + index);
    }




}

//将边权添加进矩阵
void Matrix::addWeightValue(const std::vector<verticle> verticles)
{
    for(int i = 0; i < matrix->size(); i++)
    {
        for(Edge edge : verticles[i].edges)
        {
            matrix->at(i).at(edge.i) = edge.weightValue;
        }

        matrix->at(i).at(i) = 0;
    }


}


//利用狄克斯特拉算法算出每个节点间最短距离
void Matrix::Dijkstra()
{
    for(int i = 0; i < matrix->size(); i++)
    {
        for(int j = 1; j < matrix->size(); j++)
        {
            for(int k = 0; k < matrix->size(); k++)
            {
                if(matrix->at(j).at(k) != -1)
                {
                    if(matrix->at(i).at(k) == -1)
                        matrix->at(i).at(k) = matrix->at(i).at(j) + matrix->at(j).at(k);
                    else
                        matrix->at(i).at(k) = min(matrix->at(i).at(k), matrix->at(i).at(j) + matrix->at(j).at(k) );
                }
            }
        }
    }

    //对称化
    for(int i1 = 0; i1 < matrix->size(); i1++)
    {
        for(int i2 = 0; i2 < i1; i2++)
        {
            matrix->at(i1).at(i2) = matrix->at(i2).at(i1);
        }
    }
}

//找汉密尔顿路
Hamilton* Matrix::findHamilton()
{

    Dijkstra();
    if(!isConnectivity())//检验连通性
        return nullptr;

    Hamilton* minHamilton = nullptr;

    std::vector<int> index;

    for(int i = 0; i < matrix->size(); i++)
    {
        index.push_back(i);
    }



    int sum = 0;
    do
    {
        sum = 0;
        for(int j = 0; j < matrix->size() - 1; j++)
        {
            sum += (*matrix)[index[j]][index[j+1]];
        }

        if(minHamilton == nullptr)
        {
            minHamilton = new Hamilton();
            minHamilton->weightValue = sum;
            for(int k = 0; k < matrix->size(); k++)
            {
                minHamilton->order.push_back(index[k]);
            }
            continue;
        }
        else if(sum < minHamilton->weightValue)
        {
            minHamilton->weightValue = sum;
            for(int k = 0; k < matrix->size(); k++)
            {
                minHamilton->order.at(k) = index[k];
            }
        }


    }while(std::next_permutation(index.begin(), index.end()));

    return minHamilton;

}

bool Matrix::isConnectivity()
{
    for(int i = 0; i < matrix->size(); i++)
    {
        for(int k = 0; k < i; k++)
        {
            if((*matrix)[i][k] == -1)
                return false;
        }
    }
    return true;
}









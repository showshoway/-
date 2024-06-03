#include "Matrix.h"
#include <vector>
#include "Painter.h"
#include <iterator>
#include <list>
#include <algorithm>

void permute(std::vector<int>& nums, int start, std::vector<std::vector<int>>& result) {
    if (start == nums.size() - 1) {
        result.push_back(nums);
        return;
    }

    for (int i = start; i < nums.size(); ++i) {
        std::swap(nums[start], nums[i]);
        permute(nums, start + 1, result);
        std::swap(nums[start], nums[i]);  // 回溯
    }
}

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

    std::vector<std::vector<int>> results;
    permute(index, 0, results);//穷举排列组合并存入results中

    int sum = 0;
    for(std::vector<int> result : results)
    {
        sum = 0;
        for(int j = 0; j < matrix->size() - 1; j++)
        {
            sum += (*matrix)[result[j]][result[j + 1]];
        }
        if(minHamilton == nullptr)
        {
            minHamilton = new Hamilton();
            minHamilton->weightValue = sum;

            for(int j = 0; j < matrix->size(); j++)
            {
                minHamilton->order.push_back(result[j]);
            }
        }
        else if(sum < minHamilton->weightValue)
        {
            minHamilton->weightValue = sum;
            for(int j = 0; j < matrix->size(); j++)
            {
                minHamilton->order[j] = result[j];
            }
        }
    }

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









#include "mainwindow.h"


//检测鼠标事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        int x = this->mapFromGlobal(QCursor().pos()).x();
        int y = this->mapFromGlobal(QCursor().pos()).y();
        if(PAINTING_MODE == PAINT_ADD)
        {
            if(PAINTING_SHAPE == VERTICLE)
            {
                verticle a_verticle;
                a_verticle.name = lineEdit2->text();
                a_verticle.x = x;
                a_verticle.y = y;
                verticles.push_back(a_verticle);
                matrix.addPoint();
            }
            else if(PAINTING_SHAPE == EDGE)
            {

                for(int i = 0; i < verticles.size(); i++)
                {
                    if(std::abs(x - verticles[i].x) <= 10
                        && std::abs(y - verticles[i].y <= 10))
                    {
                        if(holdVerticleIndex == -1)
                        {
                            holdVerticleIndex = i;
                        }
                        else
                        {
                            Edge edge1;
                            Edge edge2;

                            edge1.weightValue = lineEdit1->text().toInt();
                            edge2.weightValue = lineEdit1->text().toInt();

                            edge1.i = holdVerticleIndex;
                            edge2.i = i;

                            verticles[i].edges.push_back(edge1);
                            verticles[holdVerticleIndex].edges.push_back(edge2);

                            holdVerticleIndex = -1;
                        }
                        break;
                    }
                }
            }

        }

        if(PAINTING_MODE == PAINT_REMOVE)
        {
            if(PAINTING_SHAPE == VERTICLE)
            {
                for(int i = 0; i < verticles.size(); i++)
                {
                    if(std::abs(x - verticles[i].x) <= 10
                        && std::abs(y - verticles[i].y <= 10))
                    {
                        matrix.removePoint(i);
                        verticles.erase(verticles.begin() + i);

                        for(verticle &currenVerticle : verticles)
                        {
                            for (int k = 0; k < currenVerticle.edges.size(); k++)
                            {
                                if(currenVerticle.edges.at(k).i == i)
                                {
                                    currenVerticle.edges.erase(currenVerticle.edges.begin() + k);
                                }
                                else if(currenVerticle.edges.at(k).i > i)
                                {
                                    currenVerticle.edges.at(k).i = currenVerticle.edges.at(k).i - 1;
                                }
                            }
                        }

                        break;
                    }
                }
            }
            else if(PAINTING_SHAPE == EDGE)
            {
                for(verticle &currentVerticle : verticles)
                {
                    for(int i = 0; i < currentVerticle.edges.size(); i++)
                    {
                        if(std::abs(x - ( currentVerticle.x + verticles[ currentVerticle.edges[i].i ].x ) / 2) <= 20
                            && std::abs(y - ( currentVerticle.y + verticles[ currentVerticle.edges[i].i ].y ) / 2) <= 20)
                        {
                            currentVerticle.edges.erase(currentVerticle.edges.begin() + i);
                        }
                    }
                }
            }
        }
    }
}

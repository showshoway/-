#include "Painter.h"
#include <QPainter>
#include <QMainWindow>
#include <QPainterPath>


void paintVerticle(std::vector<verticle> verticles, QMainWindow *mainwindow, int r = 10)
{
    QPainter painter(mainwindow);
    QPainterPath path;
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush( QBrush(QColor("lightblue")) );


    for(verticle &currentVerticle : verticles)
    {
        path.addEllipse(currentVerticle.x - r, currentVerticle.y - r, 2 * r, 2 * r);
        path.addEllipse(currentVerticle.x - r / 2, currentVerticle.y - r / 2, r, r);

        painter.drawPath(path);
        painter.drawText(currentVerticle.x - r, currentVerticle.y - 2 * r, currentVerticle.name);


        for(Edge edge : currentVerticle.edges)
        {

            painter.drawLine(currentVerticle.x, currentVerticle.y,
                             verticles[edge.i].x, verticles[edge.i].y);
            painter.drawText(( currentVerticle.x + verticles[edge.i].x ) / 2
                             ,( currentVerticle.y + verticles[edge.i].y ) / 2
                             ,QString::number(edge.weightValue));

        }

    }

}





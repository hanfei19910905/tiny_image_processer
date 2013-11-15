#ifndef ALGO_HPP
#define ALGO_HPP

#include<QObject>
#include<QtCore>
#include<cmath>
#include<iostream>


const double pi = std::acos(-1.0);
const int MAXR = 250;

namespace IWarp{
//#ifdef IWarp
    void IwarpDeform(QImage& img,int x,int y){
       // if(!enable) return ;

        int r = radius;
        if(x < r || x + r > w || y < r || y + r > h){
         //   emit iwarp_err(QString("exceed the bound !"));
            return ;
        }
        int x0 = -r, x1 = r, y0 = -r, y1 = r;
        // x0, y0 stand for the left buttom point, and x1, y1 is the oppisite
        int r2 = radius * radius;
        for(int yi = y0; yi <= y1 ; yi ++)
            for(int xi = x0; xi <= x1; xi ++){
                qDebug() << "pos: "<<yi<<" "<<xi<<"\n";
                double len2 = (xi*xi + yi*yi) / r2; // dis^2 / r^2
                qDebug() << "len2: "<<len2<<"\n";
                if(len2 < 1.0){
                    double deformValue = 0.1 * deformAmount * std::pow(std::cos(std::sqrt(len2) * pi) * 0.5,0.7);
                    qDebug() << std::cos(std::sqrt(len2) * pi) <<"\n";
                    qDebug() << std::pow(std::cos(std::sqrt(len2) * pi) * 0.5,0.7) <<"\n";
                    qDebug() << deformAmount <<"\n";
                    double nvx = -deformValue * xi;
                    double nvy = -deformValue * yi; // (x,y) is replaced by (nvx,nvy)
                    int xv = (int)nvx + x + xi,yv = (int) nvy + y + yi;
                    //Regular(nvx + x + xi , nvy + y + yi, xv,yv);

                   }
            }
    }
};
#endif // ALGO_HPP

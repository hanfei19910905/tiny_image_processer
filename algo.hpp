#ifndef ALGO_HPP
#define ALGO_HPP

#include<opencv2/opencv.hpp>

class Algo{
    Q_OBJECT
public:
    explicit Algo(int _r = 35):radius(_r){
    }
private:
    int radius;
private slots :
    void DrawCricle(cv::Mat& img,int x,int y){
        cv::circle(img,cv::Point(x,y),radius,cv::Scalar(255,255,255));
        emit refrush(img);
    }
signals :
    void refrush(cv::Mat&);
};

#endif // ALGO_HPP

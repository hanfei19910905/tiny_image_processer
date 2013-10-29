#include <opencv2/opencv.hpp>
#include <iostream>

// personal tools

template<typename T> void chkmin(T &a, T b){if(a == -1 || a > b) a = b;}
template<typename T> void chkmax(T &a, T b){if(a == -1 || a < b) a = b;}
typedef unsigned char color_t;
//

const int MAXC = 256;

color_t lut[3][MAXC];
color_t low_input[4], high_input[4];
int num[4][MAXC] ;

int aws(cv::Mat& image)
{
    memset(low_input,-1,sizeof(low_input));
    memset(high_input,-1,sizeof(high_input));
    memset(num,0,sizeof(num));
    memset(lut,0,sizeof(lut));
    for(cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>(); it != image.end<cv::Vec3b>(); ++it){
        for(int channel = 0; channel < 3; ++ channel){
            color_t i = (*it)[channel];
            num[channel][i] += 1;
        }
    }
    for(int i = 0; i < 4; i++){
        double sum = 0;
        for(int j = 0; j < MAXC; j ++){
            sum += num[i][j];
        }
        double now = 0;
        for(int j = 0; j < MAXC - 1; j++){
            double s = now + num[i][j]/sum;
            double t = now + s + num[i][j+1]/sum;
            if(std::fabs(s - 0.006) < std::fabs(t - 0.006)){
                low_input[i] = j;
                break;
            }
            now += s;
        }
        now = 0;
        for(int j = MAXC - 1; j >= 0; j--){
            double s = now + num[i][j]/sum;
            double t = now + s + num[i][j-1]/sum;
            if(std::fabs(s - 0.006) < std::fabs(t - 0.006)){
                high_input[i] = j;
                break;
            }
            now += s;
        }
    }
    

    for(int channel = 0; channel < 3; channel ++){
        double low = (double)low_input[channel] / 255.0;
        double high = (double)high_input[channel] / 255.0;
        for(int value = 0; value < MAXC; value ++){
            double v = value / 255.0;
            double result = (1.0 * (v - low) / (high - low) * 255);
            if(result < 0) result = 0;
            if(result > 255.0) result = 255.0;

            lut[channel][value] = (color_t)result;
        }
    }


    cv::Mat result ( image);

    for(cv::Mat_<cv::Vec3b>::iterator it = result.begin<cv::Vec3b>(); it != result.end<cv::Vec3b>(); ++it){
        for(int channel = 0; channel < 3; channel ++){
            color_t& value = (*it)[channel];
            value = lut[channel][value];
        }
    }
//    cout<< sizeof(image[0][0]) <<endl;

    return 1;
}

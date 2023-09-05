#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

Mat Binary(Mat f) {


    Mat msk(f.rows, f.cols, CV_8U, Scalar(0));

    for(int row = 0; row < f.rows; row++){
        for(int col = 0; col < f.cols; col++){
            if(f.at<uchar>(row, col) > 125){
                msk.at<uchar>(row,col) = uchar(255);
            }
            else{
                msk.at<uchar>(row,col) = uchar(0);
            }
        }
    }

    return msk;
}

void BinaryMask(Mat g, Mat m, Mat f, Mat h){

    for(int row = 0; row < g.rows; row++){
        for(int col = 0; col < g.cols; col++){
            if(m.at<uchar>(row, col) >= 200){
                g.at<uchar>(row,col) = uchar(h.at<uchar>(row,col));
            }
            else{
                g.at<uchar>(row,col) = uchar(f.at<uchar>(row,col));
            }
        }
    }

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", m);
    imwrite("Mask2.jpg", m);
    waitKey(0);

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", f);
    imwrite("Ori1.jpg", f);
    waitKey(0);

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    imwrite("Ori2.jpg", h);
    waitKey(0);

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", g);
    imwrite("BinaryMask2.jpg", g);
    waitKey(0);

}


int main() {
    Mat f = imread("../Dice.png", IMREAD_GRAYSCALE);
    Mat tH = Binary(f);
    Mat h = imread("../Flower.png", IMREAD_GRAYSCALE);

    int srows = min(f.rows, h.rows);
    int scols = min(f.cols, h.cols);

    Mat g(srows, scols, CV_8U, Scalar(0, 0, 0));
    BinaryMask(g, tH, f, h);
}

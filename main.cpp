#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

/**
 * @brief Creates a binary mask from a grayscale input image.
 *
 * This function takes an input grayscale image 'f' and creates a binary mask based on a threshold.
 * Pixels with values greater than 125 are set to 255 (white), and others are set to 0 (black).
 *
 * @param f Input grayscale image.
 * @return Binary mask image.
 */

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

/**
 * @brief Applies a binary mask to two grayscale images and generates an output image.
 *
 * This function creates a binary mask 'm' based on a threshold and applies it to two images 'f' and 'h'.
 * Pixels in 'g' are taken from 'h' where 'm' is >= 200 and from 'f' otherwise.
 * Additionally, this function displays and saves intermediate images for debugging purposes.
 *
 * @param g Output image where the binary mask is applied.
 * @param m Binary mask image.
 * @param f First grayscale input image.
 * @param h Second grayscale input image.
 */
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
    imshow("PhotoFrame", f);
    waitKey(0);

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", m);
    imwrite("Mask2.jpg", m);
    waitKey(0);

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    waitKey(0);

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", g);
    imwrite("BinaryMask2.jpg", g);
    waitKey(0);

}

Mat LoadImage(const string& filename, int flags){
    Mat image = imread(filename, flags);
    if(image.empty()) {
        cerr << "Error: Unable to load image from file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}


int main() {
    Mat f = LoadImage("../Dice.png", IMREAD_GRAYSCALE);
    Mat tH = Binary(f);
    Mat h = LoadImage("../Flower.png", IMREAD_GRAYSCALE);

    int srows = min(f.rows, h.rows);
    int scols = min(f.cols, h.cols);

    Mat g(srows, scols, CV_8U, Scalar(0, 0, 0));
    BinaryMask(g, tH, f, h);
}

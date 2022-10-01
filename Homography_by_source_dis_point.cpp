

// import opencv library
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

// import c++ library
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <vector>


// namespaces
using namespace std;
using namespace cv;

// find the homography matrix of the desired pespective trasformation

int main(int argc, char** argv)
{
    // Read source image.
    Mat im_src = imread("C:/Users/sagar/Downloads/10455130.jpg");
    // Four corners of the book in source image
    vector<Point2f> pts_src;
    pts_src.push_back(Point2f(445, 385));
    pts_src.push_back(Point2f(610, 385));
    pts_src.push_back(Point2f(270, 683));
    pts_src.push_back(Point2f(815, 683));

    // Read destination image.
    Mat Blankdisplay = Mat::zeros(Size(1024, 683), CV_8UC1);
    // Four corners of the book in destination image.
    vector<Point2f> pts_dst;
    pts_dst.push_back(Point2f(445, 385));
    pts_dst.push_back(Point2f(610, 385));
    pts_dst.push_back(Point2f(435, 683));
    pts_dst.push_back(Point2f(650, 683));

    // Calculate Homography
    // Mat h = findHomography(pts_src, pts_dst);
    Mat h = findHomography(pts_src, pts_dst, INTER_LINEAR | WARP_INVERSE_MAP);

    // Output image
    Mat im_out;
    // Warp source image to destination based on homography
    warpPerspective(im_src, im_out, h, Blankdisplay.size(), INTER_LINEAR);
    Mat resized_image;
    resize(im_out, resized_image, Size(624, 300));


    Rect cropimage = Rect(70, 70, 554, 230);
    Mat crop = resized_image(cropimage);

    // Display images
    imshow("Source Image", im_src);
    //imshow("Destination Image", Blankdisplay);
    imshow("Warped Source Image", im_out);
    imshow("Warped Source Image2", resized_image);
    imshow("crop image", crop);


    //imwrite("Source Image.jpg", im_src);
    //imwrite("Warped Source Image.jpg", im_out);
    //imwrite("Warped Source Image2.jpg", resized_image);
    //imwrite("crop image.jpg", crop);



    waitKey(0);

    im_src.release();
    destroyAllWindows();
}


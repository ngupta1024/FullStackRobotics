#include <vector>
#include <Eigen/Dense>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>

// 1 raster is 0.04m log
#define METERSPERPIXELS 0.04
#define ZOOMFACTOR 50
// #define INPUTIMG "occInput2.png"

namespace FSR
{
    struct ContourData
    {
        // \TODO we can convert this to Eigen and make another struct if needed 
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy; 
    };

    void loadImage(cv::Mat &occGridZoomImg)
    {
        #ifndef INPUTIMG
        const int obstacleLookahead=2;
        const int imgRows = static_cast<double>(obstacleLookahead)/METERSPERPIXELS;
        const int imgCols = static_cast<double>(obstacleLookahead)/METERSPERPIXELS+10;
        // zoomed image 
        
        const int zoomImgRows= imgRows*ZOOMFACTOR;
        const int zoomImgCols = imgCols*ZOOMFACTOR;
    
        // make a random eigen matrix of 1s and 0s
        Eigen::MatrixXd occGrid=Eigen::MatrixXd::Constant(imgRows,imgCols, 0);
        Eigen::MatrixXd occZoomGrid=Eigen::MatrixXd::Constant(zoomImgRows,zoomImgCols, 0);
        // lets fill 2000 cells out of 250000
        std::vector<int> rows(100);
        std::vector<int> cols(100);
        std::generate(rows.begin(), rows.end(), [](){return static_cast<int>(std::rand()%(imgRows-2)+1);});
        std::generate(cols.begin(), cols.end(), [](){return static_cast<int>(std::rand()%(imgCols-2)+1);});
        for (const auto& row: rows)
        {
            for (const auto& col: cols)
            {
                occGrid(row, col)=0;
                for (int i=row*ZOOMFACTOR;i<(row+1)*ZOOMFACTOR; i++)
                {
                    for(int j=col*ZOOMFACTOR; j<(col+1)*ZOOMFACTOR; j++)
                    {
                        occZoomGrid(i,j)=1;
                    }
                }
            }
        }
        //convert -1s to 1s
        
        // save it as png with occupied grids in black
        cv::Mat occGridImg;//(cv::Size(imgCols, imgRows), CV_32FC1, cv::Scalar(0));
        std::cout<<occGridImg.rows<<" "<<occGridImg.cols<<std::endl;
        eigen2cv(occGrid, occGridImg);
        std::cout<<occGridImg.rows<<" "<<occGridImg.cols<<std::endl;
        occGridImg.convertTo(occGridImg, CV_8U, 255.0);
        cv::imwrite("occGridImg.png", occGridImg);
        // (cv::Size(zoomImgRows, zoomImgCols), CV_32FC1, cv::Scalar(0));
        eigen2cv(occZoomGrid, occGridZoomImg);
        occGridZoomImg.convertTo(occGridZoomImg, CV_8U, 255.0);
        cv::imwrite("occZoomGridImg.png", occGridZoomImg);
        #else
        cv::Mat occGridZoomImgUnpad=cv::imread(INPUTIMG, CV_8UC1);
        // since it finds the corners of an image as a contour as well
        // we should add some padding to this image
        // otherwise the obstacles get encoded with the boundary as one contour and that sucks
        occGridZoomImg=cv::Mat(cv::Size(occGridZoomImgUnpad.cols+20,occGridZoomImgUnpad.rows+20), CV_8UC1, cv::Scalar(255));
        std::cout<<occGridZoomImg.size()<<std::endl;
        occGridZoomImgUnpad.copyTo(occGridZoomImg.colRange(10, 10+occGridZoomImgUnpad.cols).rowRange(10, 10+occGridZoomImgUnpad.rows));
        std::cout<<occGridZoomImg.size()<<std::endl;
        cv::imwrite("occZoomGridImg.png", occGridZoomImg);
        #endif
    }

    ContourData convexHullopenCV(cv::Mat &occGridZoomImg)
    {
        ContourData contourData;
        // find contours
        cv::Mat occGridBinaryImg;
        cv::threshold(occGridZoomImg, occGridBinaryImg,230, 230, cv::THRESH_BINARY);
        // occGridZoomImg.convertTo(occGridBinaryImg, CV_8U, 1.0/255.0);
        cv::imwrite("occZoomGridBinaryImg.png", occGridBinaryImg);
        findContours(occGridBinaryImg, contourData.contours, contourData.hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
        /**
         * this function keeps finding the boundary of the image itself as a boundary/contour
         * so i am gonna pop that out
         * need to check what happens with the occupancy grid of the robot
        */
        contourData.contours.pop_back();
        contourData.hierarchy.pop_back();
        std::vector<std::vector<cv::Point>> hull(contourData.contours.size()); 
        // std::cout<<"What the hell 1"<<std::endl;
        for(int i = 0; i < contourData.contours.size(); i++)
        {
            cv::convexHull(cv::Mat(contourData.contours[i]), hull[i], false);
        }

        // draw the convex hull
        // create a blank image (black image)
        // std::cout<<contourData.contours.size()<<" "<<contourData.hierarchy.size()<<std::endl;
        // std::cout<<contourData.contours[3].size()<<std::endl;
        cv::Mat drawing = cv::Mat::zeros(occGridBinaryImg.size(), CV_8UC3); 
        for(int i = 0; i < contourData.contours.size(); i++) 
        {
            std::cout<<i<<std::endl;
            cv::Scalar color_contours = cv::Scalar(0, 255, 0); // green - color for contours
            cv::Scalar color = cv::Scalar(255, 0, 0); // blue - color for convex hull
            // draw ith contour
            cv::drawContours(drawing, contourData.contours, i, color_contours, 1, 8,contourData.hierarchy);
            // draw ith convex hull
            // cv::drawContours(drawing, hull, i, color, 1, 8, contourData.hierarchy);
        }
        // std::cout<<"What the hell 3"<<std::endl;
        // std::cout<<hull.size()<<std::endl;
        cv::imwrite("occGridImgContours.png", drawing);
        return contourData;
    }

    void contours2Poly(cv::Mat& occGridZoomImg, ContourData& contourData)
    {
        // approximates each contour to polygon
        std::vector<cv::Mat> polygonsVec;
        for (const auto& contour: contourData.contours) 
        {

            cv::Mat polygon;
            std::cout<<"size of contour= "<<contour.size()<<std::endl;
            cv::approxPolyDP(contour, polygon, std::min(static_cast<double>(contour.size())/100.0, 10.0), true);
            polygonsVec.push_back(polygon);
        }
        // draw contours with random Scalar
        cv::Mat dst = cv::Mat::zeros(occGridZoomImg.size(), CV_8UC3); 
        for (int i = 0; i < contourData.contours.size(); ++i) 
        {
            cv::Scalar color=cv::Scalar(0,255,0);
            cv::drawContours(dst, polygonsVec, i, color, 1, 8, contourData.hierarchy, 0);
        }
        cv::Mat dstUnpad=cv::Mat(cv::Size(dst.cols-20,dst.rows-20), CV_8UC1, cv::Scalar(0));
        // cv::Rect rect(10,10, dst.rows, dst.cols);
        // dstUnpad =dst.colRange(10,dst.cols-10).rowRange(10,dst.cols-10);
        // dst.copyTo(dstUnpad.colRange(10, 10+occGridZoomImgUnpad.cols).rowRange(10, 10+occGridZoomImgUnpad.rows));
        cv::imwrite("occGridImgCntPoly.png", dstUnpad);
    }
}

/**
 * https://www.learnopencv.com/convex-hull-using-opencv-in-python-and-c/
 * https://docs.opencv.org/3.4/js_contour_features_approxPolyDP.html
 * https://www.youidraw.com/apps/painter/#
 */ 
int main()
{
    // input to be specified or taken as an external png
    cv::Mat occGridZoomImg;
    FSR::loadImage(occGridZoomImg);
    FSR::ContourData contourData = FSR::convexHullopenCV(occGridZoomImg);
    // just use the contours and make them coarse/sparse
    FSR::contours2Poly(occGridZoomImg, contourData);
    // make a signed distance field

    return 0;
}
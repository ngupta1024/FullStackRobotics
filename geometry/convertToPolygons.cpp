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

int main()
{
    // meters 20mx20m occupancy
    const int obstacleLookahead=2;
    const int imgRows = static_cast<double>(obstacleLookahead)/METERSPERPIXELS;
    const int imgCols = static_cast<double>(obstacleLookahead)/METERSPERPIXELS;
    // zoomed image 
      
    const int zoomImgRows= imgRows*ZOOMFACTOR;
    const int zoomImgCols = imgCols*ZOOMFACTOR;
   
    // make a random eigen matrix of 1s and 0s
    Eigen::MatrixXd occGrid=Eigen::MatrixXd::Constant(imgRows,imgCols, 255);
    Eigen::MatrixXd occZoomGrid=Eigen::MatrixXd::Constant(zoomImgRows,zoomImgCols, 255);
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
                    occZoomGrid(i,j)=0;
                }
            }
        }
    }
    
    // save it as png with occupied grids in black
    cv::Mat occGridImg(cv::Size(imgRows, imgCols), CV_32FC1, cv::Scalar(0));
    eigen2cv(occGrid, occGridImg);
    cv::imwrite("occGridImg.png", occGridImg);
    cv::Mat occGridZoomImg(cv::Size(zoomImgRows, zoomImgCols), CV_32FC1, cv::Scalar(0));
    eigen2cv(occZoomGrid, occGridZoomImg);
    cv::imwrite("occZoomGridImg.png", occGridZoomImg);

    std::vector< std::vector<cv::Point> > contours; // list of contour points
    std::vector<cv::Vec4i> hierarchy; 
    // find contours
    cv::Mat occGridBinaryImg;
    occGridZoomImg.convertTo(occGridBinaryImg, CV_8U, 1.0/255.0);
    findContours(occGridBinaryImg, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    std::vector<std::vector<cv::Point> > hull(contours.size()); 
    for(int i = 0; i < contours.size(); i++)
    {
        cv::convexHull(cv::Mat(contours[i]), hull[i], false);
    }

    // draw the convex hull
    // create a blank image (black image)
    cv::Mat drawing = cv::Mat::zeros(occGridBinaryImg.size(), CV_8UC3); 
    for(int i = 0; i < contours.size(); i++) 
    {
        cv::Scalar color_contours = cv::Scalar(0, 255, 0); // green - color for contours
        cv::Scalar color = cv::Scalar(255, 0, 0); // blue - color for convex hull
        // draw ith contour
        cv::drawContours(drawing, contours, i, color_contours, 1, 8,hierarchy);
        // draw ith convex hull
        cv::drawContours(drawing, hull, i, color, 1, 8,hierarchy);
    }
    std::cout<<hull.size()<<std::endl;
    cv::imwrite("occGridImgContours.png", drawing);
    return 0;
}

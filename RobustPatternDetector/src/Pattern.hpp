#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "CameraCalibration.hpp"
#include <opencv2/opencv.hpp>

/**
 * Store the image data and computed descriptors of target pattern
 */
struct Pattern
{
    cv::Size                  size;
    cv::Mat                   frame;
    cv::Mat                   grayImg;

    std::vector<cv::KeyPoint> keypoints;
    cv::Mat                  descriptors;

    std::vector<cv::Point2f>  points2d;
    std::vector<cv::Point3f>  points3d;
};

/**
 * Intermediate pattern tracking info structure
 */
struct PatternTrackingInfo
{
    cv::Mat                     homography;
    std::vector<cv::Point2f>    points2d;

    void draw2dContour(cv::Mat& image, cv::Scalar color) const;
};

#endif

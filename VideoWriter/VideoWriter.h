#ifndef VIDEOWRITER_H
#define VIDEOWRITER_H

#include "opencv2/opencv.hpp"

class VideoWriter
{
public:
    explicit VideoWriter();

public:
    void updateFrame(const cv::Mat &img);
    void release();
    bool startRecordToFile(std::string filename, int codec = CV_FOURCC('D','I','V','X'), double fps = 15.0, cv::Size frameSize = cv::Size(640, 480));

private:
    cv::VideoWriter m_writer;

};

#endif // QVIDEOWRITER_H

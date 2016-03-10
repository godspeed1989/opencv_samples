#include "PatternDetector.hpp"
#include "CameraCalibration.hpp"
#include <opencv2/opencv.hpp>

int main(int argc, const char * argv[])
{
    if (argc < 2)
    {
        std::cout << "Input image not specified" << std::endl;
        std::cout << "Usage: markerless_ar_demo <pattern image> <query image>" << std::endl;
        return 1;
    }

    // Try to read the pattern:
    cv::Mat patternImage = cv::imread(argv[1]);
    if (patternImage.empty())
    {
        std::cout << "Input image cannot be read" << std::endl;
        return 2;
    }

    std::string input = argv[2];
    cv::Mat testImage = cv::imread(input);
    if (!testImage.empty())
    {
        // Change this calibration to yours:
        //CameraCalibration calibration(526.58037684199849f, 524.65577209994706f, 318.41744018680112f, 202.96659047014398f);
        PatternDetector m_patternDetector;

        //
        Pattern m_pattern;
        m_patternDetector.buildPatternFromImage(patternImage, m_pattern);
        m_patternDetector.train_matcher(m_pattern);
        std::cout << "pattern keys " << m_pattern.keypoints.size() << std::endl;

        // Tries to find a @m_pattern object on given @testImage.
        PatternTrackingInfo m_queryInfo;
        bool patternFound = m_patternDetector.findPattern(testImage, m_queryInfo);

        std::cout << m_queryInfo.homography << std::endl;
        m_queryInfo.draw2dContour(testImage, cv::Scalar(0,0,255));
        cv::imwrite("out.jpg", testImage);
    }

    return 0;
}

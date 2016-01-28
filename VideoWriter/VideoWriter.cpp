#include "VideoWriter.h"
#include <stdio.h>

VideoWriter::VideoWriter()
{
}

void VideoWriter::updateFrame(const cv::Mat &img)
{
    if(m_writer.isOpened()) {
        cv::Mat output = img.clone();
        m_writer.write(output);
    }
    else
        printf("writer is not ready\n");
}

void VideoWriter::release()
{
    m_writer.release();
}

bool VideoWriter::startRecordToFile(std::string filename, int codec, double fps, cv::Size frameSize)
{
    return m_writer.open(filename, codec, fps, frameSize);
}

#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    VideoWriter VW;
    VW.startRecordToFile("VideoWriterOut.MP4");
    for (i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
        cv::Mat im = cv::imread(argv[i]);
        VW.updateFrame(im);
        sleep(1);
    }
    VW.release();
    return 0;
}

#include "depthtounity.h"

#include "depthtounity_global.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "monodepth/monodepth.h"

cv::Mat _currentFrame;


extern "C" DEPTHTOUNITYSHARED_EXPORT void GetRawImageBytes(uchar *data, int width, int height)
{
    monodepth::MonoDepth m(width, height, "/home/ruslan/repos/monodepth-cpp/model_city2kitti.pb");
    cv::Mat depth;
    //Mat fillIt(height, width, CV_8UC4, raw);
    cv::Mat frame(cv::imread("/home/ruslan/repos/monodepth-cpp/images/img.png"));
    assert(!frame.empty());

    m.inference(frame, depth);

    // convert disparity to depth
    depth = 0.3128f / (depth + 0.00001f);

    double min_val, max_val;
    cv::Mat depthmap_visual;
    cv::threshold(depth, depthmap_visual, 50.0, 50.0, cv::THRESH_TRUNC);
    minMaxLoc(depthmap_visual, &min_val, &max_val);
    depthmap_visual = 255 * (depthmap_visual - min_val) / (max_val - min_val);
    depthmap_visual.convertTo(depthmap_visual, CV_8U);
    applyColorMap(depthmap_visual, depthmap_visual, 2);

    _currentFrame = depthmap_visual;

    //Resize Mat to match the array passed to it from C#
    cv::Mat resizedMat(height, width, _currentFrame.type());
    cv::resize(_currentFrame, resizedMat, resizedMat.size(), cv::INTER_CUBIC);

    //Convert from RGB to ARGB
    cv::Mat argbImg;
    cv::cvtColor(resizedMat, argbImg, CV_RGB2BGRA);
    cv::Mat argb_img;
    cv::cvtColor(resizedMat, argb_img, CV_RGB2BGRA);
    std::vector<cv::Mat> bgra;
    cv::split(argb_img, bgra);
    std::swap(bgra[0], bgra[3]);
    std::swap(bgra[1], bgra[2]);
    std::memcpy( data, argbImg.data, argbImg.total() * argbImg.elemSize() );

}

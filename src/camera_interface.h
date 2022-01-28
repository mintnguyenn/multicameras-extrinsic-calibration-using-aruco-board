#ifndef CAMERA_INTERFACE_H
#define CAMERA_INTERFACE_H

#include <iostream>

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/calib3d.hpp>

#include <yaml-cpp/yaml.h>
#include <unistd.h>

struct BoardConfiguration{
    std::vector<std::vector<cv::Point3f>> objPoints;
    cv::Ptr<cv::aruco::Dictionary> dictionary;
    std::vector<int> ids;
}; 

struct CameraData{
    cv::Mat image;
    std::mutex img_mtx;
    cv::Mat instrinsic;
    std::mutex i_mtx;
};

class CameraInterface{
public:
    CameraInterface(){}; // Default constructor

    virtual void setCameraMatrix(cv::Mat camera_matrix) = 0;

    virtual void setCameraImage(cv::Mat input_image) = 0;

    virtual bool Read_ArUco_YAML(const std::string &fileName, cv::Ptr<cv::aruco::Dictionary> &dictionary,
                                 std::vector<int> &ids, std::vector<std::vector<cv::Point3f>> &objPoints) = 0;

    /**
    Create and run the threads of this class
    */
    virtual void runThreads() = 0;

    virtual void extrinsicCalibration() = 0;

    virtual cv::Mat getTransformationMatrix() = 0;
};

#endif // CAMERA_INTERFACE_H
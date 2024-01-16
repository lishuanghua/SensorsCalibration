/*
 * Copyright (C) 2022 by Autonomous Driving Group, Shanghai AI Laboratory
 * Limited. All rights reserved.
 * Yan Guohang <yanguohang@pjlab.org.cn>
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include "camera_calibrator.hpp"

int main(int argc, char **argv)
{
    std::cout << "Enter in int main(int argc, char **argv) function" << std::endl;

    if (argc != 3)
    {
        std::cout << "Usage: ./main camera_dir csv_file"
                     "\nexample:\n\t"
                     "./bin/lidar2camera data/intrinsic/ data/circle.csv"
                  << std::endl;

        return 0;
    }

    std::string image_dir = argv[1];
    std::string csv_file = argv[2];
    std::cout << "csv_file : " << csv_file << std::endl;
    std::ifstream fin(csv_file);
    std::string line;
    bool is_first = true;
    std::vector<std::vector<std::string>> lidar_3d_pts;

    while (getline(fin, line))
    {
        // std::cout << "line : " << line << std::endl;
        if (is_first)
        {
            is_first = false;
            continue;
        }

        std::istringstream sin(line);
        std::vector<std::string> fields;
        std::string field;

        while (getline(sin, field, ','))
        {
            // std::cout << "field : " << field << std::endl;
            fields.push_back(field);
        }

        /*
        for (auto it : fields)
        {
            std::cout << it << " ";
        }
        std::cout << std::endl;
        */

        lidar_3d_pts.push_back(fields);
    }

    /*
    for (auto x : lidar_3d_pts)
    {
        for (auto y : x)
        {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
    */

    std::cout << "image_dir : " << image_dir << std::endl;
    std::vector<cv::String> images;
    cv::glob(image_dir, images);
    std::vector<cv::Mat> vec_mat;
    std::vector<std::string> images_name;

    for (const auto &path : images)
    {
        // std::cout << "path : " << path << std::endl;
        cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE); // 读取图片时直接转换为灰度图
        vec_mat.push_back(img);
        images_name.push_back(path);
    }

    CameraCalibrator m;
    cv::Mat camera_matrix = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0));
    cv::Mat k = cv::Mat(1, 5, CV_32FC1, cv::Scalar::all(0));
    std::vector<cv::Mat> tvecsMat;
    std::vector<cv::Mat> rvecsMat;
    m.set_input(images_name, vec_mat, cv::Size{17, 7}, lidar_3d_pts);
    m.get_result(camera_matrix, k, cv::Size{1920, 1200}, rvecsMat, tvecsMat);

    std::cout << "Leave out int main(int argc, char **argv) function" << std::endl;

    return 0;
}
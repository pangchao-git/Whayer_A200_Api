/*****************************************************************************
Copyright: Whayer
File name: hy_detect.h
Author: pc
email: 1569598596@qq.com
Description: 
Version: 
Date_time: 2022/8/15 下午3:50
History: 
*****************************************************************************/

#ifndef A200_NPU_SAMPLE_HY_DETECT_H
#define A200_NPU_SAMPLE_HY_DETECT_H

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "yolo_v3_com.h"
#include "sample_npu_main.h"
#include "sample_svp_npu_software.h"
#include "sample_comm_svp.h"
#include "sample_comm_npu.h"
#include <mutex>
using namespace std;
using namespace cv;

enum Model_type {
	YOLOV3 = 0,
	FASTER_RCNN_FPN
};


typedef struct Parms_t {
	int model_type; // 1 yolov3 2 fast rcnn 3 yolov4 4 mask rcnn
	int lettbox;   //1 等比例缩放 0 直接resize到模型的宽高
	float class_th;
//    float Anchors[30]={0};
	std::vector<float> Anchors;
	std::vector<int>   mask;
	int class_num;
	int kGridSize[3];
	float nms_th;
	float model_h;
	float model_w;
} Parms;

class hy_detect {
public:
	hy_detect();
	~hy_detect();
	int A200_load_model(std::string cfg_file,std::string bmodel_path,int device_id);
	int A200_detect(const cv::Mat &image, HYYOLOV3RESULT_PLIST pResultList);
	int A200_detect(YOLOV3_PIMAGES Img,HYYOLOV3RESULT_PLIST pResultList);
	int A200_detect(char *p_data, const int img_h,const int img_w, HYYOLOV3RESULT_PLIST pResultList);

private:
	void Clean_str(std::string &str);
	vector<string> split(string strtem, char a);
	cv::Mat color_convert(const cv::Mat &img_src);
	void SetParams(const char *cfgfile, Parms_t &params);
	int CheckFile(const std::string &file_path);
	Parms m_params;
	
	SAMPLE_SVP_NPU_MODEL_S                   s_stYolov3Model = {0};
	SAMPLE_SVP_NPU_PARAM_S                   s_stYolov3NpuParam = {0};
//	std::mutex m_mtx;

};


#endif //A200_NPU_SAMPLE_HY_DETECT_H

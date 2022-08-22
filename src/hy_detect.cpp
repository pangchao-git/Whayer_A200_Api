/*****************************************************************************
Copyright: Whayer
File name: hy_detect.cpp
Author: pc
email: 1569598596@qq.com
Description: 
Version: 
Date_time: 2022/8/15 下午3:50
History: 
*****************************************************************************/

#include "hy_detect.h"
#include <sys/prctl.h>
#include "cJSON.h"
#include <time.h>


#include <chrono>
using namespace chrono;




/******************************************************************************
* function : NPU Forward
******************************************************************************/
SC_S32 SAMPLE_COMM_SVP_NPU_Forward(SAMPLE_SVP_NPU_MODEL_S *pstNpuModel,
                                   SAMPLE_SVP_NPU_PARAM_S *pstNpuParam, NPU_IMAGE_S *pstImg,
                                   SC_BOOL bInstant)
{
	SC_S32 s32Ret = SC_FAILURE;
	SVP_NPU_HANDLE hSvpNpuHandle = 0;
	
	s32Ret =  SC_MPI_SVP_NPU_Forward(&hSvpNpuHandle, pstImg, &pstNpuParam->stIntMem, &pstNpuModel->stModel,
	                                 &pstNpuParam->stOutMem, bInstant);
	SAMPLE_SVP_CHECK_EXPR_RET(SC_SUCCESS != s32Ret, s32Ret, SAMPLE_SVP_ERR_LEVEL_ERROR,
	                          "Error,SC_MPI_SVP_NPU_Forward failed!\n");
	
	return s32Ret;
}

SC_S32 SAMPLE_SVP_NPU_Deinit(SAMPLE_SVP_NPU_MODEL_S *pstNpuModel, SAMPLE_SVP_NPU_PARAM_S *pstNpuParam)
{
	SC_S32 s32Ret = SC_SUCCESS;
	/*hardware para deinit*/
	if(pstNpuParam != NULL)
	{
		s32Ret = SAMPLE_COMM_SVP_NPU_ParamDeinit(pstNpuParam);
		SAMPLE_SVP_CHECK_EXPR_TRACE(SC_SUCCESS != s32Ret, SAMPLE_SVP_ERR_LEVEL_ERROR,
		                            "Error,SAMPLE_COMM_SVP_NPU_ParamDeinit failed!\n");
	}
	
	/*model deinit*/
	if(pstNpuModel != NULL)
	{
		s32Ret = SAMPLE_COMM_SVP_NPU_UnloadModel(pstNpuModel);
		SAMPLE_SVP_CHECK_EXPR_TRACE(SC_SUCCESS != s32Ret, SAMPLE_SVP_ERR_LEVEL_ERROR,
		                            "Error,SAMPLE_COMM_SVP_NPU_UnloadModel failed!\n");
	}
	return s32Ret;
}


/*** function : print detection result
******************************************************************************/
SC_S32 SAMPLE_SVP_NPU_Detection_PrintResult(SAMPLE_SVP_NPU_DETECTION_OUTPUT *pResult, SC_S32 s32ResultNum,
		float scale_w,float scale_h,HYYOLOV3RESULT_PLIST pResultList)
{
	if(0 == s32ResultNum)
	{
		SAMPLE_SVP_TRACE_INFO("SAMPLE_SVP_NPU_Detection_PrintResult is NULL\n");
		return 0;
	}
	else
	{
		if(SC_NULL == pResult)
		{
			SAMPLE_SVP_TRACE_ERR("pResult is NULL\n");
			return SC_FAILURE;
		}
		
		int target_num=0;
		for(int i = 0; i < s32ResultNum; ++ i)
		{
			
			int class_id = pResult[i].classId;
			float left = pResult[i].x*scale_w;
			float top = pResult[i].y*scale_h;
			float right = (pResult[i].w+pResult[i].x)*scale_w;
			float bottom = (pResult[i].h+pResult[i].y)*scale_h;
			float score = pResult[i].confidence;
			
			#if 0
			SAMPLE_SVP_TRACE_INFO("x1=%f y1=%f x2=%f y2=%f conf=%f,class_id=%d\n", left, top, right, bottom,
			                      pResult[i].confidence,class_id);
			#endif
			
			pResultList->pResult[target_num].Target.left = left;
			pResultList->pResult[target_num].Target.top = top;
			pResultList->pResult[target_num].Target.right = right;
			pResultList->pResult[target_num].Target.bottom = bottom;
			pResultList->pResult[target_num].dVal = class_id;
			pResultList->pResult[target_num].dConfidence = score;
			target_num++;
			
		}
		pResultList->lResultNum =target_num;
	}
	
	return SC_SUCCESS;
}


hy_detect::hy_detect(){

}

int hy_detect::A200_detect(YOLOV3_PIMAGES Img, HYYOLOV3RESULT_PLIST pResultList) {
	
	
	auto start = system_clock::now();
	if (!Img || !pResultList) {
		//printf("input error!!!!\n");
		return -1;
	}
	int img_c = Img->lPixelArrayFormat;
	int img_h = Img->lHeight;
	int img_w = Img->lWidth;
	cv::Mat image;
	if (img_c == 1) {
		image = cv::Mat(img_h, img_w, CV_8UC1, Img->pixelArray.chunky.pPixel,
		                Img->pixelArray.chunky.lLineBytes);
	} else if (img_c == 3) {
		
		image = cv::Mat(img_h, img_w, CV_8UC3, Img->pixelArray.chunky.pPixel,
		                Img->pixelArray.chunky.lLineBytes);
		
	} else if (img_c == 4) {
		image = cv::Mat(img_h, img_w, CV_8UC4,
		                Img->pixelArray.chunky.pPixel,
		                Img->pixelArray.chunky.lLineBytes);
	} else {
		//nothing to do!!
	}
	
	//Img to mat
	
	
	
	
	cv::Mat sample_resized;
	cv::resize(image, sample_resized, cv::Size(m_params.model_w,m_params.model_h), cv::INTER_LINEAR);
	cv::cvtColor(sample_resized, sample_resized, cv::COLOR_BGR2RGB);
	
	unsigned short u16Stride = ALIGNED_256B(sample_resized.cols);
	
	int s32FileSize = u16Stride * sample_resized.rows * sample_resized.channels();
	char *pBuf = (char*)malloc(s32FileSize);
	if(pBuf == NULL)
	{
		printf("Malloc %d bytes failed.\n", s32FileSize);
		return -1;
	}
	
	cv::Mat channels[3];
	cv::split(sample_resized, channels);
	char *pchR = (char *)channels[2].data;
	char *pchG = (char *)channels[1].data;
	char *pchB = (char *)channels[0].data;
	
	for(int i = 0;i< sample_resized.rows;i++)
	{
		for(int j = 0;j< sample_resized.cols;j++)
		{
			pBuf[i*u16Stride + j] 				  = pchR[i*sample_resized.cols + j];
			pBuf[(i+sample_resized.rows)*u16Stride + j]    = pchG[i*sample_resized.cols + j];
			pBuf[(i+sample_resized.rows*2)*u16Stride + j]  = pchB[i*sample_resized.cols + j];
		}
		for(int j = sample_resized.cols;j< u16Stride;j++)
		{
			pBuf[i*u16Stride + j] 				  = 0;
			pBuf[(i+sample_resized.rows)*u16Stride + j]    = 0;
			pBuf[(i+sample_resized.rows*2)*u16Stride + j]  = 0;
		}
	}
	
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout<<"A200 propress cost"
	    <<double(duration.count())*microseconds::period::num/microseconds::period::den
	    <<"s"<<endl;
	
	int ret =   A200_detect(pBuf,img_h,img_w,pResultList);
	free(pBuf);
	pBuf=NULL;
	return ret;
	
	
}

int hy_detect::A200_detect(char*p_data, const int img_h,const int img_w, HYYOLOV3RESULT_PLIST pResultList){
	
//	std::lock_guard<std::mutex> lck(m_mtx);
	NPU_IMAGE_S yolov3_image;
	SC_S32 s32Ret = SC_FAILURE;
	yolov3_image.u32InputNum = 1;
	yolov3_image.astInputImg[0].u32BatchNum = 1;
//    yolov3_image.astInputImg[0].stImages[0].enType = SVP_IMG_YUV420P;
	SVP_IMAGE_TYPE_E model_types;
	model_types = SVP_IMG_RGB;
	const int model_h = m_params.model_h;
	const int model_w = m_params.model_w;
	float scale_w=(float)img_w/model_w;
	float scale_h=(float)img_h/model_h;
	//读取图片数据,转化为yuv数据传入模型
	
	yolov3_image.astInputImg[0].stImages[0].enType = model_types;
	yolov3_image.astInputImg[0].stImages[0].u32Height = model_h;
	yolov3_image.astInputImg[0].stImages[0].u32Width = model_w;
//    s32Ret = SAMPLE_COMM_SVP_NPU_FillSrcData(pcSrcFile, &s_stYolov3NpuParam, &yolov3_image, SVP_IMG_YUV420P);
	
	auto start = system_clock::now();
	s32Ret = SAMPLE_COMM_SVP_NPU_FillSrcData(p_data, &s_stYolov3NpuParam, &yolov3_image, model_types);
	if(SC_SUCCESS != s32Ret){
		std::cout<<"Error,SAMPLE_SVP_NPU_FillSrcData failed!\n";
		SAMPLE_SVP_NPU_Deinit(&s_stYolov3Model, &s_stYolov3NpuParam);
		return -1;
	}
	
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout<<"A200 SAMPLE_COMM_SVP_NPU_FillSrcData cost"
	    <<double(duration.count())*microseconds::period::num/microseconds::period::den
	    <<"s"<<endl;
	
	/*NPU process*/
	start = system_clock::now();;
	for(int j = 0; j < 1; j++)
	{
		s32Ret = SAMPLE_COMM_SVP_NPU_Forward(&s_stYolov3Model, &s_stYolov3NpuParam, &yolov3_image, SC_TRUE);
		
		if(SC_SUCCESS != s32Ret){
			std::cout<<"Error,SAMPLE_COMM_SVP_NPU_Forward failed!\n";
			SAMPLE_SVP_NPU_Deinit(&s_stYolov3Model, &s_stYolov3NpuParam);
			return -1;
		}
	}
	end = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	cout<<"A200 npu Forward cost"
	    <<double(duration.count())*microseconds::period::num/microseconds::period::den
	    <<"s"<<endl;
	/*Software process and Get result*/
	SC_VOID *pResult = SC_NULL;
	SC_S32   s32ResultNum;
	//获取后处理结果
	int tensor_output_nums = s_stYolov3Model.stModel.u16DstNum;
	printf("tensor_output_nums=%d\n",tensor_output_nums);
	float anchors[18]={0};
	for(int i=0;i<m_params.Anchors.size();i++){
		anchors[i]=m_params.Anchors[i];
	}
	float class_th=m_params.class_th;
	float nms_th=m_params.nms_th;
	
	SAMPLE_SVP_NPU_YOLOVX_GetResult(s_stYolov3Model.stModel.astDstTensor, s_stYolov3Model.stModel.u16DstNum,
	                                (uintptr_t)s_stYolov3NpuParam.stOutMem.u64VirAddr, &pResult, &s32ResultNum, 3,
	                                yolov3_image.astInputImg[0].stImages[0].u32Width, yolov3_image.astInputImg[0].stImages[0].u32Height
	                                ,anchors,class_th,nms_th);
	SAMPLE_SVP_TRACE_INFO("Yolov3 result:\n");
	//获取输出结果
	s32Ret = SAMPLE_SVP_NPU_Detection_PrintResult((SAMPLE_SVP_NPU_DETECTION_OUTPUT*)pResult,
			s32ResultNum,scale_w,scale_h, pResultList);
	return s32Ret;
	
	
}

int hy_detect::A200_detect(const cv::Mat &image, HYYOLOV3RESULT_PLIST pResultList) {
	
	cv::Mat bgr_mat=image.clone();
	int im_height = bgr_mat.rows;
	int im_width = bgr_mat.cols;
	cv::Mat sample_resized;
	cv::resize(bgr_mat, sample_resized, cv::Size(m_params.model_w,m_params.model_h), cv::INTER_LINEAR);
	cv::cvtColor(sample_resized, sample_resized, cv::COLOR_BGR2RGB);
	
	unsigned short u16Stride = ALIGNED_256B(sample_resized.cols);
	
	int s32FileSize = u16Stride * sample_resized.rows * sample_resized.channels();
	char *pBuf = (char*)malloc(s32FileSize);
	if(pBuf == NULL)
	{
		printf("Malloc %d bytes failed.\n", s32FileSize);
		return -1;
	}
	
	cv::Mat channels[3];
	cv::split(sample_resized, channels);
	char *pchR = (char *)channels[2].data;
	char *pchG = (char *)channels[1].data;
	char *pchB = (char *)channels[0].data;
	
	for(int i = 0;i< sample_resized.rows;i++)
	{
		for(int j = 0;j< sample_resized.cols;j++)
		{
			pBuf[i*u16Stride + j] 				  = pchR[i*sample_resized.cols + j];
			pBuf[(i+sample_resized.rows)*u16Stride + j]    = pchG[i*sample_resized.cols + j];
			pBuf[(i+sample_resized.rows*2)*u16Stride + j]  = pchB[i*sample_resized.cols + j];
		}
		for(int j = sample_resized.cols;j< u16Stride;j++)
		{
			pBuf[i*u16Stride + j] 				  = 0;
			pBuf[(i+sample_resized.rows)*u16Stride + j]    = 0;
			pBuf[(i+sample_resized.rows*2)*u16Stride + j]  = 0;
		}
	}
	int ret =   A200_detect(pBuf,im_height,im_width,pResultList);
	free(pBuf);
	pBuf=NULL;
	return ret;

	
	
	


}

hy_detect::~hy_detect() {

}


int hy_detect::A200_load_model(std::string cfg_file, std::string bmodel_path, int device_id) {
//	std::lock_guard<std::mutex> lck(m_mtx);
	SetParams(cfg_file.c_str(),m_params);
	auto start = system_clock::now();
	s_stYolov3Model.stModelConf.enCbMode = SVP_NPU_NO_CB;
	s_stYolov3Model.stModelConf.enPriority = SVP_NPU_PRIORITY_NORMAL;
	
	/*Yolov3 Load model*/
	
	SC_S32 s32Ret = SC_FAILURE;
	SAMPLE_SVP_TRACE_INFO("Yolov3 Load model!!!!\n");
	s32Ret = SAMPLE_COMM_SVP_NPU_LoadModel((char*)bmodel_path.c_str(), &s_stYolov3Model);
	if(SC_SUCCESS !=s32Ret){
		std::cout<<"SAMPLE_COMM_SVP_NPU_LoadModel failed"<<std::endl;
//		SAMPLE_SVP_NPU_Deinit(&s_stYolov3Model, &s_stYolov3NpuParam);
		return -1;
	}
	
	/*Yolov3 parameter initialization*/
	s32Ret = SAMPLE_COMM_SVP_NPU_ParamInit(&s_stYolov3Model, &s_stYolov3NpuParam);
	if(SC_SUCCESS !=s32Ret){
		std::cout<<"AMPLE_SVP_NPU_Cnn_ParamInit failed!"<<std::endl;
//		SAMPLE_SVP_NPU_Deinit(&s_stYolov3Model, &s_stYolov3NpuParam);
		return -1;
	}
	
	
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout<<"Load model cost"
	    <<double(duration.count())*microseconds::period::num/microseconds::period::den
	    <<"s"<<endl;
	return s32Ret;
	
}

cv::Mat hy_detect::color_convert(const cv::Mat &img_src) {
	cv::Mat img_dst;
	if (img_src.channels() == 4) {
		cv::cvtColor(img_src, img_dst, cv::COLOR_BGRA2BGR);
		
		
	} else if (img_src.channels() == 3) {
		img_dst = img_src;
	} else if (img_src.channels() == 1) {
		cv::cvtColor(img_src, img_dst, cv::COLOR_GRAY2BGR);
	} else {
		std::cerr << " Warning: img_src.channels() is not 1, 3 or 4. It is = " << img_src.channels() << std::endl;
	}
	return img_dst;
}


vector<string> hy_detect::split(string strtem, char a) {
	vector<string> strvec;
	
	string::size_type pos1, pos2;
	pos2 = strtem.find(a);
	pos1 = 0;
	while (string::npos != pos2) {
		strvec.push_back(strtem.substr(pos1, pos2 - pos1));
		
		pos1 = pos2 + 1;
		pos2 = strtem.find(a, pos1);
	}
	strvec.push_back(strtem.substr(pos1));
	return strvec;
}

void hy_detect::Clean_str(std::string &str) {
	// str=str.substr(str.find('=')+1);
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '{'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '{'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '}'), str.end());
}



int hy_detect::CheckFile(const std::string &file_path) {
	struct stat buffer;
	return (stat(file_path.c_str(), &buffer) == 0);
	
}


void hy_detect::SetParams(const char *cfgfile, Parms_t &params) {
	
	int ret = access(cfgfile, F_OK);
	if (ret != 0) {
		//printf("%s is not exist!\n", cfgfile);
		return;
	}
	params.Anchors.clear();
	params.mask.clear();
	ifstream in(cfgfile);
	string line;
	std::vector<std::string> File_data;
	if (in) {
		while (getline(in, line)) {
			if (line.length() == 0) {
				continue;
			}
			Clean_str(line);
			//  //printf("File_data=%s\n",line.c_str());
			File_data.push_back(line);
		}
	}
	in.close();
	std::string label_str, anchor_str, kgride_str;
	for (int i = 0; i < File_data.size(); i++) {
		std::string str = File_data[i];
		string suffix_str = str.substr(0, str.find("="));
		// //printf("str=%s\n",suffix_str.c_str());
		if (suffix_str == "model_type") {
			int yolov3 = std::atoi(File_data[i].substr(File_data[i].find('=') + 1).c_str());
			params.model_type = yolov3;
		} else if (suffix_str == "lettbox") {
			int lettbox = std::atoi(File_data[i].substr(File_data[i].find('=') + 1).c_str());
			params.lettbox = lettbox;
		} else if (suffix_str == "anchor") {
			anchor_str = File_data[i].substr(File_data[i].find('=') + 1);
			std::vector<string> anchor_tmp = split(anchor_str, ',');
			for (int index = 0; index < anchor_tmp.size(); index++) {
//                params.Anchors[index] = std::atof(anchor_tmp[index].c_str());
				params.Anchors.push_back(std::atof(anchor_tmp[index].c_str()));
			}
			
		}else if (suffix_str == "mask") {
			anchor_str = File_data[i].substr(File_data[i].find('=') + 1);
			std::vector<string> anchor_tmp = split(anchor_str, ',');
			for (int index = 0; index < anchor_tmp.size(); index++) {
//                params.Anchors[index] = std::atof(anchor_tmp[index].c_str());
				params.mask.push_back(std::atoi(anchor_tmp[index].c_str()));
			}
			
		}else if (suffix_str == "model_h") {
			params.model_h = std::atoi(File_data[i].substr(File_data[i].find('=') + 1).c_str());
		} else if (suffix_str == "model_w") {
			params.model_w = std::atoi(File_data[i].substr(File_data[i].find('=') + 1).c_str());
		} else if (suffix_str == "class_num") {
			params.class_num = std::atoi(File_data[i].substr(File_data[i].find('=') + 1).c_str());
		} else if (suffix_str == "class_ths") {
			params.class_th = std::atof(File_data[i].substr(File_data[i].find('=') + 1).c_str());
		} else if (suffix_str == "nms_th") {
			params.nms_th = std::atof(File_data[i].substr(File_data[i].find('=') + 1).c_str());
		} else {
		
		}
	}

//	numBBoxes=params.Anchors.size()/6;
	if (params.nms_th == 0) {
		params.nms_th = 0.3;
	}
	if (params.class_th == 0) {
		params.class_th = 0.7;
	}
	int step=params.model_w/32;
	params.kGridSize[0]=step;
	params.kGridSize[1]=step*2;
	params.kGridSize[2]=step*4;
	
}


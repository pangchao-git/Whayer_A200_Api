#include <iostream>
#include <thread>
#include <string>
#include <stdlib.h>
#include <stdio.h>
//#include "whayer_bm1684_dll.h"
//#include "whayer_deetct.h"
//#include "Common.h"
#include "atlas_dll.h"
#include "yolo_v3_com.h"
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <sys/stat.h>
#include <mutex>
#include <chrono>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
typedef  struct model_s{
	std::string model_cfg;
	std::string model_wht;
	int device_id;
	std::string img_path;
	std::string label_path;
}model_t;

#define Draw_Rectangle 1
#define NC_TEST 0

using namespace cv;
using namespace std;
using namespace chrono;
std::mutex g_mutex;

bool g_stop_jyz=true;
bool g_stop_waiguan=true;
std::string DETECT_TYPE="yw_nc";
static void Clean_str(std::string & str){
//    str=str.substr(str.find('=')+1);
	str.erase(std::remove(str.begin(),str.end(),' '),str.end());
	str.erase(std::remove(str.begin(),str.end(),'\n'),str.end());
	str.erase(std::remove(str.begin(),str.end(),'\t'),str.end());
	str.erase(std::remove(str.begin(),str.end(),'\r'),str.end());
	str.erase(std::remove(str.begin(),str.end(),'{'),str.end());
	str.erase(std::remove(str.begin(),str.end(),'{'),str.end());
	str.erase(std::remove(str.begin(),str.end(),'}'),str.end());
}

static void Read_label(const char*label_txt,std::vector<std::string> & label){
	int ret = access(label_txt,F_OK);
	if (ret != 0){
		printf("%s is not exist!\n",label_txt);
		return;
	}
	ifstream in(label_txt);
	string line;
	std::vector<std::string> File_data;
	if (in){
		while (getline(in,line)){
			if (line.length() == 0){
				continue;
			}
			Clean_str(line);
			//  printf("File_data=%s\n",line.c_str());
			label.push_back(line);
		}
	}
	in.close();
	
}

static int IsFolderExist(const char*path){
	DIR *dr;
	dr = opendir(path);
	if (dr == NULL){
		closedir(dr);
		return -1;
	}
	closedir(dr);
	return 0;
}

void Draw_pic(const char*image_path,HYYOLOV3RESULT_LIST & result_list,std::vector<std::string> label_txt,
              std::string save_path){
	const vector<cv::Scalar> kColors{
			cv::Scalar(237,149,100),cv::Scalar(0,215,255),cv::Scalar(50,205,50),
			cv::Scalar(139,85,26)};
	const double kFountScale = 0.5;
	const cv::Scalar kFontColor(0,0,255);
	const uint32_t kLabelOffset = 11;
	cv::Mat image = cv::imread(image_path);
	stringstream sstream;
	for (int i = 0;i < result_list.lResultNum;i++){
		
		cv::Point p1,p2;
		p1.x = result_list.pResult[i].Target.left;
		p1.y = result_list.pResult[i].Target.top;
		p2.x = result_list.pResult[i].Target.right;
		p2.y = result_list.pResult[i].Target.bottom;
		int class_id = result_list.pResult[i].dVal;
		cv::Rect box = cv::Rect(p1.x, p1.y, p2.x - p1.x, p2.y - p1.y);
		cv::rectangle(image,p1,p2,kColors[i%kColors.size()],2);
		sstream.str(" ");
		sstream<<label_txt[int(result_list.pResult[i].dVal)]<<"=";
		sstream.precision(3);
		sstream<<result_list.pResult[i].dConfidence;
		string obj_str = sstream.str();
		cv::putText(image,obj_str,cv::Point(p1.x,p1.y + kLabelOffset),
		            cv::FONT_HERSHEY_COMPLEX,1,kFontColor);
		
		#if 0
		//绘制mask
		cv::Scalar color = kColors[i % kColors.size()];
		cv::Mat mask=result_list.pResult[i].mask.clone();
		printf("mask_h=%d,mask_w=%d\n",mask.rows,mask.cols);
		if (!mask.empty())
		{
			
			resize(mask, mask, cv::Size(p2.x - p1.x, p2.y - p1.y));
			int img_width=mask.cols;
			int img_height= mask.rows;
			
			
			//叠加获得颜色掩模
			cv::Mat coloredRoi = (0.4 * color + 0.6 * image(box));
			coloredRoi.convertTo(coloredRoi, CV_8UC3);
			// Draw the contours on the image 画轮廓
			std::vector<cv::Mat> contours;
			cv::Mat hierarchy;
			mask.convertTo(mask, CV_8U);
			//提取轮廓，用于提取图像的轮廓,contours 保存轮廓信息
			// findContours(mask, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
			findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
			drawContours(coloredRoi, contours, -1, color, 5, cv::LINE_8, hierarchy, 100);
			// cv::line(image,Start_point,End_point,cv::Scalar(0,0,255),5,CV_AA);
			coloredRoi.copyTo(image(box), mask);
		}
		#endif
		
	}
	printf("the save_path=%s\n",save_path.c_str());
	if (0 != IsFolderExist(save_path.c_str())){
		int ret = mkdir(save_path.c_str(),S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
		if (ret != 0){
			printf("mkdir failed,ret=%d\n",ret);
			return;
		}
	}
	
	std::string Image_path = image_path;
	int pos1 = Image_path.find_last_of('/');
	std::string tmp = Image_path.substr(pos1 + 1);
	int pos2 = tmp.find_last_of('.');
	std::string save_name = tmp.substr(0,pos2);
	save_name = save_path + "/" + save_name + ".jpg";
	cv::imwrite(save_name,image);
	printf("save %s ok!\n",save_name.c_str());
	
}

static std::string getExePath(){
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe",result,PATH_MAX);
	string exePath = string(result,(count > 0)?count:0);
	size_t pos = exePath.find_last_of("\\/");
	return (string::npos == pos)
	       ?""
	       :exePath.substr(0,pos);
}






void thread_loop3(int thread_id,const char*config_file,
                  const char*acl_file,const char*filename,std::vector<std::string> label_txt,std::string save_path,
                  int loop_count,int device_id){
	
	int Ret = -1;
	HYYOLOV3RESULT_LIST resultlist = {0};
	printf("**************!\n");
	resultlist.pResult = (HYYOLOV3_RESULT*)malloc(255*sizeof(HYYOLOV3_RESULT));
	if (resultlist.pResult == NULL){
		return;
	}
	printf("cfg_path=%s,model_path=%s\n",config_file,acl_file);
	std::vector<cv::String> file_names;
	cv::glob(filename,file_names);
	
	ofstream outfile;
	ofstream image_list;
	std::string save_txt = "Detect_100.txt";
	outfile.open(save_txt,ios_base::trunc);
	std::string imagelist = "image_list.txt";
	image_list.open(imagelist,ios_base::trunc);
	std::string head_line = "filename,name,score,xmin,ymin,xmax,ymax";
	outfile<<head_line<<endl;
	
	int count = loop_count;
	void *pHandle= nullptr;
	Ret = init_atlas(&pHandle,const_cast<char*>(config_file),const_cast<char*>(acl_file),0.3,device_id);
//	Ret = hy_init_bm(&pHandle,const_cast<char*>(config_file),const_cast<char*>(acl_file),0.3,0);
	if (0 != Ret){
		printf("init_atlas failed!\n");
		return;
	}
	while (count--){
		
		for (int i = 0;i < file_names.size();i++){
			
			auto start = system_clock::now();
//			init(config_file,acl_file,thread_id,&pHandle);
			if(pHandle==nullptr){
				printf("handle is nullprt!!!!!!!!!!!!!!!!!!!!!!!\n");
				continue;
			}
			
			auto end_pic = system_clock::now();
			auto duration = duration_cast<microseconds>(end_pic - start);
			cout<<"init const "
			    <<double(duration.count())*microseconds::period::num/microseconds::period::den
			    <<"秒"<<endl;
			
			
			std::string Image_path = file_names[i];
			int pos1 = Image_path.find_last_of('/');
			std::string image_name = Image_path.substr(pos1 + 1);
			
			image_list<<image_name<<endl;
			
			
			memset(resultlist.pResult,0,255*sizeof(HYYOLOV3_RESULT));
			struct timeval begin = {0};
			
			
			struct timeval begin_1 = {0};
			struct timeval end = {0};
			gettimeofday(&begin,nullptr);
			gettimeofday(&begin_1,nullptr);
			
			start = system_clock::now();
			cv::Mat img = cv::imread(file_names[i].c_str());
			if (img.empty()){
				continue;
			}
			end_pic = system_clock::now();
			duration = duration_cast<microseconds>(end_pic - start);
			cout<<"imread"
			    <<double(duration.count())*microseconds::period::num/microseconds::period::den
			    <<"秒"<<endl;
			std::cout<<"load image "<<file_names[i]<<" ok\n";
			YOLOV3_IMAGES p_img;
			p_img.lPixelArrayFormat = img.channels();
			p_img.lWidth = img.cols;
			p_img.lHeight = img.rows;
			p_img.pixelArray.chunky.pPixel = img.data;
			p_img.pixelArray.chunky.lLineBytes = img.step;
			start = system_clock::now();
//			hy_detect_bm(pHandle,&p_img,&resultlist);
			detec_atlas(pHandle,&p_img,&resultlist);
//			detec_atlas(pHandle,img,&resultlist);
			auto end_detect = system_clock::now();
			duration = duration_cast<microseconds>(end_detect - start);
			cout<<"detect chorn"
			    <<double(duration.count())*microseconds::period::num/microseconds::period::den
			    <<"秒"<<endl;
			
			gettimeofday(&end,nullptr);
			
			int numbox = resultlist.lResultNum;
			printf("numbox=%d\n",numbox);
			for (int index = 0;index < numbox;index++){
				
				std::string detect_txt;
				std::string detect_txt_nc_yw;
				int left = resultlist.pResult[index].Target.left;
				int top = resultlist.pResult[index].Target.top;
				int right = resultlist.pResult[index].Target.right;
				int bottom = resultlist.pResult[index].Target.bottom;
				int class_id = resultlist.pResult[index].dVal;
				float confidence = resultlist.pResult[index].dConfidence;
				detect_txt = image_name + "," + label_txt[class_id] + "," + std::to_string(confidence) + ","
				             + std::to_string(left) + "," + std::to_string(top) + "," + std::to_string(right) +
				             "," + std::to_string(bottom);
				printf("detect_txt=%s\n",detect_txt.c_str());
				outfile<<detect_txt<<endl;
			}

#if Draw_Rectangle
#if NC_TEST
			Draw_pic(file_names[i].c_str(),resultlist_nc_yw,label_txt,save_path);
#else
			Draw_pic(file_names[i].c_str(),resultlist,label_txt,save_path);

#endif

#endif
		
		}
	}
//	hy_uninit_bm(pHandle);
	uninit_atlas(pHandle);
	free(resultlist.pResult);
	resultlist.pResult = NULL;
	outfile.close();
	
	printf("Demo ALL Done thread_loop3!\n");
}



int main(int argc,char*argv[]){
	
	if(argc<6){
		printf("usage:cfg om pic_dir voc_name loop_count device_id!\n");
		return -1;
	}
	
	auto start = system_clock::now();
	//初始化算法库
//	Init_Atlas_Lib();
	
	std::string label_path=argv[4];
	std::vector<std::string> label;
	Read_label(label_path.c_str(),label);
	
	int loop_count=std::atoi(argv[5]);
	int device_id=std::atoi(argv[6]);
	std::thread thread_t=std::thread(thread_loop3,0,argv[1],argv[2],argv[3],label,"save_result",loop_count,device_id);
	std::thread thread_2=std::thread(thread_loop3,0,argv[1],argv[2],argv[3],label,"save_result1",loop_count,device_id);
	thread_t.join();
	thread_2.join();
	
	printf("ALL THREAD_TEST DONE!\n");
	auto end_pic = system_clock::now();
	auto duration = duration_cast<microseconds>(end_pic - start);
	cout<<"Detect cost"
	    <<double(duration.count())*microseconds::period::num/microseconds::period::den
	    <<"秒"<<endl;
	//卸载算法库
//	Uninit_Atlas_Lib();
	printf("ALL THREAD_TEST DONE Uninit_Atlas_Lib!\n");
	return 0;
}

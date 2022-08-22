#ifndef YOLOV3_COM_H
#define YOLOV3_COM_H
//#include <opencv2/opencv.hpp>
typedef struct {
	int		lWidth;				// Off-screen width
	int 	lHeight;			// Off-screen height
	int		lPixelArrayFormat;	// Format of pixel array
	union
	{
		struct
		{
			int lLineBytes;
			void *pPixel;
		} chunky;
		struct
		{
			int lLinebytesArray[4];
			void *pPixelArray[4];
		} planar;
	} pixelArray;
} YOLOV3_IMAGES, *YOLOV3_PIMAGES;

typedef struct
{
	int left;
	int top;
	int right;
	int bottom;
} YOLOV3RECT, *YOLOV3PRECT;

typedef struct
{
	int  flag;			// 
	YOLOV3RECT Target;	//Ŀ��rectangle
	float dVal;  		//Ŀ��value
	float dConfidence; 	//Ŀ��confidence
}HYYOLOV3_RESULT;///text read result

typedef struct
{
	HYYOLOV3_RESULT *pResult;
	int lResultNum;   //����õ������Ŀ
}HYYOLOV3RESULT_LIST,*HYYOLOV3RESULT_PLIST;

//#if defined(_MSC_VER)
//#define YOLODLL_API __declspec(dllexport)
//#else
//#define YOLODLL_API __attribute__((visibility("default")))
//#endif
#define YOLODLL_API

#endif
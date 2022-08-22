#pragma once
#include "yolo_v3_com.h"

YOLODLL_API int init_atlas(void **handle, char *cfgfile, char *weightfile,float thresh,int atlas_index);
YOLODLL_API int uninit_atlas(void *handle);
YOLODLL_API int detec_atlas(void *handle, YOLOV3_PIMAGES img, HYYOLOV3RESULT_PLIST pResultList);

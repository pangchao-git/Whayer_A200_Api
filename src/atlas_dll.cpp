
#include "atlas_dll.h"
#include "hy_detect.h"
YOLODLL_API int init_atlas(void **handle, char *cfgfile, char *weightfile,float thresh,int atlas_index){
	 hy_detect   *p_detector = new hy_detect();
	int ret = p_detector->A200_load_model(cfgfile, weightfile,atlas_index);
	
	if (0 != ret) {
		printf("%s  %d failed!\n", __func__, __LINE__);
	}
	*handle = p_detector;
	return ret;

}
YOLODLL_API int uninit_atlas(void *handle){
	
	if (handle) {
		hy_detect *impl = (hy_detect *) handle;
		delete impl;
		impl= nullptr;
	}
	return 0;

}
YOLODLL_API int detec_atlas(void *handle, YOLOV3_PIMAGES img, HYYOLOV3RESULT_PLIST pResultList){
	
	
	std::cout<<"start to detec_atlas!!\n";
	if (!handle || !img || !pResultList) {
		printf("hy_detect_bm input error!!!!\n");
		return -1;
	}
	hy_detect *detect = (hy_detect *) handle;
	
	return detect->A200_detect(img, pResultList);
	
}
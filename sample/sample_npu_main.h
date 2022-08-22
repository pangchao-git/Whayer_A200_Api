#ifndef __SAMPLE_NPU_MAIN_H__
#define __SAMPLE_NPU_MAIN_H__

#ifdef __cplusplus

extern "C" {
#endif
#include "sc_type.h"

/******************************************************************************
* function : show Cnn sample
******************************************************************************/
void SAMPLE_SVP_NPU_Dcnn();

/******************************************************************************
* function : show SSD sample
******************************************************************************/
void SAMPLE_SVP_NPU_Ssd(void);

/******************************************************************************
* function : show YOLOV3 sample
******************************************************************************/
void SAMPLE_SVP_NPU_Yolov3(int model_type,SC_CHAR*npu_model,SC_CHAR*p_data);


void SAMPLE_SVP_NPU_Yolov3_file(int model_type,SC_CHAR*npu_model,SC_CHAR*src_image);

/******************************************************************************
* function : show CallBack to Arm sample
******************************************************************************/
void SAMPLE_SVP_NPU_CB(void);

/*****************************************************************************
* function : Dcnn sample signal handle
******************************************************************************/
void SAMPLE_SVP_NPU_Dcnn_HandleSig(void);

/******************************************************************************
* function : SSD sample signal handle
******************************************************************************/
void SAMPLE_SVP_NPU_Ssd_HandleSig(void);

/******************************************************************************
* function : yolov3 sample signal handle
******************************************************************************/
void SAMPLE_SVP_NPU_Yolov3_HandleSig(void);

/******************************************************************************
* function : CallBack to Arm sample signal handle
******************************************************************************/
void SAMPLE_SVP_NPU_CB_HandleSig(void);
#ifdef __cplusplus
}
#endif
#endif /* __SAMPLE_NPU_MAIN_H__ */


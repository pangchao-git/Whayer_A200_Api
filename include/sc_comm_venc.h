#ifndef __SC_COMM_VENC_H__
#define __SC_COMM_VENC_H__

#include "sc_type.h"
#include "sc_common.h"
#include "sc_errno.h"
#include "sc_comm_video.h"
#include "sc_comm_rc.h"
#include "sc_comm_vb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifndef VB_POOL
typedef SC_U32 VB_POOL;
#endif

/* invlalid channel ID */
#define SC_ERR_VENC_INVALID_CHNID SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_INVALID_CHNID)
/* at lease one parameter is illagal ,eg, an illegal enumeration value  */
#define SC_ERR_VENC_ILLEGAL_PARAM SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_ILLEGAL_PARAM)
/* channel exists */
#define SC_ERR_VENC_EXIST         SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_EXIST)
/* channel exists */
#define SC_ERR_VENC_UNEXIST       SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_UNEXIST)
/* using a NULL point */
#define SC_ERR_VENC_NULL_PTR      SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_NULL_PTR)
/* try to enable or initialize system,device or channel, before configing attribute */
#define SC_ERR_VENC_NOT_CONFIG    SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_CONFIG)
/* operation is not supported by NOW */
#define SC_ERR_VENC_NOT_SUPPORT   SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_SUPPORT)
/* operation is not permitted ,eg, try to change stati attribute */
#define SC_ERR_VENC_NOT_PERM      SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_PERM)
/* failure caused by malloc memory */
#define SC_ERR_VENC_NOMEM         SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_NOMEM)
/* failure caused by malloc buffer */
#define SC_ERR_VENC_NOBUF         SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_NOBUF)
/* no data in buffer */
#define SC_ERR_VENC_BUF_EMPTY     SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_BUF_EMPTY)
/* no buffer for new data */
#define SC_ERR_VENC_BUF_FULL      SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_BUF_FULL)
/* system is not ready,had not initialed or loaded */
#define SC_ERR_VENC_SYS_NOTREADY  SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_SYS_NOTREADY)
/* system is busy */
#define SC_ERR_VENC_BUSY          SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_BUSY)

#define SC_ERR_VENC_BADADDR       SC_DEF_ERR(SC_ID_VENC, EN_ERR_LEVEL_ERROR, EN_ERR_BADADDR)

/* the nalu type of H264E */
typedef enum
{
    H264E_NALU_BSLICE = 0,                         /* B SLICE types */
    H264E_NALU_PSLICE = 1,                         /* P SLICE types */
    H264E_NALU_ISLICE = 2,                         /* I SLICE types */
    H264E_NALU_IDRSLICE = 5,                       /* IDR SLICE types */
    H264E_NALU_SEI    = 6,                         /* SEI types */
    H264E_NALU_SPS    = 7,                         /* SPS types */
    H264E_NALU_PPS    = 8,                         /* PPS types */
    H264E_NALU_BUTT
} H264E_NALU_TYPE_E;

/* the nalu type of H265E */
typedef enum
{
    H265E_NALU_BSLICE = 0,                          /* B SLICE types */
    H265E_NALU_PSLICE = 1,                          /* P SLICE types */
    H265E_NALU_ISLICE = 2,                          /* I SLICE types */
    H265E_NALU_IDRSLICE = 19,                       /* IDR SLICE types */
    H265E_NALU_VPS    = 32,                         /* VPS types */
    H265E_NALU_SPS    = 33,                         /* SPS types */
    H265E_NALU_PPS    = 34,                         /* PPS types */
    H265E_NALU_SEI    = 39,                         /* SEI types */

    H265E_NALU_BUTT
} H265E_NALU_TYPE_E;

/* the reference type of H264E slice */
typedef enum
{
    H264E_REFSLICE_FOR_1X = 1,                     /* Reference slice for H264E_REF_MODE_1X */
    H264E_REFSLICE_FOR_2X = 2,                     /* Reference slice for H264E_REF_MODE_2X */
    H264E_REFSLICE_FOR_4X = 5,                     /* Reference slice for H264E_REF_MODE_4X */
    H264E_REFSLICE_FOR_BUTT                        /* slice not for reference */
} H264E_REFSLICE_TYPE_E;

/* the pack type of JPEGE */
typedef enum
{
    JPEGE_PACK_ECS = 5,                            /* ECS types */
    JPEGE_PACK_APP = 6,                            /* APP types */
    JPEGE_PACK_VDO = 7,                            /* VDO types */
    JPEGE_PACK_PIC = 8,                            /* PIC types */
    JPEGE_PACK_DCF = 9,                            /* DCF types */
    JPEGE_PACK_DCF_PIC = 10,                       /* DCF PIC types */
    JPEGE_PACK_BUTT
} JPEGE_PACK_TYPE_E;

/* the pack type of PRORES */
typedef enum
{
    PRORES_PACK_PIC = 1,                            /* PIC types */
    PRORES_PACK_BUTT
} PRORES_PACK_TYPE_E;

/* the data type of VENC */
typedef union
{
    H264E_NALU_TYPE_E    enH264EType;               /* R; H264E NALU types */
    JPEGE_PACK_TYPE_E    enJPEGEType;               /* R; JPEGE pack types */
    H265E_NALU_TYPE_E    enH265EType;               /* R; H264E NALU types */
    PRORES_PACK_TYPE_E   enPRORESType;
} VENC_DATA_TYPE_U;

/* the pack info of VENC */
typedef struct
{
    VENC_DATA_TYPE_U  u32PackType;                  /* R; the pack type */
    SC_U32 u32PackOffset;
    SC_U32 u32PackLength;
} VENC_PACK_INFO_S;

/* Defines a stream packet */
typedef struct
{
    SC_U64               u64PhyAddr;                 /* R; the physics address of stream */
    SC_U8                ATTRIBUTE *pu8Addr;         /* R; the virtual address of stream */
    SC_U32               ATTRIBUTE u32Len;           /* R; the length of stream */

    SC_U64               u64PTS;                     /* R; PTS */
    SC_BOOL              bFrameEnd;                  /* R; frame end */

    VENC_DATA_TYPE_U     DataType;                   /* R; the type of stream */
    SC_U32               u32Offset;                  /* R; the offset between the Valid data and the start address */
    SC_U32               u32DataNum;                 /* R; the  stream packets num */
    VENC_PACK_INFO_S     stPackInfo[8];              /* R; the stream packet Information */
} VENC_PACK_S;

/* Defines the frame type and reference attributes of the H.264 frame skipping reference streams */
typedef enum
{
    BASE_IDRSLICE = 0,                              /* the Idr frame at Base layer */
    BASE_PSLICE_REFTOIDR,                           /* the P frame at Base layer, referenced by other frames
                                                        at Base layer and reference to Idr frame */
    BASE_PSLICE_REFBYBASE,                          /* the P frame at Base layer, referenced by other frames
                                                        at Base layer */
    BASE_PSLICE_REFBYENHANCE,                       /* the P frame at Base layer, referenced by other frames
                                                        at Enhance layer */
    ENHANCE_PSLICE_REFBYENHANCE,                    /* the P frame at Enhance layer, referenced by other frames
                                                        at Enhance layer */
    ENHANCE_PSLICE_NOTFORREF,                       /* the P frame at Enhance layer ,not referenced */
    ENHANCE_PSLICE_BUTT
} H264E_REF_TYPE_E;

typedef H264E_REF_TYPE_E H265E_REF_TYPE_E;

/* Defines the features of an H.264 stream */
typedef struct
{
    SC_U32                 u32PicBytesNum;         /* R; the coded picture stream byte number */
    SC_U32                 u32Inter16x16MbNum;     /* R; the inter16x16 macroblock num */
    SC_U32                 u32Inter8x8MbNum;       /* R; the inter8x8 macroblock num */
    SC_U32                 u32Intra16MbNum;        /* R; the intra16x16 macroblock num */
    SC_U32                 u32Intra8MbNum;         /* R; the intra8x8 macroblock num */
    SC_U32                 u32Intra4MbNum;         /* R; the inter4x4 macroblock num */

    H264E_REF_TYPE_E       enRefType;              /* R; Type of encoded frames in
                                                       advanced frame skipping reference mode */
    SC_U32                 u32UpdateAttrCnt;       /* R; Number of times that channel attributes or parameters
                                                       (including RC parameters) are set */
    SC_U32                 u32StartQp;             /* R; the start Qp of encoded frames */
    SC_U32                 u32MeanQp;              /* R; the mean Qp of encoded frames */
    SC_BOOL                bPSkip;
} VENC_STREAM_INFO_H264_S;

/* Defines the features of an H.265 stream */
typedef struct
{
    SC_U32                 u32PicBytesNum;        /* R; the coded picture stream byte number */
    SC_U32                 u32Inter64x64CuNum;    /* R; the inter64x64 cu num  */
    SC_U32                 u32Inter32x32CuNum;    /* R; the inter32x32 cu num  */
    SC_U32                 u32Inter16x16CuNum;    /* R; the inter16x16 cu num  */
    SC_U32                 u32Inter8x8CuNum;      /* R; the inter8x8   cu num  */
    SC_U32                 u32Intra32x32CuNum;    /* R; the Intra32x32 cu num  */
    SC_U32                 u32Intra16x16CuNum;    /* R; the Intra16x16 cu num  */
    SC_U32                 u32Intra8x8CuNum;      /* R; the Intra8x8   cu num  */
    SC_U32                 u32Intra4x4CuNum;      /* R; the Intra4x4   cu num  */

    H265E_REF_TYPE_E       enRefType;            /* R; Type of encoded frames
                                                     in advanced frame skipping reference mode */
    SC_U32                 u32UpdateAttrCnt;     /* R; Number of times that channel attributes or
                                                     parameters (including RC parameters) are set */
    SC_U32                 u32StartQp;           /* R; the start Qp of encoded frames */
    SC_U32                 u32MeanQp;            /* R; the mean Qp of encoded frames */
    SC_BOOL                bPSkip;
} VENC_STREAM_INFO_H265_S;

/* the sse info */
typedef struct
{
    SC_BOOL bSSEEn;        /* RW; Range:[0,1]; Region SSE enable */
    SC_U32  u32SSEVal;     /* R; Region SSE value */
} VENC_SSE_INFO_S;

/* the advance information of the h264e */
typedef struct
{
    SC_U32             u32ResidualBitNum;                    /* R; the residual num */
    SC_U32             u32HeadBitNum;                        /* R; the head bit num */
    SC_U32             u32MadiVal;                           /* R; the madi value */
    SC_U32             u32MadpVal;                           /* R; the madp value */
    SC_DOUBLE          dPSNRVal;                             /* R; the PSNR value */
    SC_U32             u32MseLcuCnt;                         /* R; the lcu cnt of the mse */
    SC_U32             u32MseSum;                            /* R; the sum of the mse */
    VENC_SSE_INFO_S    stSSEInfo[8];                         /* R; the information of the sse */
    SC_U32             u32QpHstgrm[VENC_QP_HISGRM_NUM];      /* R; the Qp value */
    SC_U32             u32MoveScene16x16Num;                 /* R; the 16x16 cu num of the move scene */
    SC_U32             u32MoveSceneBits;                     /* R; the stream bit num of the move scene */
} VENC_STREAM_ADVANCE_INFO_H264_S;

/* the advance information of the Jpege */
typedef struct
{
    // SC_U32 u32Reserved;
} VENC_STREAM_ADVANCE_INFO_JPEG_S;

/* the advance information of the Prores */
typedef struct
{
    // SC_U32 u32Reserved;
} VENC_STREAM_ADVANCE_INFO_PRORES_S;

/* the advance information of the h265e */
typedef struct
{
    SC_U32             u32ResidualBitNum;               /* R; the residual num */
    SC_U32             u32HeadBitNum;                   /* R; the head bit num */
    SC_U32             u32MadiVal;                      /* R; the madi value */
    SC_U32             u32MadpVal;                      /* R; the madp value */
    SC_DOUBLE          dPSNRVal;                        /* R; the PSNR value */
    SC_U32             u32MseLcuCnt;                    /* R; the lcu cnt of the mse */
    SC_U32             u32MseSum;                       /* R; the sum of the mse */
    VENC_SSE_INFO_S    stSSEInfo[8];                    /* R; the information of the sse */
    SC_U32             u32QpHstgrm[VENC_QP_HISGRM_NUM]; /* R; the Qp value */
    SC_U32             u32MoveScene32x32Num;            /* R; the 32x32 cu num of the move scene */
    SC_U32             u32MoveSceneBits;                /* R; the stream bit num of the move scene */
} VENC_STREAM_ADVANCE_INFO_H265_S;

/* Defines the features of an jpege stream */
typedef struct
{
    SC_U32 u32PicBytesNum;
    SC_U32 u32UpdateAttrCnt;
} VENC_STREAM_INFO_PRORES_S;

/* Defines the features of an jpege stream */
typedef struct
{
    SC_U32 u32PicBytesNum;                      /* R; the coded picture stream byte number */
    SC_U32 u32UpdateAttrCnt;                    /* R; Number of times that channel attributes or parameters
                                                    (including RC parameters) are set */
    SC_U32 u32Qfactor;                          /* R; image quality */
} VENC_STREAM_INFO_JPEG_S;

/* Defines the features of an stream */
typedef struct
{
    VENC_PACK_S ATTRIBUTE *pstPack;            /* R; stream pack attribute */
    SC_U32      ATTRIBUTE u32PackCount;        /* R; the pack number of one frame stream */
    SC_U32      u32Seq;                        /* R; the list number of stream */

    union
    {
        VENC_STREAM_INFO_H264_S   stH264Info;                        /* R; the stream info of h264 */
        VENC_STREAM_INFO_JPEG_S   stJpegInfo;                        /* R; the stream info of jpeg */
        VENC_STREAM_INFO_H265_S   stH265Info;                        /* R; the stream info of h265 */
        VENC_STREAM_INFO_PRORES_S stProresInfo;                      /* R; the stream info of prores */
    };

    union
    {
        VENC_STREAM_ADVANCE_INFO_H264_S   stAdvanceH264Info;         /* R; the stream info of h264 */
        VENC_STREAM_ADVANCE_INFO_JPEG_S   stAdvanceJpegInfo;         /* R; the stream info of jpeg */
        VENC_STREAM_ADVANCE_INFO_H265_S   stAdvanceH265Info;         /* R; the stream info of h265 */
        VENC_STREAM_ADVANCE_INFO_PRORES_S stAdvanceProresInfo;       /* R; the stream info of prores */
    };
} VENC_STREAM_S;

typedef struct
{
    H265E_REF_TYPE_E enRefType;  /* R;Type of encoded frames in advanced frame skipping reference mode */

    SC_U32  u32PicBytesNum;      /* R;the coded picture stream byte number */
    SC_U32  u32PicCnt;           /* R;When channel attributes 'bByFrame == 1', it means count of frames.
                                      When channel attributes 'bByFrame == 0', it means count of packets */
    SC_U32  u32StartQp;          /* R;the start Qp of encoded frames */
    SC_U32  u32MeanQp;           /* R;the mean Qp of encoded frames */
    SC_BOOL bPSkip;

    SC_U32  u32ResidualBitNum;   /* R;residual */
    SC_U32  u32HeadBitNum;       /* R;head information */
    SC_U32  u32MadiVal;          /* R;madi */
    SC_U32  u32MadpVal;          /* R;madp */
    SC_U32  u32MseSum;           /* R;Sum of MSE value */
    SC_U32  u32MseLcuCnt;        /* R;Sum of LCU number */
    SC_DOUBLE dPSNRVal;          /* R;PSNR */
} VENC_STREAM_INFO_S;

/* the size of array is 2,that is the maximum */
typedef struct
{
    SC_U8   u8LargeThumbNailNum;      /* RW; Range:[0, 2]; the large thumbnail pic num of the MPF */
    SIZE_S  astLargeThumbNailSize[2]; /* RW; The resolution of large ThumbNail */
} VENC_MPF_CFG_S;

typedef enum
{
    VENC_PIC_RECEIVE_SINGLE = 0,
    VENC_PIC_RECEIVE_MULTI,

    VENC_PIC_RECEIVE_BUTT
} VENC_PIC_RECEIVE_MODE_E;

/* the attribute of jpege */
typedef struct
{
    SC_BOOL                     bSupportDCF;    /*RW; Range:[0, 1]; support dcf */
    VENC_MPF_CFG_S              stMPFCfg;       /*RW; Range:[0, 1]; config of Mpf */
    VENC_PIC_RECEIVE_MODE_E     enReceiveMode;  /*RW; Config the receive mode; */
} VENC_ATTR_JPEG_S;

/* the attribute of mjpege */
typedef struct
{
    // reserved
} VENC_ATTR_MJPEG_S;

/* the attribute of h264e */
typedef struct
{
    SC_BOOL bRcnRefShareBuf;                 /* RW; Range:[0, 1]; Whether to enable the Share Buf of Rcn and Ref */
} VENC_ATTR_H264_S;

/* the attribute of h265e */
typedef struct
{
    SC_BOOL bRcnRefShareBuf;                 /* RW; Range:[0, 1]; Whether to enable the Share Buf of Rcn and Ref */
} VENC_ATTR_H265_S;

/* the frame rate of PRORES */
typedef enum
{
    PRORES_FR_UNKNOWN = 0,
    PRORES_FR_23_976,
    PRORES_FR_24,
    PRORES_FR_25,
    PRORES_FR_29_97,
    PRORES_FR_30,
    PRORES_FR_50,
    PRORES_FR_59_94,
    PRORES_FR_60,
    PRORES_FR_100,
    PRORES_FR_119_88,
    PRORES_FR_120,
    PRORES_FR_BUTT
} PRORES_FRAMERATE;

/* the aspect ratio of PRORES */
typedef enum
{
    PRORES_ASPECT_RATIO_UNKNOWN = 0,
    PRORES_ASPECT_RATIO_SQUARE,
    PRORES_ASPECT_RATIO_4_3,
    PRORES_ASPECT_RATIO_16_9,
    PRORES_ASPECT_RATIO_BUTT
} PRORES_ASPECT_RATIO;

/* the attribute of PRORES */
typedef struct
{
    SC_CHAR             cIdentifier[4];
    PRORES_FRAMERATE    enFrameRateCode;
    PRORES_ASPECT_RATIO enAspectRatio;
} VENC_ATTR_PRORES_S;

/* the attribute of the Venc */
typedef struct
{
    PAYLOAD_TYPE_E  enType;              /* RW; the type of payload */

    SC_U32  u32MaxPicWidth;              /* RW; Range:[0, 16384];maximum width of a picture to be encoded, in pixel */
    SC_U32  u32MaxPicHeight;             /* RW; Range:[0, 16384];maximum height of a picture to be encoded, in pixel */

    SC_U32  u32BufSize;                  /* RW; stream buffer size */
    SC_U32  u32Profile;                  /* RW; Range:[0, 3];
                                            H.264:   0: baseline; 1:MP; 2:HP; 3: SVC-T [0, 3];
                                            H.265:   0:MP; 1:Main 10  [0 1];
                                            Jpege/MJpege:   0:Baseline
                                            prores: 0:ProRes Proxy; 1:ProRes 422(LT); 2:ProRes 422; 3:ProRes 422(HQ) */
    SC_BOOL bByFrame;                    /* RW; Range:[0, 1]; get stream mode is slice mode or frame mode */
    SC_U32  u32PicWidth;                 /* RW; Range:[0, 16384];width of a picture to be encoded, in pixel */
    SC_U32  u32PicHeight;                /* RW; Range:[0, 16384];height of a picture to be encoded, in pixel */
    union
    {
        VENC_ATTR_H264_S stAttrH264e;    /* attributes of H264e */
        VENC_ATTR_H265_S stAttrH265e;    /* attributes of H265e */
        VENC_ATTR_MJPEG_S stAttrMjpege;  /* attributes of Mjpeg */
        VENC_ATTR_JPEG_S  stAttrJpege;   /* attributes of jpeg  */
        VENC_ATTR_PRORES_S stAttrProres; /* attributes of prores  */
    };
} VENC_ATTR_S;

/* the gop mode */
typedef enum
{
    VENC_GOPMODE_NORMALP    = 0,     /* NORMALP */
    VENC_GOPMODE_DUALP      = 1,     /* DUALP;   */
    VENC_GOPMODE_SMARTP     = 2,     /* SMARTP;  */
    VENC_GOPMODE_ADVSMARTP  = 3,     /* ADVSMARTP ;  */
    VENC_GOPMODE_BIPREDB    = 4,     /* BIPREDB ; */
    VENC_GOPMODE_LOWDELAYB  = 5,     /* LOWDELAYB; Not support */

    VENC_GOPMODE_BUTT,
} VENC_GOP_MODE_E;

/* the attribute of the normalp */
typedef struct
{
    SC_S32   s32IPQpDelta;           /* RW; Range:[-10, 30]; QP variance between P frame and I frame */
} VENC_GOP_NORMALP_S;

/* the attribute of the dualp */
typedef struct
{
    SC_U32 u32SPInterval;            /* RW; Range:[0, 65536]; Interval of the special P frames,
                                        1 is not supported and should be less than Gop */
    SC_S32 s32SPQpDelta;             /* RW; Range:[-10, 30]; QP variance between P frame and special P frame */
    SC_S32 s32IPQpDelta;             /* RW; Range:[-10, 30]; QP variance between P frame and I frame */
} VENC_GOP_DUALP_S;

/* the attribute of the smartp */
typedef struct
{
    SC_U32  u32BgInterval;           /* RW; Interval of the long-term reference frame, can not be less than gop */
    SC_S32  s32BgQpDelta;            /* RW; Range:[-10, 30]; QP variance between P frame and Bg frame */
    SC_S32  s32ViQpDelta;            /* RW; Range:[-10, 30]; QP variance between P frame and virtual I  frame */
} VENC_GOP_SMARTP_S;

/* the attribute of the advsmartp */
typedef struct
{
    SC_U32  u32BgInterval;           /* RW; Interval of the long-term reference frame, can not be less than gop */
    SC_S32  s32BgQpDelta;            /* RW; Range:[-10, 30]; QP variance between P frame and Bg frame */
    SC_S32  s32ViQpDelta;            /* RW; Range:[-10, 30]; QP variance between P frame and virtual I  frame */
} VENC_GOP_ADVSMARTP_S;

/* the attribute of the bipredb */
typedef struct
{
    SC_U32 u32BFrmNum;              /* RW; Range:[1, 3]; Number of B frames */
    SC_S32 s32BQpDelta;             /* RW; Range:[-10, 30]; QP variance between P frame and B frame */
    SC_S32 s32IPQpDelta;            /* RW; Range:[-10, 30]; QP variance between P frame and I frame */
} VENC_GOP_BIPREDB_S;

/* the attribute of the gop */
typedef struct
{
    VENC_GOP_MODE_E enGopMode;                   /* RW; Encoding GOP type */
    union
    {
        VENC_GOP_NORMALP_S   stNormalP;          /* attributes of normal P */
        VENC_GOP_DUALP_S     stDualP;            /* attributes of dual   P */
        VENC_GOP_SMARTP_S    stSmartP;           /* attributes of Smart P */
        VENC_GOP_ADVSMARTP_S stAdvSmartP;        /* attributes of AdvSmart P */
        VENC_GOP_BIPREDB_S   stBipredB;          /* attributes of b */
    };

} VENC_GOP_ATTR_S;

/* the attribute of the venc chnl */
typedef struct
{
    VENC_ATTR_S     stVencAttr;                   /* the attribute of video encoder */
    VENC_RC_ATTR_S  stRcAttr;                     /* the attribute of rate  ctrl */
    VENC_GOP_ATTR_S stGopAttr;                    /* the attribute of gop */
} VENC_CHN_ATTR_S;

/* the param of receive picture */
typedef struct
{
    SC_S32 s32RecvPicNum;                         /* RW; Range:[-1, 2147483647]; Number of frames received and
                                                    encoded by the encoding channel,0 is not supported */
} VENC_RECV_PIC_PARAM_S;

/* the status of the venc chnl */
typedef struct
{
    SC_U32 u32LeftPics;                           /* R; left picture number */
    SC_U32 u32LeftStreamBytes;                    /* R; left stream bytes */
    SC_U32 u32LeftStreamFrames;                   /* R; left stream frames */
    SC_U32 u32CurPacks;                           /* R; pack number of current frame */
    SC_U32 u32LeftRecvPics;                       /* R; Number of frames to be received. Tmember is valid
                                                    after SC_MPI_VENC_StartRecvPicEx is called. */
    SC_U32 u32LeftEncPics;                        /* R; Number of frames to be encoded. Tmember is valid
                                                    after SC_MPI_VENC_StartRecvPicEx is called. */
    SC_BOOL bJpegSnapEnd;                         /* R; the end of Snap.*/
    VENC_STREAM_INFO_S stVencStrmInfo;
} VENC_CHN_STATUS_S;

/* the param of the h264e slice split */
typedef struct
{
    SC_BOOL bSplitEnable;                         /* RW; Range:[0, 1]; slice split enable, SC_TRUE:enable,
                                                    SC_FALSE:diable, default value:SC_FALSE */
    SC_U32  u32MbLineNum;                         /* RW; the max number is (Picture height + 15)/16;
                                                    this value presents the mb line number of one slice */
} VENC_H264_SLICE_SPLIT_S;

/* the param of the h264e intra pred */
typedef struct
{
    SC_U32     constrained_intra_pred_flag;       /* RW; Range:[0, 1];default: SC_FALSE,
                                                    see the H.264 protocol for the meaning */
} VENC_H264_INTRA_PRED_S;

/* the param of the h264e trans */
typedef struct
{
    SC_U32     u32IntraTransMode;               /* RW; Range:[0, 2]; Conversion mode for intra-prediction,
                                                    0: trans4x4, trans8x8; 1: trans4x4, 2: trans8x8 */
    SC_U32     u32InterTransMode;               /* RW; Range:[0, 2]; Conversion mode for inter-prediction,
                                                    0: trans4x4, trans8x8; 1: trans4x4, 2: trans8x8 */

    SC_BOOL    bScalingListValid;               /* RW; Range:[0, 1]; enable Scaling,default: SC_FALSE  */
    SC_U8      InterScalingList8X8[64];         /* RW; Range:[1, 255]; A quantization table for 8x8 inter-prediction */
    SC_U8      IntraScalingList8X8[64];         /* RW; Range:[1, 255]; A quantization table for 8x8 intra-prediction */

    SC_S32     chroma_qp_index_offset;          /* RW; Range:[-12, 12];default value: 0,
                                                    see the H.264 protocol for the meaning */
} VENC_H264_TRANS_S;

/* the param of the h264e entropy */
typedef struct
{
    SC_U32 u32EntropyEncModeI;                  /* RW; Range:[0, 1]; Entropy encoding mode for the I frame,
                                                    0:cavlc, 1:cabac */
    SC_U32 u32EntropyEncModeP;                  /* RW; Range:[0, 1]; Entropy encoding mode for the P frame,
                                                    0:cavlc, 1:cabac */
    SC_U32 u32EntropyEncModeB;                  /* RW; Range:[0, 1]; Entropy encoding mode for the B frame,
                                                    0:cavlc, 1:cabac */
    SC_U32 cabac_init_idc;                      /* RW; Range:[0, 2]; see the H.264 protocol for the meaning */
} VENC_H264_ENTROPY_S;

/* the config of the h264e poc */
typedef struct
{
    SC_U32 pic_order_cnt_type;                  /* RW; Range:[0, 2]; see the H.264 protocol for the meaning */

} VENC_H264_POC_S;

/* the param of the h264e deblocking */
typedef struct
{
    SC_U32 disable_deblocking_filter_idc;       /*  RW; Range:[0, 2]; see the H.264 protocol for the meaning */
    SC_S32 slice_alpha_c0_offset_div2;          /*  RW; Range:[-6, +6]; see the H.264 protocol for the meaning */
    SC_S32 slice_beta_offset_div2;              /*  RW; Range:[-6, +6]; see the H.264 protocol for the meaning */
} VENC_H264_DBLK_S;

/* the param of the h264e vui timing info */
typedef struct
{
    SC_U8  timing_info_present_flag;          /* RW; Range:[0, 1];
                                                If 1, timing info belows will be encoded into vui.*/
    SC_U8  fixed_frame_rate_flag;             /* RW; Range:[0, 1];
                                                see the H.264 protocol for the meaning. */
    SC_U32 num_units_in_tick;                 /* RW; Range:(0, 4294967295];
                                                see the H.264 protocol for the meaning */
    SC_U32 time_scale;                        /* RW; Range:(0, 4294967295];
                                                see the H.264 protocol for the meaning */
} VENC_VUI_H264_TIME_INFO_S;

/* the param of the vui aspct ratio */
typedef struct
{
    SC_U8  aspect_ratio_info_present_flag;    /* RW; Range:[0, 1]; If 1, aspectratio info belows
                                                will be encoded into vui */
    SC_U8  aspect_ratio_idc;                  /* RW; Range:[0, 255]; 17~254 is reserved,
                                                see the protocol for the meaning. */
    SC_U8  overscan_info_present_flag;        /* RW; Range:[0, 1]; If 1,
                                                oversacan info belows will be encoded into vui. */
    SC_U8  overscan_appropriate_flag;         /* RW; Range:[0, 1]; see the protocol for the meaning. */
    SC_U16 sar_width;                         /* RW; Range:(0, 65535]; see the protocol for the meaning. */
    SC_U16 sar_height ;                       /* RW; Range:(0, 65535]; see the protocol for the meaning.
                                                notes: sar_width  and  sar_height  shall  be  relatively  prime. */
} VENC_VUI_ASPECT_RATIO_S;

/* the param of the vui video signal */
typedef struct
{
    SC_U8  video_signal_type_present_flag ;        /* RW; Range:[0, 1];
                                                    If 1, video singnal info will be encoded into vui */
    SC_U8  video_format ;                          /* RW; H.264e Range:[0, 7], H.265e Range:[0,5];
                                                    see the protocol for the meaning. */
    SC_U8  video_full_range_flag;                  /* RW; Range: [0, 1]; see the protocol for the meaning */
    SC_U8  colour_description_present_flag ;       /* RO; Range: [0, 1]; see the protocol for the meaning */
    SC_U8  colour_primaries ;                      /* RO; Range: [0, 255]; see the protocol for the meaning */
    SC_U8  transfer_characteristics;               /* RO; Range: [0, 255]; see the protocol for the meaning */
    SC_U8  matrix_coefficients;                    /* RO; Range:[0, 255]; see the protocol for the meaning */
} VENC_VUI_VIDEO_SIGNAL_S;

/* the param of the vui video signal */
typedef struct
{
    SC_U8  bitstream_restriction_flag ;            /* RW; Range: [0, 1]; see the protocol for the meaning */
} VENC_VUI_BITSTREAM_RESTRIC_S;

/* the param of the h264e vui */
typedef struct
{
    VENC_VUI_ASPECT_RATIO_S           stVuiAspectRatio;
    VENC_VUI_H264_TIME_INFO_S          stVuiTimeInfo;
    VENC_VUI_VIDEO_SIGNAL_S           stVuiVideoSignal;
    VENC_VUI_BITSTREAM_RESTRIC_S      stVuiBitstreamRestric;
} VENC_H264_VUI_S;

/* the param of the h265e vui timing info */
typedef struct
{
    SC_U32 timing_info_present_flag;      /* RW; Range:[0, 1]; If 1, timing info belows will be encoded into vui. */
    SC_U32 num_units_in_tick;             /* RW; Range:[0, 4294967295]; see the H.265 protocol for the meaning. */
    SC_U32 time_scale;                    /* RW; Range:(0, 4294967295]; see the H.265 protocol for the meaning */
    SC_U32 num_ticks_poc_diff_one_minus1; /* RW; Range:(0, 4294967294]; see the H.265 protocol for the meaning */
} VENC_VUI_H265_TIME_INFO_S;

/* the param of the h265e vui */
typedef struct
{
    VENC_VUI_ASPECT_RATIO_S        stVuiAspectRatio;
    VENC_VUI_H265_TIME_INFO_S     stVuiTimeInfo;
    VENC_VUI_VIDEO_SIGNAL_S       stVuiVideoSignal;
    VENC_VUI_BITSTREAM_RESTRIC_S  stVuiBitstreamRestric;
} VENC_H265_VUI_S;

/* the param of the jpege */
typedef struct
{
    SC_U32 u32Qfactor;                /* RW; Range:[1, 99]; Qfactor value  */
    SC_U8  u8YQt[64];                 /* RW; Range:[1, 255]; Y quantization table */
    SC_U8  u8CbQt[64];                /* RW; Range:[1, 255]; Cb quantization table */
    SC_U8  u8CrQt[64];                /* RW; Range:[1, 255]; Cr quantization table */
    SC_U32 u32MCUPerECS;              /* RW; the max MCU number is (picwidth + 15) >> 4 x (picheight + 15) >> 4 x 2];
                                        MCU number of one ECS*/
} VENC_JPEG_PARAM_S;

/* the param of the mjpege */
typedef struct
{
    SC_U8 u8YQt[64];                  /* RW; Range:[1, 255]; Y quantization table */
    SC_U8 u8CbQt[64];                 /* RW; Range:[1, 255]; Cb quantization table */
    SC_U8 u8CrQt[64];                 /* RW; Range:[1, 255]; Cr quantization table */
    SC_U32 u32MCUPerECS;              /* RW; the max MCU number is (picwidth + 15) >> 4 x (picheight + 15) >> 4 x 2];
                                        MCU number of one ECS */
} VENC_MJPEG_PARAM_S;

/* the param of the ProRes */
typedef struct
{
    SC_U8 u8LumaQt[64];               /* RW; Range:[1, 255]; Luma quantization table */
    SC_U8 u8ChromaQt[64];             /* RW; Range:[1, 255]; Chroma quantization table */
    SC_CHAR encoder_identifier[4];    /* RW: identifies the encoder vendor or product that
                                        generated the compressed frame */
} VENC_PRORES_PARAM_S;

/* the attribute of the roi */
typedef struct
{
    SC_U32  u32Index;                     /* RW; Range:[0, 7]; Index of an ROI.
                                            The system supports indexes ranging from 0 to 7 */
    SC_BOOL bEnable;                      /* RW; Range:[0, 1]; Whether to enable this ROI */
    SC_BOOL bAbsQp;                       /* RW; Range:[0, 1]; QP mode of an ROI.
                                            SC_FALSE: relative QP.SC_TURE: absolute QP */
    SC_S32  s32Qp;                        /* RW; Range:[-51, 51];
                                            QP value,only relative mode can QP value less than 0. */
    RECT_S  stRect;                       /* RW; Region of an ROI */
} VENC_ROI_ATTR_S;

/* ROI struct */
typedef struct
{
    SC_U32  u32Index;                     /* RW; Range:[0, 7]; Index of an ROI.
                                            The system supports indexes ranging from 0 to 7 */
    SC_BOOL bEnable[3];                   /* RW; Range:[0, 1]; Subscript of array
                                            0: I Frame; 1: P/B Frame; 2: VI Frame; other params are the same */
    SC_BOOL bAbsQp[3];                    /* RW; Range:[0, 1]; QP mode of an ROI.
                                            SC_FALSE: relative QP.SC_TURE: absolute QP */
    SC_S32  s32Qp[3];                     /* RW; Range:[-51, 51]; QP value,
                                            only relative mode can QP value less than 0 */
    RECT_S  stRect[3];                    /* RW;Region of an ROI */
} VENC_ROI_ATTR_EX_S;

/* the param of the roibg frame rate */
typedef struct
{
    SC_S32 s32SrcFrmRate;                 /* RW; Range:[-1, 2147483647];Source frame rate of a non-ROI,
                                            can not be configured 0 */
    SC_S32 s32DstFrmRate;                 /* RW; Range:[-1, 2147483647];Target frame rate of a non-ROI,
                                            can not be larger than s32SrcFrmRate */
} VENC_ROIBG_FRAME_RATE_S;

/* the param of the roibg frame rate */
typedef struct
{
    SC_U32       u32Base;               /* RW; Range:[0, 4294967295]; Base layer period */
    SC_U32       u32Enhance;            /* RW; Range:[0, 255]; Enhance layer period */
    SC_BOOL      bEnablePred;           /* RW; Range:[0, 1]; Whether some frames at the base layer are referenced
                                            by other frames at the base layer. When bEnablePred is SC_FALSE,
                                            all frames at the base layer reference IDR frames */
} VENC_REF_PARAM_S;

/* Jpeg snap mode */
typedef enum
{
    JPEG_ENCODE_ALL   = 0,                        /* Jpeg channel snap all the pictures when started. */
    JPEG_ENCODE_SNAP  = 1,                        /* Jpeg channel snap the flashed pictures when started. */
    JPEG_ENCODE_BUTT,
} VENC_JPEG_ENCODE_MODE_E;

/* the information of the stream */
typedef struct
{
    SC_U64   u64PhyAddr[MAX_TILE_NUM];             /* R; Start physical address for a stream buffer */
    SC_VOID ATTRIBUTE *pUserAddr[MAX_TILE_NUM];    /* R; Start virtual address for a stream buffer */
    SC_U64  ATTRIBUTE u64BufSize[MAX_TILE_NUM];    /* R; Stream buffer size */
} VENC_STREAM_BUF_INFO_S;

/* the param of the h265e slice split */
typedef struct
{
    SC_BOOL bSplitEnable;                          /* RW; Range:[0, 1]; slice split enable,
                                                    SC_TRUE:enable, SC_FALSE:diable, default value:SC_FALSE */
    SC_U32  u32LcuLineNum;                         /* RW; Range:(Picture height + lcu size minus one)/lcu size;
                                                    this value presents lcu line number */
} VENC_H265_SLICE_SPLIT_S;

/* the param of the h265e pu */
typedef struct
{
    SC_U32    constrained_intra_pred_flag;         /* RW; Range:[0, 1]; see the H.265 protocol for the meaning. */
    SC_U32    strong_intra_smoot; /* RW; Range:[0, 1]; see the H.265 protocol for the meaning. */
} VENC_H265_PU_S;

/* the param of the h265e trans */
typedef struct
{
    SC_S32  cb_qp_offset;                     /* RW; Range:[-12, 12]; see the H.265 protocol for the meaning. */
    SC_S32  cr_qp_offset;                     /* RW; Range:[-12, 12]; see the H.265 protocol for the meaning. */

    SC_BOOL bScalingListEnabled;              /* RW; Range:[0, 1]; If 1, specifies that a scaling list is used. */

    SC_BOOL bScalingListTu4Valid;             /* RW; Range:[0, 1]; If 1, ScalingList4X4 belows will be encoded. */
    SC_U8   InterScalingList4X4[2][16];       /* RW; Range:[1, 255]; Scaling List for inter 4X4 block. */
    SC_U8   IntraScalingList4X4[2][16];       /* RW; Range:[1, 255]; Scaling List for intra 4X4 block. */

    SC_BOOL bScalingListTu8Valid;             /* RW; Range:[0, 1]; If 1, ScalingList8X8 belows will be encoded. */
    SC_U8   InterScalingList8X8[2][64];       /* RW; Range:[1, 255]; Scaling List for inter 8X8 block. */
    SC_U8   IntraScalingList8X8[2][64];       /* RW; Range:[1, 255]; Scaling List for intra 8X8 block. */

    SC_BOOL bScalingListTu16Valid;            /* RW; Range:[0, 1]; If 1, ScalingList16X16 belows will be encoded. */
    SC_U8   InterScalingList16X16[2][64];     /* RW; Range:[1, 255]; Scaling List for inter 16X16 block. */
    SC_U8   IntraScalingList16X16[2][64];     /* RW; Range:[1, 255]; Scaling List for inter 16X16 block. */

    SC_BOOL bScalingListTu32Valid;            /* RW; Range:[0, 1]; If 1, ScalingList32X32 belows will be encoded. */
    SC_U8   InterScalingList32X32[64];        /* RW; Range:[1, 255]; Scaling List for inter 32X32 block. */
    SC_U8   IntraScalingList32X32[64];        /* RW; Range:[1 ,255]; Scaling List for inter 32X32 block. */

} VENC_H265_TRANS_S;

/* the param of the h265e entroy */
typedef struct
{
    SC_U32 cabac_init_flag;                    /* RW; Range:[0, 1]; see the H.265 protocol for the meaning. */
} VENC_H265_ENTROPY_S;

/* the param of the h265e deblocking */
typedef struct
{
    SC_U32 slice_deblocking_filter_disabled_flag;   /* RW; Range:[0, 1]; see the H.265 protocol for the meaning. */
    SC_S32 slice_beta_offset_div2;                  /* RW; Range:[-6, 6]; see the H.265 protocol for the meaning. */
    SC_S32 slice_tc_offset_div2;                    /* RW; Range:[-6, 6]; see the H.265 protocol for the meaning. */
} VENC_H265_DBLK_S;

/* the param of the h265e sao */
typedef struct
{
    SC_U32  slice_sao_luma_flag;      /* RW; Range:[0, 1]; Indicates whether SAO filtering is performed on the
                                        luminance component of the current slice. */
    SC_U32  slice_sao_chroma_flag;    /* RW; Range:[0, 1]; Indicates whether SAO filtering is performed on
                                        the chrominance component of the current slice */
} VENC_H265_SAO_S;

/* venc mode type */
typedef enum
{
    INTRA_REFRESH_ROW = 0,                      /* Line mode */
    INTRA_REFRESH_COLUMN,                       /* Column mode */
    INTRA_REFRESH_BUTT
} VENC_INTRA_REFRESH_MODE_E;

/* the param of the intra refresh */
typedef struct
{
    SC_BOOL                     bRefreshEnable;     /* RW; Range:[0, 1]; intra refresh enable,
                                                        SC_TRUE:enable, SC_FALSE:diable, default value:SC_FALSE */
    VENC_INTRA_REFRESH_MODE_E   enIntraRefreshMode; /* RW; The mode of intra refresh */
    SC_U32                      u32RefreshNum;      /* RW; Number of rows/column to be refreshed
                                                        during each I macroblock refresh */
    SC_U32                      u32ReqIQp;          /* RW; Range:[0, 51]; QP value of the I frame */
} VENC_INTRA_REFRESH_S;

/* venc mode type */
typedef enum
{
    MODTYPE_VENC = 1,
    MODTYPE_H264E,
    MODTYPE_H265E,
    MODTYPE_JPEGE,
    MODTYPE_RC,
    MODTYPE_BUTT
} VENC_MODTYPE_E;

/* the param of the h264e mod */
typedef struct
{
    SC_U32          u32OneStreamBuffer;     /* RW; Range:[0, 1]; one stream buffer */
    SC_U32          u32H264eMiniBufMode;    /* RW; Range:[0, 1]; H264e MiniBufMode */
    SC_U32          u32H264ePowerSaveEn;    /* RW; Range:[0, 1]; H264e PowerSaveEn */
    VB_SOURCE_E     enH264eVBSource;        /* RW; H264e VBSource */
    SC_BOOL         bQpHstgrmEn;            /* RW; Range:[0, 1] */
    SC_U32          u32UserDataMaxLen;      /* RW; Range:[0, 65536]; one user data buffer len */
    SC_U32          u32CoreClock;         /* RW; Range:{75, 150, 200, 250, 300, 360, 400, 450, 500, 600, 666, 700} Mhz note:H264与H265的编码和解码共用 */
    SC_U32          u32BpuClock;          /* RW; Range:{75, 150, 200, 250, 300, 360, 400, 450, 500, 600, 666, 700} Mhz note:H264与H265的编码和解码共用 */
} VENC_MOD_H264E_S;

/* the param of the h265e mod */
typedef struct
{
    SC_U32          u32OneStreamBuffer;      /* RW; Range:[0, 1]; one stream buffer */
    SC_U32          u32H265eMiniBufMode;     /* RW; Range:[0, 1]; H265e MiniBufMode */
    SC_U32          u32H265ePowerSaveEn;     /* RW; Range:[0, 2]; H265e PowerSaveEn */
    VB_SOURCE_E     enH265eVBSource;         /* RW; H265e VBSource */
    SC_BOOL         bQpHstgrmEn;             /* RW; Range:[0, 1] */
    SC_U32          u32UserDataMaxLen;       /* RW; Range:[0, 65536]; one user data buffer len */
    SC_U32          u32CoreClock;         /* RW; Range:{75, 150, 200, 250, 300, 360, 400, 450, 500, 600, 666, 700} Mhz note:H264与H265的编码和解码共用 */
    SC_U32          u32BpuClock;          /* RW; Range:{75, 150, 200, 250, 300, 360, 400, 450, 500, 600, 666, 700} Mhz note:H264与H265的编码和解码共用 */
} VENC_MOD_H265E_S;

/* the param of the jpege mod */
typedef struct
{
    SC_U32  u32OneStreamBuffer;         /* RW; Range:[0, 1]; one stream buffer */
    SC_U32  u32JpegeMiniBufMode;        /* RW; Range:[0, 1]; Jpege MiniBufMode */
    SC_U32  u32JpegClearStreamBuf;      /* RW; Range:[0, 1]; JpegClearStreamBuf */
    SC_U32  u32JpegeDeringMode;         /* RW; Range:[0, 1]; Jpege Dering Mode */
    SC_U32  u32CoreClock;             /* RW; Range:{75, 150, 200, 250, 300, 360, 400, 450, 500, 600, 666, 700} Mhz note:H264与H265的编码和解码共用 */
} VENC_MOD_JPEGE_S;

typedef struct
{
    SC_U32  u32ClrStatAfterSetBr;
} VENC_MOD_RC_S;
/* the param of the venc mod */
typedef struct
{
    SC_U32 u32VencBufferCache;  /* RW; Range:[0, 1]; VencBufferCache */
    SC_U32 u32FrameBufRecycle;  /* RW; Range:[0, 1]; FrameBufRecycle */
} VENC_MOD_VENC_S;

/* the param of the mod */
typedef struct
{
    VENC_MODTYPE_E enVencModType;        /* RW; VencModType */
    union
    {
        VENC_MOD_VENC_S  stVencModParam;
        VENC_MOD_H264E_S stH264eModParam;
        VENC_MOD_H265E_S stH265eModParam;
        VENC_MOD_JPEGE_S stJpegeModParam;
        VENC_MOD_RC_S    stRcModParam;
    };
} VENC_PARAM_MOD_S;

typedef enum
{
    VENC_FRAME_TYPE_NONE = 1,
    VENC_FRAME_TYPE_IDR,
    VENC_FRAME_TYPE_PSKIP,
    VENC_FRAME_TYPE_BUTT
} VENC_FRAME_TYPE_E;

/* the information of the user rc */
typedef struct
{
    SC_BOOL bQpMapValid;           /* RW; Range:[0, 1];
                                    Indicates whether the QpMap mode is valid for the current frame */
    SC_BOOL bSkipWeightValid;      /* RW; Range:[0, 1];
                                    Indicates whether the SkipWeight mode is valid for the current frame */
    SC_U32  u32BlkStartQp;         /* RW; Range:[0, 51]; QP value of the first 16 x 16 block in QpMap mode */
    SC_U64  u64QpMapPhyAddr;       /* RW; Physical address of the QP table in QpMap mode */
    SC_U64  u64SkipWeightPhyAddr;  /* RW; Physical address of the SkipWeight table in QpMap mode */
    VENC_FRAME_TYPE_E enFrameType; /* RW; Encoding frame type of the current frame */
} USER_RC_INFO_S;

/* the information of the user frame */
typedef struct
{
    VIDEO_FRAME_INFO_S stUserFrame;
    USER_RC_INFO_S     stUserRcInfo;
} USER_FRAME_INFO_S;

/* the config of the sse */
typedef struct
{
    SC_U32  u32Index;       /* RW; Range:[0, 7]; Index of an SSE. The system supports indexes ranging from 0 to 7 */
    SC_BOOL bEnable;        /* RW; Range:[0, 1]; Whether to enable SSE */
    RECT_S  stRect;         /* RW; */
} VENC_SSE_CFG_S;

/* the param of the crop */
typedef struct
{
    SC_BOOL bEnable;                       /* RW; Range:[0, 1]; Crop region enable */
    RECT_S  stRect;                        /* RW; Crop region, note: s32X must be multi of 16 */
} VENC_CROP_INFO_S;

/* the param of the venc frame rate */
typedef struct
{
    SC_S32 s32SrcFrmRate;                  /* RW; Range:[0, 240]; Input frame rate of a  channel */
    SC_S32 s32DstFrmRate;                  /* RW; Range:[0, 240]; Output frame rate of a channel */
} VENC_FRAME_RATE_S;

/* the param of the venc encode chnl */
typedef struct
{
    SC_BOOL bColor2Grey;            /* RW; Range:[0, 1]; Whether to enable Color2Grey. */
    SC_U32  u32Priority;            /* RW; Range:[0, 1]; The priority of the coding chnl. */
    SC_U32  u32MaxStrmCnt;          /* RW: Range:[0, 4294967295]; Maximum number of frames in a stream buffer */
    SC_U32  u32PollWakeUpFrmCnt;    /* RW: Range:(0, 4294967295]; the frame num needed to wake up  obtaining streams */
    VENC_CROP_INFO_S    stCropCfg;
    VENC_FRAME_RATE_S   stFrameRate;
} VENC_CHN_PARAM_S;

/*the ground protect of FOREGROUND */
typedef struct
{
    SC_BOOL bForegroundCuRcEn;
    SC_U32  u32ForegroundDirectionThresh;              /* RW; Range:[0, 16];
                                                        The direction for controlling the macroblock-level bit rate */
    SC_U32  u32ForegroundThreshGain;                   /* RW; Range:[0, 15]; The gain of the thresh */
    SC_U32  u32ForegroundThreshOffset;                 /* RW; Range:[0, 255]; The offset of the thresh */
    SC_U32  u32ForegroundThreshP[RC_TEXTURE_THR_SIZE]; /* RW; Range:[0, 255]; Mad threshold for controlling
                                                        the foreground macroblock-level bit rate of P frames */
    SC_U32  u32ForegroundThreshB[RC_TEXTURE_THR_SIZE]; /* RW; Range:[0, 255]; Mad threshold for controlling
                                                        the foreground macroblock-level bit rate of B frames */
} VENC_FOREGROUND_PROTECT_S;

/* the scene mode of the venc encode chnl */
typedef enum
{
    SCENE_0  = 0,              /* RW; A scene in wthe camera does not move or periodically moves continuously */
    SCENE_1  = 1,              /* RW; Motion scene at bit rate */
    SCENE_2  = 2,              /* RW; It has regular continuous motion at medium bit rate and
                                the encoding pressure is relatively large */
    SCENE_BUTT
} VENC_SCENE_MODE_E;

typedef struct
{
    SC_BOOL   bEnable;                 /* RW; Range:[0, 1];  default: 0, DeBreathEffect enable */
    SC_S32    s32Strength0;            /* RW; Range:[0, 35]; The Strength0 of DeBreathEffect. */
    SC_S32    s32Strength1;            /* RW; Range:[0, 35]; The Strength1 of DeBreathEffect. */
} VENC_DEBREATHEFFECT_S;

typedef struct
{
    OPERATION_MODE_E enPredMode;     /* RW; CU tendency configuration mode  */

    SC_U32 u32Intra32Cost;           /* RW; Range:[0, 15]; Tendency adjustment in Intra32 mode */
    SC_U32 u32Intra16Cost;           /* RW; Range:[0, 15]; Tendency adjustment in Intra16 mode */
    SC_U32 u32Intra8Cost;            /* RW; Range:[0, 15]; Tendency adjustment in Intra8 mode */
    SC_U32 u32Intra4Cost;            /* RW; Range:[0, 15]; Tendency adjustment in Intra4 mode */

    SC_U32 u32Inter64Cost;           /* RW; Range:[0, 15]; Tendency adjustment in Intra64 mode */
    SC_U32 u32Inter32Cost;           /* RW; Range:[0, 15]; Tendency adjustment in Inter32 mode */
    SC_U32 u32Inter16Cost;           /* RW; Range:[0, 15]; Tendency adjustment in Inter16 mode */
    SC_U32 u32Inter8Cost;            /* RW; Range:[0, 15]; Tendency adjustment in Inter8 mode */
} VENC_CU_PREDICTION_S;

typedef struct
{
    SC_BOOL bSkipBiasEn;             /* RW; Range:[0, 1];
                                        Flag indicating whether the skip tendency function is enabled */
    SC_U32  u32SkipThreshGain;       /* RW; Range:[0, 15];
                                        used to calculate the SAD threshold for foreground detection */
    SC_U32  u32SkipThreshOffset;     /* RW; Range:[0, 255];
                                        used to calculate the SAD threshold for foreground detection */
    SC_U32  u32SkipBackgroundCost;   /* RW; Range:[0, 15];
                                        Skip tendency adjustment in the background */
    SC_U32  u32SkipForegroundCost;   /* RW; Range:[0, 15];
                                        Skip tendency adjustment in the foreground */
} VENC_SKIP_BIAS_S;

typedef struct
{
    SC_BOOL     bHierarchicalQpEn;              /* RW; Range:[0, 1];    Hierarchical QP enable */
    SC_S32      s32HierarchicalQpDelta[4];      /* RW; Range:[-10, 10]; QP delta of the frames at each layer
                                                relative to the P-frame at layer 0 */
    SC_S32      s32HierarchicalFrameNum[4];     /* RW; Range:[0, 5];    Number of frames at each layer */
} VENC_HIERARCHICAL_QP_S;

typedef struct
{
    VB_POOL hPicVbPool;     /* RW;  vb pool id for pic buffer */
    VB_POOL hPicInfoVbPool; /* RW;  vb pool id for pic info buffer */
} VENC_CHN_POOL_S;

typedef struct
{
    SC_U32 u32ClearStatAfterSetAttr; /* RW; Range:[0, 1]; Clear Stat After SetAttr enable */
} VENC_RC_ADVPARAM_S;

typedef struct
{
    SC_BOOL bSplitEnable;
    SC_U32  u32SplitMode;
    SC_U32  u32SplitSize;
} VENC_SLICE_SPLIT_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SC_COMM_VENC_H__ */

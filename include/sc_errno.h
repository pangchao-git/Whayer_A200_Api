/*
 * @file     sc_errno.h
 * @brief    错误号
 * @version  1.0.1
 * @since    1.0.0
 * @author
 */

/*
 ********************************************************************************************************
 * Copyright 2021, BEIJIING SMARTCHIP MICROELECTRONICS TECHNOLOGY CO., LTD.
 *             ALL RIGHTS RESERVED
 * Permission is hereby granted to licensees of BEIJIING SMARTCHIP MICROELECTRONICS TECHNOLOGY CO., LTD.
 * to use or abstract this computer program for the sole purpose of implementing a product based on
 * BEIJIING SMARTCHIP MICROELECTRONICS TECHNOLOGY CO., LTD. No other rights to reproduce, use,
 * or disseminate this computer program,whether in part or in whole, are granted.
 * BEIJIING SMARTCHIP MICROELECTRONICS TECHNOLOGY CO., LTD. makes no representation or warranties
 * with respect to the performance of this computer program, and specifically disclaims
 * any responsibility for any damages, special or consequential, connected with the use of this program.
 * For details, see http://www.sgitg.sgcc.com.cn/
 ********************************************************************************************************
 */

#ifndef __SC_ERRNO_H__
#define __SC_ERRNO_H__

#include "sc_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/* 1010 0000b
 * VTOP use from 0~31
 * APPID based on 32
 */
#define SC_ERR_APPID (0x80000000L + 0x20000000L)

typedef enum
{
    EN_ERR_LEVEL_DEBUG = 0,  /* debug-level                                  */
    EN_ERR_LEVEL_INFO,       /* informational                                */
    EN_ERR_LEVEL_NOTICE,     /* normal but significant condition             */
    EN_ERR_LEVEL_WARNING,    /* warning conditions                           */
    EN_ERR_LEVEL_ERROR,      /* error conditions                             */
    EN_ERR_LEVEL_CRIT,       /* critical conditions                          */
    EN_ERR_LEVEL_ALERT,      /* action must be taken immediately             */
    EN_ERR_LEVEL_FATAL,      /* just for compatibility with previous version */
    EN_ERR_LEVEL_BUTT
} ERR_LEVEL_E;

/******************************************************************************
|----------------------------------------------------------------|
| 1 |   APP_ID   |   MOD_ID    | ERR_LEVEL |   ERR_ID            |
|----------------------------------------------------------------|
|<--><--7bits----><----8bits---><--3bits---><------13bits------->|
******************************************************************************/

#define SC_DEF_ERR(module, level, errid) \
    ((SC_S32)((SC_ERR_APPID) | ((module) << 16) | ((level) << 13) | (errid)))

/* NOTE! the following defined all common error code,
** all module must reserved 0~63 for their common error code
*/
typedef enum
{
    EN_ERR_INVALID_DEVID = 1, /* invlalid device ID                           */
    EN_ERR_INVALID_CHNID = 2, /* invlalid channel ID                          */
    EN_ERR_ILLEGAL_PARAM = 3, /* at lease one parameter is illagal
                               * eg, an illegal enumeration value             */
    EN_ERR_EXIST         = 4, /* resource exists                              */
    EN_ERR_UNEXIST       = 5, /* resource unexists                            */

    EN_ERR_NULL_PTR      = 6, /* using a NULL point                           */

    EN_ERR_NOT_CONFIG    = 7, /* try to enable or initialize system, device
                              ** or channel, before configing attribute       */

    EN_ERR_NOT_SUPPORT   = 8, /* operation or type is not supported by NOW    */
    EN_ERR_NOT_PERM      = 9, /* operation is not permitted
                              ** eg, try to change static attribute           */
    EN_ERR_INVALID_PIPEID = 10, /* invlalid pipe ID                           */
    EN_ERR_INVALID_STITCHGRPID  = 11, /* invlalid stitch group ID                           */

    EN_ERR_NOMEM         = 12,/* failure caused by malloc memory              */
    EN_ERR_NOBUF         = 13,/* failure caused by malloc buffer              */

    EN_ERR_BUF_EMPTY     = 14,/* no data in buffer                            */
    EN_ERR_BUF_FULL      = 15,/* no buffer for new data                       */

    EN_ERR_SYS_NOTREADY  = 16,/* System is not ready,maybe not initialed or
                              ** loaded. Returning the error code when opening
                              ** a device file failed.                        */

    EN_ERR_BADADDR       = 17,/* bad address,
                              ** eg. used for copy_from_user & copy_to_user   */

    EN_ERR_BUSY          = 18,/* resource is busy,
                              ** eg. destroy a venc chn without unregister it */
    EN_ERR_SIZE_NOT_ENOUGH = 19, /* buffer size is smaller than the actual size required */

    EN_ERR_BUTT          = 63,/* maxium code, private error code of all modules
                              ** must be greater than it                      */
} EN_ERR_CODE_E;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SC_ERRNO_H__ */


/**
  * @file      internal_msg_codec.h
  * @brief     内部消息编解码头文件
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */
#ifndef _INTERNAL_MSG_CODEC_H_
#define _INTERNAL_MSG_CODEC_H_

#include "v2x_types.h"

#ifdef __cplusplus         //定义对CPP进行C处理
extern "C" {
#endif

/**
  * @brief      内部消息编码
  * @param[in]  in_type     消息类型
  * @param[in]  in_buf      原始数据
  * @param[out] out_buf     编码数据
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int encode_internal_message(v2x_info_type_enum in_type, char *in_buf, char *out_buf);

/**
  * @brief      内部消息解码
  * @param[in]  in_buf      编码数据
  * @param[out] out_buf     原始数据
  * @param[out] out_type    消息类型
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int decode_internal_message(char *in_buf, char *out_buf, int *out_type);


#ifdef __cplusplus
}
#endif

#endif

/**
  * @file      v2x_includes.h
  * @brief     通用引用头文件
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */

#ifndef _V2X_INCLUDES_H_
#define _V2X_INCLUDES_H_

#ifdef __cplusplus         //定义对CPP进行C处理
extern "C" {
#endif

//系统头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//内部头文件
#include "v2x_types.h"
#include "internal_msg_codec.h"
#include "general_funcs.h"
#include "general_algorithms.h"
#include "v2x_sockets.h"
#include "general_list.h"
#include "general_queue.h"
#include "general_circular_queue.h"

#ifdef __cplusplus
}
#endif

#endif

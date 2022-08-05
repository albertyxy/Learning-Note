/**
  * @file      general_queue.h
  * @brief     通用队列及操作头文件
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */

#ifndef _GENERAL_QUEUE_H_
#define _GENERAL_QUEUE_H_

#ifdef __cplusplus         //定义对CPP进行C处理
extern "C" {
#endif

#include "general_list.h"

/**
  * @brief 通用队列
  */
typedef general_list general_queue;

/**
  * @brief      创建队列
  * @return     队列指针
  */
general_queue* queue_create();

/**
  * @brief      释放队列
  * @param[in]  queue   队列
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
void queue_free(general_queue *queue);

/**
  * @brief      在队列尾部插入节点
  * @param[in]  queue   队列
  * @param[in]  data    节点数据
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int queue_insert(general_queue* const queue, void* const data);

/**
  * @brief      删除队列头部节点
  * @param[in]  queue   队列
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int queue_delete(general_queue* const queue);

/**
  * @brief      获取队列头部节点数据
  * @param[in]  queue   队列
  * @return     节点数据
  */
void* queue_data_first(const general_queue* const queue);

/**
  * @brief      获取队列节点数量
  * @param[in]  queue   队列
  * @return     节点数量
  */
int queue_size(const general_queue* const queue);

/**
  * @brief      清空队列
  * @param[in]  queue   队列
  * @return     无
  */
void queue_clear(general_queue* const queue);

#ifdef __cplusplus
}
#endif

#endif

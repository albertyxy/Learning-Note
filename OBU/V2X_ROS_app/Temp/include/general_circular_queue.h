/**
  * @file      general_circular_queue.h
  * @brief     通用循环队列及操作头文件
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */

#ifndef _GENERAL_CIRCULAR_QUEUE_H_
#define _GENERAL_CIRCULAR_QUEUE_H_

#ifdef __cplusplus         //定义对CPP进行C处理
extern "C" {
#endif

/**
  * @brief 循环队列结构体
  */
typedef struct
{
    int     front;      ///< 队列头
    int     rear;       ///< 队列尾
    int     size;       ///< 队列大小
    int     max_size;   ///< 队列最大大小
    void*   data;       ///< 数据
    int     data_len;   ///< 数据长度
} general_circular_queue;

/**
  * @brief 循环队列迭代器结构体
  */
typedef struct
{
    int     count;                    ///< 迭代数量
    int     index;                    ///< 迭代索引
    general_circular_queue* queue;    ///< 循环队列
} general_circular_queue_iterator;

/**
  * @brief      创建循环队列
  * @param[out] queue       循环队列
  * @param[in]  max_size    循环队列大小，即队列节点个数
  * @param[in]  data_len    节点数据长度
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int circular_queue_create(general_circular_queue* queue, int max_size, int data_len);

/**
  * @brief      释放循环队列
  * @param[in]  queue       循环队列
  * @return     无
  */
void circular_queue_free(general_circular_queue *queue);

/**
  * @brief      清空循环队列
  * @param[in]  queue       循环队列
  * @return     无
  */
void circular_queue_clear(general_circular_queue *queue);

/**
  * @brief      入循环队列
  * @param[in]  queue    循环队列
  * @param[in]  data     节点数据
  * @return     执行结果
  * @retval     0       成功
  * @retval     -1      循环队列已满
  */
int circular_queue_insert(general_circular_queue* const queue, void* const data);

/**
  * @brief      出循环队列
  * @param[in]  queue    循环队列
  * @return     队列头节点数据
  * @retval     NULL    队列空
  * @retval     !NULL   循环队列头节点数据
  */
void* circular_queue_delete(general_circular_queue* const queue);

/**
  * @brief      替换节点数据
  * @param[in]  queue   循环队列
  * @param[in]  index   节点索引
  * @param[in]  data    节点数据
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int circular_queue_replace(general_circular_queue* const queue, int index, void* const data);

/**
  * @brief      循环队列是否已满
  * @param[in]  queue       循环队列
  * @return     判断结果
  * @retval     0       未满
  * @retval     1       已满
  */
int circular_queue_full(const general_circular_queue* const queue);

/**
  * @brief      循环队列是否已空
  * @param[in]  queue    循环队列
  * @return     判断结果
  * @retval     0       未空
  * @retval     1       已空
  */
int circular_queue_empty(const general_circular_queue* const queue);

/**
  * @brief      创建循环队列遍历器
  * @param[in]  iterator    遍历器
  * @param[in]  queue       循环队列
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int circular_queue_iterator_create(general_circular_queue_iterator* iterator, const general_circular_queue * const queue);

/**
  * @brief      判断遍历器是否有下一个元素
  * @param[in]  iterator    遍历器
  * @return     判断结果
  * @retval     0       没有
  * @retval     1       有
  */
int circular_queue_iterator_has_next(const general_circular_queue_iterator* const iterator);

/**
  * @brief      获取遍历器中的下一个元素
  * @param[in]  iterator    遍历器
  * @param[out] index       节点索引
  * @return     节点数据
  */
void* circular_queue_iterator_next(general_circular_queue_iterator* const iterator, int* index);

#ifdef __cplusplus
}
#endif

#endif

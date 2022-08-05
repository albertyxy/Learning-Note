/**
  * @file      general_list.h
  * @brief     通用链表及操作头文件
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */

#ifndef _GENERAL_LIST_H_
#define _GENERAL_LIST_H_

#ifdef __cplusplus         //定义对CPP进行C处理
extern "C" {
#endif

#include <stdio.h>

typedef int (*data_equal_func)(void*, void*);    ///< 数据比较函数指针
typedef void (*data_free_func)(void*);           ///< 数据释放函数指针

/**
  * @brief 链表节点结构体
  */
typedef struct _general_node
{
    void                    *data;      ///< 节点数据,只存储了指针,没有储存实际的数据
    struct _general_node    *next;      ///< 下一个节点
} general_node;

/**
  * @brief 链表结构体
  */
typedef struct
{
    general_node            *first;     ///< 头节点
    general_node            *last;      ///< 尾节点
    int                     count;      ///< 节点数量
    data_equal_func         data_equal; ///< 节点数据比较函数指针
    data_free_func          data_free;  ///< 节点数据释放函数指针
} general_list;

/**
  * @brief 链表迭代器结构体
  */
typedef struct
{
    general_node     *p;        ///< 节点
    int             count;      ///< 节点数量
    int             index;      ///< 节点索引
} general_list_iterator;

/**
  * @brief      创建链表
  * @return     链表指针
  */
general_list* list_create();

/**
  * @brief      释放链表
  * @param[in]  list    链表
  * @return     无
  */
void list_free(general_list *list);

/**
  * @brief      在链表尾部插入数据
  * @param[in]  list    链表
  * @param[in]  data    节点数据
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int list_insert_last(general_list* const list, void* const data);

/**
  * @brief      在链表头部插入数据
  * @param[in]  list    链表
  * @param[in]  data    节点数据
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int list_insert_first(general_list* const list, void* const data);

/**
  * @brief      在指定位置插入数据
  * @param[in]  list    链表
  * @param[in]  data    节点数据
  * @param[in]  index   位置索引
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int list_insert_at(general_list* const list, void* const data, int index);

/**
  * @brief      删除链表尾部节点
  * @param[in]  list    链表
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int list_delete_last(general_list* const list);

/**
  * @brief      删除链表头部节点
  * @param[in]  list    链表
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int list_delete_first(general_list* const list);

/**
  * @brief      在指定位置删除节点
  * @param[in]  list    链表
  * @param[in]  index   位置索引
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int list_delete_at(general_list* const list, int index);

/**
  * @brief      删除相同数据的节点
  *
  * 通过链表中的data_equal_func比较节点数据是否相同
  * @param[in]  list    链表
  * @param[in]  data    节点数据
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
int list_delete_data(general_list* const list, void *data);

/**
  * @brief      清空链表
  *
  * 通过链表中的data_equal_func释放节点数据
  * @param[in]  list    链表
  * @return     无
  */
void list_clear(general_list* const list);

/**
  * @brief      获取链表节点个数
  * @param[in]  list    链表
  * @return     链表节点个数
  */
int list_size(const general_list* const list);

/**
  * @brief      打印链表
  * @param[in]  list    链表
  * @param[in]  pt      打印函数
  * @return     无
  */
void list_output(const general_list* const list, void(*pt)(const void * const));

/**
  * @brief      获取链表指定位置的节点数据
  * @param[in]  list    链表
  * @param[in]  index   位置索引
  * @return     节点数据
  */
void* list_data_at(const general_list* const list, int index);

/**
  * @brief      获取链表头部节点数据
  * @param[in]  list    链表
  * @return     节点数据
  */
void* list_data_first(const general_list* const list);

/**
  * @brief      获取链表尾部节点数据
  * @param[in]  list    链表
  * @return     节点数据
  */
void* list_data_last(const general_list* const list);

/**
  * @brief      根据节点数据，查找节点位置
  *
  * 如果链表中的data_equal_func非空，则调用该方法进行比较，反之则根据指针地址来比较
  * @param[in]  list    链表
  * @param[in]  data    节点数据
  * @return     查找到的节点位置
  * @retval     -1      未找到
  * @retval     其他    第一个数据相同的节点位置
  */
int list_data_find(const general_list* const list, void *data);

/**
  * @brief      创建链表遍历器
  * @param[in]  list    链表
  * @return     链表遍历器指针
  */
general_list_iterator* list_iterator_create(const general_list * const list);

/**
  * @brief      释放链表遍历器
  * @param[in]  iterator    链表遍历器
  * @return     无
  */
void list_iterator_free(general_list_iterator* iterator);

/**
  * @brief      判断遍历器是否有下一个元素
  * @param[in]  iterator    链表遍历器
  * @return     判断结果
  * @retval     0           没有
  * @retval     1           有
  */
int list_iterator_has_next(const general_list_iterator* const iterator);

/**
  * @brief      获取遍历器中的下一个元素
  * @param[in]  iterator    遍历器
  * @return     节点数据
  */
void* list_iterator_next(general_list_iterator* const iterator);

#ifdef __cplusplus
}
#endif

#endif

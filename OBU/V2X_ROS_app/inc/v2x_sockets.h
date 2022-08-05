/**
  * @file      v2x_sockets.h
  * @brief     通用socket操作头文件
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */

#ifndef _V2X_SOCKETS_H_
#define _V2X_SOCKETS_H_

#ifdef __cplusplus         //定义对CPP进行C处理
extern "C" {
#endif

//头文件
#include <netinet/in.h>

//---- 常量定义 开始 ----
//---- 常量定义 结束 ----


//---- 枚举定义 开始 ----
//---- 枚举定义 结束 ----


//---- 结构体定义 开始 ----
//---- 结构体定义 结束 ----

//---- 函数定义 开始 ----

/**
  * @brief      创建inet tcp服务端socket
  *
  * 主要操作包括：
  * - 创建socket
  * - 绑定端口
  * - 监听端口
  * @param[out] fd      socket句柄
  * @param[in]  addr    绑定地址
  * @param[in]  port    绑定端口
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int create_server_inet_stream_socket(int *fd, const char *addr, unsigned short port);

/**
  * @brief      创建inet tcp客户端socket
  *
  * 主要操作包括：
  * - 创建socket
  * - 连接服务端
  * @param[out] fd      socket句柄
  * @param[in]  addr    服务端地址
  * @param[in]  port    服务端端口
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int create_client_inet_stream_socket(int *fd, const char *addr, unsigned short port);

/**
  * @brief      创建inet udp客户端socket
  *
  * 主要操作包括：
  * - 创建socket
  * - 若本地端口大于0，则绑定本地端口
  * @param[out] fd      socket句柄
  * @param[in]  addr    本地地址
  * @param[in]  port    本地端口
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int create_inet_dgram_socket(int *fd, const char *addr, unsigned short port);

/**
  * @brief      inet udp socket数据发送
  * @param[in]  fd      socket句柄
  * @param[in]  addr    目的地址
  * @param[in]  port    目的端口
  * @param[in]  msg     发送数据
  * @param[in]  len     发送数据长度
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int send_inet_dgram_socket(int fd, const char *addr, unsigned short port, const char *msg, int len);

/**
  * @brief      设置socket属性
  * @param[in]  fd      socket句柄
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int set_socket_option(int fd);

/**
  * @brief      创建unix tcp服务端socket
  *
  * 主要操作包括：
  * - 创建socket
  * - 绑定地址
  * - 监听地址
  * @param[out] fd      socket句柄
  * @param[in]  addr    绑定地址
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int create_server_unix_stream_socket(int *fd, const char *addr);

/**
  * @brief      创建unix tcp客户端socket
  *
  * 主要操作包括：
  * - 创建socket
  * - 连接服务端
  * @param[out] fd      socket句柄
  * @param[in]  addr    服务端地址
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int create_client_unix_stream_socket(int *fd, const char *addr);

/**
  * @brief      创建unix udp socket
  *
  * 主要操作包括：
  * - 创建socket
  * - 若绑定地址不为空，则绑定该地址
  * @param[out] fd      socket句柄
  * @param[in]  addr    绑定地址
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int create_unix_dgram_socket(int *fd, const char *addr);

/**
  * @brief      unix udp socket数据发送
  * @param[in]  fd      socket句柄
  * @param[in]  addr    目的地址
  * @param[in]  msg     发送数据
  * @param[in]  len     发送数据长度
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int send_unix_dgram_socket(int fd, const char *addr, const char *msg, int len);

//---- 函数定义 结束 ----

#ifdef __cplusplus
}
#endif

#endif

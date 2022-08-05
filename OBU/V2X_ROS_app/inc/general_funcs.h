/**
  * @file      general_funcs.h
  * @brief     通用方法头文件
  *
  * 包括配置读取、通用结构体操作、通用socket操作等相关的通用方法
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */
#ifndef _GENERAL_FUNCS_H_
#define _GENERAL_FUNCS_H_

//=================================================
//头文件
#include <libgen.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "v2x_types.h"

#define V2X_PR(level, id, fmt, args...) v2x_pr(basename((char *)__FILE__), __LINE__, level, id, fmt, ##args)

//函数=================================================

/**
  * @brief      获取数组长度
  * @param[in]  array   数组名
  * @return     数组长度
  */
#define GET_ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/**
  * @brief      日志级别初始化，从配置文件中读取日志级别，并设置
  * @return     无
  */
extern void log_level_init(void);


/**
  * @brief      格式化字符串(可变参数)
  * @param[in]  size    字符串缓存最大长度
  * @param[in]  format  字符串格式
  * @param[out] str     格式化的字符串
  * @return     字符串长度
  * @retval     <0      执行失败
  * @retval     其他    格式化的字符串长度.
  */
extern int format_str(char *str, int size, const char *format, ...);

/**
  * @brief      打印日志(可变参数)
  * @param[in]  file    代码文件名
  * @param[in]  line    代码行数
  * @param[in]  level   日志级别
  * @param[in]  app_id  模块ID
  * @param[in]  format  格式化的字符串
  * @return     无
  */
extern void v2x_pr(const char *file, int line, v2x_log_level_enum level, const char *app_id, const char* format, ...);

/**
  * @brief      获取设备ID
  * @param[out] dev_id     设备ID
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_dev_id(char *dev_id);

/**
  * @brief      校验ID数据是否一致
  * @param[in]  id1         ID1数据
  * @param[in]  id2         ID2数据
  * @param[in]  id_len      ID长度
  * @return     执行结果
  * @retval     0       相同
  * @retval     其他    不相同
  */
extern int check_id_from_len(char *id1, char *id2, int id_len);

//配置文件操作
/**
  * @brief      获取文件完整路径（应用所在目录）
  * @param[out] path        文件完整路径
  * @param[in]  maxlen      path最大长度
  * @param[in]  file_name   文件名
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_file_path(char *path, int maxlen, const char *file_name);

/**
  * @brief      读取模块配置信息
  * @param[in]  file        配置文件名（完整路径）
  * @param[in]  name        模块名称
  * @param[out] out_info    模块配置信息
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int read_config_info(char *file, char *name, v2x_config_struct *out_info);

/**
  * @brief      读取指定配置项的整数值
  * @param[in]  in_info         模块配置信息
  * @param[in]  name            配置项名称
  * @param[in]  log_id          日志ID，用于打印日志
  * @param[in]  default_value   默认值，读取失败则取默认值
  * @param[out] value           配置值
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int read_config_value_int(v2x_config_struct *in_info, const char *name, const char *log_id, int default_value, int *value);

/**
  * @brief      读取指定配置项的浮点值
  * @param[in]  in_info         模块配置信息
  * @param[in]  name            配置项名称
  * @param[in]  log_id          日志ID，用于打印日志
  * @param[in]  default_value   默认值，读取失败则取默认值
  * @param[out] value           配置值
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int read_config_value_double(v2x_config_struct *in_info, const char *name, const char *log_id, double default_value, double *value);

/**
  * @brief      读取指定配置项的字符串值
  * @param[in]  in_info         模块配置信息
  * @param[in]  name            配置项名称
  * @param[in]  log_id          日志ID，用于打印日志
  * @param[in]  default_value   默认值，读取失败则取默认值
  * @param[out] value           配置值
  * @param[in]  out_len         value最大长度
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int read_config_value_string(v2x_config_struct *in_info, const char *name, const char *log_id, const char *default_value, char *value, int out_len);

/**
  * @brief      读取指定配置项的数组值
  * @param[in]  in_info         模块配置信息
  * @param[in]  name            配置项名称
  * @param[in]  log_id          日志ID，用于打印日志
  * @param[out] value           配置值
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int read_config_value_array(v2x_config_struct *in_info, const char *name, const char *log_id, v2x_config_struct **value);

/**
  * @brief      读取通用配置信息
  * @param[in]  file_name       配置文件名（完整路径）
  * @param[in]  log_id          日志ID，用于打印日志
  * @param[out] config          通用配置信息
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int read_common_config(const char *file_name, const char *log_id, v2x_com_config_struct *config);

/**
  * @brief      读取数据文件
  * @param[in]  type        读取数据文件内容的类型
  * @param[out] out_info    数据文件内容，动态分配，使用完毕后需手动释放
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int read_data_file(int type, void *out_info);

/**
  * @brief      获取系统当前时间
  * @return     UTC时间，单位：秒
  */
extern double get_sys_utc_time(void);

/**
  * @brief      设置系统时间
  * @param[in]  utc    UTC时间
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int set_sys_utc_time(double utc);

/**
  * @brief      获取当前年份已经过去的总分钟数
  * @return     当前年份已经过去的总分钟数
  */
extern int get_minute_of_the_year_utc(void);

/**
  * @brief      获取UTC时间时，当前年份已经过去的总分钟数
  * @param[in]  utc_time    UTC时间
  * @return     当前年份已经过去的总分钟数
  */
extern int get_minute_of_the_year_from_utc_time(double utc_time);

/**
  * @brief      获取当前1分钟内的毫秒级时刻
  * @return     当前1分钟内的毫秒级时刻，单位秒
  */
extern double get_ms_of_the_minute(void);

/**
  * @brief      获取当前1小时内的毫秒级时刻
  * @return     当前1小时内的毫秒级时刻，单位秒
  */
extern double get_ms_of_the_hour(void);

/**
  * @brief      在时间周期内，存在差值限制下，获取时间差值，time2-time1
  * @param[in]  time1           输入时间1
  * @param[in]  time2           输入时间2
  * @param[in]  period          时间切换周期，常用为3600
  * @param[in]  diff_limit      时间差值最大范围限制
  * @param[out] time_diff       时间差值
  * @return     执行结果
  * @retval     0               成功
  * @retval     其他            失败
  */
extern int get_time_diff_in_period(double time1, double time2, double period, double diff_limit, double *time_diff);

/**
* @brief      将内部使用的double类型UTC时间转换成LTEV使用的格式时间
* @param[in]  utc_time              内部使用的double类型UTC时间
* @param[out] minute_of_the_year    当前年份已经过去的总分钟数
* @param[out] ms_of_the_minute      1分钟内的毫秒级时刻
* @return     无
*/
extern void utc_time_to_ltev_time(double utc_time, int *minute_of_the_year, int *ms_of_the_minute);

/**
* @brief      将LTEV使用的格式时间转换成内部使用的double类型UTC时间
* @param[in]  minute_of_the_year    当前年份已经过去的总分钟数
* @param[in]  ms_of_the_minute      1分钟内的毫秒级时刻
* @param[out] utc_time              内部使用的double类型UTC时间
* @return     无
*/
extern void ltev_time_to_utc_time(int *minute_of_the_year, int ms_of_the_minute, double *utc_time);

/**
  * @brief      检测system函数操作是否成功
  * @param[in]  status    进程ID
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int check_system_func_result(pid_t status);

/**
  * @brief      通用结构体初始化
  * @param[in]  in_struct   结构体指针
  * @param[in]  type        结构体类型
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int general_strcut_init(void *in_struct, v2x_info_type_enum type);

/**
  * @brief      通用结构体拷贝
  * @param[out] dst_struct  目的结构体指针，动态分配，使用完成后需手动释放
  * @param[in]  src_struct  源结构体指针
  * @param[in]  type        结构体类型
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int general_strcut_copy(void *dst_struct, const void *src_struct, v2x_info_type_enum type);

/**
  * @brief      通用结构体释放
  * @param[in]  in_struct   结构体指针
  * @param[in]  type        结构体类型
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int general_strcut_free(void *in_struct, v2x_info_type_enum type);

/**
  * @brief      获取结构体名称字符串
  * @param[in]  type    结构体类型
  * @return     结构体名称
  * @retval     "err_msg"   错误信息
  * @retval     其他        结构体名称字符串，如type为INFO_BSM，则返回值为"BSM".
  */
extern char *get_info_string(v2x_info_type_enum type);

/**
  * @brief      通用socket创建函数
  *
  * 根据socket类型自动完成socket创建、监听或连接等过程：
  * - SOCK_TCP_SERVER:创建tcp server socket，绑定并监听设定地址及端口
  * - SOCK_TCP_CLIENT:创建tcp client socket，连接设定的服务器地址及端口，若存在注册信息，则自动完成注册
  * - SOCK_UDP:创建udp socket，若设定本地地址和端口，则绑定本地地址和端口
  * @param[in]  com_socks   通用socket数组
  * @param[in]  num         通用socket数组数量
  * @param[in]  log_id      日志ID，用于打印日志
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int com_create_socks(v2x_com_sock_struct* com_socks, int num, const char *log_id);

/**
  * @brief      多路socket检测函数
  * @param[in]  com_socks   通用socket数组
  * @param[in]  num         通用socket数组数量
  * @param[in]  log_id      日志ID，用于打印日志
  * @param[in]  rx_timeout  检测超时时间
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int com_select_socks(v2x_com_sock_struct* com_socks, int num, const char *log_id, struct timeval* rx_timeout);

/**
  * @brief      通用socket 关闭函数
  * @param[in]  com_socks   通用socket数组
  * @param[in]  num         通用socket数组数量
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int com_close_socks(v2x_com_sock_struct* com_socks, int num);

/**
  * @brief      通用数据接收处理函数
  * @param[in]  com_sock    通用socket
  * @param[in]  log_id      日志ID，用于打印日志
  * @param[in]  in_buf      接收数据缓存
  * @param[in]  in_len      接收数据长度
  * @param[in]  func        解析数据回调函数
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int com_recv_deal(v2x_com_sock_struct* com_sock, const char *log_id, char *in_buf, int in_len, int (*func)(v2x_com_sock_struct*, char *, int));

/**
  * @brief      通用发送消息至客户端
  *
  * 将指定消息发送至已注册的多个客户端
  * @param[in]  com_socks   通用socket数组
  * @param[in]  num         通用socket数组数量
  * @param[in]  log_id      日志ID，用于打印日志
  * @param[in]  buf         发送数据缓存
  * @param[in]  len         发送数据长度
  * @param[in]  msg_str     消息名称
  * @param[in]  rm_info     注册信息，需指定消息类型
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int com_send_clients(v2x_com_sock_struct* com_socks, int num, const char *log_id, char* buf, int len, char* msg_str, void* rm_info);

/**
  * @brief      通用建立连接处理函数
  *
  * 判断服务端的连接数是否已满，若连接数未满，则存储相关信息，反之则直接关闭新建立的连接
  * @param[in]  com_socks   通用socket数组
  * @param[in]  num         通用socket数组数量
  * @param[in]  log_id      日志ID，用于打印日志
  * @param[in]  srv_sock    服务端socket
  * @param[in]  accept_fd   socket连接句柄
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int com_accept_deal(v2x_com_sock_struct* com_socks, int num, const char *log_id, v2x_com_sock_struct* srv_sock, int accept_fd);

/**
  * @brief      通用socket发送函数
  *
  * 根据socket类型，调用对应的系统函数，将数据发送至设定目的
  * @param[in]  buf         发送数据缓存
  * @param[in]  len         发送数据长度
  * @param[in]  com_sock    通用socket
  * @param[in]  log_id      日志ID，用于打印日志
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int com_send_sock(char *buf, int len, v2x_com_sock_struct *com_sock, const char *log_id);

/**
  * @brief      通用客户端注册函数
  *
  * 客户端发送注册信息至服务端
  * @param[in]  com_sock    通用socket
  * @param[in]  log_id      日志ID，用于打印日志
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int com_client_register(v2x_com_sock_struct* com_sock, const char *log_id);

/**
  * @brief      大端char数组转int
  * @param[in]  buf     char数组
  * @return     转换后的int值
  */
extern int charbe_to_int(const char *buf);

/**
  * @brief      大端char数组转short int
  * @param[in]  buf     char数组
  * @return     转换后的short int值
  */
extern short int charbe_to_short(const char *buf);

/**
  * @brief      short int转大端char数组
  * @param[in]  val     short int值
  * @param[out] buf     转换后的char数组
  * @return     转换后的char数组长度
  */
extern int short_to_charbe(short int val, char *buf);

/**
  * @brief      int转大端char数组
  * @param[in]  val     int值
  * @param[out] buf     转换后的char数组
  * @return     转换后的char数组长度
  */
extern int int_to_charbe(int val, char *buf);

/**
  * @brief      字符数组转十六进制字符串
  * @param[in]  in_buf      字符数组
  * @param[in]  in_len      字符数组长度
  * @param[out] out_buf     十六进制字符数组缓存
  * @param[in]  out_size    十六进制字符数组最大长度
  * @return     字符串长度
  * @retval     <0      失败
  * @retval     其他    转换后的十六进制字符数组长度.
  */
extern int bytes_to_hexstr(const char *in_buf, int in_len, char *out_buf, int out_size);

/**
  * @brief      十六进制字符串转字符数组
  * @param[in]  in_buf      十六进制字符串（需包含结尾符）
  * @param[out] out_buf     字符数组
  * @param[out] out_len     字符数组长度
  * @param[in]  out_size    字符数组最大长度
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int hexstr_to_bytes(const char *in_buf, char *out_buf, int *out_len, int out_size);

/**
  * @brief      车辆ID对比
  * @param[in]  in_id1      输入车辆ID1
  * @param[in]  in_id2      输入车辆ID2
  * @return     执行结果
  * @retval     0       相同
  * @retval     其他    不同或错误
  */
extern int veh_id_cmp(char *in_id1, char *in_id2);

/**
  * @brief      打印自定义字符数组
  * @param[in]  head_buf    打印数据头
  * @param[in]  buf         字符数组缓存
  * @param[in]  len         字符数组长度
  * @param[in]  flag        打印标识
  * @param[in]  log_id      日志ID
  * @return     无
  */
extern void pr_ud_buf(const char *head_buf, const char *buf, int len, int flag, const char *log_id);

/**
  * @brief      获取车辆所在的地图信息
  * @param[in]  map         地图数据
  * @param[in]  pos         车辆位置信息
  * @param[in]  heading     车辆方向信息
  * @param[in]  heading_diff 车辆方向与区域方向差额判断阈值
  * @param[in]  radius_correction 判断区域半径修正
  * @param[out] out_node    车辆所在节点指针
  * @param[out] out_link    车辆所在路段指针
  * @param[out] out_lane    车辆所在道路指针
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    车辆不在地图信息包含范围内
  */
extern int get_in_map_info(v2x_map_struct* map, v2x_position_struct* pos, double heading, double heading_diff, double radius_correction, v2x_node_struct** out_node, v2x_link_struct** out_link, v2x_lane_struct** out_lane);

/**
  * @brief      获取车辆所在的RSI信息
  * @param[in]  rsi         RSI数据
  * @param[in]  pos         车辆位置信息
  * @param[in]  up_ref_id   车辆所处路段上游节点ID
  * @param[in]  down_ref_id 车辆所处路段下游节点ID
  * @param[in]  lane_id     车辆所处车道ID
  * @param[in]  heading     车辆方向信息
  * @param[in]  heading_diff    车辆方向与区域方向差额判断阈值
  * @param[in]  radius_correction   判断区域半径修正
  * @param[out] priority    匹配RSI优先级
  * @param[out] type        匹配RSI类型
  * @param[out] subtype     匹配RSI子类型
  * @param[out] description 匹配RSI描述
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_in_rsi_info(v2x_rsi_struct *rsi, v2x_position_struct *pos, v2x_node_ref_id_struct *up_ref_id,
    v2x_node_ref_id_struct *down_ref_id, int lane_id, double heading, double heading_diff, double radius_correction,
    int *priority, int *type, int *subtype, char **description);

/**
  * @brief      获取车辆到停止线距离和位置数据
  * @param[in]  link        路段数据
  * @param[in]  lane        道路数据
  * @param[in]  pos         车辆位置数据
  * @param[out] dis         车辆到停止线距离
  * @param[out] out_pos     停止线位置数据
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_stopline_dis_pos(v2x_link_struct *link, v2x_lane_struct *lane, v2x_position_struct *pos, double *dis, v2x_position_struct **out_pos);

/**
  * @brief      获取速度限制信息
  * @param[in]  link        路段数据
  * @param[in]  lane        道路数据
  * @param[out] speed_limit 速度限制信息
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_speed_limit(v2x_link_struct *link, v2x_lane_struct *lane, double *speed_limit);

/**
  * @brief      获取相位ID
  * @param[in]  link        路段数据
  * @param[in]  lane        道路数据
  * @param[out] phase_id    相位ID
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_phase_id(v2x_link_struct *link, v2x_lane_struct *lane, unsigned long *phase_id);

/**
  * @brief      获取相位信息
  * @param[in]  spat        SPAT数据
  * @param[in]  node_ref_id 节点ID信息
  * @param[in]  phase_id    相位ID信息
  * @param[out] phase       相位信息
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_phase(v2x_spat_struct *spat, v2x_node_ref_id_struct *node_ref_id, unsigned long phase_id, v2x_phase_struct **phase);

/**
  * @brief      获取相位信息和相关时间
  * @param[in]  spat        SPAT数据
  * @param[in]  node_ref_id 节点ID信息
  * @param[in]  phase_id    相位ID信息
  * @param[out] phase       相位信息
  * @param[out] ref_time    相关时间
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_phase_and_ref_time(v2x_spat_struct *spat, v2x_node_ref_id_struct *node_ref_id, unsigned long phase_id, v2x_phase_struct **phase, double *ref_time);


/**
  * @brief      获取相位状态信息
  * @param[in]  phase                           相位数据
  * @param[in]  ref_time                        参考时间
  * @param[out] curr_light_state                当前灯状态
  * @param[out] curr_light_likely_end_time      当前灯结束时间
  * @param[out] green_start_time_opt            绿灯开始时间OPT
  * @param[out] green_start_time                绿灯开始时间
  * @return     执行结果
  * @retval     0       成功获取当前灯状态和结束时间
  * @retval     其他    失败
  */
extern int get_phase_state(v2x_phase_struct *phase, double ref_time, int *curr_light_state, double *curr_light_likely_end_time, bool *green_start_time_opt, double *green_start_time);

/**
  * @brief      校验节点参考ID是否相同
  * @param[in]  id1         ID1数据
  * @param[in]  id2         ID2数据
  * @return     执行结果
  * @retval     0       相同
  * @retval     其他    不相同
  */
extern int check_node_ref_id(v2x_node_ref_id_struct* id1, v2x_node_ref_id_struct* id2);

/**
  * @brief      utf-8转为gb2312
  * @param[in]  inbuf           输入数据
  * @param[in]  inlen           输入数据长度
  * @param[out] outbuf          输出数据
  * @param[in]  outlen          输出数据缓存大小
  * @return     执行结果
  * @retval     0               成功
  * @retval     其他            失败
  */
extern int utf_8_to_gb2312(char *inbuf,int inlen,char *outbuf,int outlen);

/**
  * @brief      gb2312转为utf-8
  * @param[in]  inbuf           输入数据
  * @param[in]  inlen           输入数据长度
  * @param[out] outbuf          输出数据
  * @param[in]  outlen          输出数据缓存大小
  * @return     执行结果
  * @retval     0               成功
  * @retval     其他            失败
  */
extern int gb2312_to_utf_8(char *inbuf,size_t inlen,char *outbuf,size_t outlen);

#endif

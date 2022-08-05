#ifndef _app_bsj_general__h_
#define _app_bsj_general__h_

#include "v2x_includes.h"

//自定义
#define LOG_ID				"BSJ"
#define IP_ADDR_SIZE		 16

//结构体
typedef struct bsj_config
{
    double veh_width;				//车宽 
    double veh_length;				//车长
    int basic_vehicle_class;		//车辆类型
    double braking_acc_threshold;	//紧急制动加速度阈值
    int	 rsp_type;					//车辆当前行驶或驾驶状态
	char tx_addr[IP_ADDR_SIZE];		//发送地址
    int  tx_port;					//发送端口
    int  rx_port;					//接收端口

} bsj_config_struct;

//全局变量
extern bsj_config_struct g_bsj_config;

//全局函数
extern int config_init(void);

#endif

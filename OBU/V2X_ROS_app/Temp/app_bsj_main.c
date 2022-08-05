/******************************************************************
 版权信息   : 金溢科技版权所有，保留一切权利
 文件名称   : app_bsj_main.c
 作者       : zhangchao
 完成日期   : 2021-08-26
 当前版本号 : V2.0.0
 主要功能   : 接收保时捷BSM/MAP/SPAT/RSI消息组包通过无线编解码广播发送
 版本历史   : 无
 ******************************************************************/
#include <math.h>
#include <sys/time.h>

#include "lib_v2x_wmcp.h"
#include "v2x_includes.h"
#include "app_bsj_general.h"

//常量定义
#define SOFTWARE_VERSION	"SOFTWARE_VERSION:V1.0.0"
#define SOFTWARE_DATE		"SOFTWARE_DATE:2021-08-27"

#define MAX_SOCK_NUM            3
#define TX_V2X_HEART_INTERVAL   3

#define CONTROL_YEAR            (2021)
#define CONTROL_MONTH           (9)
#define CONTROL_DAY             (25)

//变量定义
static v2x_com_sock_struct s_com_socks[MAX_SOCK_NUM];
static v2x_clt_sock_struct s_wmh_sock;
static v2x_com_sock_struct* s_com_wmh_sock;
static v2x_udp_sock_struct s_bsj_udp_sock;
static v2x_udp_sock_struct s_auto_udp_sock;
static v2x_com_sock_struct* s_com_auto_sock;

static v2x_bsm_struct s_host_bsm,s_remote_bsm;

/*************************************************
 函数名称:    tx_bsm_info
 函数描述:    发送BSM消息
 作者：
 输入参数:    无
 输出参数:    无
 返回说明:    无
 其它说明:    无
 *************************************************/
static int tx_bsm_info(void)
{
    //封装BSM数据
    char tx_buf[MAX_COMM_BUF_LEN] = {0};
    int ret = encode_internal_message(INFO_BSM, (char *)(&s_host_bsm), tx_buf);
    if(ret)
    {
        V2X_PR(LOG_LEVEL_WARNING, LOG_ID, "encode internal message %s err(%d)", get_info_string(INFO_BSM), ret);
        return -1;
    }
    int tx_len = strlen(tx_buf) + 1;
    v2x_clt_rm_struct rm_info;
    general_strcut_init((void *)&rm_info, INFO_CLT_RM);
    rm_info.msg_type = MSG_TYPE_BSM;
    V2X_PR(LOG_LEVEL_DEBUG, LOG_ID, "tx wmh %s:[%d]%s", get_info_string(INFO_BSM), tx_len, tx_buf);
    com_send_sock(tx_buf, tx_len, s_com_wmh_sock, LOG_ID);
    return 0;
}

/*************************************************
 函数名称:    tx_map_info
 函数描述:    发送MAP至客户端
 作者：
 输入参数:    map：地图信息；
 输出参数:    无
 返回说明:    0：成功；非0：失败
 其它说明:    无
 *************************************************/
static int tx_map_info(v2x_map_struct *map)
{
    if (map == NULL)
    {
        return -1;
    }

    int ret = -1;
    char tx_buf[MAX_COMM_BUF_LEN] = {0};
    int tx_len = 0;

    ret = encode_internal_message(INFO_MAP, (char*)map, tx_buf);
    if(ret)
    {
        V2X_PR(LOG_LEVEL_WARNING, LOG_ID, "encode internal message %s err(%d)", get_info_string(INFO_MAP), ret);
        return -1;
    }
    tx_len = strlen(tx_buf) + 1;
    v2x_clt_rm_struct rm_info;
    general_strcut_init((void *)&rm_info, INFO_CLT_RM);
    rm_info.msg_type = MSG_TYPE_MAP;
    V2X_PR(LOG_LEVEL_DEBUG, LOG_ID, "tx wmh %s:[%d]%s", get_info_string(INFO_MAP), tx_len, tx_buf);
    com_send_sock(tx_buf, tx_len, s_com_wmh_sock, LOG_ID);

    return 0;
}

/*************************************************
 函数名称:    tx_spat_info
 函数描述:    发送SPAT至客户端
 作者：
 输入参数:    spat：信号灯状态信息；
 输出参数:    无
 返回说明:    0：成功；非0：失败
 其它说明:    无
 *************************************************/
static int tx_spat_info(v2x_spat_struct *spat)
{
    if (spat == NULL)
    {
        return -1;
    }

    int ret = -1;
    char tx_buf[MAX_COMM_BUF_LEN] = {0};
    int tx_len = 0;

    ret = encode_internal_message(INFO_SPAT, (char*)spat, tx_buf);
    if(ret)
    {
        V2X_PR(LOG_LEVEL_WARNING, LOG_ID, "encode internal message %s err(%d)", get_info_string(INFO_SPAT), ret);
        return -1;
    }
    tx_len = strlen(tx_buf) + 1;
    v2x_clt_rm_struct rm_info;
    general_strcut_init((void *)&rm_info, INFO_CLT_RM);
    rm_info.msg_type = MSG_TYPE_SPAT;
    V2X_PR(LOG_LEVEL_DEBUG, LOG_ID, "tx wmh %s:[%d]%s", get_info_string(INFO_SPAT), tx_len, tx_buf);
    com_send_sock(tx_buf, tx_len, s_com_wmh_sock, LOG_ID);

    return 0;
}

/*************************************************
 函数名称:    tx_rsi_info
 函数描述:    发送RSI至客户端
 作者：
 输入参数:    rsi：路侧告警信息；
 输出参数:    无
 返回说明:    0：成功；非0：失败
 其它说明:    无
 *************************************************/
static int tx_rsi_info(v2x_rsi_struct *rsi)
{
    if(rsi == NULL)
    {
        return -1;
    }

    int ret = -1;
    char tx_buf[MAX_COMM_BUF_LEN] = {0};
    int tx_len = 0;

    ret = encode_internal_message(INFO_RSI, (char*)rsi, tx_buf);
    if(ret)
    {
        V2X_PR(LOG_LEVEL_WARNING, LOG_ID, "encode internal message %s err(%d)", get_info_string(INFO_RSI), ret);
        return -1;
    }
    tx_len = strlen(tx_buf) + 1;
    v2x_clt_rm_struct rm_info;
    general_strcut_init((void *)&rm_info, INFO_CLT_RM);
    rm_info.msg_type = MSG_TYPE_RSI;
    V2X_PR(LOG_LEVEL_DEBUG, LOG_ID, "tx wmh %s:[%d]%s", get_info_string(INFO_RSI), tx_len, tx_buf);
    com_send_sock(tx_buf, tx_len, s_com_wmh_sock, LOG_ID);

    return 0;
}

/*************************************************
 函数名称:    deal_decode_info
 函数描述:    处理接收解析信息
 作者：
 输入参数:    com_sock：通用socket； buf：解析数据缓存；type：解析数据类型；index：数据索引
 输出参数:    无
 返回说明:    无
 其它说明:    无
 *************************************************/
static int deal_decode_info(v2x_com_sock_struct* com_sock, char *buf, int type)
{
    int ret = -1;
    char tx_buf[MAX_COMM_BUF_LEN] = {0};
    int tx_len = 0;

    switch(type)
    {
        case INFO_CLT_RM:
        {
            v2x_clt_sock_struct* clt_sock = (v2x_clt_sock_struct*)com_sock->ex;
            memcpy(clt_sock->reg_info,buf,sizeof(v2x_clt_rm_struct));
            clt_sock->reg_type = type;
            v2x_clt_rm_struct *rm_info = (v2x_clt_rm_struct *)clt_sock->reg_info;
            snprintf(com_sock->name, sizeof(com_sock->name), "%s", rm_info->name);
            break;
        }
        case INFO_BSM:
        {
            v2x_bsm_struct *tmp_struct = (v2x_bsm_struct *)(buf);
            if(tmp_struct->host_flag == VEH_FLAG_REMOTE)
            {
				memcpy(&s_remote_bsm, tmp_struct, sizeof(v2x_bsm_struct));
                //封装BSM数据
                ret = encode_internal_message(INFO_BSM, buf, tx_buf);
                if(ret)
                {
                    V2X_PR(LOG_LEVEL_WARNING, LOG_ID, "encode internal message %s err(%d)", get_info_string(INFO_BSM), ret);
                    return -1;
                }
                tx_len = strlen(tx_buf) + 1;
				V2X_PR(LOG_LEVEL_DEBUG, LOG_ID, "tx bsj udp %s:[%d]%s", get_info_string(type), tx_len, tx_buf);
				com_send_sock(tx_buf, tx_len, s_com_auto_sock, LOG_ID);
            }
            break;
        }
        default:
        {
            V2X_PR(LOG_LEVEL_WARNING, LOG_ID, "%s is not need", get_info_string(type));
            return -1;
        }
    }

    return 0;
}

/*************************************************
 函数名称:    deal_out_decode_info
 函数描述:    处理客户端解析信息
 作者：
 输入参数:    com_sock：通用socket； buf：解析数据缓存；type：解析数据类型；index：数据索引
 输出参数:    无
 返回说明:    0：成功；非0：失败
 其它说明:    无
 *************************************************/
static int deal_udp_decode_info(v2x_com_sock_struct* com_sock, char *buf, int type)
{
	switch(type)
    {
        case INFO_BSM:
        {
			if(s_com_wmh_sock->fd <= 0)
            {
                V2X_PR(LOG_LEVEL_WARNING, LOG_ID, "wmh fd disconnect");
                return -1;
            }

			v2x_bsm_struct *tmp_struct = (v2x_bsm_struct *)(buf);
			
			//Dev ID ok
			memcpy(s_host_bsm.id, tmp_struct->id, MAX_ID_LEN);
			s_host_bsm.plate_no_opt	= tmp_struct->plate_no_opt;
			memcpy(s_host_bsm.plate_no, tmp_struct->plate_no, MAX_PLATE_NO_LEN);


			//平均速度[车宽] average speed ok[1023]
			s_host_bsm.veh_size.width = tmp_struct->veh_size.width;

			//方向盘转角小数[时间] steeringAngle after dot 待定[9999] ok [65535]
			//s_host_bsm.veh_size.length = tmp_struct->veh_size.length;	//范围不满足要求
			
			//圈数[车辆类型] lapNumber ok[255]
			s_host_bsm.vehicle_classification.classification = tmp_struct->vehicle_classification.classification;

			//TPS data
			//laptime 圈时间 UTC时间替代 ok
			s_host_bsm.time_stamp				= tmp_struct->time_stamp;
			s_host_bsm.pos 						= tmp_struct->pos;
			s_host_bsm.pos.elevation_opt		= true;
			s_host_bsm.pos.elevation			= tmp_struct->pos.elevation;
			s_host_bsm.speed					= tmp_struct->speed;
			s_host_bsm.heading					= tmp_struct->heading;
			s_host_bsm.events_opt				= tmp_struct->events_opt;
			s_host_bsm.path_his_opt				= tmp_struct->path_his_opt;
			s_host_bsm.path_pre_opt				= tmp_struct->path_pre_opt;
			
			//VIS
			s_host_bsm.angle_opt 				= tmp_struct->angle_opt;
			s_host_bsm.angle					= tmp_struct->angle;
			s_host_bsm.accel_set.acc_lat_opt	= tmp_struct->accel_set.acc_lat_opt;
			s_host_bsm.accel_set.acc_lat		= tmp_struct->accel_set.acc_lat;
			s_host_bsm.accel_set.acc_vert_opt	= tmp_struct->accel_set.acc_vert_opt;
			s_host_bsm.accel_set.acc_vert		= tmp_struct->accel_set.acc_vert;
			s_host_bsm.accel_set.acc_lng		= tmp_struct->accel_set.acc_lng;
			s_host_bsm.accel_set.yaw_rate		= tmp_struct->accel_set.yaw_rate;
			s_host_bsm.lights_opt				= tmp_struct->lights_opt;
			s_host_bsm.lights					= tmp_struct->lights;
			s_host_bsm.trans_opt				= tmp_struct->trans_opt;
			s_host_bsm.trans					= tmp_struct->trans;
			s_host_bsm.pos_acc_opt				= tmp_struct->pos_acc_opt;	//方向盘转角小数
			s_host_bsm.pos_acc					= tmp_struct->pos_acc;
			s_host_bsm.pos_confidence_opt		= tmp_struct->pos_confidence_opt;
			s_host_bsm.pos_confidence			= tmp_struct->pos_confidence;
			s_host_bsm.climb_opt				= tmp_struct->climb_opt;
			s_host_bsm.climb					= tmp_struct->climb;
			s_host_bsm.relative_pos_opt			= tmp_struct->relative_pos_opt;
			s_host_bsm.relative_pos				= tmp_struct->relative_pos;
			s_host_bsm.brakes.scs_opt			= tmp_struct->brakes.scs_opt;
			s_host_bsm.brakes.scs				= tmp_struct->brakes.scs;
			
			tx_bsm_info();					
            break;
        }
		case INFO_MAP:
        {
            tx_map_info((v2x_map_struct *)(buf));
            break;
        }
		case INFO_SPAT:
        {
            tx_spat_info((v2x_spat_struct *)(buf));
            break;
        }
		case INFO_RSI:
        {
            tx_rsi_info((v2x_rsi_struct *)(buf));
            break;
        }
        default:
        {
            V2X_PR(LOG_LEVEL_WARNING, LOG_ID, "%s is not need", get_info_string(type));
            return -1;
        }
    }

	return 0;
}

/*************************************************
 函数名称:    on_recv_udp
 函数描述:    接收数据处理信息
 作者：
 输入参数:    com_sock：通用socket； buf：接收数据缓存；len：接收数据长度；
 输出参数:    无
 返回说明:    无
 其它说明:    无
 *************************************************/

static int on_recv_udp(v2x_com_sock_struct* com_sock, char* buf, int len)
{
	//BSJ UDP SOCKET ：接收来保时捷驾驶的信息
	V2X_PR(LOG_LEVEL_DEBUG, LOG_ID, "app_bsj rx data:%d:%s", len,buf);
	return com_recv_deal(com_sock, LOG_ID, buf, len, deal_udp_decode_info);

}

/*************************************************
 函数名称:    on_recv
 函数描述:    接收数据处理信息
 作者：
 输入参数:    com_sock：通用socket； buf：接收数据缓存；len：接收数据长度；
 输出参数:    无
 返回说明:    无
 其它说明:    无
 *************************************************/
static int on_recv(v2x_com_sock_struct* com_sock, char* buf, int len)
{
	return com_recv_deal(com_sock, LOG_ID, buf, len, deal_decode_info);
}

/*************************************************
 函数名称:    init_socks
 函数描述:    初始化socks
 作者：
 输入参数:    无
 输出参数:    无
 返回说明:    无
 其它说明:    无
 *************************************************/
static void init_socks()
{
    int i;

    for (i = 0; i < MAX_SOCK_NUM; i++)
    {
        general_strcut_init((void *)&s_com_socks[i], INFO_COMM_SOCK);
    }

	//初始化BSJ UDP SOCKET ：接收来保时捷驾驶的信息
    i = 0;
    general_strcut_init((void *)&s_bsj_udp_sock, INFO_UDP_SOCK);
    s_bsj_udp_sock.on_recv = on_recv_udp;
    s_com_socks[i].ex = (void *)&s_bsj_udp_sock;
    s_com_socks[i].type = SOCK_UDP;
    sprintf(s_com_socks[i].name, "porsche design");
	sprintf(s_com_socks[i].addr, INET_RX_ADDR);
    s_com_socks[i].port = g_bsj_config.rx_port;

	//初始化BSJ UDP SOCKET：发送给保时捷驾驶信息
	i++;
    general_strcut_init((void *)&s_auto_udp_sock,INFO_UDP_SOCK);
	sprintf(s_auto_udp_sock.tx_addr, g_bsj_config.tx_addr);
    s_auto_udp_sock.tx_port = g_bsj_config.tx_port;
    s_com_socks[i].ex = (void *)&s_auto_udp_sock;
    s_com_socks[i].type = SOCK_UDP;
    sprintf(s_com_socks[i].name,"porsche design");
    s_com_auto_sock = &s_com_socks[i];

	//初始化wmh socket 
    i++;
    general_strcut_init((void *)&s_wmh_sock, INFO_CLIENT_SOCK);
    s_wmh_sock.on_connect = com_client_register;
    s_wmh_sock.on_recv = on_recv;
    s_wmh_sock.reg_type = INFO_CLT_RM;
    v2x_clt_rm_struct *pclt_rm = (v2x_clt_rm_struct *)s_wmh_sock.reg_info;
    general_strcut_init((void *)pclt_rm, INFO_CLT_RM);
    pclt_rm->msg_type = MSG_TYPE_BSM|MSG_TYPE_PTC;
    sprintf(pclt_rm->name, "a_bsj");
    s_com_socks[i].ex = (void *)&s_wmh_sock;
    s_com_socks[i].type = SOCK_TCP_CLIENT;
    sprintf(s_com_socks[i].name, "wmh");
    sprintf(s_com_socks[i].addr, LOCAL_INET_ADDR);
    s_com_socks[i].port = WMH_TCP_PORT;
	s_com_wmh_sock = &s_com_socks[i];

}

/*************************************************
 函数名称:    main
 函数描述:    主函数
 作者：
 输入参数:    无
 输出参数:    无
 返回说明:    无
 其它说明:    无
 *************************************************/
int main(int argc, char *argv[])
{
    //无视SIGPIPE信号，防止连接断开时产生SIGPIPE信号终止进程
    signal(SIGPIPE, SIG_IGN);
    struct timeval rx_timeout;

    //日志级别初始化
    log_level_init();

	V2X_PR(LOG_LEVEL_DEBUG, LOG_ID, SOFTWARE_VERSION);
	V2X_PR(LOG_LEVEL_DEBUG, LOG_ID, SOFTWARE_DATE);

	struct tm *tm_now;
    struct timeval tv_now;

    gettimeofday(&tv_now, NULL);
    tv_now.tv_sec += (8 * 3600);
    tm_now = gmtime(&tv_now.tv_sec);
    if (((tm_now->tm_year + 1900) >= CONTROL_YEAR) && ((tm_now->tm_mon + 1) >= CONTROL_MONTH) && (tm_now->tm_mday >= CONTROL_DAY)){
        V2X_PR(LOG_LEVEL_ERROR, LOG_ID, "recv err:%d-%02d-%02d", tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday);
        return -1;
    }
    
    printf("%s\n","start success");
	//获取配置
	if(config_init())
	{
		V2X_PR(LOG_LEVEL_ERROR, LOG_ID, "config init err");
	}
	printf("%s\n","init success");
	general_strcut_init((void *)(&s_host_bsm), INFO_BSM);

	//bsm config info
	s_host_bsm.host_flag = VEH_FLAG_HOST;
    s_host_bsm.relative_pos_opt = false;
    s_host_bsm.relative_pos = 0;
    //s_host_bsm.veh_size.width = g_bsj_config.veh_width;
    s_host_bsm.veh_size.length = g_bsj_config.veh_length;
    //s_host_bsm.vehicle_classification.classification = g_bsj_config.basic_vehicle_class;
    if(g_bsj_config.rsp_type >= 0)
    {
        s_host_bsm.veh_emergency_ext_opt = true;
        s_host_bsm.veh_emergency_ext.response_type_opt = true;
        s_host_bsm.veh_emergency_ext.response_type = g_bsj_config.rsp_type;
    }
	
	//初始化socks
    init_socks();
    if(com_create_socks(s_com_socks,MAX_SOCK_NUM,LOG_ID))
    {
        return -1;
    }
    printf("%s\n","sock success");
    while(1)
    {
        rx_timeout.tv_sec = 5;
        rx_timeout.tv_usec = 0;
        printf("%s\n","pass success");
        com_select_socks(s_com_socks,MAX_SOCK_NUM,LOG_ID,&rx_timeout);
        printf("%s\n","select success");
        com_create_socks(s_com_socks,MAX_SOCK_NUM,LOG_ID);	
    }

    com_close_socks(s_com_socks,MAX_SOCK_NUM);
    return 0;
}


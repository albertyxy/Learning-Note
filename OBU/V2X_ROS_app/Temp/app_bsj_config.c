/******************************************************************
 版权信息   : 金溢科技版权所有，保留一切权利
 文件名称   : app_bsj_config.c
 作者       : zhanghcao
 完成日期   : 2021-08-27
 当前版本号 : V2.0.0
 主要功能   : 保时捷项目所需数据
 版本历史   : 无
 ******************************************************************/
#include "app_bsj_general.h"

//自定义
#define CONFIG_KEY_TX_ADDR						"tx_addr"
#define CONFIG_KEY_TX_PORT						"tx_port"
#define CONFIG_KEY_RX_PORT						"rx_port"
#define CONFIG_KEY_VEH_WIDTH                    "veh_width"
#define CONFIG_KEY_VEH_LENGTH                   "veh_length"
#define CONFIG_KEY_BASIC_VEHICLE_CLASS          "basic_vehicle_class"
#define CONFIG_KEY_BRAKING_ACC_THRESHOLD        "braking_acc_threshold"
#define CONFIG_KEY_RSP_TYPE                     "rsp_type"

//变量
bsj_config_struct g_bsj_config;

/*************************************************
 函数名称:    config_init
 函数描述:    配置文件初始化
 作者：
 输入参数:    无
 输出参数:    无
 返回说明:    0：成功；非0：失败
 其它说明:    无
 *************************************************/
int config_init(void)
{
    int ret = -1;

    //获取配置文件路径
    char config_file_path[MAX_BUF_LEN] = {0};
    ret = get_file_path(config_file_path, MAX_BUF_LEN, USER_CONFIG_FILE_NAME);
    if (ret)
    {
        return -1;
    }

    //获取配置结构体信息
    char config_buf[MAX_CONFIG_BUF_LEN] = {0};
    v2x_config_struct *config_info = (v2x_config_struct *)config_buf;
    ret = read_config_info(config_file_path, LOG_ID, config_info);
    if (ret)
    {
        //获取配置结构体信息失败
        config_info = NULL;
    }

	//车宽 单位米
    read_config_value_double(config_info, CONFIG_KEY_VEH_WIDTH, LOG_ID, 2, &g_bsj_config.veh_width);

    //车长 单位米
    read_config_value_double(config_info, CONFIG_KEY_VEH_LENGTH, LOG_ID, 5, &g_bsj_config.veh_length);

    //车辆类型
    read_config_value_int(config_info, CONFIG_KEY_BASIC_VEHICLE_CLASS, LOG_ID, 0, &g_bsj_config.basic_vehicle_class);

    //紧急制动加速度阈值 单位米/秒平方
    read_config_value_double(config_info, CONFIG_KEY_BRAKING_ACC_THRESHOLD, LOG_ID, -3.92, &g_bsj_config.braking_acc_threshold);

    //车辆当前行驶或驾驶状态，默认值-1，范围：-1至6，-1标识不可用，其他参考国标消息集
    read_config_value_int(config_info, CONFIG_KEY_RSP_TYPE, LOG_ID, -1, &g_bsj_config.rsp_type);

	//发送地址，必须配置
    read_config_value_string(config_info, CONFIG_KEY_TX_ADDR, LOG_ID, "192.168.2.121", g_bsj_config.tx_addr, sizeof(g_bsj_config.tx_addr));

    //发送端口，范围：1024-65535，必须配置
    read_config_value_int(config_info, CONFIG_KEY_TX_PORT, LOG_ID, 6800, &g_bsj_config.tx_port);

    //接收端口，范围：1024-65535，必须配置
    read_config_value_int(config_info, CONFIG_KEY_RX_PORT, LOG_ID, 6801, &g_bsj_config.rx_port);
 
	//释放配置信息申请空间
    general_strcut_free((void *)config_info, INFO_CONFIG);

    return 0;
}

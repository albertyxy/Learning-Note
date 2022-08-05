/**
  * @file      v2x_types.h
  * @brief     通用数据类型头文件
  *
  * 包含通用的宏、枚举和结构体等类型定义
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */

#ifndef _V2X_TYPES_H_
#define _V2X_TYPES_H_

#ifdef __cplusplus         //定义对CPP进行C处理
extern "C" {
#endif

//头文件
#include <stdbool.h>
#include <netinet/in.h>
#include <linux/can.h>
#include <linux/can/raw.h>

//---- 常量定义 开始 ----
#define MAX_BUF_LEN                 4096    ///< 通用缓存最大长度

#define MAX_COMM_BUF_LEN            65536   ///< 通信缓存最大长度

#define MAX_CONFIG_BUF_LEN          65536   ///< 参数配置缓存最大长度
#define CONFIG_ITEM_BUF_LEN         128     ///< 参数配置项缓存最大长度

#define MAX_WM_DATA_LEN             1400    ///< 无线消息数据最大长度
#define MAX_UDM_DATA_LEN            1024    ///< 自定义无线消息数据最大长度
#define MAX_SHORT_DATA_LEN          128     ///< 短数据最大长度
#define MAX_NAME_LEN                32      ///< 名称最大长度

#define MAX_POINTS_NUM              32      ///< 路径信息最大点数
#define MAX_DESCRIPTION_LEN         1024    ///< 备注最大长度
#define MAX_SPEED_LIMITS_NUM        9       ///< 速度限制列表最大数量
#define MAX_CONNECTION_TO_LIST_NUM  8       ///< 转向连接关系列表最大数量

#define MAX_SIGNAL_INFO_MEMBER_NUM  32      ///< 最大信号灯数量

#define MAX_CAN_FILTER_NUM          32      ///< CAN过滤器最大数量
#define MAX_CAN_RM_FILTER_NUM       4       ///< CAN请求过滤器最大数量
#define IP_ADDR_SIZE                16      ///< IP地址最大长度

#define MAX_RTE_LIST_NUM            8       ///< 道路交通事件集合最大数量
#define MAX_RTS_LIST_NUM            16      ///< 道路交通标识集合最大数量
#define MAX_REF_PATH_LIST_NUM       8       ///< 道路交通事件和标志的参考路径集合最大数量
#define MAX_REF_LINK_LIST_NUM       16      ///< 参考路段集合最大数量

#define MAX_PHASE_LIST_NUM          16      ///<  相位列表最大数量
#define MAX_PHASE_STATE_LIST_NUM    16      ///<  相位状态列表最大数量

#define MAX_ID_LEN                  8       ///< id最大长度
#define MAX_PLATE_NO_LEN			16		///< PLATE_NO最大长度

//配置文件相关
#define COM_CONFIG_FILE_NAME        "com_config.ini"    ///< 通用配置文件名
#define USER_CONFIG_FILE_NAME       "user_config.ini"   ///< 用户配置文件名
#define SYS_CONFIG_FILE_NAME        "sys_config.ini"    ///< 系统配置文件名

//模块通信相关
#define LOCAL_INET_ADDR     "127.0.0.1"     ///< 本地内部地址，内部通信
#define INET_RX_ADDR        "0.0.0.0"       ///< 本地所有IP地址

//---- 常量定义 结束 ----

//---- 枚举定义 开始 ----

/**
  * @brief 通用socket类型枚举
  */
typedef enum
{
    SOCK_TCP_SERVER = 1,    ///< TCP服务端
    SOCK_TCP_CLIENT,        ///< TCP客户端
    SOCK_TCP_CONNECT,       ///< TCP连接(用于服务端记录已建立的连接)
    SOCK_UDP,               ///< UDP

    SOCK_TCP_SERVER_UNIX,   ///< TCP服务端(Unix domain)
    SOCK_TCP_CLIENT_UNIX,   ///< TCP客户端(Unix domain)
    SOCK_UDP_UNIX,          ///< UDP(Unix domain)
    SOCK_TCP_CONNECT_UNIX,  ///< TCP连接(用于服务端记录已建立的连接)(Unix domain)

    SOCK_OTHER_COM_RECV,    ///< 其他，调用com_recv_sock函数接收数据
    SOCK_OTHER_UD_RECV,     ///< 其他，自定义接收接收
} v2x_sock_type_enum;

/**
  * @brief 模块socket端口号枚举
  */
typedef enum
{
    SYS_OPER_TCP_PORT   = 7001,     ///< 系统操作端口
    LOG_UDP_PORT        = 7110,     ///< 日志记录端口
    VIS_TCP_PORT        = 7111,     ///< VIS内部通信端口
    VIS_TCP_OUT_PORT    = 7112,     ///< VIS外部通信端口
    TPS_TCP_PORT        = 7113,     ///< TPS内部通信端口
    WMS_TCP_PORT        = 7114,     ///< WMS内部通信端口
    SDH_TCP_PORT        = 7115,     ///< SDH内部通信端口
    WMH_TCP_PORT        = 7116,     ///< WMH内部通信端口
    TC_TCP_PORT         = 7117,     ///< TC内部通信端口
    TA_UDP_PORT         = 7118,     ///< TA内部通信端口
    DVIN_TCP_PORT       = 7129,     ///< DVIN内部通信端口
    DVIN_TCP_OUT_PORT   = 7130,     ///< DVIN外部通信端口
    DATA_TCP_PORT       = 7131,     ///< 数据采集端口
    WMH_TCP_IN_PORT     = 7132,     ///< WMH内部数据端口
    WMH_TCP_OUT_PORT    = 7133,     ///< WMH外发数据处理端口
    TS_TPS_PORT         = 7180,     ///< 模拟TPS接收端口
    TS_SEND_PORT        = 7181,     ///< 模拟SEND接收端口
} v2x_sock_port_enum;

/**
  * @brief 注册消息类型枚举
  */
typedef enum
{
    MSG_TYPE_NONE       = 0,    ///< 无
    /**
      * @see v2x_vis_hvsm_struct
      */
    MSG_TYPE_VIS_HVSM   = 1,
    /**
      * @see v2x_vis_udm_struct
      */
    MSG_TYPE_VIS_UDM    = 2,
    /**
      * @see v2x_vis_sm_struct
      */
    MSG_TYPE_VIS_SM     = 4,
    /**
      * @see v2x_tps_tpm_struct
      */
    MSG_TYPE_TPS_TPM    = 8,
    /**
      * @see v2x_tps_sm_struct
      */
    MSG_TYPE_TPS_SM     = 16,
    /**
      * @see v2x_wms_wm_struct
      */
    MSG_TYPE_WMS_WM     = 32,
    /**
      * @see v2x_bsm_struct
      */
    MSG_TYPE_BSM        = 64,
    /**
      * @see v2x_rsi_struct
      */
    MSG_TYPE_RSI        = 128,
    /**
      * @see v2x_map_struct
      */
    MSG_TYPE_MAP        = 256,
    /**
      * @see v2x_spat_struct
      */
    MSG_TYPE_SPAT       = 512,
    /**
      * @see v2x_wmh_udm_struct
      */
    MSG_TYPE_WMH_UDM    = 1024,
    /**
      * @see v2x_ta_tm_struct
      */
    MSG_TYPE_TA_TM      = 2048,
    /**
      * @see v2x_heart_struct
      */
    MSG_TYPE_HEART      = 4096,
    /**
      * @see v2x_bsm_struct
      */
    MSG_TYPE_BSM_VRU    = 8192, ///< 行人BSM
    /**
      * @see v2x_dvin_ssm_struct
      */
    MSG_TYPE_DVIN_SSM   = 16384,
    /**
      * @see v2x_map_src_struct
      */
    MSG_TYPE_MAP_SRC    = 32768,
    /**
      * @see v2x_spat_src_struct
      */
    MSG_TYPE_SPAT_SRC   = 65536,
    /**
      * @see v2x_rsm_struct
      */
    MSG_TYPE_RSM        = 131072,
    /**
      * @see v2x_ptc_struct
      */
    MSG_TYPE_PTC        = 262144,
    /**
      * @see v2x_ptc_struct
      */
    MSG_TYPE_PTC_VRU    = 524288, ///< 行人PTC
    MSG_TYPE_ALL        = 0xFFFFFFFF    ///< 全部
} v2x_msg_type_enum;

/**
  * @brief 预警类型枚举
  */
typedef enum
{
    ALERT_TYPE_NW = 0,      ///< 无预警/解除预警
    ALERT_TYPE_FCW,           ///< 前向碰撞预警
    ALERT_TYPE_ICW,           ///< 交叉碰撞预警
    ALERT_TYPE_LTA,           ///< 左转辅助
    ALERT_TYPE_LCW,           ///< 变道预警
    ALERT_TYPE_DNPW,          ///< 逆向超车预警
    ALERT_TYPE_EBW,           ///< 紧急制动预警
    ALERT_TYPE_AVW,           ///< 异常车辆提醒
    ALERT_TYPE_CLW,           ///< 车辆失控预警
    ALERT_TYPE_EVW,           ///< 紧急车辆提醒
    ALERT_TYPE_BSW,       ///< 盲区提醒
    ALERT_TYPE_RLVW,      ///< 闯红灯预警
    ALERT_TYPE_RSI_E,     ///< 道路交通事件信息
    ALERT_TYPE_RSI_S,     ///< 道路交通标识信息
    ALERT_TYPE_SLW,       ///< 限速预警
    ALERT_TYPE_VRUCW,     ///< 弱势交通参与者碰撞预警
} v2x_alert_type_enum;

/**
  * @brief 相对位置定义枚举
  */
typedef enum
{
    POS_AHEAD_FAR_LEFT      = 1 << 0,   ///< 同向非相邻左前方
    POS_AHEAD_LEFT          = 1 << 1,   ///< 同向相邻左前方
    POS_AHEAD               = 1 << 2,   ///< 同向正前方
    POS_AHEAD_RIGHT         = 1 << 3,   ///< 同向相邻右前方
    POS_AHEAD_FAR_RIGHT     = 1 << 4,   ///< 同向非相邻右前方
    POS_BEHIND_FAR_LEFT     = 1 << 5,   ///< 同向非相邻左后方
    POS_BEHIND_LEFT         = 1 << 6,   ///< 同向相邻左后方
    POS_BEHIND              = 1 << 7,   ///< 同向正后方
    POS_BEHIND_RIGHT        = 1 << 8,   ///< 同向相邻右后方
    POS_BEHIND_FAR_RIGHT    = 1 << 9,   ///< 同向非相邻右后方
    POS_ONCOMING_FAR_LEFT   = 1 << 10,  ///< 反向非相邻左前方
    POS_ONCOMING_LEFT       = 1 << 11,  ///< 反向相邻左前方
    POS_ONCOMING            = 1 << 12,  ///< 反向正前方
    POS_ONCOMING_RIGHT      = 1 << 13,  ///< 反向相邻右前方
    POS_ONCOMING_FAR_RIGHT  = 1 << 14,  ///< 反向非相邻右前方
    POS_INTERSECTING_LEFT   = 1 << 15,  ///< 交叉左前方
    POS_INTERSECTING_RIGHT  = 1 << 16,  ///< 交叉右前方
    POS_SAME_DIR = POS_AHEAD_FAR_LEFT | POS_AHEAD_LEFT | POS_AHEAD
                        | POS_AHEAD_RIGHT | POS_AHEAD_FAR_RIGHT | POS_BEHIND_FAR_LEFT
                        | POS_BEHIND_LEFT | POS_BEHIND | POS_BEHIND_RIGHT
                        | POS_BEHIND_FAR_RIGHT,     ///< 同向方位
    POS_ONCOMING_ALL = POS_ONCOMING_FAR_LEFT | POS_ONCOMING_LEFT
                        | POS_ONCOMING | POS_ONCOMING_RIGHT | POS_ONCOMING_FAR_RIGHT,   ///< 反向方位
    POS_INTERSECTING = POS_INTERSECTING_LEFT | POS_INTERSECTING_RIGHT,  ///< 交叉方位
    POS_ALL                 = 0xFFFFFFFF    ///< 所有位置
} v2x_relative_pos_enum;

/**
  * @brief 模块状态枚举
  */
typedef enum
{
    MODULE_NORMAL = 0,      ///< 正常
    MODULE_ABNORMAL = 1,    ///< 异常
} v2x_module_status_enum;

/**
  * @brief 设备状态枚举
  */
typedef enum
{
    DEV_NORMAL = 0,         ///< 正常
    DEV_GPS_ERR = 1,        ///< 无GPS数据
    DEV_VEH_COMM_ERR = 2,   ///< 车辆通信错误
} v2x_dev_status_enum;

/**
  * @brief 车辆接口类型枚举
  */
typedef enum
{
    VI_TYPE_CAN = 1,        ///< CAN
    VI_TYPE_INET = 2,       ///< INET
} v2x_vi_type_enum;

/**
  * @brief 设备类型枚举
  */
typedef enum
{
    DEV_TYPE_VEH = 1,           ///< 车载
    DEV_TYPE_ROADSIDE = 2,      ///< 路侧
    DEV_TYPE_PEDESTRIAN = 3,    ///< 行人
} v2x_dev_type_enum;

/**
  * @brief 车辆档位状态枚举
  */
typedef enum
{
    TRANSMISSION_NEUTRAL = 0,       ///< 空挡
    TRANSMISSION_PARK = 1,          ///< 驻车
    TRANSMISSION_FORWARD = 2,       ///< 前进
    TRANSMISSION_REVERSE = 3,       ///< 后退
    TRANSMISSION_RESERVED1 = 4,     ///< 后退
    TRANSMISSION_RESERVED2 = 5,     ///< 后退
    TRANSMISSION_RESERVED3 = 6,     ///< 后退
    TRANSMISSION_UNAVAILABLE = 7,   ///< 无法获取
} v2x_trans_state_enum;

/**
  * @brief 车辆类型枚举，参考GB/T 31024.3
  */
typedef enum
{
    BASIC_VEHICLE_CLASS_UNKNOWN                = 0,        ///< 未装备，未知或不可用

    BASIC_VEHICLE_CLASS_SPECIAL                = 1,        ///< 特殊使用

    BASIC_VEHICLE_CLASS_PASSENGER_UNKNOWN      = 10,       ///< 客运机动车（轿车），默认
    BASIC_VEHICLE_CLASS_PASSENGER_OTHER        = 11,       ///< 客运机动车（轿车），其他

    BASIC_VEHICLE_CLASS_LIGHT_TRUCK_UNKNOWN    = 20,       ///< 轻型卡车，默认
    BASIC_VEHICLE_CLASS_LIGHT_TRUCK_OTHER      = 21,       ///< 轻型卡车，其他

    BASIC_VEHICLE_CLASS_TRUCK_UNKNOWN          = 25,       ///< 卡车，默认
    BASIC_VEHICLE_CLASS_TRUCK_OTHER            = 26,       ///< 卡车，其他
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT2        = 27,       ///< 卡车
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT3        = 28,       ///< 卡车
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT4        = 29,       ///< 卡车
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT4T       = 30,       ///< 卡车
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT5T       = 31,       ///< 卡车
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT6T       = 32,       ///< 卡车
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT5M       = 33,       ///< 卡车
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT6M       = 34,       ///< 卡车
    BASIC_VEHICLE_CLASS_TRUCK_AXLE_CNT7M       = 35,       ///< 卡车

    BASIC_VEHICLE_CLASS_MOTORCYCLE_UNKNOWN     = 40,       ///< 摩托车，默认
    BASIC_VEHICLE_CLASS_MOTORCYCLE_OTHER       = 41,       ///< 摩托车，其他
    BASIC_VEHICLE_CLASS_MOTORCYCLE_CS          = 42,       ///< 摩托车
    BASIC_VEHICLE_CLASS_MOTORCYCLE_SU          = 43,       ///< 摩托车
    BASIC_VEHICLE_CLASS_MOTORCYCLE_ST          = 44,       ///< 摩托车
    BASIC_VEHICLE_CLASS_MOTORCYCLE_SS          = 45,       ///< 摩托车
    BASIC_VEHICLE_CLASS_MOTORCYCLE_T           = 46,       ///< 摩托车
    BASIC_VEHICLE_CLASS_MOTORCYCLE_TB          = 47,       ///< 摩托车
    BASIC_VEHICLE_CLASS_MOTORCYCLE_WP          = 48,       ///< 摩托车

    BASIC_VEHICLE_CLASS_TRANSIT_UNKNOWN        = 50,       ///< 交通运输车辆，默认
    BASIC_VEHICLE_CLASS_TRANSIT_OTHER          = 51,       ///< 交通运输车辆，其他
    BASIC_VEHICLE_CLASS_TRANSIT_BRT            = 52,       ///< 交通运输车辆
    BASIC_VEHICLE_CLASS_TRANSIT_EB             = 53,       ///< 交通运输车辆
    BASIC_VEHICLE_CLASS_TRANSIT_LB             = 54,       ///< 交通运输车辆
    BASIC_VEHICLE_CLASS_TRANSIT_SB             = 55,       ///< 交通运输车辆
    BASIC_VEHICLE_CLASS_TRANSIT_FG             = 56,       ///< 交通运输车辆
    BASIC_VEHICLE_CLASS_TRANSIT_P              = 57,       ///< 交通运输车辆
    BASIC_VEHICLE_CLASS_TRANSIT_PA             = 58,       ///< 交通运输车辆

    BASIC_VEHICLE_CLASS_EMERGENCY_UNKNOWN      = 60,       ///< 紧急车辆，默认
    BASIC_VEHICLE_CLASS_EMERGENCY_OTHER        = 61,       ///< 紧急车辆，其他
    BASIC_VEHICLE_CLASS_EMERGENCY_FL           = 62,       ///< 紧急车辆
    BASIC_VEHICLE_CLASS_EMERGENCY_FH           = 63,       ///< 紧急车辆
    BASIC_VEHICLE_CLASS_EMERGENCY_FP           = 64,       ///< 紧急车辆
    BASIC_VEHICLE_CLASS_EMERGENCY_FA           = 65,       ///< 紧急车辆
    BASIC_VEHICLE_CLASS_EMERGENCY_PL           = 66,       ///< 紧急车辆
    BASIC_VEHICLE_CLASS_EMERGENCY_PH           = 67,       ///< 紧急车辆
    BASIC_VEHICLE_CLASS_EMERGENCY_OR           = 68,       ///< 紧急车辆
    BASIC_VEHICLE_CLASS_EMERGENCY_OA           = 69,       ///< 紧急车辆

    BASIC_VEHICLE_CLASS_OT_UNKNOWN             = 80,       ///< 其他出行类型，默认
    BASIC_VEHICLE_CLASS_OT_OTHER               = 81,       ///< 其他出行类型，其他
    BASIC_VEHICLE_CLASS_OT_PEDESTRIAN          = 82,       ///< 其他出行类型，行人
    BASIC_VEHICLE_CLASS_OT_VD                  = 83,       ///< 其他出行类型，不可见
    BASIC_VEHICLE_CLASS_OT_PD                  = 84,       ///< 其他出行类型，非物理
    BASIC_VEHICLE_CLASS_OT_BICYCLE             = 85,       ///< 其他出行类型，自行车
    BASIC_VEHICLE_CLASS_OT_VR                  = 86,       ///< 其他出行类型，弱势交通工作者

    BASIC_VEHICLE_CLASS_OVEDT_I_UNKNOWN        = 90,       ///< 基础设施，默认
    BASIC_VEHICLE_CLASS_OVEDT_I_FIXED          = 91,       ///< 基础设施，固定
    BASIC_VEHICLE_CLASS_OVEDT_I_MOVABLE        = 92,       ///< 基础设施，可移动
    BASIC_VEHICLE_CLASS_OVEDT_E_CT             = 93,       ///< 载货挂车
} v2x_basic_vehicle_class_enum;

/**
  * @brief 车辆特殊事件枚举
  */
typedef enum
{
    EVENTS_NONE                          = 0,    ///< 无特殊事件
    EVENTS_HAZARD_LIGHTS                 = 1,    ///< 警示灯亮起
    EVENTS_STOP_LINE_VIOLATION           = 2,    ///< 越过停止线
    EVENTS_ABS_ACTIVATED                 = 4,    ///< ABS系统被触发
    EVENTS_TRACTION_CONTROL_LOSS         = 8,    ///< 牵引力控制系统被触发
    EVENTS_STABILITY_CONTROL_ACTIVATED   = 16,   ///< 车身稳定控制系统被触发
    EVENTS_HAZARDOUS_MATERIALS           = 32,   ///< 危险品运输车
    EVENTS_RESERVED1                     = 64,   ///< 预留1
    EVENTS_HARD_BRAKING                  = 128,  ///< 紧急刹车
    EVENTS_LIGHTS_CHANGED                = 256,  ///< 车灯状态改变
    EVENTS_WIPERS_CHANGED                = 512,  ///< 雨刷状态改变
    EVENTS_FLAT_TIRE                     = 1024, ///< 轮胎爆胎
    EVENTS_DISABLED_VEHICLE              = 2048, ///< 车辆故障
    EVENTS_AIR_BAG_DEPLOYMENT            = 4092, ///< 安全气囊弹出
} v2x_events_status_enum;

/**
  * @brief 车灯状态枚举
  */
typedef enum
{
    LIGHTS_ALL_LIGHTS_OFF              = 0,    ///< 所有灯关闭
    LIGHTS_LOW_BEAM_HEAD_LIGHTS_ON     = 1,    ///< 近光灯打开
    LIGHTS_HIGH_BEAM_HEAD_LIGHTS_ON    = 2,    ///< 远光灯打开
    LIGHTS_LEFT_TURN_SIGNAL_ON         = 4,    ///< 左转灯打开
    LIGHTS_RIGHT_TURN_SIGNAL_ON        = 8,    ///< 右转灯打开
    LIGHTS_HAZARD_SIGNAL_ON            = 16,   ///< 危险报警灯打开
    LIGHTS_AUTOMATIC_LIGHT_CONTROL_ON  = 32,   ///< 自动灯光控制打开
    LIGHTS_DAYTIME_RUNNING_LIGHTS_ON   = 64,   ///< 日行灯打开
    LIGHTS_FOG_LIGHT_ON                = 128,  ///< 雾灯打开
    LIGHTS_PARKING_LIGHTS_ON           = 256,  ///< 驻车灯打开
} v2x_lights_status_enum;

/**
  * @brief 车辆刹车状态枚举
  */
typedef enum
{
    BRAKES_ALL_OFF  = 0,    ///< 所有刹车未踩下
    BRAKES_PEDAL_ON = 1,    ///< 制动踏板踩下
    BRAKES_TCS_ON   = 2,    ///< TCS激活
    BRAKES_ABS_ON   = 4,    ///< ABS激活
    BRAKES_SCS_ON   = 8,    ///< SCS激活
} v2x_brakes_status_enum;

/**
  * @brief 当前行驶状态或驾驶行为枚举
  */
typedef enum
{
    RESPONSE_TYPE_NOT_IN_USE_OR_NOT_EQUIPPED,   ///< 未使用
    RESPONSE_TYPE_EMERGENCY,                    ///< 紧急
    RESPONSE_TYPE_NON_EMERGENCY,                ///< 非紧急
    RESPONSE_TYPE_PURSUIT,                      ///< 追击
    RESPONSE_TYPE_STATIONARY,                   ///< 静止
    RESPONSE_TYPE_SLOW_MOVING,                  ///< 缓慢运动
    RESPONSE_TYPE_STOP_AND_GO_MOVEMENT,         ///< 停止然后继续行驶
} v2x_response_type_enum;

/**
  * @brief 警笛或发声装置状态枚举
  */
typedef enum
{
    SIREN_IN_USE_UNAVAILABLE,                   ///< 不可用
    SIREN_IN_USE_NOTINUSE,                      ///< 未使用
    SIREN_IN_USE_INUSE,                         ///< 使用中
    SIREN_IN_USE_RESERVED,                      ///< 保留
} v2x_siren_in_use_enum;

/**
  * @brief 紧急车辆或特殊车辆的警示灯或外置专用显示设备的工作状态枚举
  */
typedef enum
{
    LIGHTBAR_IN_USE_UNAVAILABLE,                ///< 不可用
    LIGHTBAR_IN_USE_NOT_IN_USE,                 ///< 未使用
    LIGHTBAR_IN_USE_IN_USE,                     ///< 使用中
    LIGHTBAR_IN_USE_YELLOW_CAUTION_LIGHTS,      ///< 使用黄色警示灯
    LIGHTBAR_IN_USE_SCHOOLD_BUS_LIGHTS,         ///< 使用校车灯
    LIGHTBAR_IN_USE_ARROW_SIGNS_ACTIVE,         ///< 箭头表示启动
    LIGHTBAR_IN_USE_SLOW_MOVING_VEHICLE,        ///< 缓慢行驶车辆
    LIGHTBAR_IN_USE_FREQ_STOPS,                 ///< 频繁停止
} v2x_lightbar_in_use_enum;

/**
  * @brief 路段中指定的参考车道枚举
  */
typedef enum
{
    reference_lanes_reserved            = 0,    ///< 不可用
    reference_lanes_lane1               = 1,    ///< 不可用
    reference_lanes_lane2               = 2,    ///< 不可用
    reference_lanes_lane3               = 4,    ///< 不可用
    reference_lanes_lane4               = 8,    ///< 不可用
    reference_lanes_lane5               = 16,   ///< 不可用
    reference_lanes_lane6               = 32,   ///< 不可用
    reference_lanes_lane7               = 64,   ///< 不可用
    reference_lanes_lane8               = 128,  ///< 不可用
    reference_lanes_lane9               = 256,  ///< 不可用
    reference_lanes_lane10              = 512,  ///< 不可用
    reference_lanes_lane11              = 1024, ///< 不可用
    reference_lanes_lane12              = 2048, ///< 不可用
    reference_lanes_lane13              = 4096, ///< 不可用
    reference_lanes_lane14              = 8192, ///< 不可用
    reference_lanes_lane15              = 16384,///< 不可用
} v2x_reference_lanes_enum;

/**
  * @brief 限速类型枚举
  */
typedef enum
{
    SPEED_LIMIT_UNKNOWN,                ///< 位置
    SPEED_LIMIT_MAX_SCHOOL,             ///< 学校路段，最高限速
    SPEED_LIMIT_MAX_SCHOOL_CHILDREN,    ///< 学校学生路段，最高限速
    SPEED_LIMIT_MAX_CONSTRUCTION,       ///< 施工路段，最高限速
    SPEED_LIMIT_MIN_VEHICLE,            ///< 小型客车最低限速
    SPEED_LIMIT_MAX_VEHICLE,            ///< 小型客车最高限速
    SPEED_LIMIT_MAX_VEHICLE_NIGHT,      ///< 夜间时段，小型客车最高限速
    SPEED_LIMIT_MIN_TRUCK,              ///< 货车最低限速
    SPEED_LIMIT_MAX_TRUCK,              ///< 货车最高限速
    SPEED_LIMIT_MAX_TRUCK_NIGHT,        ///< 夜间时段，货车最高限速
    SPEED_LIMIT_MIN_TRAILER,            ///< 挂车最低限速
    SPEED_LIMIT_MAX_TRAILER,            ///< 挂车最高限速
    SPEED_LIMIT_MAX_TRAILER_NIGHT,      ///< 夜间时段，挂车最高限速
} v2x_speed_limit_type_enum;

/**
  * @brief 车道类型枚举
  */
typedef enum
{
    LANE_TYPE_VEHICLE,          ///< 机动车道
    LANE_TYPE_CROSSWALK,        ///< 人行横道
    LANE_TYPE_BIKE,             ///< 自行车道
    LANE_TYPE_SIDEWALK,         ///< 人行道
    LANE_TYPE_MEDIAN,           ///< 隔离带
    LANE_TYPE_STRIPING,         ///< 条带车道
    LANE_TYPE_VEHICLE_TRACK,    ///< 货车车道
    LANE_TYPE_PARKING,          ///< 停车道
} v2x_lane_type_enum;

/**
  * @brief 车道转向类型枚举
  */
typedef enum
{
    LANE_MANEUVER_STRAIGHT  = 1,    ///< 直行
    LANE_MANEUVER_LEFT      = 2,    ///< 左转
    LANE_MANEUVER_RIGHT     = 4,    ///< 右转
    LANE_MANEUVER_UTURN     = 8,    ///< 掉头
    LANE_MANEUVER_LEFT_RED  = 16,   ///< 红灯左转
    LANE_MANEUVER_RIGHT_RED = 32,   ///< 红灯右转
    LANE_MANEUVER_CHANGE    = 64,   ///< 变道
    LANE_MANEUVER_NO_STOP   = 128,  ///< 禁停
} v2x_lane_maneuver_enum;

/**
  * @brief 车辆标志枚举（HV和RV）
  */
typedef enum
{
    VEH_FLAG_NONE = 0,  ///< 无
    VEH_FLAG_HOST,      ///< 本车
    VEH_FLAG_REMOTE,    ///< 他车
} v2x_veh_flag_enum;

/**
  * @brief 信息类型枚举
  */
typedef enum
{
    /**
      * @see v2x_bsm_struct
      */
    INFO_BSM = 1,
    /**
      * @see v2x_rsi_struct
      */
    INFO_RSI,
    /**
      * @see v2x_wmh_udm_struct
      */
    INFO_WMH_UDM,
    /**
      * @see v2x_wms_wm_struct
      */
    INFO_WMS_WM,
    /**
      * @see v2x_vis_hvsm_struct
      */
    INFO_VIS_HVSM,
    /**
      * @see v2x_vis_sm_struct
      */
    INFO_VIS_SM,
    /**
      * @see v2x_vis_udm_struct
      */
    INFO_VIS_UDM,
    /**
      * @see v2x_tps_tpm_struct
      */
    INFO_TPS_TPM,
    /**
      * @see v2x_tps_sm_struct
      */
    INFO_TPS_SM,
    /**
      * @see v2x_ta_tm_struct
      */
    INFO_TA_TM,
    /**
      * @see v2x_dvin_ssm_struct
      */
    INFO_DVIN_SSM,
    /**
      * @see v2x_heart_struct
      */
    INFO_HEART,
    /**
      * @see v2x_clt_rm_struct
      */
    INFO_CLT_RM,
    /**
      * @see v2x_com_sock_struct
      */
    INFO_COMM_SOCK,
    /**
      * @see v2x_srv_sock_struct
      */
    INFO_SERVER_SOCK,
    /**
      * @see v2x_clt_sock_struct
      */
    INFO_CLIENT_SOCK,
    /**
      * @see v2x_udp_sock_struct
      */
    INFO_UDP_SOCK,
    /**
      * @see v2x_other_ud_recv_sock_struct
      */
    INFO_OTHER_UD_RECV_SOCK,
    /**
      * @see v2x_sys_oper_struct
      */
    INFO_SYS_OPER,
    /**
      * @see v2x_config_struct
      */
    INFO_CONFIG,
    /**
      * @see v2x_map_struct
      */
    INFO_MAP,
    /**
      * @see v2x_map_src_struct
      */
    INFO_MAP_SRC,
    /**
      * @see v2x_spat_struct
      */
    INFO_SPAT,
    /**
      * @see v2x_spat_src_struct
      */
    INFO_SPAT_SRC,
    /**
      * @see v2x_rsm_struct
      */
    INFO_RSM,
    /**
      * @see v2x_ptc_struct
      */
    INFO_PTC,
    /**
      * @see v2x_string_struct
      */
    INFO_STRING,
    INFO_ALL = 0xFFFFFFFF,  ///< 全部
} v2x_info_type_enum;

/**
  * @brief 日志级别枚举
  */
typedef enum
{
    LOG_LEVEL_DEBUG = 1,    ///< 调试
    LOG_LEVEL_INFO,         ///< 信息
    LOG_LEVEL_WARNING,      ///< 警告
    LOG_LEVEL_ERROR,        ///< 错误
} v2x_log_level_enum;

/**
  * @brief 配置项数据类型枚举
  */
typedef enum
{
    CONFIG_TYPE_INT = 0,        ///< int
    CONFIG_TYPE_DOUBLE = 1,     ///< double
    CONFIG_TYPE_STRING = 2,     ///< string
    CONFIG_TYPE_ARRAY = 3,      ///< array
    CONFIG_TYPE_OBJECT = 4,     ///< object
} v2x_config_type_enum;

/**
  * @brief 信号灯状态枚举
  */
typedef enum
{
    TRAFFIC_LIGHT_UNAVAILABLE,  ///< 未知状态
    TRAFFIC_LIGHT_DARK,         ///< 未工作
    TRAFFIC_LIGHT_RED_FLASH,    ///< 红闪
    TRAFFIC_LIGHT_RED,          ///< 红灯
    TRAFFIC_LIGHT_WAIT,         ///< 绿灯待行
    TRAFFIC_LIGHT_GREEN,        ///< 绿灯
    TRAFFIC_LIGHT_ARROW,        ///< 箭头灯
    TRAFFIC_LIGHT_YELLOW,       ///< 黄灯
    TRAFFIC_LIGHT_YELLOW_FLASH, ///< 黄闪
} v2x_traffic_light_state_enum;

/**
  * @brief 信号灯状态枚举
  */
typedef enum
{
    DVIN_SSM_DATA_ERR = 1,          ///< 数据错误，无法计算
    DVIN_SSM_OVER_SPEED_LIMIT = 2,  ///< 速度值为最小速度，但最小速度超过限速值
    DVIN_SSM_MIN_SPEED = 3,         ///< 速度值为最小速度
    DVIN_SSM_MAX_SPEED = 4,         ///< 速度值为最大速度
} v2x_dvin_ssm_type_enum;

/**
  * @brief 信号灯状态枚举
  */
typedef enum
{
    PTC_TYPE_UNKNOWN = 0,       ///< 位置
    PTC_TYPE_MOTOR = 1,         ///< 机动车
    PTC_TYPE_NON_MOTOR = 2,     ///< 非机动车
    PTC_TYPE_PEDESTRIAN = 3,    ///< 行人
    PTC_TYPE_RSU = 4,           ///< 天线
} v2x_ptc_type_enum;

/**
  * @brief 数据检测来源枚举
  */
typedef enum {
    SOURCE_UNKNOWN  = 0,        ///< 未知
    SOURCE_SELF,                ///< 自身信息
    SOURCE_V2X,                 ///< V2X
    SOURCE_VIDEO,               ///< 视频
    SOURCE_RADAR_MICROWAVE,     ///< 微波雷达
    SOURCE_LOOP,                ///< 线圈
    SOURCE_LIDAR,               ///< 激光雷达
    SOURCE_INTEGRATED,          ///< 整体
} v2x_source_type_enum;

/**
  * @brief 信号灯相位的计时状态数据格式枚举
  */
typedef enum {
    TIME_CHANGE_DETAILS_COUNTING,       ///< 倒计时形式
    TIME_CHANGE_DETAILS_UTC_TIMING,     ///< UTC世界标准时间形式
} v2x_time_change_details_enum;

/**
  * @brief 数据检测来源枚举
  */
typedef enum {
    PR_UD_BUF_CMD  = 1,         ///< 打印自定义BUF数据至调试串口
    PR_UD_BUF_LOG  = 2,         ///< 打印自定义BUF数据至日志
} v2x_pr_ud_buf_enum;

//---- 枚举定义 结束 ----

//---- 结构体定义 开始 ----
#pragma pack (1)

/**
  * @brief 通用配置结构体
  */
typedef struct
{
    v2x_dev_type_enum   dev_type;                       ///< 设备类型
    char                soft_ver[CONFIG_ITEM_BUF_LEN];  ///< 软件版本号
} v2x_com_config_struct;

/**
  * @brief 位置信息结构体
  */
typedef struct
{
    double  latitude;       ///< 纬度
    double  longitude;      ///< 经度
    bool    elevation_opt;  ///< 是否包含海拔
    double  elevation;      ///< 海拔
} v2x_position_struct;

/**
  * @brief 位置偏移结构体
  */
typedef struct
{
    char    off_type;       ///< 偏移类型（1偏移0绝对值）：1-经纬度偏移值bit；2-海拔偏移值bit。例如0x02表示经纬度是绝对值，海拔是偏移值。
    double  off_lat;        ///< 纬度偏移量
    double  off_lng;        ///< 精度偏移量
    bool    off_elv_opt;    ///< 是否包含海拔偏移量
    double  off_elv;        ///< 海拔偏移量
} v2x_position_offset_struct;

/**
  * @brief 字符串结构体
  */
typedef struct
{
    int     len;    ///< 长度
    char    *buf;   ///< 数据
} v2x_string_struct;

/**
  * @brief 定位系统自身的精度
  */
typedef struct
{
    double  smajor_dev;         ///< 椭圆长半轴精度
    double  sminor_dev;         ///< 椭圆短半轴精度
    double  smajor_orien;       ///< 椭圆长半轴方向
} v2x_pos_accuracy_struct;

/**
  * @brief 实时位置（经纬度和高程）的精度大
  */
typedef struct
{
    int     pos;                    ///< 95%置信水平的车辆位置精度
    bool    elevation_opt;          ///< 是否包含95%置信水平的车辆高程精度
    int     elevation;              ///< 95%置信水平的车辆高程精度
} v2x_pos_confidence_struct;

/**
  * @brief 加速度集合结构体
  */
typedef struct
{
    double  acc_lng;        ///< 纵向加速度
    bool    acc_lat_opt;    ///< 是否包含横向加速度
    double  acc_lat;        ///< 横向加速度
    bool    acc_vert_opt;   ///< 是否包含垂直加速度
    double  acc_vert;       ///< 垂直加速度
    double  yaw_rate;       ///< 横摆角速度
} v2x_acceleration_set_struct;

/**
  * @brief 刹车系统状态结构体
  */
typedef struct
{
    bool brake_padel_opt;   ///< 是否包含刹车踏板踩下情况
    int brake_padel;        ///< 刹车踏板踩下情况
    bool wheel_brakes_opt;  ///< 是否包含车辆车轮制动情况
    int wheel_brakes;       ///< 车辆车轮制动情况
    bool traction_opt;      ///< 是否包含牵引力控制系统作用情况
    int traction;           ///< 牵引力控制系统作用情况
    bool abs_opt;           ///< 是否包含制动防抱死系统作用情况
    int abs;                ///< 制动防抱死系统作用情况
    bool scs_opt;           ///< 是否包含车身稳定控制系统作用情况
    int scs;                ///< 车身稳定控制系统作用情况
    bool brake_boost_opt;   ///< 是否包含刹车助力系统作用情况
    int brake_boost;        ///< 刹车助力系统作用情况
    bool aux_brakes_opt;    ///< 是否包含辅助制动系统（一般指手刹）情况
    int aux_brakes;         ///< 辅助制动系统（一般指手刹）情况
} v2x_brake_system_status_struct;

/**
  * @brief 车辆尺寸结构体
  */
typedef struct
{
    double      width;      ///< 宽度
    double      length;     ///< 长度
    bool        height_opt; ///< 是否包含高度
    double      height;     ///< 高度
} v2x_vehicle_size_struct;

/**
  * @brief 车辆的分类结构体
  */
typedef struct
{
    int classification;     ///< 车辆基本类型
    bool fuel_type_opt;     ///< 是否包含燃料动力类型
    int fuel_type;          ///< 燃料动力类型
} v2x_vehicle_classification_struct;

/**
  * @brief 历史路径点结构体
  */
typedef struct
{
    v2x_position_struct pos;            ///< 位置
    double              utc_time;       ///< 时钟
    bool                speed_opt;      ///< 是否包含速度
    double              speed;          ///< 速度
    bool                heading_opt;    ///< 是否包含方向角
    double              heading;        ///< 方向角
} v2x_path_history_point_struct;

/**
  * @brief 历史路径结构体
  */
typedef struct
{
    int count;                                              ///< 历史路径点数量
    v2x_path_history_point_struct points[MAX_POINTS_NUM];   ///< 历史路径点列表
} v2x_path_history_struct;

/**
  * @brief 路径预测结构体
  */
typedef struct
{
    double  curve_radius;   ///< 曲率半径
    int     confidence;     ///< 置信度
} v2x_path_prediction_struct;

/**
  * @brief 车辆紧急扩展结构体
  */
typedef struct
{
    bool                            response_type_opt;  ///< 是否包含当前行驶状态或驾驶行为
    int                             response_type;      ///< 当前行驶状态或驾驶行为
    bool                            siren_use_opt;      ///< 是否包含警笛或发声装置状态
    int                             siren_use;          ///< 警笛或发声装置状态
    bool                            lights_use_opt;     ///< 是否包含紧急车辆或特殊车辆的警示灯或外置专用显示设备的工作状态
    int                             lights_use;         ///< 紧急车辆或特殊车辆的警示灯或外置专用显示设备的工作状态
} v2x_veh_emergency_ext_struct;

/**
  * @brief 基础安全消息结构体
  */
typedef struct
{
    v2x_veh_flag_enum               host_flag;          ///< 车辆标志，区分主车和远车
    char                            id[MAX_ID_LEN];     ///< 编号
    double                          time_stamp;         ///< 1分钟内的毫秒级时刻
    v2x_position_struct             pos;                ///< 位置
    bool                            pos_acc_opt;        ///< 是否包含定位系统自身的精度
    v2x_pos_accuracy_struct         pos_acc;            ///< 定位系统自身的精度
    bool                            pos_confidence_opt; ///< 是否包含实时位置（经纬度和高程）的精度大小
    v2x_pos_confidence_struct       pos_confidence;     ///< 实时位置（经纬度和高程）的精度大小
    bool                            trans_opt;          ///< 是否包含车辆档位
    int                             trans;              ///< 车辆档位
    double                          speed;              ///< 速度
    double                          heading;            ///< 行驶方向
    bool                            angle_opt;          ///< 是否包含方向盘转角
    int                             angle;              ///< 方向盘转角
    v2x_acceleration_set_struct     accel_set;          ///< 加速度集合
    v2x_brake_system_status_struct  brakes;             ///< 刹车系统状态
    v2x_vehicle_size_struct         veh_size;           ///< 车辆尺寸大小
    v2x_vehicle_classification_struct   vehicle_classification;     ///< 车辆的分类
    bool                            events_opt;         ///< 是否包含特殊事件
    /**
      * @see v2x_events_status_enum
      */
    int                             events;             ///< 特殊事件
    bool                            lights_opt;         ///< 是否包含灯状态
    /**
      * @see v2x_lights_status_enum
      */
    int                             lights;             ///< 灯状态
    bool                            path_his_opt;       ///< 是否包含历史路径
    v2x_path_history_struct         path_his;           ///< 历史路径
    bool                            path_pre_opt;       ///< 是否包含路径预测
    v2x_path_prediction_struct      path_pre;           ///< 路径预测

    bool                            veh_emergency_ext_opt;  ///< 是否包含车辆紧急扩展信息
    v2x_veh_emergency_ext_struct    veh_emergency_ext;      ///< 车辆紧急扩展信息

    bool                            climb_opt;          ///< 是否包含爬升速度
    double                          climb;              ///< 爬升速度
    bool                            relative_pos_opt;   ///< 是否包含相对位置
    v2x_relative_pos_enum           relative_pos;       ///< 相对位置
	bool							plate_no_opt;		///< 是否包含车辆编号信息
	char                            plate_no[MAX_PLATE_NO_LEN];    ///< 车辆编号

} v2x_bsm_struct;

/**
  * @brief 位置点列表结构体
  */
typedef struct
{
    int count;                      ///< 数量
    v2x_position_struct *tab;      ///< 位置点列表缓存，动态分配
} v2x_point_list_struct;

/**
  * @brief RSI时间信息结构体
  */
typedef struct
{
    bool                            start_time_opt;             ///< 是否包含开始时间
    int                             start_time;                 ///< 开始时间
    bool                            end_time_opt;               ///< 是否包含结束时间
    int                             end_time;                   ///< 结束时间
    bool                            end_time_confidence_opt;    ///< 是否包含结束时间置信度
    int                             end_time_confidence;        ///< 结束时间置信度
} v2x_rsi_time_details_struct;

/**
  * @brief 道路交通事件和标志的参考路径结构体
  */
typedef struct
{
    v2x_point_list_struct           active_path;    ///< 轨迹
    double                          path_radius;    ///< 半径
} v2x_reference_path_struct;

/**
  * @brief 道路交通事件和标志的参考路径集合结构体
  */
typedef struct
{
    int                             count;  ///< 数量
    v2x_reference_path_struct*      tab;    ///< 参考路径缓存，动态分配
} v2x_reference_path_list_struct;

/**
  * @brief 参考ID结构体
  */
typedef struct
{
    bool            region_id_opt;  ///< 是否包含区域ID
    unsigned long   region_id;      ///< 区域ID
    unsigned long   node_id;        ///< 节点ID
} v2x_node_ref_id_struct;

/**
  * @brief 参考路段结构体
  */
typedef struct
{
    v2x_node_ref_id_struct          upstream_node_id;       ///< 上游节点ID
    v2x_node_ref_id_struct          downstream_node_id;     ///< 下游节点ID
    bool                            reference_lanes_opt;    ///< 是否包含路段中指定的参考车道
    int                             reference_lanes;        ///< 路段中指定的参考车道
} v2x_reference_link_struct;

/**
  * @brief 参考路段集合结构体
  */
typedef struct
{
    int                             count;  ///< 数量
    v2x_reference_link_struct*      tab;    ///< 参考路段缓存，动态分配
} v2x_reference_link_list_struct;

/**
  * @brief 道路交通事件信息结构体
  */
typedef struct
{
    int                             rte_id;                                 ///< ID
    int                             event_type;                             ///< 事件类型，参考GB/T 29100-2012
    int                             event_source;                           ///< 道路交通事件的信息来源
    bool                            event_pos_opt;                          ///< 是否包含道路交通事件的位置
    v2x_position_struct             event_pos;                              ///< 道路交通事件的位置
    bool                            event_radius_opt;                       ///< 是否包含道路交通事件的半径区域
    double                          event_radius;                           ///< 道路交通事件的半径区域
    bool                            description_opt;                        ///< 是否包含描述信息
    char                            description[MAX_DESCRIPTION_LEN + 1];   ///< 描述信息
    bool                            time_details_opt;                       ///< 是否包含RSI时间信息
    v2x_rsi_time_details_struct     time_details;                           ///< RSI时间信息
    bool                            priority_opt;                           ///< 是否包含优先级
    int                             priority;                               ///< 优先级
    bool                            reference_paths_opt;                    ///< 是否包含道路交通事件和标志的参考路径
    v2x_reference_path_list_struct  reference_paths;                        ///< 道路交通事件和标志的参考路径
    bool                            reference_links_opt;                    ///< 是否包含参考路段集合
    v2x_reference_link_list_struct  reference_links;                        ///< 参考路段集合
    bool                            event_confidence_opt;                   ///< 是否包含事件置信度
    int                             event_confidence;                       ///< 事件置信度
} v2x_rte_data_struct;

/**
  * @brief 道路交通事件信息集合结构体
  */
typedef struct
{
    int                             count;  ///< 数量
    v2x_rte_data_struct*            tab;    ///< 道路交通事件信息，动态分配
} v2x_rte_list_struct;

/**
  * @brief 道路交通标识信息结构体
  */
typedef struct
{
    int                             rts_id;                                 ///< ID
    int                             sign_type;                              ///< 标识信息
    bool                            sign_pos_opt;                           ///< 是否包含标识位置信息
    v2x_position_struct             sign_pos;                               ///< 标识位置信息
    bool                            description_opt;                        ///< 是否包含描述信息
    char                            description[MAX_DESCRIPTION_LEN + 1];   ///< 描述信息
    bool                            time_details_opt;                       ///< 是否包含RSI时间信息
    v2x_rsi_time_details_struct     time_details;                           ///< RSI时间信息
    bool                            priority_opt;                           ///< 是否包含优先级
    int                             priority;                               ///< 优先级
    bool                            reference_paths_opt;                    ///< 是否包含道路交通事件和标志的参考路径
    v2x_reference_path_list_struct  reference_paths;                        ///< 道路交通事件和标志的参考路径
    bool                            reference_links_opt;                    ///< 是否包含路段集合
    v2x_reference_link_list_struct  reference_links;                        ///< 路段集合
} v2x_rts_data_struct;

/**
  * @brief 道路交通标识信息集合结构体
  */
typedef struct
{
    int                             count;  ///< 数量
    v2x_rts_data_struct*            tab;    ///< 道路交通标识信息，动态分配
} v2x_rts_list_struct;

/**
  * @brief 路侧交通消息结构体
  */
typedef struct
{
    bool                    moy_opt;            ///< 是否包含当前年份已经过去的总分钟数
    int                     moy;                ///< 当前年份已经过去的总分钟数
    char                    id[MAX_ID_LEN];     ///< 编号
    v2x_position_struct     ref_pos;            ///< 预警位置
    bool                    rtes_opt;           ///< 是否包含道路交通事件集合
    v2x_rte_list_struct     rtes;               ///< 道路交通事件集合
    bool                    rtss_opt;           ///< 是否包含道路交通标识集合
    v2x_rts_list_struct     rtss;               ///< 道路交通标识集合
} v2x_rsi_struct;

/**
  * @brief 交通参与者的基本安全信息结构体
  */
typedef struct
{
    v2x_ptc_type_enum               ptc_type;                       ///< 参与者类型
    int                             ptc_id;                         ///< 参与者ID
    v2x_source_type_enum            src_type;                       ///< 数据来源
    bool                            id_opt;                         ///< 是否包含ID
    char                            id[MAX_ID_LEN];                 ///< ID
    double                          time_stamp;                     ///< 1分钟内的毫秒级时刻
    v2x_position_struct             pos;                            ///< 位置
    v2x_pos_confidence_struct       pos_confidence;                 ///< 实时位置（经纬度和高程）的精度大小
    bool                            relative_pos_opt;               ///< 是否包含相对位置
    v2x_relative_pos_enum           relative_pos;                   ///< 相对位置
    bool                            trans_opt;                      ///< 是否包含车辆档位
    int                             trans;                          ///< 车辆档位
    double                          speed;                          ///< 速度
    double                          heading;                        ///< 行驶方向
    bool                            angle_opt;                      ///< 是否包含方向盘转角
    int                             angle;                          ///< 方向盘转角
    bool                            accel_set_opt;                  ///< 是否包含加速度集合
    v2x_acceleration_set_struct     accel_set;                      ///< 加速度集合
    v2x_vehicle_size_struct         veh_size;                       ///< 车辆尺寸大小
    bool                            vehicle_classification_opt;     ///< 是否包含车辆的分类
    v2x_vehicle_classification_struct   vehicle_classification;     ///< 车辆的分类
} v2x_ptc_struct;

/**
  * @brief 路侧安全消息结构体
  */
typedef struct
{
    int count;                      ///< 参与者数量
    v2x_ptc_struct *tab;            ///< 参与者列表缓存，动态分配
} v2x_ptc_list_struct;

/**
  * @brief 路侧安全消息结构体
  */
typedef struct
{
    char                    id[MAX_ID_LEN];     ///< RSU ID
    v2x_position_struct     ref_pos;            ///< 参考位置
    v2x_ptc_list_struct     ptc_list;           ///< 参与者列表
} v2x_rsm_struct;

/**
  * @brief 速度限制结构体
  */
typedef struct
{
    v2x_speed_limit_type_enum   type;    ///< 限速类型
    double                      speed;   ///< 限制速度
} v2x_speed_limit_struct;

/**
  * @brief 速度限制列表结构体
  */
typedef struct
{
    int                         count;  ///< 数量
    v2x_speed_limit_struct*     tab;    ///< 限速列表缓存，动态分配
} v2x_speed_limit_list_struct;

/**
  * @brief 车道属性结构体
  */
typedef struct
{
    bool                share_opt;  ///< 是否包含共享信息
    int                 share;      ///< 共享信息
    v2x_lane_type_enum  type;       ///< 车道类型
    int                 attrs;      ///< 车道属性
} v2x_lane_attributes_struct;

/**
  * @brief 连接车道信息结构体
  */
typedef struct
{
    unsigned long       lane_id;        ///< 车道ID
    bool                maneuvers_opt;  ///< 是否包含转向信息
    /**
      * @see v2x_lane_maneuver_enum
      */
    int                 maneuvers;      ///< 转向信息
} v2x_connecting_lane_struct;

/**
  * @brief 车道连接结构体
  */
typedef struct
{
    v2x_node_ref_id_struct      remote_intersection;    ///< 远端路口ID
    bool                        connect_lane_opt;       ///< 是否包含连接车道
    v2x_connecting_lane_struct  connect_lane;           ///< 连接车道
    bool                        phase_id_opt;           ///< 是否包含相位ID
    unsigned long               phase_id;               ///< 相位ID
} v2x_connection_struct;

/**
  * @brief 车道连接列表结构体
  */
typedef struct
{
    int                     count;  ///< 数量
    v2x_connection_struct*  tab;    ///< 车辆连接列表缓存，动态分配
} v2x_connection_list_struct;

/**
  * @brief 车道信息结构体
  */
typedef struct
{
    unsigned long               id;                 ///< 车道ID
    bool                        lane_width_opt;     ///< 是否包含车道宽度
    double                      lane_width;         ///< 车道宽度
    bool                        attributes_opt;     ///< 是否包含车道属性
    v2x_lane_attributes_struct  attributes;         ///< 车道属性
    bool                        maneuvers_opt;      ///< 是否包含转向信息
    /**
      * @see v2x_lane_maneuver_enum
      */
    int                         maneuvers;          ///< 转向信息
    bool                        connects_to_opt;    ///< 是否包含车道连接列表
    v2x_connection_list_struct  connects_to;        ///< 车道连接列表
    bool                        speed_limits_opt;   ///< 是否包含速度限制列表
    v2x_speed_limit_list_struct speed_limits;       ///< 速度限制列表
    bool                        points_opt;         ///< 是否包含位置点列表
    v2x_point_list_struct       points;             ///< 位置点列表
} v2x_lane_struct;

/**
  * @brief 车道列表结构体
  */
typedef struct
{
    int                 count;  ///< 数量
    v2x_lane_struct*    tab;    ///< 车辆列表缓存，动态分配
} v2x_lane_list_struct;

/**
  * @brief 路段连接信息结构体
  */
typedef struct
{
    v2x_node_ref_id_struct  remote_intersection;    ///< 远端路口ID
    bool                    phase_id_opt;           ///< 是否包含相位ID
    unsigned long           phase_id;               ///< 相位ID
} v2x_movement_struct;

/**
  * @brief 路段连接列表结构体
  */
typedef struct
{
    int                     count;  ///< 数量
    v2x_movement_struct*    tab;    ///< 路段连接列表缓存，动态分配
} v2x_movement_list_struct;

/**
  * @brief 路段信息结构体
  */
typedef struct
{
    bool                        name_opt;           ///< 是否包含名称
    v2x_string_struct           name;               ///< 名称
    v2x_node_ref_id_struct      ups_node_id;        ///< 上游节点ID
    bool                        speed_limits_opt;   ///< 是否包含速度限制列表
    v2x_speed_limit_list_struct speed_limits;       ///< 速度限制列表
    bool                        link_width_opt;     ///< 是否包含路段宽度
    double                      link_width;         ///< 路段宽度
    bool                        points_opt;         ///< 是否包含位置点列表
    v2x_point_list_struct       points;             ///< 位置点列表
    bool                        movements_opt;      ///< 是否包含路段连接列表
    v2x_movement_list_struct    movements;          ///< 路段连接列表
    v2x_lane_list_struct        lanes;              ///< 车道列表
} v2x_link_struct;

/**
  * @brief 路段列表结构体
  */
typedef struct
{
    int                 count;  ///< 数量
    v2x_link_struct*    tab;    ///< 路段列表缓存，动态分配
} v2x_link_list_struct;

/**
  * @brief 节点信息结构体
  */
typedef struct
{
    bool                    name_opt;       ///< 是否包含名称
    v2x_string_struct       name;           ///< 名称
    v2x_node_ref_id_struct  id;             ///< 节点ID
    v2x_position_struct     ref_pos;        ///< 参考位置
    bool                    links_opt;      ///< 是否包含路段列表
    v2x_link_list_struct    links;          ///< 路段列表
} v2x_node_struct;

/**
  * @brief 节点列表结构体
  */
typedef struct
{
    int                 count;  ///< 数量
    v2x_node_struct*    tab;    ///< 节点列表缓存，动态分配
} v2x_node_list_struct;

/**
  * @brief 地图数据结构体
  */
typedef struct
{
    bool                    moy_opt;            ///< 是否包含当前年份已经过去的总分钟数
    int                     moy;                ///< 当前年份已经过去的总分钟数
    v2x_node_list_struct    nodes;              ///< 节点列表
} v2x_map_struct;

/**
  * @brief 地图源数据结构体
  */
typedef struct
{
    int     length;                         ///< 数据长度
    char    data[MAX_WM_DATA_LEN];          ///< 数据
} v2x_map_src_struct;

/**
  * @brief 信号灯时间信息结构体，用倒计时形式，描述一个信号灯相位状态的完整计时状态
  */
typedef struct
{
    double  start_time;             ///< 开始时间
    bool    min_end_time_opt;       ///< 是否包含最短结束时间
    double  min_end_time;           ///< 最短结束时间
    bool    max_end_time_opt;       ///< 是否包含最长结束时间
    double  max_end_time;           ///< 最长结束时间
    double  likely_end_time;        ///< 可能结束时间
    bool    time_confidence_opt;    ///< 是否包含时间置信度
    int     time_confidence;        ///< 时间置信度
    bool    next_start_time_opt;    ///< 是否包含第二次再出现的估计时间
    double  next_start_time;        ///< 再出现的估计时间
    bool    next_duration_opt;      ///< 是否包含第二次再出现的估计持续时长
    double  next_duration;          ///< 再出现的估计持续时长
} v2x_time_counting_down_struct;

/**
  * @brief 信号灯时间信息结构体，用UTC世界标准时间形式，描述一个信号灯相位状态的完整计时状态
  */
typedef struct
{
    double  start_time;             ///< 开始时间
    bool    min_end_time_opt;       ///< 是否包含最短结束时间
    double  min_end_time;           ///< 最短结束时间
    bool    max_end_time_opt;       ///< 是否包含最长结束时间
    double  max_end_time;           ///< 最长结束时间
    double  likely_end_time;        ///< 可能结束时间
    bool    time_confidence_opt;    ///< 是否包含时间置信度
    int     time_confidence;        ///< 时间置信度
    bool    next_start_time_opt;    ///< 是否包含第二次再出现的估计时间
    double  next_start_time;        ///< 再出现的估计时间
    bool    next_end_time_opt;      ///< 是否包含第二次再结束的估计时间
    double  next_end_time;          ///< 第二次再结束的估计时间
} v2x_utc_timing_struct;

/**
  * @brief 信号灯时间信息结构体
  */
typedef struct
{
    v2x_time_change_details_enum type;          ///< 信号灯相位的计时状态数据格式枚举
    union
    {
        v2x_time_counting_down_struct counting; ///< 倒计时形式
        v2x_utc_timing_struct utc_timing;       ///< UTC世界标准时间形式
    } timing;
} v2x_time_change_details_struct;

/**
  * @brief 相位状态结构体
  */
typedef struct
{
    v2x_traffic_light_state_enum    lights;                 ///< 灯状态
    bool                            phase_state_timing_opt; ///< 是否包含时间信息
    v2x_time_change_details_struct  phase_state_timing;     ///< 时间信息
} v2x_phase_state_struct;

/**
  * @brief 相位状态列表结构体
  */
typedef struct
{
    int                     count;  ///< 数量
    v2x_phase_state_struct* tab;    ///< 相位状态列表缓存，动态分配
} v2x_phase_state_list_struct;

/**
  * @brief 信号灯相位结构体
  */
typedef struct
{
    int                         id;             ///< 相位ID
    v2x_phase_state_list_struct phase_states;   ///< 相位状态列表，不同灯色
} v2x_phase_struct;

/**
  * @brief 相位列表结构体
  */
typedef struct
{
    int                 count;  ///< 数量
    v2x_phase_struct*   tab;    ///< 相位列表缓存，动态分配
} v2x_phase_list_struct;

/**
  * @brief 路口状态结构体
  */
typedef struct
{
    v2x_node_ref_id_struct  id;             ///< 路口ID
    int                     status;         ///< 路口状态
    bool                    moy_opt;        ///< 是否包含当前年份已经过去的总分钟数
    int                     moy;            ///< 当前年份已经过去的总分钟数
    bool                    time_stamp_opt; ///< 是否包含1分钟内的毫秒级时刻
    double                  time_stamp;     ///< 1分钟内的毫秒级时刻
    v2x_phase_list_struct   phases;         ///< 相位列表
} v2x_intersection_state_struct;

/**
  * @brief 路口状态列表结构体
  */
typedef struct
{
    int                             count;  ///< 数量
    v2x_intersection_state_struct*  tab;    ///< 路口状态列表缓存，动态分配
} v2x_intersection_state_list_struct;

/**
  * @brief 信号灯信息结构体
  */
typedef struct
{
    bool                                moy_opt;            ///< 是否包含当前年份已经过去的总分钟数
    int                                 moy;                ///< 当前年份已经过去的总分钟数
    bool                                time_stamp_opt;     ///< 是否包含1分钟内的毫秒级时刻
    double                              time_stamp;         ///< 1分钟内的毫秒级时刻
    bool                                name_opt;           ///< 是否包含名称
    v2x_string_struct                   name;               ///< 名称
    v2x_intersection_state_list_struct  intersections;      ///< 路口状态列表
} v2x_spat_struct;

/**
  * @brief 信号灯源数据结构体
  */
typedef struct
{
    int     length;                         ///< 数据长度
    char    data[MAX_WM_DATA_LEN];          ///< 数据
} v2x_spat_src_struct;

/**
  * @brief 用户自定义无线信息结构体
  */
typedef struct
{
    int     type;                   ///< 消息类型
    int     length;                 ///< 数据长度
    char    data[MAX_UDM_DATA_LEN]; ///< 消息数据
} v2x_wmh_udm_struct;

/**
  * @brief 无线消息结构体
  */
typedef struct
{
    int     length;                 ///< 消息长度
    char    data[MAX_WM_DATA_LEN];  ///< 消息数据
} v2x_wms_wm_struct;

/**
  * @brief 车辆状态信息结构体
  */
typedef struct
{
    bool                            speed_opt;          ///< 是否包含速度
    double                          speed;              ///< 速度
    bool                            lights_opt;         ///< 是否包含灯状态
    /**
      * @see v2x_lights_status_enum
      */
    int                             lights;             ///< 灯状态
    bool                            transmission_opt;   ///< 是否包含档位状态
    int                             transmission;       ///< 档位状态
    bool                            brakes_opt;         ///< 是否包含刹车状态
    v2x_brake_system_status_struct  brakes;             ///< 刹车状态
} v2x_vis_hvsm_struct;

/**
  * @brief 车辆接口状态结构体
  */
typedef struct
{
    v2x_module_status_enum status;  ///< 接口状态
} v2x_vis_sm_struct;

/**
  * @brief 用户自定义车辆信息结构体
  */
typedef struct
{
    v2x_vi_type_enum    vi_type;                ///< 接口类型
    int                 msg_type;               ///< 消息类型
    int                 length;                 ///< 数据长度
    char                data[MAX_UDM_DATA_LEN]; ///< 消息数据
} v2x_vis_udm_struct;

/**
  * @brief 时钟位置消息结构体
  */
typedef struct
{
    double                          utc_time;   ///< UTC时间
    v2x_position_struct             pos;        ///< 位置信息
    double                          speed;      ///< 速度
    double                          heading;    ///< 方向角
    bool                            pos_acc_opt;        ///< 是否包含定位系统自身的精度
    v2x_pos_accuracy_struct         pos_acc;            ///< 定位系统自身的精度
    bool                            pos_confidence_opt; ///< 是否包含实时位置（经纬度和高程）的精度大小
    v2x_pos_confidence_struct       pos_confidence;     ///< 实时位置（经纬度和高程）的精度大小
    v2x_acceleration_set_struct     accel_set;  ///< 加速度集合
    bool                            climb_opt;  ///< 是否包含爬升速度
    double                          climb;      ///< 爬升速度
} v2x_tps_tpm_struct;

/**
  * @brief 时钟位置服务状态结构体
  */
typedef struct
{
    v2x_module_status_enum status; ///< 状态
} v2x_tps_sm_struct;

/**
  * @brief 显示信号灯状态信息结构体（包含建议车速）
  */
typedef struct
{
    v2x_traffic_light_state_enum    state;                  ///< 灯状态
    bool                            time_opt;               ///< 是否包含剩余时间
    double                          time;                   ///< 剩余时间
    bool                            pos_opt;                ///< 是否包含位置
    v2x_position_struct             pos;                    ///< 位置
    double                          dis;                    ///< 距离
    double                          speed_limit;            ///< 限速值
    v2x_dvin_ssm_type_enum          type;                   ///< 类型
    bool                            speed_opt;              ///< 是否包含速度值
    double                          speed;                  ///< 速度值
} v2x_dvin_ssm_struct;

/**
  * @brief 注册数据结构体
  */
typedef struct
{
    int     length;                     ///< 长度
    char    data[MAX_SHORT_DATA_LEN];   ///< 数据
} v2x_rm_data_struct;

/**
  * @brief 客户端注册信息结构体
  */
typedef struct
{
    /**
      * @see v2x_msg_type_enum
      */
    int                 msg_type;               ///< 注册消息类型
    char                name[MAX_NAME_LEN+1];   ///< 客户端名称
    bool                rm_data_option;         ///< 是否包含注册数据
    v2x_rm_data_struct  rm_data;                ///< 注册数据，扩展使用
} v2x_clt_rm_struct;

/**
  * @brief 心跳信息结构体
  */
typedef struct
{
    char                id[MAX_ID_LEN];         ///< 设备ID
    v2x_dev_type_enum   dev_type;               ///< 设备类型
    int                 count;                  ///< 计数器，循环加1
    /**
      * @see v2x_dev_status_enum
      */
    int                 status;                 ///< 设备状态
    char                soft_ver[64];           ///< 软件版本
} v2x_heart_struct;

/**
  * @brief 系统操作数据结构体
  */
typedef struct
{
    int     length;                     ///< 长度
    char    data[MAX_SHORT_DATA_LEN];   ///< 数据
} v2x_sys_oper_data_struct;

/**
  * @brief 系统操作信结构体
  */
typedef struct
{
    int                         type;                   ///< 操作类型
    bool                        result_option;          ///< 是否包含操作结果
    int                         result;                 ///< 操作结果
    bool                        sys_oper_data_option;   ///< 是否包含操作数据
    v2x_sys_oper_data_struct    sys_oper_data;          ///< 操作数据
} v2x_sys_oper_struct;

/**
  * @brief 配置信息结构体
  */
typedef struct v2x_config
{
    char                    name[32];                       ///< 名称
    v2x_config_type_enum    type;                           ///< 类型
    bool                    value_opt;                      ///< 是否包含值
    char                    value[CONFIG_ITEM_BUF_LEN];     ///< 值

    int                     items_num;                      ///< 子项数量
    struct v2x_config*      items;                          ///< 子项列表，动态分配，支持嵌套
} v2x_config_struct;

/**
  * @brief 预警信息结构体
  */
typedef struct
{
    v2x_alert_type_enum     type;                       ///< 预警类型
    int                     priority;                   ///< 预警级别
    int                     confidence;                 ///< 预警可信度
    bool                    id_opt;                     ///< 是否包含预警ID
    char                    id[MAX_ID_LEN];             ///< 预警ID（车车预警为他车ID，车路预警为路侧ID）
    bool                    pos_opt;                    ///< 是否包含位置信息
    v2x_position_struct     pos;                        ///< 预警位置（车车预警为他车位置，车路预警为路侧位置）
    bool                    relative_pos_opt;           ///< 是否包含相对位置
    v2x_relative_pos_enum   relative_pos;               ///< 相对位置
    bool                    remote_heading_opt;         ///< 是否包含预警车辆方向角
    double                  remote_heading;             ///< 预警车辆方向角
    bool                    remote_speed_opt;           ///< 是否包含预警车辆速度
    double                  remote_speed;               ///< 预警车辆速度
    bool                    subtype_opt;                ///< 是否包含预警子类型
    int                     subtype;                    ///< 预警子类型（当前主要为RSI类型）
    bool                    speed_limit_opt;            ///< 是否包含限速值
    double                  speed_limit;                ///< 限速值（预警类型为限速预警时，包含此项）
    bool                    data_opt;                   ///< 是否包含数据
    int                     data_length;                ///< 数据长度
    char                    data[CONFIG_ITEM_BUF_LEN];  ///< 数据
} v2x_ta_tm_struct;

/**
  * @brief 通用socket信息结构体
  */
typedef struct
{
    v2x_sock_type_enum  type;                   ///< 类型
    char                name[MAX_NAME_LEN+1];   ///< 名称
    int                 fd;                     ///< 句柄
    char                addr[IP_ADDR_SIZE];     ///< 地址
    int                 port;                   ///< 端口
    void*               ex;                     ///< 扩展信息，用于指向不同类型特有的信息
} v2x_com_sock_struct;

/**
  * @brief 服务端socket信息结构体
  */
typedef struct
{
    int (*on_accept)(v2x_com_sock_struct*, int);    ///< 接收回调函数
} v2x_srv_sock_struct;

/**
  * @brief 客户端socket信息结构体
  */
typedef struct
{
    v2x_info_type_enum  reg_type;                                       ///< 注册类型
    char                reg_info[256];                                  ///< 注册信息
    int                 rx_len;                                         ///< 接收数据长度，用于粘包处理
    char                *rx_buf;                                        ///< 接收数据，用于粘包处理
    double              disconnect_time;                                ///< 连接断开时间
    int                 (*on_connect)(v2x_com_sock_struct*, const char*);   ///< 连接回调函数
    int                 (*on_recv)(v2x_com_sock_struct*, char*, int);   ///< 接收回调函数
    int                 (*on_close)(v2x_com_sock_struct*);              ///< 关闭回调函数
} v2x_clt_sock_struct;

/**
  * @brief udp socket信息结构体
  */
typedef struct
{
    int     rx_len;                                         ///< 接收数据长度
    char    tx_addr[IP_ADDR_SIZE];                          ///< 发送地址
    int     tx_port;                                        ///< 发送端口
    int     (*on_recv)(v2x_com_sock_struct*, char*, int);   ///< 接收回调函数
} v2x_udp_sock_struct;

/**
  * @brief 其他自定义接收 socket信息结构体
  */
typedef struct
{
    int     (*on_recv)(v2x_com_sock_struct*);   ///< 接收回调函数
} v2x_other_ud_recv_sock_struct;

/**
  * @brief CAN过滤器列表结构体
  */
typedef struct
{
    int count;  ///< 数量
    struct can_filter can_filters[MAX_CAN_FILTER_NUM];  ///< CAN过滤列表
} v2x_can_info_struct;

/**
  * @brief CAN请求过滤器列表结构体
  */
typedef struct
{
    int count;  ///< 数量
    struct can_filter can_filters[MAX_CAN_RM_FILTER_NUM];  ///< CAN过滤列表
} v2x_can_rm_info_struct;

/**
  * @brief 车辆接口服务注册信息结构体
  */
typedef struct
{
    bool                    vi_type_option;     ///< 是否包含接口类型
    v2x_vi_type_enum        vi_type;            ///< 接口类型
    bool                    can_info_option;    ///< 是否包含CAN过滤列表
    v2x_can_rm_info_struct  can_info;           ///< CAN过滤列表
} v2x_vis_rm_struct;

#pragma pack ()
//---- 结构体定义 结束 ----

#ifdef __cplusplus
}
#endif

#endif

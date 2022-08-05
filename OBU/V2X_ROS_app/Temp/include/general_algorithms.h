/**
  * @file      general_algorithms.h
  * @brief     通用算法头文件
  * @copyright Genvict
  * @author    wuhh
  * @version   1.0.0
  * @date      2019-12-02
  * @par history:
  * | version | date | author | description |
  * | ------- | ---- | ------ | ----------- |
  * | 1.0.0 | 2019-12-02 | wuhh | create |
  */
#ifndef _GENERAL_ALGORITHMS_H_
#define _GENERAL_ALGORITHMS_H_

#ifdef __cplusplus         //定义对CPP进行C处理
extern "C" {
#endif

#define MIN_VALUE           1e-8  ///< 最小值
/**
  * @brief      判断double值为0
  * @param[in]  d   double值
  * @return     判断结果
  * @retval     true    为0
  * @retval     false   不为0
  */
#define IS_DOUBLE_ZERO(d)   (fabs(d) < MIN_VALUE)

#define PI                  3.1415926   ///< 圆周率

/**
  * @brief      角度转弧度
  * @param[in]  angle    角度值
  * @return     弧度值
  */
extern double radian(double angle);

/**
  * @brief      解1元2次方程(a*x^2+b*x+c=0)
  * @param[in]  a   二次项系数
  * @param[in]  b   一次项系数
  * @param[in]  c   常数项
  * @param[out] x1  解1
  * @param[out] x2  解2
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_roots_of_a_quadric_equation(double a, double b, double c, double *x1, double *x2);

/**
  * @brief      计算角度差值
  *
  * 以角度A为0度，获取角度A到角度B的顺时针角度差值
  * @param[in]  angle_a   角度A
  * @param[in]  angle_b   角度B
  * @return     角度A到角度B的顺时针角度差值,范围：0<=x<360
  */
extern double get_angle_dif(double angle_a, double angle_b);

/**
  * @brief      计算最小夹角值
  *
  * 计算角度A和角度B之间的最小夹角值
  * @param[in]  angle_a   角度A
  * @param[in]  angle_b   角度B
  * @return     角度A和角度B的最小夹角值,范围：0<=x<180
  */
extern double get_angle_dif_abs(double angle_a, double angle_b);

/**
  * @brief      计算最小夹角的弧度值
  *
  * 计算角度A和角度B之间的最小夹角的弧度值
  * @param[in]  angle_a   角度A
  * @param[in]  angle_b   角度B
  * @return     角度A和角度B的最小夹角的弧度值,范围：0<=x<PI
  */
extern double get_radian_dif_abs(double angle_a, double angle_b);

/**
  * @brief      计算方位角
  *
  * 计算从位置点A到位置点B的方位角
  * @param[in]  latitude_a      位置点A纬度
  * @param[in]  longitude_a     位置点A经度
  * @param[in]  latitude_b      位置点B纬度
  * @param[in]  longitude_b     位置点B经度
  * @return     从位置点A到位置点B的方位角, 范围：0<=x<360, 正北方向为0度, 顺时针方向
  */
extern double get_azimuth_angle(double latitude_a, double longitude_a, double latitude_b, double longitude_b);

/**
  * @brief      角度差值是否满足设定阈值
  *
  * 计算角度A和角度B之间的最小夹角值是否小于等于设定阈值
  * @param[in]  angle_a         角度A
  * @param[in]  angle_b         角度B
  * @param[in]  angle_threshold 角度阈值
  * @return     判断结果
  * @retval     0       满足
  * @retval     其他    不满足
  */
extern int check_angle(double angle_a, double angle_b, double angle_threshold);

/**
  * @brief      计算直线距离
  *
  * 计算位置点A和位置点B之间的直线距离
  * @param[in]  latitude_a      位置点A纬度
  * @param[in]  longitude_a     位置点A经度
  * @param[in]  latitude_b      位置点B纬度
  * @param[in]  longitude_b     位置点B经度
  * @return     距离，单位：米
  */
extern double get_distance(double latitude_a, double longitude_a, double latitude_b, double longitude_b);

/**
  * @brief      计算纵向距离
  *
  * 计算从位置点A到位置点B沿着方向角A的纵向距离
  * @param[in]  latitude_a      位置点A纬度
  * @param[in]  longitude_a     位置点A经度
  * @param[in]  heading_a       行驶方向角A，0~360
  * @param[in]  latitude_b      位置点B纬度
  * @param[in]  longitude_b     位置点B经度
  * @return     距离，单位：米
  */
extern double get_distance_vertical(double latitude_a, double longitude_a, double heading_a, double latitude_b, double longitude_b);

/**
  * @brief      计算横向距离
  *
  * 计算从位置点A到位置点B沿着方向角A的横向距离
  * @param[in]  latitude_a      位置点A纬度
  * @param[in]  longitude_a     位置点A经度
  * @param[in]  heading_a       行驶方向角A，0~360
  * @param[in]  latitude_b      位置点B纬度
  * @param[in]  longitude_b     位置点B经度
  * @return     距离，单位：米
  */
extern double get_distance_horizontal(double latitude_a, double longitude_a, double heading_a, double latitude_b, double longitude_b);

/**
  * @brief      判断点是否在矩形区域内
  *
  * 判断点C是否在由相对两边的中心点A、B及相对边长度的一半组成的矩形区域内
  * @param[in]  lat_a   矩形相对边1中心点A纬度
  * @param[in]  lng_a   矩形相对边1中心点A经度
  * @param[in]  lat_b   矩形相对边2中心点B纬度
  * @param[in]  lng_b   矩形相对边2中心点B经度
  * @param[in]  width   矩形边1长度的一半
  * @param[in]  lat_c   位置点C纬度
  * @param[in]  lng_c   位置点C经度
  * @return     判断结果
  * @retval     0       点在矩形内
  * @retval     其他    点不在矩形内
  */
extern int pt_in_rect(double lat_a, double lng_a, double lat_b, double lng_b, double width, double lat_c, double lng_c);

/**
  * @brief      计算相遇时间
  *
  * 计算A和B的相遇时间
  * @param[in]  v_a     A速度
  * @param[in]  v_b     B速度，若B与A同向行驶，为正值，反之则为负值
  * @param[in]  a_a     A加速度
  * @param[in]  a_b     B加速度，若B与A同向行驶，加速为正值，减速为负值，反之则加速为负值，减速为正值
  * @param[in]  s       A和B之间的直线距离
  * @param[out] t       A和B的相遇时间，单位：秒
  * @return     是否相遇
  * @retval     0       相遇
  * @retval     其他    不相遇
  */
extern int get_encounter_time(double v_a, double v_b, double a_a, double a_b, double s, double *t);

/**
  * @brief      计算相对位置坐标
  *
  * 计算位置点B在以位置点A为原点，A行驶方向为Y轴正方向，垂直于A行驶方向顺时针方向为X轴正方向的直角坐标系下的坐标值
  * @param[in]  latitude_a      位置点A纬度
  * @param[in]  longitude_a     位置点A经度
  * @param[in]  heading_a       A行驶方向角，范围：0~360度
  * @param[in]  latitude_b      位置点B纬度
  * @param[in]  longitude_b     位置点B经度
  * @param[out] x               相对位置横坐标，单位：米
  * @param[out] y               相对位置纵坐标，单位：米
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_relative_x_y(double latitude_a, double longitude_a, double heading_a, double latitude_b, double longitude_b, double *x, double *y);

/**
  * @brief      根据参考点位置、方位角和距离，计算当前点位置
  *
  * 已知位置点A位置、位置点B相对于点A的方位角及点A和点B之间的距离，计算点B的位置
  * @param[in]  latitude_a      位置点A纬度
  * @param[in]  longitude_a     位置点A经度
  * @param[in]  dis             点A和点B之间的距离
  * @param[in]  angle           点B相对于点A的方位角
  * @param[out] latitude_b      位置点B纬度
  * @param[out] longitude_b     位置点B经度
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_lat_long_from_dis_angle(double latitude_a, double longitude_a, double dis, double angle, double *latitude_b, double *longitude_b);

/**
  * @brief      根据相对位置坐标，计算绝对位置
  *
  * 已知位置点B相对于位置点A的坐标，计算点B的绝对位置
  * @param[in]  latitude_a      位置点A纬度
  * @param[in]  longitude_a     位置点A经度
  * @param[in]  x               点B相对于点A的横坐标
  * @param[in]  y               点B相对于点A的纵坐标
  * @param[in]  heading         点B相对于点A的方位角
  * @param[out] latitude_b      位置点B纬度
  * @param[out] longitude_b     位置点B经度
  * @return     执行结果
  * @retval     0       成功
  * @retval     其他    失败
  */
extern int get_lat_long_from_xy(double latitude_a, double longitude_a, double x, double y, double heading, double *latitude_b, double *longitude_b);

#ifdef __cplusplus
}
#endif

#endif

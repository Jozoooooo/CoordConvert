/*****************************************************************//**
 * \file   GeoCoordTrans.h
 * \brief  地理坐标转换类
 * \author Jozoooooo
 * \date   April 2023
 *********************************************************************/

#pragma once

#include "Datum.h"
#include "Eigen/Dense"

#define RAD_TO_DEG  57.295779513082321
#define DEG_TO_RAD .017453292519943296

using namespace Eigen;

class GeoCoordTrans
{
public:
	/**
	 * 大地坐标转空间直角坐标.
	 * \param pPoint 大地坐标 (大地纬度B, 大地经度L, 大地高H)
	 * \param pDatum 地球椭球体
	 * \return 空间直角坐标 (北方向X, 东方向Y, 高程坐标Z)
	 */
	Vector3d BLH2XYZ(Vector3d pPoint, Datum pDatum);

	/**
	 * 空间直角坐标转大地坐标.
	 * \param pPoint 空间直角坐标 (北方向X, 东方向Y, 高程坐标Z)
	 * \param pDatum 地球椭球体
	 * \return 大地坐标 (大地纬度B, 大地经度L, 大地高H)
	 */
	Vector3d XYZ2BLH(Vector3d pPoint, Datum pDatum);

	/**
	 * 高斯正算.
	 * \param pPoint 大地坐标 (大地纬度B, 大地经度L)
	 * \param pDatum 地球椭球体
	 * \return 高斯平面直角坐标 (x, y)
	 */
	Vector2d BL2XY(Vector2d pPoint, Datum pDatum);

	/**
	 * 高斯反算.
	 * \param pPoint 高斯平面直角坐标 (x, y)
	 * \param pDatum 地球椭球体
	 * \return 大地坐标 (大地纬度B, 大地经度L)
	 */
	Vector2d XY2BL(Vector2d pPoint, Datum pDatum);

	/**
	 * 高斯正算三维大地坐标点.
	 * \param pPoint 大地坐标 (大地纬度B, 大地经度L, 大地高H)
	 * \param pDatum 地球椭球体
	 * \return 高斯平面直角坐标 + 大地高 (x, y, H)
	 */
	Vector3d BLH2XYH(Vector3d pPoint, Datum pDatum);

	/**
	 * 高斯反算带大地高的直角坐标点.
	 * \param pPoint 高斯平面直角坐标 + 大地高 (x, y, H)
	 * \param pDatum 地球椭球体
	 * \return 大地坐标 (大地纬度B, 大地经度L, 大地高H)
	 */
	Vector3d XYH2BLH(Vector3d pPoint, Datum pDatum);

	/**
	 * 大地坐标点集转空间直角坐标点集.
	 * \param pPoints 大地坐标点集 {(大地纬度B, 大地经度L, 大地高H)}
	 * \param pDatum 地球椭球体
	 * \return 空间直角坐标点集 {(北方向X, 东方向Y, 高程坐标Z)}
	 */
	MatrixXd BLH2XYZ(MatrixXd pPoints, Datum pDatum);

	/**
	 * 空间直角坐标点集转大地坐标点集.
	 * \param pPoints 空间直角坐标点集 {(北方向X, 东方向Y, 高程坐标Z)}
	 * \param pDatum 地球椭球体
	 * \return 大地坐标点集 {(大地纬度B, 大地经度L, 大地高H)}
	 */
	MatrixXd XYZ2BLH(MatrixXd pPoints, Datum pDatum);

	/**
	 * 高斯正算大地坐标点集.
	 * \param pPoints 大地坐标点集 {(大地纬度B, 大地经度)}
	 * \param pDatum 地球椭球体
	 * \return 高斯平面直角坐标 {(x, y)}
	 */
	MatrixXd BL2XY(MatrixXd pPoints, Datum pDatum);

	/**
	 * 高斯反算直角坐标点集.
	 * \param pPoints 高斯平面直角坐标 {(x, y)}
	 * \param pDatum 地球椭球体
	 * \return 大地坐标点集 {(大地纬度B, 大地经度L)
	 */
	MatrixXd XY2BL(MatrixXd pPoints, Datum pDatum);

	/**
	 * 高斯正算三维大地坐标点集.
	 * \param pPoints 大地坐标点集 {(大地纬度B, 大地经度L, 大地高H)}
	 * \param pDatum 地球椭球体
	 * \return 高斯平面直角坐标 + 大地高点集 {(x, y, H)}
	 */
	MatrixXd BLH2XYH(MatrixXd pPoints, Datum pDatum);

	/**
	 * 高斯反算带大地高的直角坐标点集.
	 * \param pPoints 高斯平面直角坐标 + 大地高点集 {(x, y, H)}
	 * \param pDatum 地球椭球体
	 * \return 大地坐标点集 {(大地纬度B, 大地经度L, 大地高H)}
	 */
	MatrixXd XYH2BLH(MatrixXd pPoints, Datum pDatum);

	/**
	 * 弧度制角度转为度分秒角度.
	 * \param pAngle 弧度制角度
	 * \return 度分秒字符串
	 */
	static std::string radAng2DmsDeg(double pAngle);

	/**
	 * 十进制角度转为度分秒角度.
	 * \param pAngle 十进制角度
	 * \return 度分秒字符串
	 */
	static std::string decDeg2DmsDeg(double pAngle);

	/**
	 * 是否投影到三度带.
	 */
	bool mIs3Degree = true;

	/**
	 * 是否转为通用坐标（加代号 + 加500公里后坐标）.
	 */
	bool mIsUniCoord = true;
};
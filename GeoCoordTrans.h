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
	 * \param pIs3Dgree 是否投影到三度带
	 * \param pIsUniCoord 是否转为通用坐标（加代号 + 加500公里后坐标）
	 * \return 高斯平面直角坐标（x, y）
	 */
	Vector2d BL2XY(Vector2d pPoint, Datum pDatum, bool pIs3Dgree, bool pIsUniCoord = true);

	/**
	 * 高斯反算.
	 * \param pPoint 高斯平面直角坐标（x, y）
	 * \param pDatum 地球椭球体
	 * \param pIs3Dgree 是否为三度带投影下坐标
	 * \param pIsUniCoord 是否为通用坐标（加代号 + 加500公里后坐标）
	 * \return 大地坐标 (大地纬度B, 大地经度L)
	 */
	Vector2d XY2BL(Vector2d pPoint, Datum pDatum, bool pIs3Dgree, bool pIsUniCoord = true);
};


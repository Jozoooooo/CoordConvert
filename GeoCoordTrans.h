/*****************************************************************//**
 * \file   GeoCoordTrans.h
 * \brief  ��������ת����
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
	 * �������ת�ռ�ֱ������.
	 * \param pPoint ������� (���γ��B, ��ؾ���L, ��ظ�H)
	 * \param pDatum ����������
	 * \return �ռ�ֱ������ (������X, ������Y, �߳�����Z)
	 */
	Vector3d BLH2XYZ(Vector3d pPoint, Datum pDatum);

	/**
	 * �ռ�ֱ������ת�������.
	 * \param pPoint �ռ�ֱ������ (������X, ������Y, �߳�����Z)
	 * \param pDatum ����������
	 * \return ������� (���γ��B, ��ؾ���L, ��ظ�H)
	 */
	Vector3d XYZ2BLH(Vector3d pPoint, Datum pDatum);

	/**
	 * ��˹����.
	 * \param pPoint ������� (���γ��B, ��ؾ���L)
	 * \param pDatum ����������
	 * \return ��˹ƽ��ֱ������ (x, y)
	 */
	Vector2d BL2XY(Vector2d pPoint, Datum pDatum);

	/**
	 * ��˹����.
	 * \param pPoint ��˹ƽ��ֱ������ (x, y)
	 * \param pDatum ����������
	 * \return ������� (���γ��B, ��ؾ���L)
	 */
	Vector2d XY2BL(Vector2d pPoint, Datum pDatum);

	/**
	 * ��˹������ά��������.
	 * \param pPoint ������� (���γ��B, ��ؾ���L, ��ظ�H)
	 * \param pDatum ����������
	 * \return ��˹ƽ��ֱ������ + ��ظ� (x, y, H)
	 */
	Vector3d BLH2XYH(Vector3d pPoint, Datum pDatum);

	/**
	 * ��˹�������ظߵ�ֱ�������.
	 * \param pPoint ��˹ƽ��ֱ������ + ��ظ� (x, y, H)
	 * \param pDatum ����������
	 * \return ������� (���γ��B, ��ؾ���L, ��ظ�H)
	 */
	Vector3d XYH2BLH(Vector3d pPoint, Datum pDatum);

	/**
	 * �������㼯ת�ռ�ֱ������㼯.
	 * \param pPoints �������㼯 {(���γ��B, ��ؾ���L, ��ظ�H)}
	 * \param pDatum ����������
	 * \return �ռ�ֱ������㼯 {(������X, ������Y, �߳�����Z)}
	 */
	MatrixXd BLH2XYZ(MatrixXd pPoints, Datum pDatum);

	/**
	 * �ռ�ֱ������㼯ת�������㼯.
	 * \param pPoints �ռ�ֱ������㼯 {(������X, ������Y, �߳�����Z)}
	 * \param pDatum ����������
	 * \return �������㼯 {(���γ��B, ��ؾ���L, ��ظ�H)}
	 */
	MatrixXd XYZ2BLH(MatrixXd pPoints, Datum pDatum);

	/**
	 * ��˹����������㼯.
	 * \param pPoints �������㼯 {(���γ��B, ��ؾ���)}
	 * \param pDatum ����������
	 * \return ��˹ƽ��ֱ������ {(x, y)}
	 */
	MatrixXd BL2XY(MatrixXd pPoints, Datum pDatum);

	/**
	 * ��˹����ֱ������㼯.
	 * \param pPoints ��˹ƽ��ֱ������ {(x, y)}
	 * \param pDatum ����������
	 * \return �������㼯 {(���γ��B, ��ؾ���L)
	 */
	MatrixXd XY2BL(MatrixXd pPoints, Datum pDatum);

	/**
	 * ��˹������ά�������㼯.
	 * \param pPoints �������㼯 {(���γ��B, ��ؾ���L, ��ظ�H)}
	 * \param pDatum ����������
	 * \return ��˹ƽ��ֱ������ + ��ظߵ㼯 {(x, y, H)}
	 */
	MatrixXd BLH2XYH(MatrixXd pPoints, Datum pDatum);

	/**
	 * ��˹�������ظߵ�ֱ������㼯.
	 * \param pPoints ��˹ƽ��ֱ������ + ��ظߵ㼯 {(x, y, H)}
	 * \param pDatum ����������
	 * \return �������㼯 {(���γ��B, ��ؾ���L, ��ظ�H)}
	 */
	MatrixXd XYH2BLH(MatrixXd pPoints, Datum pDatum);

	/**
	 * �����ƽǶ�תΪ�ȷ���Ƕ�.
	 * \param pAngle �����ƽǶ�
	 * \return �ȷ����ַ���
	 */
	static std::string radAng2DmsDeg(double pAngle);

	/**
	 * ʮ���ƽǶ�תΪ�ȷ���Ƕ�.
	 * \param pAngle ʮ���ƽǶ�
	 * \return �ȷ����ַ���
	 */
	static std::string decDeg2DmsDeg(double pAngle);

	/**
	 * �Ƿ�ͶӰ�����ȴ�.
	 */
	bool mIs3Degree = true;

	/**
	 * �Ƿ�תΪͨ�����꣨�Ӵ��� + ��500��������꣩.
	 */
	bool mIsUniCoord = true;
};
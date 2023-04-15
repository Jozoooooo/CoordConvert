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
	 * \param pIs3Dgree �Ƿ�ͶӰ�����ȴ�
	 * \param pIsUniCoord �Ƿ�תΪͨ�����꣨�Ӵ��� + ��500��������꣩
	 * \return ��˹ƽ��ֱ�����꣨x, y��
	 */
	Vector2d BL2XY(Vector2d pPoint, Datum pDatum, bool pIs3Dgree, bool pIsUniCoord = true);

	/**
	 * ��˹����.
	 * \param pPoint ��˹ƽ��ֱ�����꣨x, y��
	 * \param pDatum ����������
	 * \param pIs3Dgree �Ƿ�Ϊ���ȴ�ͶӰ������
	 * \param pIsUniCoord �Ƿ�Ϊͨ�����꣨�Ӵ��� + ��500��������꣩
	 * \return ������� (���γ��B, ��ؾ���L)
	 */
	Vector2d XY2BL(Vector2d pPoint, Datum pDatum, bool pIs3Dgree, bool pIsUniCoord = true);
};


/*****************************************************************//**
 * \file   Para4.h
 * \brief  �Ĳ�������ת��
 * \author Jozoooooo
 * \date   April 2023
 *********************************************************************/

#pragma once

#include "Eigen/Dense"

using namespace Eigen;

class Para4
{
public:
	/**
	 * ʹ�ú��������new�������ȷ��������ڴ���ȷ����.
	 */
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	/**
	 * �Ĳ��� ��X ��Y �� K.
	 */
	RowVector4d mPara4;

	/**
	 * �޲ι��캯��.
	 */
	Para4() :
		mPara4(RowVector4d::Constant(4, 0.0)) {}

	/**
	 * ��ʼ���Ĳ������캯��.
	 * \param pParam4
	 */
	Para4(RowVector4d pParam4) :
		mPara4(pParam4) {}

	/**
	 * ����ת��.
	 * \param pPoint ԭʼ����ϵ�µ����� X Y
	 * \return Ŀ������ϵ�µ����� X' Y'
	 */
	Vector2d cooConv(Vector2d pPoint);

	/**
	 * ����4������������� X = (B^T * B)^(-1) * B^T * L.
	 * \param pSrcPoints ����ԭʼ����ϵ������� {X Y}
	 * \param pDesPoints ����Ŀ������ϵ������� {X' Y'}
	 * \return �����������
	 */
	RowVectorXd cal4Args(MatrixXd pSrcPoints, MatrixXd pDesPoints);

private:
	/**
	 * �������������ϵ������B.
	 * \param pPoint ԭʼ����ϵ������� X Y
	 * \return �������ϵ������B
	 */
	MatrixXd point2B(Vector2d pPoint);

	/**
	 * ��������ԭʼ����ϵ�����������������ϵ������B.
	 * \param pPoints ����ԭʼ����ϵ������� {X Y}
	 * \return ����ϵ������B
	 */
	MatrixXd points2B(MatrixXd& pPoints);

	/**
	 * ͨ��ͬ��������ת����ϵ��������ϵ������L.
	 * \param pSrcPoints ����ԭʼ����ϵ������� {X Y}
	 * \param pDesPoints ����Ŀ������ϵ������� {X' Y'}
	 * \return ϵ������L
	 */
	VectorXd points2L(MatrixXd pSrcPoints, MatrixXd pDesPoints);
};
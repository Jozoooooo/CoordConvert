/*****************************************************************//**
 * \file   Para7.h
 * \brief  �߲�������ת��
 * \author Jozoooooo
 * \date   April 2023
 *********************************************************************/

#pragma once

#include "Eigen/Dense"

using namespace Eigen;

class Para7
{
public:
	/**
	 * �߲��� ��X ��Y ��Z ��X ��Y ��Z M.
	 */
	RowVectorXd mPara7;

	/**
	 * �޲ι��캯��.
	 */
	Para7() :
		mPara7(RowVectorXd::Constant(7, 0.0)) {}

	/**
	 * ��ʼ���߲������캯��.
	 * \param pParam7 ��֪���߲���
	 */
	Para7(RowVectorXd pParam7) :
		mPara7(pParam7) {}

	/**
	 * ����ת��.
	 * \param pPoint ԭʼ����ϵ�µ����� X Y Z
	 * \return Ŀ������ϵ�µ����� X' Y' Z'
	 */
	Vector3d cooConv(Vector3d pPoint);

	/**
	 * ����7������������� X = (B^T * B)^(-1) * B^T * L.
	 * \param pSrcPoints ����ԭʼ����ϵ������� {X Y Z}
	 * \param pDesPoints ����Ŀ������ϵ������� {X' Y' Z'}
	 * \return �����������
	 */
	RowVectorXd cal7Args(MatrixXd pSrcPoints, MatrixXd pDesPoints);

private:
	/**
	 * �������������ϵ������B.
	 * \param pPoint ԭʼ����ϵ������� X Y Z
	 * \return �������ϵ������B
	 */
	MatrixXd point2B(Vector3d pPoint);

	/**
	 * ��������ԭʼ����ϵ�����������������ϵ������B.
	 * \param pPoints ����ԭʼ����ϵ������� {X Y Z}
	 * \return ����ϵ������B
	 */
	MatrixXd points2B(MatrixXd pPoints);

	/**
	 * ͨ��ͬ��������ת����ϵ��������ϵ������L.
	 * \param pSrcPoints ����ԭʼ����ϵ������� {X Y Z}
	 * \param pDesPoints ����Ŀ������ϵ������� {X' Y' Z'}
	 * \return ϵ������L
	 */
	VectorXd points2L(MatrixXd pSrcPoints, MatrixXd pDesPoints);
};
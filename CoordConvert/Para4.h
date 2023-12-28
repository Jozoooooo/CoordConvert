/*********************************************************************
 * @file   Para4.h
 * @brief  �Ĳ�������ת��
 * @author Jozoooooo
 * @date   April 2023
 *********************************************************************/

#pragma once

#include "Eigen/Dense"

using namespace Eigen;

class Para4
{
  public:
    /**
     * @brief ʹ�ú��������new�������ȷ��������ڴ���ȷ����.
     */
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    /**
     * @brief �Ĳ��� ��X ��Y �� K.
     */
    RowVector4d mPara4;

    /**
     * @brief �޲ι��캯��.
     */
    Para4() : mPara4(RowVector4d::Constant(4, 0.0)){};

    /**
     * @brief ��ʼ���Ĳ������캯��.
     * @param pParam4 ��֪���Ĳ���
     */
    Para4(RowVector4d pParam4) : mPara4(pParam4){};

    /**
     * @brief ����ת��.
     * @param pPoint ԭʼ����ϵ�µ����� X Y
     * @return Ŀ������ϵ�µ����� X' Y'
     */
    Vector2d cooConv(Vector2d pPoint);

    /**
     * @brief ����4������������� X = (B^T * B)^(-1) * B^T * L.
     * @param pSrcPoints ����ԭʼ����ϵ������� {X Y}
     * @param pDesPoints ����Ŀ������ϵ������� {X' Y'}
     * @return �����������
     */
    RowVectorXd cal4Args(MatrixXd pSrcPoints, MatrixXd pDesPoints);

  private:
    /**
     * @brief �������������ϵ������B.
     * @param pPoint ԭʼ����ϵ������� X Y
     * @return �������ϵ������B
     */
    MatrixXd point2B(Vector2d pPoint);

    /**
     * @brief ��������ԭʼ����ϵ�����������������ϵ������B.
     * @param pPoints ����ԭʼ����ϵ������� {X Y}
     * @return ����ϵ������B
     */
    MatrixXd points2B(MatrixXd& pPoints);

    /**
     * @brief ͨ��ͬ��������ת����ϵ��������ϵ������L.
     * @param pSrcPoints ����ԭʼ����ϵ������� {X Y}
     * @param pDesPoints ����Ŀ������ϵ������� {X' Y'}
     * @return ϵ������L
     */
    VectorXd points2L(MatrixXd pSrcPoints, MatrixXd pDesPoints);
};
/*********************************************************************
 * @file   Para7.h
 * @brief  七参数坐标转换
 * @author Jozoooooo
 * @date   April 2023
 *********************************************************************/

#pragma once

#include "Eigen/Dense"

using namespace Eigen;

class Para7
{
  public:
    /**
     * @brief 七参数 ΔX ΔY ΔZ θX θY θZ M.
     */
    RowVectorXd mPara7;

    /**
     * @brief 无参构造函数.
     */
    Para7() : mPara7(RowVectorXd::Constant(7, 0.0)){};

    /**
     * @brief 初始化七参数构造函数.
     * @param pParam7 已知的七参数
     */
    Para7(RowVectorXd pParam7) : mPara7(pParam7){};

    /**
     * @brief 坐标转换.
     * @param pPoint 原始坐标系下点坐标 X Y Z
     * @return 目标坐标系下点坐标 X' Y' Z'
     */
    Vector3d cooConv(Vector3d pPoint);

    /**
     * @brief 计算7参数，求解误差方程 X = (B^T * B)^(-1) * B^T * L.
     * @param pSrcPoints 所有原始坐标系下坐标点 {X Y Z}
     * @param pDesPoints 所有目标坐标系下坐标点 {X' Y' Z'}
     * @return 各个点中误差
     */
    RowVectorXd cal7Args(MatrixXd pSrcPoints, MatrixXd pDesPoints);

  private:
    /**
     * @brief 根据坐标点求其系数矩阵B.
     * @param pPoint 原始坐标系下坐标点 X Y Z
     * @return 单个点的系数矩阵B
     */
    MatrixXd point2B(Vector3d pPoint);

    /**
     * @brief 根据所有原始坐标系下坐标点求整个误差方程系数矩阵B.
     * @param pPoints 所有原始坐标系下坐标点 {X Y Z}
     * @return 整个系数矩阵B
     */
    MatrixXd points2B(MatrixXd pPoints);

    /**
     * @brief 通过同名点坐标转换关系列立误差方程系数矩阵L.
     * @param pSrcPoints 所有原始坐标系下坐标点 {X Y Z}
     * @param pDesPoints 所有目标坐标系下坐标点 {X' Y' Z'}
     * @return 系数矩阵L
     */
    VectorXd points2L(MatrixXd pSrcPoints, MatrixXd pDesPoints);
};
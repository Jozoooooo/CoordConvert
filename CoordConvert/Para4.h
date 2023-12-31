/*********************************************************************
 * @file   Para4.h
 * @brief  四参数坐标转换
 * @author Jozoooooo
 * @date   April 2023
 *********************************************************************/

#pragma once

#include "Eigen/Dense"

using namespace Eigen;

/**
 * @brief 四参数坐标转换类.
 */
class Para4
{
  public:
    /**
     * @brief 使用宏重载类的new运算符以确保分配的内存正确对齐.
     */
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    /**
     * @brief 四参数 ΔX ΔY α K.
     */
    RowVector4d mPara4;

    /**
     * @brief 无参构造函数.
     */
    Para4() : mPara4(RowVector4d::Constant(4, 0.0)){};

    /**
     * @brief 初始化四参数构造函数.
     * @param pParam4 已知的四参数
     */
    Para4(RowVector4d pParam4) : mPara4(pParam4){};

    /**
     * @brief 坐标转换.
     * @param pPoint 原始坐标系下点坐标 X Y
     * @return 目标坐标系下点坐标 X' Y'
     */
    Vector2d cooConv(Vector2d pPoint);

    /**
     * @brief 计算4参数，求解误差方程 X = (B^T * B)^(-1) * B^T * L.
     * @param pSrcPoints 所有原始坐标系下坐标点 {X Y}
     * @param pDesPoints 所有目标坐标系下坐标点 {X' Y'}
     * @return 各个点中误差
     */
    RowVectorXd cal4Args(MatrixXd pSrcPoints, MatrixXd pDesPoints);

  private:
    /**
     * @brief 根据坐标点求其系数矩阵B.
     * @param pPoint 原始坐标系下坐标点 X Y
     * @return 单个点的系数矩阵B
     */
    MatrixXd point2B(Vector2d pPoint);

    /**
     * @brief 根据所有原始坐标系下坐标点求整个误差方程系数矩阵B.
     * @param pPoints 所有原始坐标系下坐标点 {X Y}
     * @return 整个系数矩阵B
     */
    MatrixXd points2B(MatrixXd& pPoints);

    /**
     * @brief 通过同名点坐标转换关系列立误差方程系数矩阵L.
     * @param pSrcPoints 所有原始坐标系下坐标点 {X Y}
     * @param pDesPoints 所有目标坐标系下坐标点 {X' Y'}
     * @return 系数矩阵L
     */
    VectorXd points2L(MatrixXd pSrcPoints, MatrixXd pDesPoints);
};
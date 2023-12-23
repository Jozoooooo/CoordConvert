#include "Para4.h"

Vector2d Para4::cooConv(Vector2d pPoint)
{
    Vector2d lPoint;
    double lCos = mPara4(3) * cos(mPara4(2));
    double lSin = mPara4(3) * sin(mPara4(2));
    lPoint(0) = mPara4(0) + lCos * pPoint(0) - lSin * pPoint(1);
    lPoint(1) = mPara4(1) + lCos * pPoint(1) + lSin * pPoint(0);
    return lPoint;
}

RowVectorXd Para4::cal4Args(MatrixXd pSrcPoints, MatrixXd pDesPoints)
{
    MatrixXd lMatB = points2B(pSrcPoints);
    MatrixXd lMatL = points2L(pSrcPoints, pDesPoints);
    MatrixXd lPara = lMatB.colPivHouseholderQr().solve(lMatL);
    mPara4(0) = lPara(0);
    mPara4(1) = lPara(1);
    mPara4(2) = atan(lPara(3) / (lPara(2) + 1));
    mPara4(3) = sqrt(pow(lPara(2) + 1, 2) + pow(lPara(3), 2));

    RowVectorXd lRMS = RowVectorXd::Constant(pSrcPoints.rows(), 0.0);
    for (int i = 0; i < pSrcPoints.rows(); i++)
    {
        Vector2d lSrcPoint = pSrcPoints.row(i);
        Vector2d lDesPoint = pDesPoints.row(i);
        Vector2d lConvPoint = cooConv(lSrcPoint);
        lRMS(i) = sqrt(pow(lDesPoint(0) - lConvPoint(0), 2) + pow(lDesPoint(1) - lConvPoint(1), 2));
    }
    return lRMS;
}

MatrixXd Para4::point2B(Vector2d pPoint)
{
    MatrixXd lMatB = MatrixXd::Constant(2, 4, 0.0);
    lMatB << 1, 0, pPoint(0), -pPoint(1), 0, 1, pPoint(1), pPoint(0);
    return lMatB;
}

MatrixXd Para4::points2B(MatrixXd& pPoints)
{
    MatrixXd lMatW = MatrixXd::Constant(0, 4, 0.0);
    for (int i = 0; i < pPoints.rows(); i++)
    {
        Vector2d lPoint = pPoints.row(i);
        MatrixXd lMatB = point2B(lPoint);
        lMatW.conservativeResize(lMatW.rows() + lMatB.rows(), NoChange);
        lMatW.bottomRows(lMatB.rows()) = lMatB;
    }
    return lMatW;
}

VectorXd Para4::points2L(MatrixXd pSrcPoints, MatrixXd pDesPoints)
{
    RowVectorXd lMatL = RowVectorXd::Constant(2 * pSrcPoints.rows(), 0.0);
    for (int i = 0; i < pSrcPoints.rows(); i++)
    {
        Vector2d lSrcPoint = pSrcPoints.row(i);
        Vector2d lDesPoint = pDesPoints.row(i);
        lMatL(2 * i + 0) = lDesPoint(0) - lSrcPoint(0);
        lMatL(2 * i + 1) = lDesPoint(1) - lSrcPoint(1);
    }
    return lMatL.transpose().eval();
}
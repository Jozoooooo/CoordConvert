#include "Para7.h"

Vector3d Para7::cooConv(Vector3d pPoint)
{
	Vector3d lPoint;
	lPoint << mPara7(0) + (1 + mPara7(6)) * (pPoint(0) + mPara7(5) * pPoint(1) - mPara7(4) * pPoint(2)),
		mPara7(1) + (1 + mPara7(6)) * (-mPara7(5) * pPoint(0) + pPoint(1) + mPara7(3) * pPoint(2)),
		mPara7(2) + (1 + mPara7(6)) * (mPara7(4) * pPoint(0) - mPara7(3) * pPoint(1) + pPoint(2));
	return lPoint;
}

RowVectorXd Para7::cal7Args(MatrixXd pSrcPoints, MatrixXd pDesPoints)
{
	MatrixXd lPara = RowVectorXd::Constant(7, 1.0);
	while (lPara.array().abs().sum() > 0.00001)
	{
		MatrixXd lMatB = points2B(pSrcPoints);
		MatrixXd lMatL = points2L(pSrcPoints, pDesPoints);
		lPara = lMatB.colPivHouseholderQr().solve(lMatL);
		for (int i = 0; i < 7; i++)
			mPara7(i) += lPara(i);
	}

	RowVectorXd lRMS = RowVectorXd::Constant(pSrcPoints.rows(), 0.0);
	for (int i = 0; i < pSrcPoints.rows(); i++)
	{
		Vector3d lSrcPoint = pSrcPoints.row(i);
		Vector3d lDesPoint = pDesPoints.row(i);
		Vector3d lConvPoint = cooConv(lSrcPoint);
		lRMS(i) = sqrt(pow(lDesPoint(0) - lConvPoint(0), 2) + pow(lDesPoint(1) - lConvPoint(1), 2) + pow(lDesPoint(2) - lConvPoint(2), 2));
	}
	return lRMS;
}

MatrixXd Para7::point2B(Vector3d pPoint)
{
	MatrixXd lMatB = MatrixXd::Constant(3, 7, 0.0);
	lMatB << 1, 0, 0, 0, -(1 + mPara7(6)) * pPoint(2), (1 + mPara7(6))* pPoint(1), pPoint(0) + mPara7(5) * pPoint(1) - mPara7(4) * pPoint(2),
		0, 1, 0, (1 + mPara7(6))* pPoint(2), 0, -(1 + mPara7(6)) * pPoint(0), -mPara7(5) * pPoint(0) + pPoint(1) + mPara7(3) * pPoint(2),
		0, 0, 1, -(1 + mPara7(6)) * pPoint(1), (1 + mPara7(6))* pPoint(0), 0, mPara7(4)* pPoint(0) - mPara7(3) * pPoint(1) + pPoint(2);
	return lMatB;
};

MatrixXd Para7::points2B(MatrixXd pPoints)
{
	MatrixXd lMatW = MatrixXd::Constant(0, 7, 0.0);
	for (int i = 0; i < pPoints.rows(); i++)
	{
		Vector3d lPoint = pPoints.row(i);
		MatrixXd lMatB = point2B(lPoint);
		lMatW.conservativeResize(lMatW.rows() + lMatB.rows(), NoChange);
		lMatW.bottomRows(lMatB.rows()) = lMatB;
	}
	return lMatW;
}

VectorXd Para7::points2L(MatrixXd pSrcPoints, MatrixXd pDesPoints)
{
	RowVectorXd lMatL = RowVectorXd::Constant(3 * pSrcPoints.rows(), 0.0);
	for (int i = 0; i < pSrcPoints.rows(); i++)
	{
		Vector3d lSrcPoint = pSrcPoints.row(i);
		Vector3d lDesPoint = cooConv(lSrcPoint);
		lMatL(3 * i + 0) = pDesPoints.row(i)(0) - lDesPoint(0);
		lMatL(3 * i + 1) = pDesPoints.row(i)(1) - lDesPoint(1);
		lMatL(3 * i + 2) = pDesPoints.row(i)(2) - lDesPoint(2);
	}
	return lMatL.transpose().eval();
}
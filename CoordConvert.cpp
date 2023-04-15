#include <iostream>
#include "Para7.h"
#include "Para4.h"
#include "GeoCoordTrans.h"

#define CooConvPara7

using namespace Eigen;

/**
 * 弧度转角度.
 * \param pRad 弧度
 * \return 角度 [0]度 [1]分 [2]秒
 */
double* rad2Ang(double pRad)
{
	double pAng[3];
	double lIsNegNum = (pRad < 0) ? -1.0 : 1.0;
	if (pRad < 0)
		pRad = pRad * (-1.0);
	double lResult = (pRad * 180) / 3.1415926;
	double lDegres1 = int(lResult);
	double lMinute = (lResult - lDegres1) * 60;
	double lSecond = (lMinute - int(lMinute)) * 60;
	pAng[0] = lIsNegNum * lDegres1;
	pAng[1] = lIsNegNum * int(lMinute);
	pAng[2] = lIsNegNum * lSecond;
	return pAng;
}

void main()
{
#ifdef CooConvPara7

	MatrixXd lCooWGS84 = MatrixXd::Constant(5, 3, 0.0);
	lCooWGS84 << -2066241.5001, 5360801.8835, 2761896.3022,
		-1983936.0407, 5430615.7282, 2685375.7214,
		-1887112.7302, 5468749.1944, 2677688.9806,
		-1808505.4212, 5512502.2716, 2642356.5720,
		-1847017.0670, 5573542.7934, 2483802.9904;

	MatrixXd lCooBJ54 = MatrixXd::Constant(5, 3, 0.0);
	lCooBJ54 << -2066134.4896, 5360847.0595, 2761895.5970,
		-1983828.7084, 5430658.9827, 2685374.6681,
		-1887005.1714, 5468790.6487, 2677687.2680,
		-1808397.7260, 5512542.0921, 2642354.4550,
		-1846909.0036, 5573582.6511, 2483801.6147;

 	//MatrixXd lCooWGS84 = MatrixXd::Constant(4, 3, 0.0);
 	//lCooWGS84 << 608172.995, 4053652.076, 1329.070,
 	//	609704.962, 4053801.375, 1404.835,
 	//	610402.566, 4053631.681, 1261.145,
 	//	608185.322, 4052821.909, 1231.975;
 
 	//MatrixXd lCooBJ54 = MatrixXd::Constant(4, 3, 0.0);
 	//lCooBJ54 << 608104.1022, 4053603.4450, 1329.0687,
 	//	609636.0700, 4053752.7519, 1404.8339,
 	//	610333.6756, 4053583.0613, 1261.1438,
 	//	608116.4335, 4052773.2772, 1231.9736;

	std::cout << "原始数据：" << std::endl;
	GeoCoordTrans cooTrans;
	for (int i = 0; i < lCooWGS84.rows(); i++)
	{
		Vector3d lPointXYZ = lCooWGS84.row(i);
		Vector3d lPointBLH = cooTrans.XYZ2BLH(lPointXYZ, WGS84);
		Vector3d lPointXYZ2 = cooTrans.BLH2XYZ(lPointBLH, WGS84);
		Vector2d lPointXY = cooTrans.BL2XY(Vector2d(lPointBLH(0), lPointBLH(1)), WGS84, false);
		Vector2d lPointBL = cooTrans.XY2BL(lPointXY, WGS84, false);
		std::cout << "X Y Z ：" << std::fixed << lPointXYZ.transpose() << std::endl;
		std::cout << "->BLH ：" << lPointBLH.transpose() << std::endl;
		std::cout << "->XYZ ：" << lPointXYZ2.transpose() << std::endl;
		std::cout << "->x y ：" << lPointXY.transpose() << std::endl;
		std::cout << "->B L ：" << lPointBL.transpose() << std::endl;
		std::cout << std::endl;
	}

	Para7 lPara7;
	RowVectorXd lRMS = lPara7.cal7Args(lCooWGS84, lCooBJ54);
	std::cout << "七参数计算结果：" << std::endl;
	std::cout << "ΔX:" << lPara7.mPara7[0] << " m" << std::endl;
	std::cout << "ΔY:" << lPara7.mPara7[1] << " m" << std::endl;
	std::cout << "ΔZ:" << lPara7.mPara7[2] << " m" << std::endl;
	std::cout << "θX:" << rad2Ang(lPara7.mPara7[3])[2] << " s" << std::endl;
	std::cout << "θY:" << rad2Ang(lPara7.mPara7[4])[2] << " s" << std::endl;
	std::cout << "θZ:" << rad2Ang(lPara7.mPara7[5])[2] << " s" << std::endl;
	std::cout << " m:" << lPara7.mPara7[6] / 1e-6 << " ppm" << std::endl;
	std::cout << "中误差：" << lRMS << std::endl;

#endif

#ifdef CooConvPara4

	MatrixXd lCooWGS84 = MatrixXd::Constant(5, 2, 0.0);
	lCooWGS84 << -2066241.5001, 5360801.8835,
		-1983936.0407, 5430615.7282,
		-1887112.7302, 5468749.1944,
		-1808505.4212, 5512502.2716,
		-1847017.0670, 5573542.7934;

	MatrixXd lCooBJ54 = MatrixXd::Constant(5, 2, 0.0);
	lCooBJ54 << -2066134.4896, 5360847.0595,
		-1983828.7084, 5430658.9827,
		-1887005.1714, 5468790.6487,
		-1808397.7260, 5512542.0921,
		-1846909.0036, 5573582.6511;

	//MatrixXd lCooWGS84 = MatrixXd::Constant(2, 2, 0.0);
	//lCooWGS84 << 4312820.897, 513670.931,
	//	4314058.425, 514231.984;

	//MatrixXd lCooBJ54 = MatrixXd::Constant(2, 2, 0.0);
	//lCooBJ54 << 4312816.917, 513553.719,
	//	4314054.440, 514114.777;

	Para4* lPara4 = new Para4();
	RowVectorXd lRMS = lPara4->cal4Args(lCooWGS84, lCooBJ54);
	printf("四参数计算结果：\n");
	printf("ΔX: %.12f m\n", lPara4->mPara4(0));
	printf("ΔY: %.12f m\n", lPara4->mPara4(1));
	printf(" α: %.12f\n", lPara4->mPara4(2));
	printf(" K: %.12f\n", lPara4->mPara4(3));
	std::cout << "中误差：" << lRMS << std::endl;
	//Vector2d lConvPoint = lPara4->cooConv(Vector2d(4306670.108, 511168.332));
	//std::cout << "转换结果：" << lConvPoint.transpose() << std::endl;

#endif
}
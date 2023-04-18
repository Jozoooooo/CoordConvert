#include <iostream>
#include "Para7.h"
#include "Para4.h"
#include "GeoCoordTrans.h"

#define CooConvPara7

using namespace Eigen;


void main()
{
#ifdef CooConvPara7

	// 《误差理论与测量平差基础》示例数据
	//MatrixXd lCooWGS84 = MatrixXd::Constant(5, 3, 0.0);
	//lCooWGS84 << -2066241.5001, 5360801.8835, 2761896.3022,
	//	-1983936.0407, 5430615.7282, 2685375.7214,
	//	-1887112.7302, 5468749.1944, 2677688.9806,
	//	-1808505.4212, 5512502.2716, 2642356.5720,
	//	-1847017.0670, 5573542.7934, 2483802.9904;
	//MatrixXd lCooBJ54 = MatrixXd::Constant(5, 3, 0.0);
	//lCooCGCS2000 << -2066134.4896, 5360847.0595, 2761895.5970,
	//	-1983828.7084, 5430658.9827, 2685374.6681,
	//	-1887005.1714, 5468790.6487, 2677687.2680,
	//	-1808397.7260, 5512542.0921, 2642354.4550,
	//	-1846909.0036, 5573582.6511, 2483801.6147;

	// 《地学常用软件》实验数据
 	//MatrixXd lCooBJ54 = MatrixXd::Constant(4, 3, 0.0);
 	//lCooWGS84 << 608172.995, 4053652.076, 1329.070,
 	//	609704.962, 4053801.375, 1404.835,
 	//	610402.566, 4053631.681, 1261.145,
 	//	608185.322, 4052821.909, 1231.975;
 	//MatrixXd lCooXA80 = MatrixXd::Constant(4, 3, 0.0);
 	//lCooCGCS2000 << 608104.1022, 4053603.4450, 1329.0687,
 	//	609636.0700, 4053752.7519, 1404.8339,
 	//	610333.6756, 4053583.0613, 1261.1438,
 	//	608116.4335, 4052773.2772, 1231.9736;

	MatrixXd lCooWGS84 = MatrixXd::Constant(3, 3, 0.0);
	lCooWGS84 << 32.31946077, 118.9794678, 0,
		31.87150796, 119.0242093, 0,
		32.49363731, 119.0194427, 0;
	MatrixXd lCooCGCS2000 = MatrixXd::Constant(3, 3, 0.0);
	lCooCGCS2000 << 3577734.913, 40403900.37, 0,
		3528019.697, 40407664.13, 0,
		3597016.102, 40407842.00, 0;

	std::cout << "原始数据坐标转换：" << std::endl;
	GeoCoordTrans lCoordTrans;
	MatrixXd lCooWGS84XYZ = lCoordTrans.BLH2XYZ(lCooWGS84, WGS84);
	std::cout << "X Y Z ：" << std::fixed << lCooWGS84XYZ << std::endl;
	MatrixXd lCooCGCS2000BLH = lCoordTrans.XYH2BLH(lCooCGCS2000, CGCS2000, true);
	std::cout << "B L H：" << std::fixed << lCooCGCS2000BLH << std::endl;
	MatrixXd lCooCGCS2000XYZ = lCoordTrans.BLH2XYZ(lCooCGCS2000BLH, CGCS2000);
	std::cout << "X'Y'Z'：" << std::fixed << lCooCGCS2000XYZ << std::endl;

	Para7 lPara7;
	RowVectorXd lRMS = lPara7.cal7Args(lCooWGS84XYZ, lCooCGCS2000XYZ);
	std::cout << "七参数计算结果：" << std::endl;
	std::cout << "ΔX:" << lPara7.mPara7[0] << " m" << std::endl;
	std::cout << "ΔY:" << lPara7.mPara7[1] << " m" << std::endl;
	std::cout << "ΔZ:" << lPara7.mPara7[2] << " m" << std::endl;
	std::cout << "θX:" << lCoordTrans.radAng2DmsDeg(lPara7.mPara7[3]) << std::endl;
	std::cout << "θY:" << lCoordTrans.radAng2DmsDeg(lPara7.mPara7[4]) << std::endl;
	std::cout << "θZ:" << lCoordTrans.radAng2DmsDeg(lPara7.mPara7[5]) << std::endl;
	std::cout << " m:" << lPara7.mPara7[6] / 1e-6 << " ppm" << std::endl;
	std::cout << "中误差：" << std::fixed << lRMS << std::endl;

#endif

#ifdef CooConvPara4

	MatrixXd lCooWGS84 = MatrixXd::Constant(2, 2, 0.0);
	lCooWGS84 << 4312820.897, 513670.931,
		4314058.425, 514231.984;
	MatrixXd lCooBJ54 = MatrixXd::Constant(2, 2, 0.0);
	lCooBJ54 << 4312816.917, 513553.719,
		4314054.440, 514114.777;

	Para4 lPara4;
	RowVectorXd lRMS = lPara4.cal4Args(lCooWGS84, lCooBJ54);
	printf("四参数计算结果：\n");
	printf("ΔX: %.12f m\n", lPara4.mPara4(0));
	printf("ΔY: %.12f m\n", lPara4.mPara4(1));
	printf(" α: %.12f\n", lPara4.mPara4(2));
	printf(" K: %.12f\n", lPara4.mPara4(3));
	std::cout << "中误差：" << std::fixed << lRMS << std::endl;
	Vector2d lConvPoint = lPara4.cooConv(Vector2d(4306670.108, 511168.332));
	std::cout << "转换结果：" << std::fixed << lConvPoint.transpose() << std::endl;

#endif
}
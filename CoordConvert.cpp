#include <iostream>
#include "Para7.h"
#include "Para4.h"
#include "GeoCoordTrans.h"

#define CooConvPara7

using namespace Eigen;

void main()
{
#ifdef CooConvPara7

	// ��������������ƽ�������P157 ʾ������
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

	Para7 lPara7;
	RowVectorXd lRMS = lPara7.cal7Args(lCooWGS84, lCooBJ54);
	std::cout << "�߲�����������" << std::endl;
	std::cout << "��X:" << lPara7.mPara7[0] << " m" << std::endl;
	std::cout << "��Y:" << lPara7.mPara7[1] << " m" << std::endl;
	std::cout << "��Z:" << lPara7.mPara7[2] << " m" << std::endl;
	std::cout << "��X:" << GeoCoordTrans::radAng2DmsDeg(lPara7.mPara7[3]) << std::endl;
	std::cout << "��Y:" << GeoCoordTrans::radAng2DmsDeg(lPara7.mPara7[4]) << std::endl;
	std::cout << "��Z:" << GeoCoordTrans::radAng2DmsDeg(lPara7.mPara7[5]) << std::endl;
	std::cout << " m:" << lPara7.mPara7[6] / 1e-6 << " ppm" << std::endl;
	std::cout << "����" << std::fixed << lRMS << std::endl;

#endif

#ifdef CooConvPara4

	// http://t.csdnimg.cn/Xr8b5 ʾ������
	MatrixXd lCooWGS84 = MatrixXd::Constant(2, 2, 0.0);
	lCooWGS84 << 4312820.897, 513670.931,
		4314058.425, 514231.984;
	MatrixXd lCooBJ54 = MatrixXd::Constant(2, 2, 0.0);
	lCooBJ54 << 4312816.917, 513553.719,
		4314054.440, 514114.777;

	Para4 lPara4;
	RowVectorXd lRMS = lPara4.cal4Args(lCooWGS84, lCooBJ54);
	printf("�Ĳ�����������\n");
	printf("��X: %.12f m\n", lPara4.mPara4(0));
	printf("��Y: %.12f m\n", lPara4.mPara4(1));
	printf(" ��: %.12f\n", lPara4.mPara4(2));
	printf(" K: %.12f\n", lPara4.mPara4(3));
	std::cout << "����" << std::fixed << lRMS << std::endl;
	Vector2d lConvPoint = lPara4.cooConv(Vector2d(4306670.108, 511168.332));
	std::cout << "ת�������" << std::fixed << lConvPoint.transpose() << std::endl;

#endif
}
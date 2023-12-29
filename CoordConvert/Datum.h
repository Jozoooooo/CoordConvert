/*********************************************************************
 * @file   Datum.h
 * @brief  ������������
 * @author Jozoooooo
 * @date   April 2023
 *********************************************************************/

#pragma once

#include <cmath>

/**
 * @brief ������������.
 */
class Datum
{
  public:
    /**
     * @brief ���������幹�캯��.
     * @param _a ������
     * @param _f ����
     */
    Datum(double _a, double _f) : a(_a), f(_f)
    {
        b = a * (1 - f);
        e1 = sqrt(a * a - b * b) / a;
        e2 = sqrt(a * a - b * b) / b;
        es1 = e1 * e1;
        es2 = e2 * e2;
    }

    /**
     * @brief ����ĳγ��î��Ȧ���ʰ뾶.
     * @param B γ�� ����
     * @return î��Ȧ�뾶
     */
    double getN(double B)
    {
        return a / sqrt(1.0 - es1 * sin(B) * sin(B));
    }

    /**
     * @brief ����ĳγ������Ȧ���ʰ뾶.
     * @param B γ�� ����
     * @return ����Ȧ�뾶
     */
    double getM(double B)
    {
        return a * (1 - es1) / pow(sqrt(1.0 - es1 * sin(B) * sin(B)), 3);
    }

    /**
     * @brief �������������߻���.
     * @param B γ�� ����
     * @return ���������߻���X
     */
    double getX(double B)
    {
        double cA = 1 + 3 * es1 / 4 + 45 * pow(es1, 2) / 64 + 175 * pow(es1, 3) / 256 + 11025 * pow(es1, 4) / 16384 +
                    43659 * pow(es1, 5) / 65536 + 693693 * pow(es1, 6) / 1048576;
        double cB = 3 * es1 / 8 + 15 * pow(es1, 2) / 32 + 525 * pow(es1, 3) / 1024 + 2205 * pow(es1, 4) / 4096 +
                    72765 * pow(es1, 5) / 131072 + 297297 * pow(es1, 6) / 524288;
        double cC = 15 * pow(es1, 2) / 256 + 105 * pow(es1, 3) / 1024 + 2205 * pow(es1, 4) / 16384 +
                    10395 * pow(es1, 5) / 65536 + 1486485 * pow(es1, 6) / 8388608;
        double cD = 35 * pow(es1, 3) / 3072 + 105 * pow(es1, 4) / 4096 + 10395 * pow(es1, 5) / 262144 +
                    55055 * pow(es1, 6) / 1048576;
        double cE = 315 * pow(es1, 4) / 131072 + 3465 * pow(es1, 5) / 524288 + 99099 * pow(es1, 6) / 8388608;
        double cF = 693 * pow(es1, 5) / 1310720 + 9009 * pow(es1, 6) / 5242800;
        double cG = 1001 * pow(es1, 6) / 8388608;
        return a * (1 - es1) * (cA * B - cB * sin(2 * B) + cC * sin(4 * B) - 
            cD * sin(6 * B) + cE * sin(8 * B) - cF * sin(10 * B) + cG * sin(12 * B));
    }

    /**
     * @brief ����ĳ�����괦�׵�γ��.
     * @param x ������ ��
     * @return �׵�γ��Bf
     */
    double getBf(double x)
    {
        double cA = 1 + 3 * es1 / 4 + 45 * pow(es1, 2) / 64 + 175 * pow(es1, 3) / 256 + 11025 * pow(es1, 4) / 16384 +
                    43659 * pow(es1, 5) / 65536 + 693693 * pow(es1, 6) / 1048576;
        double cB = 3 * es1 / 8 + 15 * pow(es1, 2) / 32 + 525 * pow(es1, 3) / 1024 + 2205 * pow(es1, 4) / 4096 +
                    72765 * pow(es1, 5) / 131072 + 297297 * pow(es1, 6) / 524288;
        double cC = 15 * pow(es1, 2) / 256 + 105 * pow(es1, 3) / 1024 + 2205 * pow(es1, 4) / 16384 +
                    10395 * pow(es1, 5) / 65536 + 1486485 * pow(es1, 6) / 8388608;
        double cD = 35 * pow(es1, 3) / 3072 + 105 * pow(es1, 4) / 4096 + 10395 * pow(es1, 5) / 262144 +
                    55055 * pow(es1, 6) / 1048576;
        double cE = 315 * pow(es1, 4) / 131072 + 3465 * pow(es1, 5) / 524288 + 99099 * pow(es1, 6) / 8388608;
        double cF = 693 * pow(es1, 5) / 1310720 + 9009 * pow(es1, 6) / 5242800;
        double cG = 1001 * pow(es1, 6) / 8388608;

        double B0 = x / (a * (1 - es1) * cA);
        double Bf = 0.0, delta = abs(B0 - Bf);
        while (delta > 4.8e-11)
        {
            Bf = B0;
            double FB1 = a * (1 - es1) * (cA * Bf - cB * sin(2 * Bf) + cC * sin(4 * Bf) - 
                cD * sin(6 * Bf) + cE * sin(8 * Bf) - cF * sin(10 * Bf) + cG * sin(12 * Bf));
            double FB2 = a * (1 - es1) * (cA - 2 * cB * cos(2 * Bf) + 4 * cC * cos(4 * Bf) - 
                6 * cD * cos(6 * Bf) + 8 * cE * cos(8 * Bf) - 10 * cF * cos(10 * Bf) + 12 * cG * cos(12 * Bf));
            B0 = Bf + (x - FB1) / FB2;
            delta = abs(B0 - Bf);
        }
        return Bf;
    }

    /**
     * @brief ������.
     */
    double a;

    /**
     * @brief �̰���.
     */
    double b;

    /**
     * @brief ����.
     */
    double f;

    /**
     * @brief ��һƫ����.
     */
    double e1;

    /**
     * @brief �ڶ�ƫ����.
     */
    double e2;

    /**
     * @brief ��һƫ���ʵ�ƽ��.
     */
    double es1;

    /**
     * @brief �ڶ�ƫ���ʵ�ƽ��.
     */
    double es2;
};

static Datum KARSS = Datum(6378245.0, 1 / 298.3);             // ����54: Krassovsky, 1942.
static Datum IAG75 = Datum(6378140.0, 1 / 298.257);           // ����80: IAG 1975.
static Datum WGS84 = Datum(6378137.0, 1 / 298.257223563);     // WGS 84
static Datum CGCS2000 = Datum(6378137.0, 1 / 298.257222101);  // CGCS 2000
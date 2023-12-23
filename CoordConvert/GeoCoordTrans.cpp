#include "GeoCoordTrans.h"

Vector3d GeoCoordTrans::BLH2XYZ(Vector3d pPoint, Datum pDatum)
{
    double B = pPoint(0) * DEG_TO_RAD;
    double L = pPoint(1) * DEG_TO_RAD;
    double H = pPoint(2);

    double N = pDatum.getN(B);

    double x = (N + H) * cos(B) * cos(L);
    double y = (N + H) * cos(B) * sin(L);
    double z = (N * (1 - pDatum.es1) + H) * sin(B);

    return Vector3d(x, y, z);
}

Vector3d GeoCoordTrans::XYZ2BLH(Vector3d pPoint, Datum pDatum)
{
    double x = pPoint(0);
    double y = pPoint(1);
    double z = pPoint(2);

    double preB = atan(z / sqrt(x * x + y * y));
    double resB = 0, resN = 0, t = 1;

    while (t > 0.000000000001)
    {
        resN = pDatum.getN(preB);
        resB = atan((z + resN * pDatum.es1 * sin(preB)) / sqrt(x * x + y * y));
        t = fabs(resB - preB);
        preB = resB;
    }

    double B = resB * RAD_TO_DEG;
    double L = atan2(y, x) * RAD_TO_DEG;
    double H = sqrt(x * x + y * y) / cos(resB) - resN;

    return Vector3d(B, L, H);
}

Vector2d GeoCoordTrans::BL2XY(Vector2d pPoint, Datum pDatum)
{
    double B = pPoint(0) * DEG_TO_RAD;
    double L = pPoint(1);

    int bN = mIs3Degree ? round(L / 3) : floor(L / 6 + 1);  // 带号
    int l0 = mIs3Degree ? 3 * bN : 6 * bN - 3;              // 中央经线
    double l = (L - l0) * DEG_TO_RAD;                       // 经差
    double X = pDatum.getX(B);                              // 子午线弧长
    double N = pDatum.getN(B);                              // 卯酉圈曲率半径
    double t = tan(B);                                      // tan B
    double ns = pDatum.es2 * cos(B) * cos(B);               // η^2
    double m = cos(B) * l;                                  // cos B * l

    double x = X + N * t * m * m * (0.5 + (5 - t * t + 9 * ns + 4 * ns * ns) * m * m / 24 + 
        (61 - 58 * t * t + pow(t, 4)) * pow(m, 4) / 720);
    double y = N * m * (1 + (1 - t * t + ns) * m * m / 6 + (5 - 18 * t * t + pow(t, 4) + 
        14 * ns - 58 * ns * t * t) * pow(m, 4) / 120);

    y = mIsUniCoord ? y + 500000 + bN * 1000000.0 : y;

    return Vector2d(x, y);
}

Vector2d GeoCoordTrans::XY2BL(Vector2d pPoint, Datum pDatum)
{
    double x = pPoint(0);
    double y = pPoint(1);

    int bN = mIsUniCoord ? y / 1000000.0 : 0;          // 带号
    y = mIs3Degree ? y - bN * 1000000.0 - 500000 : y;  // 修正的y坐标
    int l0 = mIs3Degree ? 3 * bN : 6 * bN - 3;         // 中央经线
    double Bf = pDatum.getBf(x);                       // 底点纬度
    double Mf = pDatum.getM(Bf);                       // 子午圈曲率半径
    double Nf = pDatum.getN(Bf);                       // 卯酉圈曲率半径
    double tf = tan(Bf);                               // tan B
    double nfs = pDatum.es2 * cos(Bf) * cos(Bf);       // η^2

    double B = Bf - tf / (2 * Mf) * y * (y / Nf) * (1 - (5 + 3 * tf * tf + nfs - 9 * nfs * tf * tf) * 
        pow(y / Nf, 2) / 12 + (61 + 90 * tf * tf + 45 * pow(tf, 4)) * pow(y / Nf, 4) / 360);
    double L = y / Nf / cos(Bf) * (1 - (1 + 2 * tf * tf + nfs) * pow(y / Nf, 2) / 6 + (5 + 28 * tf * tf + 
        24 * pow(tf, 4) + 6 * nfs + 8 * nfs * tf * tf) * pow(y / Nf, 4) / 120);
    B *= RAD_TO_DEG;
    L = L * RAD_TO_DEG + l0;

    return Vector2d(B, L);
}

Vector3d GeoCoordTrans::BLH2XYH(Vector3d pPoint, Datum pDatum)
{
    Vector2d lPointXY = BL2XY(Vector2d(pPoint(0), pPoint(1)), pDatum);
    return Vector3d(lPointXY(0), lPointXY(1), pPoint(2));
}

Vector3d GeoCoordTrans::XYH2BLH(Vector3d pPoint, Datum pDatum)
{
    Vector2d lPointBL = XY2BL(Vector2d(pPoint(0), pPoint(1)), pDatum);
    return Vector3d(lPointBL(0), lPointBL(1), pPoint(2));
}

MatrixXd GeoCoordTrans::BLH2XYZ(MatrixXd pPoints, Datum pDatum)
{
    MatrixXd lPoints = MatrixXd::Constant(pPoints.rows(), 3, 0.0);
    for (int i = 0; i < pPoints.rows(); i++)
    {
        Vector3d lPointBLH = pPoints.row(i);
        Vector3d lPointXYZ = BLH2XYZ(lPointBLH, pDatum);
        lPoints.row(i) = lPointXYZ;
    }
    return lPoints;
}

MatrixXd GeoCoordTrans::XYZ2BLH(MatrixXd pPoints, Datum pDatum)
{
    MatrixXd lPoints = MatrixXd::Constant(pPoints.rows(), 3, 0.0);
    for (int i = 0; i < pPoints.rows(); i++)
    {
        Vector3d lPointXYZ = pPoints.row(i);
        Vector3d lPointBLH = XYZ2BLH(lPointXYZ, pDatum);
        lPoints.row(i) = lPointBLH;
    }
    return lPoints;
}

MatrixXd GeoCoordTrans::BL2XY(MatrixXd pPoints, Datum pDatum)
{
    MatrixXd lPoints = MatrixXd::Constant(pPoints.rows(), 2, 0.0);
    for (int i = 0; i < pPoints.rows(); i++)
    {
        Vector2d lPointBL = pPoints.row(i);
        Vector2d lPointXY = BL2XY(lPointBL, pDatum);
        lPoints.row(i) = lPointXY;
    }
    return lPoints;
}

MatrixXd GeoCoordTrans::XY2BL(MatrixXd pPoints, Datum pDatum)
{
    MatrixXd lPoints = MatrixXd::Constant(pPoints.rows(), 2, 0.0);
    for (int i = 0; i < pPoints.rows(); i++)
    {
        Vector2d lPointXY = pPoints.row(i);
        Vector2d lPointBL = XY2BL(lPointXY, pDatum);
        lPoints.row(i) = lPointBL;
    }
    return lPoints;
}

MatrixXd GeoCoordTrans::BLH2XYH(MatrixXd pPoints, Datum pDatum)
{
    MatrixXd lPoints = MatrixXd::Constant(pPoints.rows(), 3, 0.0);
    for (int i = 0; i < pPoints.rows(); i++)
    {
        Vector3d lPointBLH = pPoints.row(i);
        Vector3d lPointXYH = BLH2XYH(lPointBLH, pDatum);
        lPoints.row(i) = lPointXYH;
    }
    return lPoints;
}

MatrixXd GeoCoordTrans::XYH2BLH(MatrixXd pPoints, Datum pDatum)
{
    MatrixXd lPoints = MatrixXd::Constant(pPoints.rows(), 3, 0.0);
    for (int i = 0; i < pPoints.rows(); i++)
    {
        Vector3d lPointXYH = pPoints.row(i);
        Vector3d lPointBLH = XYH2BLH(lPointXYH, pDatum);
        lPoints.row(i) = lPointBLH;
    }
    return lPoints;
}

std::string GeoCoordTrans::radAng2DmsDeg(double pAngle)
{
    double degree = pAngle * RAD_TO_DEG;
    int d = (int)degree;
    degree = std::abs((degree - d) * 60);
    int m = (int)degree;
    degree = std::abs((degree - m) * 60);

    std::stringstream ss;
    if (pAngle < 0)
        ss << "-";
    if (d != 0)
        ss << d << "°";
    if (m != 0 || d != 0)
        ss << m << "'";
    ss << std::fixed << degree << "\"";
    return ss.str();
}

std::string GeoCoordTrans::decDeg2DmsDeg(double pAngle)
{
    int d = (int)pAngle;
    pAngle = std::abs((pAngle - d) * 60);
    int m = (int)pAngle;
    pAngle = std::abs((pAngle - m) * 60);
    if (pAngle >= 59.9999995)
    {
        pAngle = 0;
        m += 1;
    }

    std::stringstream ss;
    if (pAngle < 0)
        ss << "-";
    if (d != 0)
        ss << d << "°";
    if (m != 0 || d != 0)
        ss << m << "'";
    ss << std::fixed << pAngle << "\"";
    return ss.str();
}
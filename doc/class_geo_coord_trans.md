# `GeoCoordTrans` <a id="class_geo_coord_trans"></a>

地理坐标转换类.

## 成员列表

 成员                                                                                                                                          | 描述                         
---------------------------------------------------------------------------------------------------------------------------------------------|----------------------------
 public bool [`mIs3Degree`](#class_geo_coord_trans_1a871d427225ae1b02564b577fea6f0a85)                                                       | 是否投影到三度带.                  
 public bool [`mIsUniCoord`](#class_geo_coord_trans_1a5fa811fc4313389130f50386dbe5ef6e)                                                      | 是否转为通用坐标（加代号 + 加500公里后坐标）. 
 public Vector3d [`BLH2XYZ`](#class_geo_coord_trans_1a3090e202cc3f3cdf95f6946f4c4829df) (Vector3d pPoint, [`Datum`](class_datum.md) pDatum)  | 大地坐标转空间直角坐标.               
 public Vector3d [`XYZ2BLH`](#class_geo_coord_trans_1af633c061f322e1ee7d9d98f3e4734785) (Vector3d pPoint, [`Datum`](class_datum.md) pDatum)  | 空间直角坐标转大地坐标.               
 public Vector2d [`BL2XY`](#class_geo_coord_trans_1a5bac6ebad4380026f16d3e18873dbffa) (Vector2d pPoint, [`Datum`](class_datum.md) pDatum)    | 高斯正算.                      
 public Vector2d [`XY2BL`](#class_geo_coord_trans_1ac29a788daf318d6b78eec32875cd3232) (Vector2d pPoint, [`Datum`](class_datum.md) pDatum)    | 高斯反算.                      
 public Vector3d [`BLH2XYH`](#class_geo_coord_trans_1a32d7b285556ab852d942c6067d7d1e1e) (Vector3d pPoint, [`Datum`](class_datum.md) pDatum)  | 高斯正算三维大地坐标点.               
 public Vector3d [`XYH2BLH`](#class_geo_coord_trans_1ae1ed715fdf321c9aa39381154fcd2f3c) (Vector3d pPoint, [`Datum`](class_datum.md) pDatum)  | 高斯反算带大地高的直角坐标点.            
 public MatrixXd [`BLH2XYZ`](#class_geo_coord_trans_1af7d0b1ed63b7fc4e2f2810f2f6ab6e45) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum) | 大地坐标点集转空间直角坐标点集.           
 public MatrixXd [`XYZ2BLH`](#class_geo_coord_trans_1aa79bde5213ef831f2d480145d2c2fa30) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum) | 空间直角坐标点集转大地坐标点集.           
 public MatrixXd [`BL2XY`](#class_geo_coord_trans_1acc7ef38748b98f104f407af9f14ab903) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum)   | 高斯正算大地坐标点集.                
 public MatrixXd [`XY2BL`](#class_geo_coord_trans_1af45f9abea8675720401c530430ff155d) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum)   | 高斯反算直角坐标点集.                
 public MatrixXd [`BLH2XYH`](#class_geo_coord_trans_1ac46ef6abd4c44dbc27a36c80a1efc327) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum) | 高斯正算三维大地坐标点集.              
 public MatrixXd [`XYH2BLH`](#class_geo_coord_trans_1af6348d485af696066943474119ce22f3) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum) | 高斯反算带大地高的直角坐标点集.           

## 成员变量

### public bool [`mIs3Degree`](#class_geo_coord_trans_1a871d427225ae1b02564b577fea6f0a85)<a id="class_geo_coord_trans_1a871d427225ae1b02564b577fea6f0a85"></a>

是否投影到三度带.

### public bool [`mIsUniCoord`](#class_geo_coord_trans_1a5fa811fc4313389130f50386dbe5ef6e)<a id="class_geo_coord_trans_1a5fa811fc4313389130f50386dbe5ef6e"></a>

是否转为通用坐标（加代号 + 加500公里后坐标）.

## 成员函数

### public Vector3d [`BLH2XYZ`](#class_geo_coord_trans_1a3090e202cc3f3cdf95f6946f4c4829df) (Vector3d pPoint, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1a3090e202cc3f3cdf95f6946f4c4829df"></a>

大地坐标转空间直角坐标.

#### 参数

* `pPoint` 大地坐标 (大地纬度B, 大地经度L, 大地高H)

* `pDatum` 地球椭球体

#### 返回值

空间直角坐标 (北方向X, 东方向Y, 高程坐标Z)

### public Vector3d [`XYZ2BLH`](#class_geo_coord_trans_1af633c061f322e1ee7d9d98f3e4734785) (Vector3d pPoint, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1af633c061f322e1ee7d9d98f3e4734785"></a>

空间直角坐标转大地坐标.

#### 参数

* `pPoint` 空间直角坐标 (北方向X, 东方向Y, 高程坐标Z)

* `pDatum` 地球椭球体

#### 返回值

大地坐标 (大地纬度B, 大地经度L, 大地高H)

### public Vector2d [`BL2XY`](#class_geo_coord_trans_1a5bac6ebad4380026f16d3e18873dbffa) (Vector2d pPoint, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1a5bac6ebad4380026f16d3e18873dbffa"></a>

高斯正算.

#### 参数

* `pPoint` 大地坐标 (大地纬度B, 大地经度L)

* `pDatum` 地球椭球体

#### 返回值

高斯平面直角坐标 (x, y)

### public Vector2d [`XY2BL`](#class_geo_coord_trans_1ac29a788daf318d6b78eec32875cd3232) (Vector2d pPoint, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1ac29a788daf318d6b78eec32875cd3232"></a>

高斯反算.

#### 参数

* `pPoint` 高斯平面直角坐标 (x, y)

* `pDatum` 地球椭球体

#### 返回值

大地坐标 (大地纬度B, 大地经度L)

### public Vector3d [`BLH2XYH`](#class_geo_coord_trans_1a32d7b285556ab852d942c6067d7d1e1e) (Vector3d pPoint, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1a32d7b285556ab852d942c6067d7d1e1e"></a>

高斯正算三维大地坐标点.

#### 参数

* `pPoint` 大地坐标 (大地纬度B, 大地经度L, 大地高H)

* `pDatum` 地球椭球体

#### 返回值

高斯平面直角坐标 + 大地高 (x, y, H)

### public Vector3d [`XYH2BLH`](#class_geo_coord_trans_1ae1ed715fdf321c9aa39381154fcd2f3c) (Vector3d pPoint, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1ae1ed715fdf321c9aa39381154fcd2f3c"></a>

高斯反算带大地高的直角坐标点.

#### 参数

* `pPoint` 高斯平面直角坐标 + 大地高 (x, y, H)

* `pDatum` 地球椭球体

#### 返回值

大地坐标 (大地纬度B, 大地经度L, 大地高H)

### public MatrixXd [`BLH2XYZ`](#class_geo_coord_trans_1af7d0b1ed63b7fc4e2f2810f2f6ab6e45) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1af7d0b1ed63b7fc4e2f2810f2f6ab6e45"></a>

大地坐标点集转空间直角坐标点集.

#### 参数

* `pPoints` 大地坐标点集 {(大地纬度B, 大地经度L, 大地高H)}

* `pDatum` 地球椭球体

#### 返回值

空间直角坐标点集 {(北方向X, 东方向Y, 高程坐标Z)}

### public MatrixXd [`XYZ2BLH`](#class_geo_coord_trans_1aa79bde5213ef831f2d480145d2c2fa30) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1aa79bde5213ef831f2d480145d2c2fa30"></a>

空间直角坐标点集转大地坐标点集.

#### 参数

* `pPoints` 空间直角坐标点集 {(北方向X, 东方向Y, 高程坐标Z)}

* `pDatum` 地球椭球体

#### 返回值

大地坐标点集 {(大地纬度B, 大地经度L, 大地高H)}

### public MatrixXd [`BL2XY`](#class_geo_coord_trans_1acc7ef38748b98f104f407af9f14ab903) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1acc7ef38748b98f104f407af9f14ab903"></a>

高斯正算大地坐标点集.

#### 参数

* `pPoints` 大地坐标点集 {(大地纬度B, 大地经度)}

* `pDatum` 地球椭球体

#### 返回值

高斯平面直角坐标 {(x, y)}

### public MatrixXd [`XY2BL`](#class_geo_coord_trans_1af45f9abea8675720401c530430ff155d) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1af45f9abea8675720401c530430ff155d"></a>

高斯反算直角坐标点集.

#### 参数

* `pPoints` 高斯平面直角坐标 {(x, y)}

* `pDatum` 地球椭球体

#### 返回值

大地坐标点集 {(大地纬度B, 大地经度L)}

### public MatrixXd [`BLH2XYH`](#class_geo_coord_trans_1ac46ef6abd4c44dbc27a36c80a1efc327) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1ac46ef6abd4c44dbc27a36c80a1efc327"></a>

高斯正算三维大地坐标点集.

#### 参数

* `pPoints` 大地坐标点集 {(大地纬度B, 大地经度L, 大地高H)}

* `pDatum` 地球椭球体

#### 返回值

高斯平面直角坐标 + 大地高点集 {(x, y, H)}

### public MatrixXd [`XYH2BLH`](#class_geo_coord_trans_1af6348d485af696066943474119ce22f3) (MatrixXd pPoints, [`Datum`](class_datum.md) pDatum)<a id="class_geo_coord_trans_1af6348d485af696066943474119ce22f3"></a>

高斯反算带大地高的直角坐标点集.

#### 参数

* `pPoints` 高斯平面直角坐标 + 大地高点集 {(x, y, H)}

* `pDatum` 地球椭球体

#### 返回值

大地坐标点集 {(大地纬度B, 大地经度L, 大地高H)}

Generated by [Moxygen](https://sourcey.com/moxygen)
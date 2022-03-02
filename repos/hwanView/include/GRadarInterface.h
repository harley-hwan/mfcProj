#pragma once

#ifdef GRADARDLL_EXPORTS
#define GRADARDLL_API __declspec(dllexport)
#else
#define GRADARDLL_API __declspec(dllimport)
#endif

enum iSensorDataType : int
{
	iType_None = 0,
	iType_Idle,
	iType_4MS,
	iType_32MS,
};
enum iShotDataState : int
{
	iShotState_ShotIdle = 0,
	iShotState_Ready,
	iShotState_ShotStart,
	iShotState_ShotComplete,
};

struct Vector3f
{
	float x;
	float y;
	float z;
};

struct iRadarData
{
#if 0 
	int shotNum;
	float ballSpeed;
	float launchAngle;
	float directionAngle;
	float backSpin;
	float sideSpin;
	float windDirection;
	float windAmount;
	float clubSpeed;
#else

	int shotNum;

	float ballSpeed;
	float launchAngle;
	float directionAngle;

	float ballSpeed_avg;
	float ballSpeed_max;

	//최종
	float backSpin;
	float sideSpin;
	float spinRate;
	float spinAxis;

	// 클럽
	float backSpin_C;
	float sideSpin_C;
	float spinRate_C;
	float spinAxis_C;

	// 볼
	float backSpin_B;
	float sideSpin_B;
	float spinRate_B;
	float spinAxis_B;

	// 피팅
	float backSpin_F;
	float sideSpin_F;
	float spinRate_F;
	float spinAxis_F;

	// 클럽+피팅 (야외 용도)	
	// Measure value + Calculated value + Fitting Value
	float backSpin_MCF1;
	float sideSpin_MCF1;
	float spinRate_MCF1;
	float spinAxis_MCF1;

	float backSpin_MCF2;
	float sideSpin_MCF2;
	float spinRate_MCF2;
	float spinAxis_MCF2;

	float backSpin_Final;
	float sideSpin_Final;
	float spinRate_Final;
	float spinAxis_Final;

	float windDirection;
	float windAmount;
	float clubSpeed;
	float attackAngle;
	float clubPath;
	float attackAngle_R;
	float clubPath_R;
	float swingPlane;
	float swingDirection;

	float Carry;
	float Total;

	float Carry_C;		// 클럽
	float Carry_B;		// 볼
	float Carry_F;		// 피팅

	float carry_x;
	float carry_y;

	// Physics Results
	float dynamicLoft;
	float spinLoft;
	float faceAngle;
	float faceToPath;

	float attackAngle_C;
	float clubPath_C;
	float attackAngle_M;
	float clubPath_M;
	float attackAngle_MC;
	float clubPath_MC;
	float attackAngle_B;
	float clubPath_B;

	float attackAngle_MCF1;
	float clubPath_MCF1;
	float attackAngle_MCF2;
	float clubPath_MCF2;

	float club_Polyfit_4th_TopView_Coef[5];
	float club_Polyfit_4th_SideView_Coef[5];

	float attackAngle_Calibrated;
	float clubPath_Calibrated;

	float BallStartCount;
	float ImpactTimeCount;
	Vector3f m_ImpactPosition;
	Vector3f m_CenterPoint;
	float m_HeadPeakAvg;

	float Polyfit_Carrry;
	float Polyfit_MaxH;
	float Polyfit_MaxW;
	float Polyfit_R2;

	float TimeMeasure[5];
	int BallType_i;

	int nSensor_Mode;

#endif


};

struct iData_Client									// GRadar_SignalProcMain.h Define참고
{
	int dataIndex;	// count
	int Ball_Index;	// 2017-12-13 추가
	int shotNum;
	int IsBallFounded;


	unsigned short Amplitude[3][512];

	float Phase_original[2];
	float Phase_modified[2];

	float Distance_XYZ[3];
};

extern "C"
{
GRADARDLL_API double Radar_Add(double a, double b);
GRADARDLL_API bool Send_DummySignal(int type);
GRADARDLL_API bool Load_LocalData(CString path);


GRADARDLL_API double GPhy_GetVersion();
GRADARDLL_API bool Radar_Open(int Mode);
GRADARDLL_API bool RadarViewer_Open(bool viewer);
GRADARDLL_API bool Radar_Close();

GRADARDLL_API iShotDataState Get_ShotState();
GRADARDLL_API iRadarData Get_ShotData();
GRADARDLL_API bool Get_ShotDataPointer(iRadarData *ret);

GRADARDLL_API int Get_ViewerDataIndex();
GRADARDLL_API int Get_ViewerDataShotNum();										//2017-12-13 이승훈 : GraphViewer 용 데이터 추가 
GRADARDLL_API int Get_ViewerDataPointer(int index, iData_Client *ret);

GRADARDLL_API bool Send_WindCondition(float windAmount, float windDirection);
GRADARDLL_API bool Send_TargetHeight(float targetHeight);
GRADARDLL_API bool Send_SensorDegree(float sensorDegree);
GRADARDLL_API float Get_SensorDegree();

}

#pragma once

#ifdef GPHYDLL_EXPORTS
#define GPHYDLL_API __declspec(dllexport)
#else
#define GPHYDLL_API __declspec(dllimport)
#endif

extern "C"
{
	GPHYDLL_API double GPhy_GetVersion();
	GPHYDLL_API void GPhy_SetSpeed(double vta);
	GPHYDLL_API void GPhy_SetLaunchAngle(double theta);
	GPHYDLL_API void GPhy_SetDirectionAngle(double phi);
	GPHYDLL_API void GPhy_SetBS(double bs);
	GPHYDLL_API void GPhy_SetSS(double ss);
	GPHYDLL_API void GPhy_SetWindCondition(double wc);
	GPHYDLL_API void GPhy_SetWindDirection(double wdcw);
	GPHYDLL_API void GPhy_SetTargetHeight(double height);
	GPHYDLL_API void GPhy_SetDeltaT(double dt);
	GPHYDLL_API void GPhy_SetClubSpeed(double hs);

	GPHYDLL_API int GPhy_GetCarryData(float *ret_x, float *ret_y, float *ret_z);
	GPHYDLL_API int GPhy_GetSimulation(float *ret_x, float *ret_y, float *ret_z ,int *carryIndex);
	GPHYDLL_API int GPhy_GetClubData(double *dlaa, double *laaa, double *aa, double *dl, double *facd, double *cd, double *fa);
}

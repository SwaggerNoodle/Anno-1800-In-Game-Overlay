#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

enum {
	ID_BTN_Close = 1000,
        ID_BTN_FarmerBlockInc = 1001,
        ID_BTN_FarmerBlockDec = 1002,

        ID_FRM_SetHousingFrame = 2001,
        ID_FRM_AdjustHousingFrame = 2002,
        ID_FRM_ResourceReqFrame = 2003,

        ID_FLD_HousingWidth = 3001,
        ID_FLD_HousingLength = 3002,

        ID_LBL_HousingWidth = 4001,
        ID_LBL_HousingLength = 4002,

        ID_SPN_HousingWidth = 5001,
        ID_SPN_HousingLength = 5002,

        ID_DSP_Fish = 6001,
        ID_DSP_Clothes = 6002,
        ID_DSP_Schnnaps = 6003
};


typedef struct CommandInfo{
        int controlId;
        int notifyCode;
        HWND controlHandle;
} CommandInfo;
typedef struct SpinnerConfig{
        HWND childHWND;
        int minVal;
        int maxVal;
        int initialVal;
} SpinnerConfig;


typedef struct HousingDimensions{
	int width;
	int height;
	int houseNum;
} HousingDimensions;
typedef struct HousingCount{
	int farmerHCount;
	int workerHCount;
	int artisanHCount;
	int engineerHCount;
	int InvestorHCount;
} HousingCount;


typedef struct NeedRequirements{
	int fish;
	int clothes;
	int schnapps;
} NeedRequirements;


typedef struct IslandData{
	HousingDimensions islandBlockSize;
	HousingCount islandPopulation;
	NeedRequirements islandNeeds;
} IslandData;
typedef struct AppData{
	IslandData Capital;
	IslandData island1;
	IslandData island2;
	IslandData island3;
} AppData;


#endif

















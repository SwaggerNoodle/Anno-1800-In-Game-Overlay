#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/*
 * X-Pos
 * Y-Pos
 * Width
 * Height
 */

enum {
	ID_FRM_SetHousingFrame = 1001,
        ID_FRM_AdjustHousingFrame = 1002,
        ID_FRM_ResourceReqFrame = 1003,
        ID_FRM_IslandSelectFrame = 1004,


	ID_BTN_Close = 2001,
        ID_BTN_FarmerBlockInc = 2002,
        ID_BTN_FarmerBlockDec = 2003,
	ID_BTN_WorkerBlockInc = 2004,
	ID_BTN_WorkerBlockDec = 2005,

	ID_BTN_CapitalIslandSel = 2101,
	ID_BTN_Island1Sel = 2102,
	ID_BTN_Island2Sel = 2103,
	ID_BTN_Island3Sel = 2104,


        ID_FLD_HousingWidth = 3001,
        ID_FLD_HousingLength = 3002,


        ID_LBL_HousingWidth = 4001,
        ID_LBL_HousingLength = 4002,
	ID_LBL_DragBar = 4100,


        ID_SPN_HousingWidth = 5001,
        ID_SPN_HousingLength = 5002,


        ID_DSP_Fish = 6001,
        ID_DSP_Clothes = 6002,
        ID_DSP_Schnnaps = 6003
};
enum {

	GRID_SetHousingFrameXPos = 15,
	GRID_SetHousingFrameYPos = 10,

	GRID_AdjustHousingFrameXPos = 15,
	GRID_AdjustHousingFrameYPos = 110,

	GRID_ResourceReqFrameXPos = 15,
	GRID_ResourceReqFrameYPos = 240,

	GRID_IslandSelectFrameXPos = 145,
	GRID_IslandSelectFrameYPos = 10

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
	int length;
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


typedef struct OverlayData{
	IslandData capital;
	IslandData island1;
	IslandData island2;
	IslandData island3;

	int currentIsland;
} OverlayData;
typedef struct OverlayUi{
	HWND setHousingFrame;
	HWND adjustHousingFrame;
	HWND resourceReqFrame;
	HWND islandSelectionFrame;

	HWND closeWindowBtn;
	HWND farmerBlockInc;
	HWND farmerBlockDec;
	HWND workerBlockInc;
	HWND workerBlockDec;

	HWND capitalIslandSel;
	HWND island1Sel;
	HWND island2Sel;
	HWND island3Sel;

	HWND housingWidth;
	HWND housingLength;

	HWND housingWidthLBL;
	HWND housingLengthLBL;
	HWND dragBar;

	HWND housingWidthSPN;
	HWND housingLengthSPN;

	HWND fishDSP;
	HWND clothesDSP;
	HWND schnnapsDSP;
} OverlayUi;
typedef struct OverlayState{
	OverlayData data;
	OverlayUi ui;
} OverlayState;


#endif

















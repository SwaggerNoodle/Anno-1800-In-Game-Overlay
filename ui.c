#include "ui.h"
#include "helpers.h"

void CreateUiFrames(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay){

	overlay->ui.setHousingFrame = CreateUiComponent(hInstance,
                                                        hwnd,
                                                        ID_FRM_SetHousingFrame,
                                                        NULL,
                                                        GRID_SetHousingFrameXPos,
                                                        GRID_SetHousingFrameYPos,
                                                        110,
                                                        90,
                                                        NULL);
        overlay->ui.adjustHousingFrame = CreateUiComponent(hInstance,
                                                           hwnd,
                                                           ID_FRM_AdjustHousingFrame,
                                                           NULL,
                                                           GRID_AdjustHousingFrameXPos,
                                                           GRID_AdjustHousingFrameYPos,
                                                           330,
                                                           120,
                                                           NULL);
        overlay->ui.resourceReqFrame = CreateUiComponent(hInstance,
                                                         hwnd,
                                                         ID_FRM_ResourceReqFrame,
                                                         NULL,
                                                         GRID_ResourceReqFrameXPos,
                                                         GRID_ResourceReqFrameYPos,
                                                         330,
                                                         150,
                                                         NULL);
        overlay->ui.islandSelectionFrame = CreateUiComponent(hInstance,
                                                             hwnd,
                                                             ID_FRM_IslandSelectFrame,
                                                             NULL,
                                                             GRID_IslandSelectFrameXPos,
                                                             GRID_IslandSelectFrameYPos,
                                                             200,
                                                             90,
                                                             NULL);
}

void CreateUiButtons(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay){

	overlay->ui.closeWindowBtn = CreateUiComponent(hInstance,
                                                       hwnd,
                                                       ID_BTN_Close,
                                                       L"X",
                                                       350,
                                                       5,
                                                       25,
                                                       25,
                                                       NULL);
	overlay->ui.farmerBlockInc = CreateUiComponent(hInstance,
                                                       hwnd,
                                                       ID_BTN_FarmerBlockInc,
                                                       L"Farmer Block\r\n+1",
                                                       GRID_AdjustHousingFrameXPos + 10,
                                                       GRID_AdjustHousingFrameYPos + 20,
                                                       100,
                                                       40,
                                                       NULL);
	overlay->ui.farmerBlockDec = CreateUiComponent(hInstance,
                                                       hwnd,
                                                       ID_BTN_FarmerBlockDec,
                                                       L"Farmer Block\r\n-1",
                                                       GRID_AdjustHousingFrameXPos + 10,
                                                       GRID_AdjustHousingFrameYPos + 60,
                                                       100,
                                                       40,
                                                       NULL);
	overlay->ui.workerBlockInc = CreateUiComponent(hInstance,
						       hwnd,
						       ID_BTN_WorkerBlockInc,
						       L"Worker Block\r\n+1",
						       GRID_AdjustHousingFrameXPos + 110,
						       GRID_AdjustHousingFrameYPos + 20,
						       100,
						       40,
						       NULL);
	overlay->ui.workerBlockDec = CreateUiComponent(hInstance,
						       hwnd,
						       ID_BTN_WorkerBlockDec,
						       L"Worker Block\r\n-1",
						       GRID_AdjustHousingFrameXPos + 110,
						       GRID_AdjustHousingFrameYPos + 60,
						       100,
						       40,
						       NULL);

	overlay->ui.capitalIslandSel = CreateUiComponent(hInstance,
							hwnd,
							ID_BTN_CapitalIslandSel,
							L"Capital",
							GRID_IslandSelectFrameXPos - 5,
							GRID_IslandSelectFrameYPos + 5,
							55,
							85,
							NULL);
	overlay->ui.island1Sel = CreateUiComponent(hInstance,
						   hwnd,
						   ID_BTN_Island1Sel,
						   L"Isle 1",
						   GRID_IslandSelectFrameXPos + 50,
						   GRID_IslandSelectFrameYPos + 5,
						   50,
						   85,
						   NULL);
	overlay->ui.island2Sel = CreateUiComponent(hInstance,
						   hwnd,
						   ID_BTN_Island2Sel,
						   L"Isle 2",
						   GRID_IslandSelectFrameXPos + 100,
						   GRID_IslandSelectFrameYPos + 5,
						   50,
						   85,
						   NULL);
	overlay->ui.island3Sel = CreateUiComponent(hInstance,
						   hwnd,
						   ID_BTN_Island3Sel,
						   L"Isle 3",
						   GRID_IslandSelectFrameXPos + 150,
						   GRID_IslandSelectFrameYPos + 5,
						   50,
						   85,
						   NULL);
}

void CreateUiFields(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay){

	overlay->ui.housingWidth = CreateUiComponent(hInstance,
                                                     hwnd,
                                                     ID_FLD_HousingWidth,
                                                     L"2",
                                                     GRID_SetHousingFrameXPos + 15,
                                                     GRID_SetHousingFrameYPos + 40,
                                                     30,
                                                     20,
                                                     NULL);
	overlay->ui.housingLength = CreateUiComponent(hInstance,
                                                      hwnd,
                                                      ID_FLD_HousingLength,
                                                      L"10",
                                                      GRID_SetHousingFrameXPos + 65,
                                                      GRID_SetHousingFrameYPos + 40,
                                                      30,
                                                      20,
                                                      NULL);
}

void CreateUiLabels(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay){

	overlay->ui.housingWidthLBL = CreateUiComponent(hInstance,
                                                        hwnd,
                                                        ID_LBL_HousingWidth,
                                                        L"Width",
                                                        GRID_SetHousingFrameXPos + 10,
                                                        GRID_SetHousingFrameYPos + 20,
                                                        40,
                                                        20,
                                                        NULL);
	overlay->ui.housingLengthLBL = CreateUiComponent(hInstance,
                                                         hwnd,
                                                         ID_LBL_HousingLength,
                                                         L"Length",
                                                         GRID_SetHousingFrameXPos + 60,
                                                         GRID_SetHousingFrameYPos + 20,
                                                         45,
                                                         20,
                                                         NULL);

        overlay->ui.dragBar = CreateUiComponent(hInstance,
                                                hwnd,
                                                ID_LBL_DragBar,
                                                NULL,
                                                0,
                                                0,
                                                200,
                                                10,
                                                NULL);
}

void CreateUiSpinners(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay){

	(void)hwnd;

	SpinnerConfig SPN_HousingWidth;
        SPN_HousingWidth.childHWND = overlay->ui.housingWidth;
        SPN_HousingWidth.minVal = 1;
        SPN_HousingWidth.maxVal = 2;
        SPN_HousingWidth.initialVal = 2;
        overlay->ui.housingWidthSPN = CreateUiComponent(hInstance,
                                                        hwnd,
                                                        ID_SPN_HousingWidth,
                                                        NULL,
                                                        GRID_SetHousingFrameXPos + 20,
                                                        GRID_SetHousingFrameYPos + 60,
                                                        50,
                                                        20,
                                                        &SPN_HousingWidth);
        SpinnerConfig SPN_HousingLength;
        SPN_HousingLength.childHWND = overlay->ui.housingLength;
        SPN_HousingLength.minVal = 1;
        SPN_HousingLength.maxVal = 14;
        SPN_HousingLength.initialVal = 10;
        overlay->ui.housingLengthSPN = CreateUiComponent(hInstance,
                                                         hwnd,
                                                         ID_SPN_HousingLength,
                                                         NULL,
                                                         GRID_SetHousingFrameXPos + 70,
                                                         GRID_SetHousingFrameYPos + 60,
                                                         50,
                                                         20,
                                                         &SPN_HousingLength);
}

void CreateUiDisplays(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay){

	overlay->ui.fishDSP = CreateUiComponent(hInstance,
                                                hwnd,
                                                ID_DSP_Fish,
                                                L"Fishery Req:\r\n0",
                                                GRID_ResourceReqFrameXPos + 10,
                                                GRID_ResourceReqFrameYPos + 20,
                                                100,
                                                40,
                                                NULL);
        overlay->ui.clothesDSP = CreateUiComponent(hInstance,
                                                   hwnd,
                                                   ID_DSP_Clothes,
                                                   L"Knitters Req:\r\n0",
                                                   GRID_ResourceReqFrameXPos + 115,
                                                   GRID_ResourceReqFrameYPos + 20,
                                                   100,
                                                   40,
                                                   NULL);
	overlay->ui.schnnapsDSP = CreateUiComponent(hInstance,
                                                    hwnd,
                                                    ID_DSP_Schnnaps,
                                                    L"Distillery Req:\r\n0",
                                                    GRID_ResourceReqFrameXPos + 220,
                                                    GRID_ResourceReqFrameYPos + 20,
                                                    100,
                                                    40,
                                                    NULL);
	overlay->ui.sausageDSP = CreateUiComponent(hInstance,
						   hwnd,
						   ID_DSP_Sausage,
						   L"Butchers Req:\r\n0",
						   GRID_ResourceReqFrameXPos + 10,
						   GRID_ResourceReqFrameYPos + 60,
						   100,
						   40,
						   NULL);
	overlay->ui.breadDSP = CreateUiComponent(hInstance,
						 hwnd,
						 ID_DSP_Bread,
						 L"Bakeries Req:\r\n0",
						 GRID_ResourceReqFrameXPos + 115,
						 GRID_ResourceReqFrameYPos + 60,
						 100,
						 40,
						 NULL);
	overlay->ui.beerDSP = CreateUiComponent(hInstance,
						hwnd,
						ID_DSP_Beer,
						L"Brewery Req:\r\n0",
						GRID_ResourceReqFrameXPos + 220,
						GRID_ResourceReqFrameYPos + 60,
						100,
						40,
						NULL);
	overlay->ui.soapDSP = CreateUiComponent(hInstance,
						hwnd,
						ID_DSP_Soap,
						L"Soapery Req:\r\n0",
						GRID_ResourceReqFrameXPos + 10,
						GRID_ResourceReqFrameYPos + 100,
						100,
						40,
						NULL);
}

















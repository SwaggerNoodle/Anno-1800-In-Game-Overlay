#include "mathFunctions.h"
#include "helpers.h"


int RecalculateFishNeed(HousingCount *housingCount){

        int fishNeed = housingCount->farmerHCount + (2 * housingCount->workerHCount);
	if (fishNeed == 0){
		return 0;
	}
        int fisheriesNeeded = (fishNeed / FISHOUTPUT) + 1;
        return fisheriesNeeded;
}
int RecalculateClothesNeed(HousingCount *housingCount){

	int clothesNeed = housingCount->farmerHCount + (2 * housingCount->workerHCount);
	if (clothesNeed == 0){
		return 0;
	}
	int knittersNeeded = (clothesNeed / CLOTHESOUTPUT) + 1;
	return knittersNeeded;
}
int RecalculateSchnnapsNeed(HousingCount *housingCount){

	int schnnapsNeed = housingCount->farmerHCount + (2 * housingCount->workerHCount);
	if (schnnapsNeed == 0){
		return 0;
	}
	int distilleriesNeeded = (schnnapsNeed / SCHNAPPSOUTPUT) + 1;
	return distilleriesNeeded;
}


void RecalculateDisplayValues(IslandData *island, OverlayUi *uiHandle){

	int fisheriesNeeded = RecalculateFishNeed(&island->islandPopulation);
	SetDisplay(uiHandle->fishDSP, L"Fishery Req:", fisheriesNeeded);

	int clothesNeeded = RecalculateClothesNeed(&island->islandPopulation);
	SetDisplay(uiHandle->clothesDSP, L"Knitters Req:", clothesNeeded);

	int schnnapsNeeded = RecalculateSchnnapsNeed(&island->islandPopulation);
	SetDisplay(uiHandle->schnnapsDSP, L"Distillery Req:", schnnapsNeeded);
}

void RecalculateBlockSize(IslandData *island, OverlayUi *uiHandle){

	island->islandBlockSize.width = GetValueFromSpinner(uiHandle->housingWidth);
	island->islandBlockSize.length = GetValueFromSpinner(uiHandle->housingLength);

	island->islandBlockSize.houseNum = island->islandBlockSize.width * island->islandBlockSize.length;
}
	






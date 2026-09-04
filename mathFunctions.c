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
int RecalculateSausageNeed(HousingCount *housingCount){

	int sausageNeed = housingCount->workerHCount + (2 * housingCount->artisanHCount);
	if (sausageNeed == 0){
		return 0;
	}
	int butchersNeeded = (sausageNeed / SAUSAGEOUTPUT) + 1;
	return butchersNeeded;
}
int RecalculateBreadNeed(HousingCount *housingCount){

	int breadNeed = housingCount->workerHCount + (2 * housingCount->artisanHCount);
	if (breadNeed == 0){
		return 0;
	}
	int bakeriesNeeded = (breadNeed / BREADOUTPUT) + 1;
	return bakeriesNeeded;
}
int RecalculateBeerNeed(HousingCount *housingCount){

	int beerNeed = housingCount->workerHCount + (2 * housingCount->artisanHCount);
	if (beerNeed == 0){
		return 0;
	}
	int breweriesNeeded = (beerNeed / BEEROUTPUT) + 1;
	return breweriesNeeded;
}
int RecalculateSoapNeed(HousingCount *housingCount){

	int soapNeed = housingCount->workerHCount + (2 * housingCount->artisanHCount);
	if (soapNeed == 0){
		return 0;
	}
	int soaperiesNeeded = (soapNeed / SOAPOUTPUT) + 1;
	return soaperiesNeeded;
}


void RecalculateDisplayValues(IslandData *island, OverlayUi *uiHandle){

	int fisheriesNeeded = RecalculateFishNeed(&island->islandPopulation);
	SetDisplay(uiHandle->fishDSP, L"Fishery Req:", fisheriesNeeded);

	int clothesNeeded = RecalculateClothesNeed(&island->islandPopulation);
	SetDisplay(uiHandle->clothesDSP, L"Knitters Req:", clothesNeeded);

	int schnnapsNeeded = RecalculateSchnnapsNeed(&island->islandPopulation);
	SetDisplay(uiHandle->schnnapsDSP, L"Distillery Req:", schnnapsNeeded);

	int sausageNeeded = RecalculateSausageNeed(&island->islandPopulation);
	SetDisplay(uiHandle->sausageDSP, L"Butchers Req:", sausageNeeded);

	int breadNeeded = RecalculateBreadNeed(&island->islandPopulation);
	SetDisplay(uiHandle->breadDSP, L"Bakeries Req:", breadNeeded);

	int beerNeeded = RecalculateBeerNeed(&island->islandPopulation);
	SetDisplay(uiHandle->beerDSP, L"Breweries Req:", beerNeeded);

	int soapNeeded = RecalculateSoapNeed(&island->islandPopulation);
	SetDisplay(uiHandle->soapDSP, L"Soapery Req:", soapNeeded);
}

void RecalculateBlockSize(IslandData *island, OverlayUi *uiHandle){

	island->islandBlockSize.width = GetValueFromSpinner(uiHandle->housingWidth);
	island->islandBlockSize.length = GetValueFromSpinner(uiHandle->housingLength);

	island->islandBlockSize.houseNum = island->islandBlockSize.width * island->islandBlockSize.length;
}
	






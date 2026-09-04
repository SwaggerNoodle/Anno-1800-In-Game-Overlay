#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include "dataStructs.h"
#include "helpers.h"

#define FISHOUTPUT 80
#define CLOTHESOUTPUT 65
#define SCHNAPPSOUTPUT 60

#define SAUSAGEOUTPUT 50
#define BREADOUTPUT 55
#define BEEROUTPUT 65
#define SOAPOUTPUT 240

#define TINNEDFOODOUTPUT 65
#define SOWINGMACHINEOUTPUT 70
#define COATSOUTPUT 75
#define RUMOUTPUT 35

#define GLASSESOUTPUT 75
#define BICYCLEOUTPUT 160
#define POCKETWATCHOUTPUT 510
#define LIGHTBULBOUTPUT 320
#define COFFEOUTPUT 42

#define JEWELLERYOUTPUT 190
#define GRAMOPHONESOUTPUT 760
#define STEAMCARRIAGEOUTPUT 600
#define CHAMPAGNEOUTPUT 85
#define CIGAROUTPUT 180
#define CHOCOLATEOUTPUT 37


int RecalculateFishNeed(HousingCount *housingCount);

int RecalculateClothesNeed(HousingCount *housingCount);

int RecalculateSchnnapsNeed(HousingCount *housingCount);

int RecalculateSausageNeed(HousingCount *housingCount);

int RecalculateBreadNeed(HousingCount *housingCount);

int RecalculateBeerNeed(HousingCount *housingCount);

int RecalculateSoapNeed(HousingCount *housingCount);

void RecalculateDisplayValues(IslandData *island, OverlayUi *uiHandle);

void RecalculateBlockSize(IslandData *island, OverlayUi *uiHandle);

#endif

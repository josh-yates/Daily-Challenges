#include "ForestClasses.h"

GameClock::GameClock() :CurrentTime(0) {}

GameClock::~GameClock() {}

int GameClock::GetCurrentTime()const {
	return CurrentTime;
}

void GameClock::Tick() {
	CurrentTime += 1;
}

Forest::ForestMap::ForestMap(const int SideSize, GameClock& ClockIn) {
	ClockPtr = &ClockIn;
	if (SideSize < 1) {
		throw std::invalid_argument("Map cannot have side size less than 1");
	}
	std::vector<TileTypes> TempRow;
	for (int i{ 0 }; i < SideSize; i++) {
		TempRow.push_back(FreeSpace);
	}
	for (int i{ 0 }; i < SideSize; i++) {
		MapArray.push_back(TempRow);
	}
}

Forest::ForestMap::~ForestMap() {
	ClockPtr = nullptr;
}

int Forest::ForestMap::GetSideSize()const {
	return MapArray.size();
}

void Forest::ForestMap::SetTile(const int xIn, const int yIn, const Forest::TileTypes TileIn) {
	if (xIn < 0 || xIn >= GetSideSize() || yIn<0 || yIn>GetSideSize()) {
		throw std::invalid_argument("ForestMap::operator(): Accessing outside map");
	}
	MapArray[xIn][yIn] = TileIn;
}

Forest::TileTypes Forest::ForestMap::operator()(const int xIn, const int yIn)const {
	if (xIn < 0 || xIn >= GetSideSize() || yIn<0 || yIn>GetSideSize()) {
		throw std::invalid_argument("ForestMap::operator(): Accessing outside map");
	}
	return MapArray[xIn][yIn];
}

Forest::ForestEntity::ForestEntity(const int xPosIn, const int yPosIn, ForestMap& ParentMapIn, GameClock& ClockIn) {
	ParentMapPtr = &ParentMapIn;
	ClockPtr = &ClockIn;
	if (xPosIn < 0 || xPosIn >= ParentMapPtr->GetSideSize() || yPosIn<0 || yPosIn > ParentMapPtr->GetSideSize()) {
		throw std::invalid_argument("ForestMap::operator(): Accessing outside map");
	}
	xPos = xPosIn;
	yPos = yPosIn;
}

Forest::ForestEntity::~ForestEntity() {
	ParentMapPtr = nullptr;
	ClockPtr = nullptr;
}

void Forest::ForestEntity::DoAction() {}

Forest::LumberJack::LumberJack(int& LumberCountIn, const int xPosIn, const int yPosIn, ForestMap& ParentMapIn, GameClock& ClockIn) :ForestEntity(xPosIn, yPosIn, ParentMapIn, ClockIn) {
	LumberCount = &LumberCountIn;
}

Forest::LumberJack::~LumberJack() {
	LumberCount = nullptr;
}
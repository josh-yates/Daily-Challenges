#include "ForestClasses.h"

Forest::ForestMap::ForestMap(const int SideSize) {
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

Forest::ForestMap::~ForestMap() {}

int Forest::ForestMap::GetSideSize()const {
	return MapArray.size();
}

Forest::TileTypes Forest::ForestMap::operator()(const int xIn, const int yIn)const {
	if (xIn < 0 || xIn >= GetSideSize() || yIn<0 || yIn>GetSideSize()) {
		throw std::invalid_argument("ForestMap::operator(): Accessing outside map");
	}
	return MapArray[xIn][yIn];
}

Forest::ForestEntity::ForestEntity(int xPosIn, int yPosIn, ForestMap& ParentMapIn) {
	ParentMapPtr = &ParentMapIn;
}
#ifndef FORESTCLASSES_H
#define FORESTCLASSES_H

#include <vector>

namespace Forest {
	enum TileTypes { FreeSpace, Sapling, Tree, ElderTree, LumberJack, Bear };

	class ForestMap {
	private:
		std::vector<std::vector<Forest::TileTypes>> MapArray;
	public:
		ForestMap(const int SideSize);
		~ForestMap();
		int GetSideSize()const;
		TileTypes operator()(const int xIn, const int yIn)const;
	};

	class ForestEntity {
	private:
		int xPos, yPos;
		ForestMap* ParentMapPtr;
	public:
		ForestEntity(int xPosIn, int yPosIn, ForestMap& ParentMapIn);
		~ForestEntity();
		virtual void DoAction() = 0;
	};
}

#endif
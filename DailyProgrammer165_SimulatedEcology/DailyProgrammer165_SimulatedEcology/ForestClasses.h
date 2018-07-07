#ifndef FORESTCLASSES_H
#define FORESTCLASSES_H

#include <vector>

class GameClock {
private:
	int CurrentTime;
public:
	GameClock();
	~GameClock();
	int GetCurrentTime()const;
	void Tick();
};

namespace Forest {
	enum TileTypes { FreeSpace, Sapling, Tree, ElderTree, LumberJack, Bear };

	class ForestMap {
	private:
		std::vector<std::vector<Forest::TileTypes>> MapArray;
		GameClock* ClockPtr;
	public:
		ForestMap(const int SideSize, GameClock& ClockIn);
		~ForestMap();
		int GetSideSize()const;
		void SetTile(const int xIn, const int yIn, const Forest::TileTypes TileIn);
		TileTypes operator()(const int xIn, const int yIn)const;
	};

	class ForestEntity {
	private:
		int xPos, yPos;
		ForestMap* ParentMapPtr;
		GameClock* ClockPtr;
	public:
		ForestEntity(const int xPosIn, const int yPosIn, ForestMap& ParentMapIn, GameClock& ClockIn);
		~ForestEntity();
		virtual void DoAction() = 0;
	};
}

#endif
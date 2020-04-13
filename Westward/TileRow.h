#pragma once
#include "Tile.h"
#include <vector>
using namespace std;
class TileRow
{
public:
	TileRow();
	~TileRow();
	bool TileContains(int index);
	Tile* getTile(int index);
	vector<Tile*> getRow();
private:
	vector<Tile*> row;


};


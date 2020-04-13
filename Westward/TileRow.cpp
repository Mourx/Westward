#include "TileRow.h"


TileRow::TileRow() {
	for (int i = 0; i < 4; i++) {
		row.push_back(new Tile());
	}
}

TileRow::~TileRow() {

}

bool TileRow::TileContains(int index) {
	if (row[index]->hasCombatant()) {
		return true;
	}
	return false;
}

Tile* TileRow::getTile(int index) {
	if (row.size() == 4) {
		return row[index];
	}
	else {
		return new Tile();
	}
}

vector<Tile*> TileRow::getRow() {
	return row;
}
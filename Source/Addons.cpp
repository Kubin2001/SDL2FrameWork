#include "Addons.h"

Point::Point() {

}

Point::Point(int x, int y) : x(x), y(y) {}


MapPos::MapPos() {

}

MapPos::MapPos(int x, int y) {
	CalcAll(x, y);
}



int MapPos::minX = 0;
int MapPos::minY = 0;
int MapPos::tileSize = 0;
int MapPos::regionSize = 0;
int MapPos::tilesPerRegion = 0;
int MapPos::regionsCountWidth = 0;
int MapPos::regionsCountHeight = 0;
int MapPos::maxX = 0;
int MapPos::maxY = 0;

void MapPos::FedData(int mX, int mY, int tSize, int tilesPerReg, int regionsW, int regionsH) {
	MapPos::minX = mX;
	MapPos::minY = mY;
	MapPos::tileSize = tSize;
	MapPos::regionSize = tSize * tilesPerReg;
	MapPos::tilesPerRegion = tilesPerReg;
	MapPos::regionsCountWidth = regionsW;
	MapPos::regionsCountHeight = regionsH;
	MapPos::maxX = mX + (tSize * tilesPerReg * regionsW);
	MapPos::maxY = mY + (tSize * tilesPerReg * regionsH);
}




void MapPos::CalcRegTile(int x, int y) {
	int localY = (y - MapPos::minY) % MapPos::regionSize;
	if (localY < 0) {
		localY += MapPos::regionSize;
	}
	rowsTile = localY / MapPos::tileSize;

	int localX = (x - MapPos::minX) % MapPos::regionSize;
	if (localX < 0) {
		localX += MapPos::regionSize;
	}
	columnTile = localX / MapPos::tileSize;
}

void MapPos::CalcRegion(int x, int y) {
	rows = (y - MapPos::minY) / MapPos::regionSize;
	if ((y - MapPos::minY) < 0) {
		rows -= 1;
	}

	column = (x - MapPos::minX) / MapPos::regionSize;
	if ((x - MapPos::minX) < 0) {
		column -= 1;
	}
}

void MapPos::CalcAbsTile(int x, int y) {
	absTileRows = (y - MapPos::minY) / MapPos::tileSize;
	if ((y - MapPos::minY) < 0) {
		absTileRows -= 1;
	}

	absTileColumn = (x - MapPos::minX) / MapPos::tileSize;
	if ((x - MapPos::minX) < 0) {
		absTileColumn -= 1;
	}
}

void MapPos::CalcAll(int x, int y) {
	CalcRegTile(x, y);
	CalcRegion(x, y);
	CalcAbsTile(x, y);
}

void MapPos::RecalculateFromAbs() {
	rows = absTileRows / MapPos::tilesPerRegion;
	if (absTileRows < 0) { --rows; }

	column = absTileColumn / MapPos::tilesPerRegion;
	if (absTileColumn < 0) { --column; }

	rowsTile = absTileRows % MapPos::tilesPerRegion;
	if (rowsTile < 0) {
		rowsTile += MapPos::tilesPerRegion;
	}
	columnTile = absTileColumn % MapPos::tilesPerRegion;
	if (columnTile < 0) {
		columnTile += MapPos::tilesPerRegion;
	}
}

bool MapPos::CorrectnessRegionTile() {
	if (rowsTile >= MapPos::tilesPerRegion) {
		std::cerr << "MapPos Incorrect tile rows too big\n";
		return false;
	}
	if (rowsTile < 0) {
		std::cerr << "MapPos Incorrect tile rows too small\n";
		return false;
	}
	if (columnTile >= MapPos::tilesPerRegion) {
		std::cerr << "MapPos Incorrect tile columns too big\n";
		return false;
	}
	if (columnTile < 0) {
		std::cerr << "MapPos Incorrect tile columns too small\n";
		return false;
	}
	return true;
}

bool MapPos::CorrectnessRegion() {
	if (rows > MapPos::regionsCountHeight - 1) {
		std::cerr << "MapPos Incorrect rows too big\n";
		return false;
	}
	if (rows < 0) {
		std::cerr << "MapPos Incorrect rows too small\n";
		return false;
	}
	if (column > MapPos::regionsCountWidth - 1) {
		std::cerr << "MapPos Incorrect columns too big\n";
		return false;
	}
	if (column < 0) {
		std::cerr << "MapPos Incorrect columns too small\n";
		return false;
	}
	return true;
}

bool MapPos::CorrectnessAbsTile() {
	int countWidth = MapPos::regionsCountWidth * MapPos::tilesPerRegion;
	int countHeight = MapPos::regionsCountHeight * MapPos::tilesPerRegion;
	if (absTileRows >= countHeight) {
		std::cerr << "MapPos Incorrect abs tile rows too big\n";
		return false;
	}
	if (absTileRows < 0) {
		std::cerr << "MapPos Incorrect abs tile rows too small\n";
		return false;
	}
	if (absTileColumn >= countWidth) {
		std::cerr << "MapPos Incorrect abs tile columns too big\n";
		return false;
	}
	if (absTileColumn < 0) {
		std::cerr << "MapPos Incorrect abs tile columns too small\n";
		return false;
	}
	return true;
}


double CalculateEuclidean(int x1,int x2,int y1,int y2) {
    double x = std::pow(x2 - x1, 2);
    double y = std::pow(y2 - y1, 2);;
    return std::sqrt(x+y);
}

Point GetRectangleCenter(const SDL_Rect rect) {
	Point point;
	point.x = rect.x + (rect.w * 0.5);
	point.y = rect.y + (rect.h * 0.5);
	return point;

}

unsigned int RectanglePointDistance(const SDL_Rect rect, const Point point) {
	return std::abs(rect.x - point.x) + std::abs(rect.y - point.y);

}

unsigned int PointsDistance(const Point point, const Point point2) {
	return std::abs(point.x - point2.x) + std::abs(point.y - point2.y);
}


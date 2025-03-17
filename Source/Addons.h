#pragma once
#include <iostream>
#include <math.h>
#include <SDL.h>
#include <vector>

struct Point
{
	int x = 0;
	int y = 0;
	Point();
	Point(int x, int y);
};



struct MapPos {
	int rows = 0; //Du�e Regiony
	int column = 0;

	int rowsTile = 0; //Pole w regionie 
	int columnTile = 0;

	int absTileRows = 0;
	int absTileColumn = 0;

    MapPos();

    MapPos(int x, int y);

    void CalcRegTile(int x, int y);

    void CalcRegion(int x, int y);

    void CalcAbsTile(int x, int y);

    void CalcAll(int x, int y);

    void RecalculateFromAbs();


    // It will never work with automaitic check cause like with mouse cause it always is between 0 and tile per region
    // it is for manual change
    bool CorrectnessRegionTile();

    bool CorrectnessRegion();

    bool CorrectnessAbsTile();

    bool CorrectnesAbsCol();

    bool CorrectnesAbsRow();

    //Silent checks without cout

    bool CorrectnessRegionTileS();

    bool CorrectnessRegionS();

    bool CorrectnessAbsTileS();

    bool CorrectnesAbsColS();

    bool CorrectnesAbsRowS();



    static int minX;
    static int minY;
    static int tileSize;
    static int regionSize;
    static int tilesPerRegion;
    static int regionsCountWidth;
    static int regionsCountHeight;
    static int maxX;
    static int maxY;

    static void FedData(int mX, int mY, int tSize, int tilesPerReg, int regionsW, int regionsH);


};


double CalculateEuclidean(int x1, int x2, int y1, int y2);

Point GetRectangleCenter(const SDL_Rect rect);

unsigned int RectanglePointDistance(const SDL_Rect rect, const Point point);

unsigned int PointsDistance(const Point point, const Point point2);




class AnyData {
    public:
    virtual ~AnyData() = default;

    template <typename T>
    T& Get();

    template <typename T>
    void Set(T tempData);
};





template <typename T>
class AnyContatiner : public AnyData {
    public:
    T data;

    AnyContatiner() = default;

    AnyContatiner(T temp) {
        data = temp;
    }


};

template <typename T>
T& AnyData::Get() {
    auto temp = static_cast<AnyContatiner<T>*>(this); // Can be static not dynamic cause only one class is using inheritance
    if (!temp) {
        std::cerr << "Error: Wrong cast in AnyDataGet deafault value returned\n";
    }
    return temp->data;
}


template <typename T>
void AnyData::Set(T tempData) {
    auto temp = static_cast<AnyContatiner<T>*>(this); // Can be static not dynamic cause only one class is using inheritance
    if (!temp) {
        std::cerr << "Error: Data set uncorrectly in any data\n";
        return;
    }
    temp->data = tempData;
}

// Wraped Pointer class for container safety
template <typename T>
class WrapPtr {
    private:
    T* pointer = nullptr;

    public:

    T*& Get() { return pointer; }

    T& GetVal() { return *pointer; }

    T& operator*() { return *pointer; }

    T* operator->() { return pointer; }
};

/*Designed to work only with Warped Pointer Class*/

template <typename T>
class RefPtr {
    private:
    T* mainArgument = nullptr;
    std::vector<T**> references;
    public:

    RefPtr() = default;


    RefPtr(T* mainArg) {
        mainArgument = mainArg;
    }

    RefPtr(const RefPtr<T>& other) = delete;

    RefPtr(RefPtr<T>&& other) noexcept {
        mainArgument = other.mainArgument;
        other.mainArgument = nullptr;

        references = std::move(other.references);
    }

    void Make(T* mainArg) {
        mainArgument = mainArg;
    }

    T* Get() {
        return mainArgument;
    }

    T& GetVal() {
        return *mainArgument;
    }

    void AddRef(T*& ref) {
        ref = mainArgument;
        references.push_back(&ref);
    }

    void ClearRefs() {
        for (auto& it : references) {
            *it = nullptr;
        }
    }


    ~RefPtr() {
        delete mainArgument;
    }

    T& operator*() {
        return *mainArgument;
    }

    T* operator->() {
        return mainArgument;
    }

};
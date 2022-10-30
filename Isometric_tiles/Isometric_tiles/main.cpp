#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class IsometricTiles : public olc::PixelGameEngine {
public:
    IsometricTiles() {
        sAppName = "Isometric Tiles";
    }
private:
    olc::vi2d vWorldSize = { 14, 10 };
    olc::vi2d vTilesSize = { 40, 20 };
    olc::vi2d vOrigin = { 5, 1 };
    olc::Sprite *sprIsom = nullptr;
    int *pWorld = nullptr;
    
public:
    bool OnUserCreate() override {
        sprIsom = new olc::Sprite("isometric_demo.png");
        pWorld = new int[vWorldSize.x * vWorldSize.y]{ 0 };
                
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(olc::WHITE);
        
        auto ToScreen = [&](int x, int y)
        {
            return  olc::vi2d
            {
                (vOrigin.x * vTilesSize.x) + (x-y)*(vTilesSize.x / 2),
                (vOrigin.y * vTilesSize.y) + (x+y)*(vTilesSize.y / 2)
            };
        };
        
        SetPixelMode(olc::Pixel::MASK);
        
        for(int y = 0; y < vWorldSize.y; y++)
        {
            for(int x = 0; x < vWorldSize.x; x++)
            {
                olc::vi2d vWorld = ToScreen(x, y);
                
                switch(pWorld[y*vWorldSize.x + x])
                {
                    case 0:
                        // Invisible Tile
                        DrawPartialSprite(vWorld.x, vWorld.y, sprIsom, 1 * vTilesSize.x, 0, vTilesSize.x, vTilesSize.y);
                        break;
//                    case 1:
                        
                }
            }
        }
        
        SetPixelMode(olc::Pixel::NORMAL);
        
        return true;
    }
};


int main(int argc, char const *argv[]) {
	IsometricTiles demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();

	return 0;
}

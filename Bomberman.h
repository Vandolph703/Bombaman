#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.hpp"
#include <vector>

class App: public GlutApp {
	// vector that holds all tiles of the grid map
	//std::vector<Rect*> gridMap;
	//std::vector<Wall*> wallMap;
	//Hero* playerOne;
	//Hero* AI;
    // Maintain app state here
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
	~App();
    // These are the events we want to handle
	// void idle();
    void draw();
    void keyPress(unsigned char key);
	void makeGridMap();
	void drawGridMap();
	bool isValidMove(unsigned char key);
	void drawHero();
	void drawEnemy();
	void isGameOver();
	void detonateBomb(int bombLocation);
};

#endif

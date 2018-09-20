#include "Bomberman.h"
#include "Rect.h"
#include "Hero.h"
#include "Wall.h"
//#include <vector>

// vector that holds all tiles of the grid map
std::vector<Rect*> gridMap;
std::vector<Wall*> wallMap;
Hero* playerOne = new Hero(0);	// 20
Hero* AI = new Hero(80);

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){

	// Dimension is 1000 x 1000
	makeGridMap();

	
	// Update the player and AI (place them onto the board)
	playerOne->setX(gridMap[0]->getX());
	playerOne->setX(gridMap[0]->getY());
	playerOne->setX(gridMap[0]->getWidth());
	playerOne->setX(gridMap[0]->getHeight());

	AI->setX(gridMap[80]->getX());
	AI->setX(gridMap[80]->getY());
	AI->setX(gridMap[80]->getWidth());
	AI->setX(gridMap[80]->getHeight());


	std::cout << "This is Bomberman v1.\nThe objective of the game is to defeat the enemy in the bottom right corner." << std::endl;
	std::cout << "You will begin in the top left corner, indicated by the shape of a triangle." << std::endl;
	std::cout << "You can destroy the boxes, or walls, that are color BLUE. Walls that are color GREEN cannot be destroyed." << std::endl;
	std::cout << "Controls:\n" << "W: move up\n" << "A: move left\n" << "S: move down\n" << "D: move right\n" << "Spacebar: drop bomb\n" << "K: detonate bomb\n" << std::endl;


}

App::~App() {
	for (int i = 0; i < gridMap.size(); i++) {
		delete gridMap[i];
		delete wallMap[i];
	}
	gridMap.clear();
	wallMap.clear();
	delete playerOne;
	delete AI;
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
	// This prints out the borders of the map
	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-0.8, 0.8);
	glVertex2f(0.8, 0.8);
	glVertex2f(0.8, 0.8);
	glVertex2f(0.8, -0.8);
	glVertex2f(0.8, -0.8);
	glVertex2f(-0.8, -0.8);
	glVertex2f(-0.8, -0.8);
	glVertex2f(-0.8, 0.8);
	glEnd();

	/*
	static int i = 0;
	if (i % 2 == 0)
		AI->move(-1);
	else
		AI->move(1);
	i++;
	*/

	//playerOne->draw();
	//AI->draw()

	drawHero();
	drawEnemy();
	drawGridMap();

	//playBomberman();

    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();

	isGameOver();

}

/*
void App::idle() {

	while (!(isGameOver())) {
		AI->changePos_Index(9);
		AI->changePos_Index(-9);
		//drawGridMap();
	}

}
*/

void App::keyPress(unsigned char key) {
    
	switch (key) {
		case 27:									// escape
			exit(0);
		case 'w':
			if (isValidMove(key)) {
				playerOne->move(-9);
				if (wallMap[AI->getPos_Index() + 1]->isEmpty() == true) {
					AI->move(1);
				}
				break;
			}
		case 'a':
			if (isValidMove(key)) {
				playerOne->move(-1);
				if (wallMap[AI->getPos_Index() + 1]->isEmpty() == true) {
					AI->move(1);
				}
				break;
			}
		case 's':
			if (isValidMove(key)) {
				playerOne->move(9);
				if (wallMap[AI->getPos_Index() - 1]->isEmpty() == true) {
					AI->move(-1);
				}
				break;
			}
		case 'd':
			if (isValidMove(key)) {
				playerOne->move(1);
				if (wallMap[AI->getPos_Index() - 1]->isEmpty() == true) {
					AI->move(-11);
				}
				break;
			}
		case 32:										// spacebar
			if (isValidMove(key)) {
				std::cout << "Dropping Bomb" << std::endl;
				wallMap[playerOne->getPos_Index()]->setColor(playerOne->playerBomb->getColor(), 0.0f, 0.0f);
				playerOne->bombPlacement(playerOne->getPos_Index());
				playerOne->decreaseBombCount();
				break;
			}
		case 'k': {
			if (playerOne->getBombCount() == 0) {
				// find a way to put this inside Hero.h
				detonateBomb(playerOne->getBomb());
				playerOne->increaseBombCount();
			}
		}
	}

}

void App::makeGridMap() {
	
	float dimension = 0.1777;
	int k = -1;									// this is to help bookkeep where we are in the matrix

	// Wall(float r, float g, float b, bool empty, bool breakable, int pos_index, float x, float y, float width, float height) : Rect(x, y, width, height)

	// it makes the grid map from left to right, similar to how one would read a matrix
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			gridMap.push_back(new Rect(-0.8 + (j * dimension), 0.8 - (i * dimension), dimension, dimension));
			// this is for the unbreakable walls
			if (i % 2 == 1 && j % 2 == 1) {
				wallMap.push_back(new Wall(0.0f, 1.0f, 0.0f, false, false, k++, gridMap[k]->getX(), gridMap[k]->getY(), gridMap[k]->getWidth(), gridMap[k]->getHeight()));
				//std::cout << "unbreakable wall" << " " << k << std::endl;
			}
			// this is for the breakable walls
			else if ((i == 0 || i == 8) && (j ==4) || (i == 4 && (j == 0 || j == 8))) {
				wallMap.push_back(new Wall(0.0f, 0.0f, 1.0f, false, true, k++, gridMap[k]->getX(), gridMap[k]->getY(), gridMap[k]->getWidth(), gridMap[k]->getHeight()));
				//std::cout << "breakable wall" << " " << k << std::endl;
			}
			// this is for the breakable walls
			else if ((i % 2 == 1 && (j % 2 == 0 && j != 0 && j != 8)) || ((i % 2 == 0 && i != 0 && i != 8) && (j % 2 == 1) )) {
				wallMap.push_back(new Wall(0.0f, 0.0f, 1.0f, false, true, k++, gridMap[k]->getX(), gridMap[k]->getY(), gridMap[k]->getWidth(), gridMap[k]->getHeight()));
				//std::cout << "breakable wall" << " " << k << std::endl;
			}
			// this is for the empty grids
			else {
				wallMap.push_back(new Wall(0.0f, 0.0f, 0.0f, true, false, k++, gridMap[k]->getX(), gridMap[k]->getY(), gridMap[k]->getWidth(), gridMap[k]->getHeight()));
				//std::cout << "empty" << " " << k << std::endl;
			}
		}
	}

}

void App::drawGridMap() {

	float dimension = 0.1777;

	glBegin(GL_POLYGON);
	for (int i = 0; i < wallMap.size(); i++) {
		/*
		if (wallMap[i]->isEmpty() == false) {				// not empty
			if (wallMap[i]->isBreakable()) {				// wall breaks; put BRICK WALL texture
				glColor3d(0.0, 0.0, 1.0);					// blue
			}
			else {											// wall does not break; put STONE texture
				glColor3d(0.0, 1.0, 0.0);					// green			
			}
		}
		else {
			glColor3d(0.0, 0.0, 0.0);						// black
		}
		*/
		// color
		glColor3d(wallMap[i]->getR(), wallMap[i]->getG(), wallMap[i]->getB());
		// draws the walls
		glVertex2f(wallMap[i]->getX(), wallMap[i]->getY());
		glVertex2f(wallMap[i]->getX() + dimension, wallMap[i]->getY());
		glVertex2f(wallMap[i]->getX() + dimension, wallMap[i]->getY() - dimension);
		glVertex2f(wallMap[i]->getX(), wallMap[i]->getY() - dimension);
	}

	glEnd();
	//glDisable(GL_TEXTURE_2D);

}

void App::isGameOver() {

	//playerOne->setIsDead(true);

	if (playerOne->getIsDead() || AI->getIsDead()) {
		std::cout << "Game Over!" << "\nPress ESC to leave the game." << std::endl;
	}

}


bool App::isValidMove(unsigned char key) {

	switch (key) {
		case 'w':
			if (playerOne->getPos_Index() < 9) {										// this means that the player is at the top row of the gridMap. Cannot move further up.
				std::cout << "Cannot move Up. Out of Bounds." << std::endl;
				return false;
			} else if (wallMap[playerOne->getPos_Index() - 9]->isEmpty()) {
				// std::cout << "Tile above is empty. Valid Move" << std::endl;
				return true;
			} else {
				std::cout << "Tile above is not empty. Invalid Move" << std::endl;
				return false;
			}
		case 'a':
			if (playerOne->getPos_Index() % 9 == 0) {									// this means that the player is at the leftmost column of the gridMap. Cannot move further to the left.
				std::cout << "Cannot move to the Left. Out of Bounds." << std::endl;
				return false;
			} else if (wallMap[playerOne->getPos_Index() - 1]->isEmpty()) {
				// std::cout << "Tile to the left is empty. Valid Move" << std::endl;
				return true;
			} else {
				std::cout << "Tile above is not empty. Invalid Move" << std::endl;
				return false;
			}
		case 's':
			if (playerOne->getPos_Index() <= 80 && playerOne->getPos_Index() >= 72) {	// this means that the player is at the bottom row of the gridMap. Cannot move further dowm.
				std::cout << "Cannot move Down. Out of Bounds." << std::endl;
				return false;
			}
			else if (wallMap[playerOne->getPos_Index() + 9]->isEmpty()) {
				// std::cout << "Tile above is empty. Valid Move" << std::endl;
				return true;
			}
			else {
				std::cout << "Tile above is not empty. Invalid Move" << std::endl;
				return false;
			}
		case 'd':
			if (playerOne->getPos_Index() % 9 == 8) {										// this means that the player is at the rightmost column of the gridMap. Cannot move further to the right.
				std::cout << "Cannot move to the Right. Out of Bounds." << std::endl;
				return false;
			}
			else if (wallMap[playerOne->getPos_Index() + 1]->isEmpty()) {
				// std::cout << "Tile to the right is empty. Valid Move" << std::endl;
				return true;
			}
			else {
				std::cout << "Tile above is not empty. Invalid Move" << std::endl;
				return false;
			}
		case 32:
			if (playerOne->getBombCount() != 0) {
				if (wallMap[playerOne->getPos_Index()]->isEmpty()) {							// the tile the player is on is empty
					return true;
				}
				else {
					return false;
				}
			}
	}

	return false;

}

// Player will be denoted as the triangle
void App::drawHero() {

	// 0.1777

	glBegin(GL_POLYGON);
	glColor3d(0.0, 1.0, 0.5);
	glVertex2f(wallMap[playerOne->getPos_Index()]->getX() + 0.05, wallMap[playerOne->getPos_Index()]->getY() - 0.11);
	glVertex2f(wallMap[playerOne->getPos_Index()]->getX() + 0.12, wallMap[playerOne->getPos_Index()]->getY() - 0.11);
	glVertex2f(wallMap[playerOne->getPos_Index()]->getX() + 0.085, wallMap[playerOne->getPos_Index()]->getY() - 0.06);
	glEnd();


}

// Enemy will be denoted as a circle
void App::drawEnemy() {

	int num_segments = 100;

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < num_segments; i++) {
		// calculates angle
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
		// calculates x component
		float x = 0.07f * cosf(theta);
		// calculates y component
		float y = 0.07f * sinf(theta);

		glVertex2f(x + wallMap[AI->getPos_Index()]->getCenter_X(), y + wallMap[AI->getPos_Index()]->getCenter_Y());
	}

	glEnd();

}

void App::detonateBomb(int bombLocation) {

	// std::cout << bombLocation << std::endl;

	// checks below
	// playerOne->getPos_Index() <= 80 && playerOne->getPos_Index() >= 72
	if (bombLocation + 9 <= 72 && wallMap[bombLocation + 9]->isBreakable()) {
		wallMap[bombLocation + 9]->setEmpty(true);
		playerOne->addScore(100);
	}
	
	// checks above
	// playerOne->getPos_Index() < 9
	if (bombLocation - 9 >= 9 && wallMap[bombLocation - 9]->isBreakable()) {
		wallMap[bombLocation - 9]->setEmpty(true);
		playerOne->addScore(100);
	}
	
	// checks to the left
	// playerOne->getPos_Index() % 9 == 0
	if (!(bombLocation - 1 % 9 == 0) && wallMap[bombLocation - 1]->isBreakable()) {
		wallMap[bombLocation - 1]->setEmpty(true);
		playerOne->addScore(100);
	}
	
	// checks to the right
	// playerOne->getPos_Index() % 9 == 8
	if (!(bombLocation + 1 % 9 == 8) && wallMap[bombLocation + 1]->isBreakable()) {
		wallMap[bombLocation + 1]->setEmpty(true);
		playerOne->addScore(100);
	}
	
	// this checks if the bomb hits either the player or AI
	if (AI->getPos_Index() == bombLocation + 9 || AI->getPos_Index() == bombLocation - 9 || AI->getPos_Index() == bombLocation + 1 || AI->getPos_Index() == bombLocation - 1) {
		AI->setIsDead(true);
	} else if (playerOne->getPos_Index() == bombLocation + 9 || playerOne->getPos_Index() == bombLocation - 9 || playerOne->getPos_Index() == bombLocation + 1 || playerOne->getPos_Index() == bombLocation - 1) {
		playerOne->setIsDead(true);
	}
	
	wallMap[bombLocation]->setEmpty(true);

	std::cout << "Player Score: " << playerOne->getScore() << std::endl;

}
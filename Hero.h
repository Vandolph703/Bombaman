#ifndef Hero_hpp
#define Hero_hpp

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <vector>
//#include <ctime>
//#include <chrono>
#include "Bomb.h"
//#include "Powerup.h"

class Hero {

	// int id;
	int score;
	int pos_index;					// position based on the grid vector, 0-99	
	int bombCount;					// number of bombs a person can put down
	//float movementSpeed;			// how many spaces the person can move
	//float bombRadius;				// how many spaces the blast is
	bool isDead;
	int whereIsBomb;

	float x, y, w, h;

	//std::vector<Powerup*> pow_Vector;		// need to make Powerup Objects

	public:

		Bomb* playerBomb = new Bomb();

		Hero(int pos_index) {
			this->x = 0;				// needed ??
			this->y = 0;				// needed ??
			this->w = 0;				// needed ??
			this->h = 0;				// needed ??
			score = 0;
			this->pos_index = pos_index;
			bombCount = 1;
			//movementSpeed = 0.1777;			// either we do it based on vector grid or grid distance
			isDead = false;
		}

		~Hero() {
			playerBomb->~Bomb();
		}

		void setX(float x) {
			this->x = x;
		}

		void setY(float y) {
			this->y = y;
		}

		void setW(float w) {
			this->w = w;
		}

		void setH(float h) {
			this->h = h;
		}

		void bombPlacement(int whereIsBomb) {
			this->whereIsBomb = whereIsBomb;
		}

		void addScore(int score) {
			this->score += score;
		}

		void move(int pos_index) {
			if (this->pos_index + pos_index >= 0 && this->pos_index + pos_index <= 80) {
				this->pos_index += pos_index;
			}
		}

		void setBombCount(int bombCount) {
			this->bombCount = bombCount;
		}

		void increaseBombCount() {
			this->bombCount++;
		}

		void decreaseBombCount() {
			this->bombCount--;
		}

		/*
		void setMovementSpeed(int movementSpeed) {
			this->movementSpeed = movementSpeed;
		}
		*/

		void setIsDead(bool isDead) {
			this->isDead = isDead;
		}

		int getBombCount() {
			return bombCount;
		}

		int getScore() {
			return score;
		}

		int getPos_Index() {
			return pos_index;
		}

		int getBomb() {
			return whereIsBomb;
		}

		bool getIsDead() {
			return isDead;
		}

		float getX() {
			return x;
		}
		float getY() {
			return y;
		}
		float getW() {
			return w;
		}

		float getH() {
			return h;
		}

		/*
		void draw() {
			glBegin(GL_POLYGON);
			glColor3d(1.0, 0.0, 0.0);
			glVertex2f(gridMap[this->getPos_Index()]->getX() + 0.06, gridMap[this->getPos_Index()]->getY() - 0.11);
			glVertex2f(gridMap[this->getPos_Index()]->getX() + 0.11, gridMap[this->getPos_Index()]->getY() - 0.11);
			glVertex2f(gridMap[this->getPos_Index()]->getX() + 0.085, gridMap[this->getPos_Index()]->getY() - 0.06);
			glEnd();
		}
		*/

		void detonateBomb() {

		}

};

#endif

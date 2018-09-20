#ifndef _RECT_H_
#define _RECT_H_

class Rect {

	protected:
		float x, y, width, height, center_x, center_y;
		//bool player;
		//int holds = 0;
	
	public:

		// Constructor and Destructor
		Rect();
		Rect(float x, float y, float width, float height);
		~Rect();

		// setters
		void setX(float x);
		void setY(float y);
		void setWidth(float width);
		void setHeight(float height);
		//void setHolds(int holds);
		//void setPlayer(bool player);


		// getters
		float getX();
		float getY();
		float getWidth();
		float getHeight();
		float getCenter_X();
		float getCenter_Y();
		//bool isPlayerHere();
		//int getHolds();

		// checks what is inside the tile
		//bool contains(float x, float y);

		// checks if the tile
		//bool isEmpty();

};

// default constructor
Rect::Rect() {
	x = 0.0;
	y = 0.0;
	width = 0.0;
	height = 0.0;
	center_x = x + (width / 2);
	center_y = y - (height / 2);
}

// constructor
Rect::Rect(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	//player = false;
	center_x = x + (width / 2);
	center_y = y - (height / 2);
}
Rect::~Rect() {}

// setters
void Rect::setX(float x) {
	this->x = x;
}
void Rect::setY(float y) {
	this->y = y;
}
void Rect::setWidth(float width) {
	this->width = width;
}
void Rect::setHeight(float height) {
	this->height = height;
}

/*
void Rect::setHolds(int holds) {
	this->holds = holds;
}
*/

/*
void Rect::setPlayer(bool player) {
	this->player = player;
}
*/

// getters
float Rect::getX() {
	return x;
}
float Rect::getY() {
	return y;
}

float Rect::getWidth() {
	return width;
}
float Rect::getHeight() {
	return height;
}

float Rect::getCenter_X() {
	return center_x;
}

float Rect::getCenter_Y() {
	return center_y;
}

/*
int Rect::getHolds() {
	return holds;
}
*/

/*
bool Rect::isPlayerHere() {
	return player;
}
*/

/*
// checks what is inside the tile
bool Rect::contains(float x, float y) {
	return true;
}

// checks if tile is empty
bool Rect::isEmpty() {
	if (holds == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
*/

#endif

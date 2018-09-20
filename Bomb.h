#ifndef _TICKING_BOMB
#define _TICKING_BOMB
//#include <ctime>
//#include <chrono>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


class Bomb {

	float r;							// color of bomb is red
	float radius;

	public:

		Bomb() {
			r = 1.0f;
			radius = 0.177;
		}

		~Bomb() {}

		void setRadius(float radius) {
			this->radius = radius;
		}

		float getRadius() {
			return radius;
		}

		float getColor() {
			return r;
		}

};

#endif
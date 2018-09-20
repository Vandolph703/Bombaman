#include "Rect.h"

class Wall : public Rect {

	float r, g, b;

	bool empty;
	bool breakable;
	int pos_index;

	public:

		Wall(float r, float g, float b, bool empty, bool breakable, int pos_index, float x, float y, float width, float height) : Rect(x, y, width, height) {					// Rect(float x, float y, float width, float height)
			this->r = r;
			this->g = g;
			this->b = b;
			this->empty = empty;
			this->breakable = breakable;
			this->pos_index = pos_index;
		}

		void setEmpty(bool empty) {
			this->empty = empty;
			if (empty == true) {						// when the bomb explodes, the breakable wall disappears and that part of the grid is now empty
				setColor(0.0, 0.0, 0.0);
				this->breakable = false;
			}
		}

		void setPos_Index(int pos_index) {
			this->pos_index = pos_index;
		}

		bool isEmpty() {
			return empty;
		}

		bool isBreakable() {
			return breakable;
		}

		int getPos_Index() {
			return pos_index;
		}

		void setColor(float r, float g, float b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}

		float getR() {
			return r;
		}

		float getG() {
			return g;
		}

		float getB() {
			return b;
		}

};
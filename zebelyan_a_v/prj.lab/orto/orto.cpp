/// ORTO !!

#include <iostream>

class Quad {
public:
	Quad(double x_start, double y_start, double l, double h) {
		this->xs = x_start;
		this->ys = y_start;
		this->length = l;
		this->height = h;
	}
	void Draw() {
		std::cout << std::endl;
		std::cout << "Start: (" << xs << "," << ys << ")" << std::endl <<
			"length and height: (" << length << "," << height << ")" << std::endl;
	}

	void Scale(double k) {
		length = length * k;
		height = height * k;
	}

private:
	double length, height, xs, ys;
};

int main() {
	Quad first(1, 1, -22, 2);
	first.Draw();
	first.Scale(2);
	first.Draw();

	return 0;
}

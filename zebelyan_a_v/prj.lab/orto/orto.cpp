#include <iostream>

class Quad {
public:
	Quad(double xs, double ys, double xe, double ye) {
		this->x_start = xs;
		this->y_start = ys;
		this->x_end = xe;
		this->y_end = ye;
	}
	void Draw() {
		std::cout << std::endl;
		std::cout << "Square with vertices:" << std::endl<<
			"(" << x_start << ", " << y_start << ")" << std::endl <<
			"(" << x_end << ", " << y_end<< ") " << std::endl;
	}

	void Scale(double k) {
		double x_radius = (x_end - x_start) / 2;
		double y_radius = (y_end - y_start) / 2;
		double x_center = x_end - (x_end - x_start) / 2;
		double y_center = y_end - (y_end - y_start) / 2;

		x_start = x_center - x_radius * k;
		y_start = y_center - y_radius * k;
		x_end= x_center + x_radius * k;
		y_end = y_center + y_radius * k;

	}
	
	void Union(){
	
	}

	void Intersection() {

	}

private:
	double x_start, y_start, x_end, y_end;
};

int main() {
	Quad first(1, 1, 2, 2);
	first.Draw();
	first.Scale(3.1);
	first.Draw();

	return 0;
}

#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <iomanip>
# define PI 3.14159265358979323846
# define g 9.80665
using namespace std;
int main() {
	ofstream cout("yeet.asy");
	const double precision = 256, airDensity = 1.2, scale = 50; 
	//precision is how many times it calculates per second in the simulation
	//scale is so that the labels for the start, end, and peak show up correctly
	long double vInit, mass , angle , dragCoeff , crossArea ;
	cin >> vInit >> mass >> angle >> dragCoeff >> crossArea;
	long double x = 0, y = 0, vx = cos(angle) * vInit, vy = sin(angle) * vInit;
	double prevx, prevy, maxx = 0, maxy = 0;
	cout << "defaultpen(1);\n";
	while (y >= 0) {
		prevx = x;
		prevy = y;
		x += vx / precision;
		y += vy / precision;
		if (y > maxy) {
			maxy = y;
			maxx = x;
		}
		/*double slope = (y-prevy)/(x-prevx);
		double yint = y-slope*x;
		cout<<"y = "<<slope<<"x + "<<yint<<"{"<<prevx<<" <= x < "<<x<<"};\n";*/
		cout << "draw((" << scale * prevx << "," << scale * prevy << ")..(" << scale * x << "," << scale * y << "));\n";
		vy -= g / precision;
		const long double dragx = 0.5 * airDensity * vx * vx * dragCoeff * crossArea;
		vx > 0 ? vx -= dragx / mass / precision : vx += dragx / mass / precision;
		const long double dragy = 0.5 * airDensity * vy * vy * dragCoeff * crossArea;
		vy > 0 ? vy -= dragy / mass / precision : vy += dragy / mass / precision;
	}
	cout << setprecision(3) << "label(\"start (0, 0)\", (0,0), SW);\n";
	cout << setprecision(3) << "label(\"end (" << x << ", 0)\", " << "(" << scale * x << "," << scale * y << "), SE);\n";
	cout << setprecision(3) << "label(\"peak (" << maxx << ", " << maxy << ")\", " << "(" << scale * maxx << "," << scale * maxy << "), N);\n";
	cout << "dot((0, 0));\n";
	cout << "dot((" << scale * x << ", " << scale * y << "));\n";
	cout << "dot((" << scale * maxx << ", " << scale * maxy << "));\n";
}
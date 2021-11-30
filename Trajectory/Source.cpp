#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>
# define PI 3.14159265358979323846
# define g 9.80665
using namespace std;
int main() {
	string filename;
	cout << "output file name: ";
	cin >> filename;
	if (filename.substr(filename.size() - 4, 4) != ".asy") filename.append(".asy");
	ofstream fout(filename);
	const double precision = 256, airDensity = 1.2;
	long double vInit, mass, angle, dragCoeff, crossArea;
	cout << "Initial velocity of projectile: ";
	cin >> vInit;
	cout << "Mass of projectile: ";
	cin >> mass;
	cout << "Angle of launch (rad): ";
	cin >> angle;
	cout << "Drag coefficient of projectile: ";
	cin >> dragCoeff;
	cout << "Cross sectional area of projectile: ";
	cin >> crossArea;

	bool err = 0;
	if (vInit <= 0) {
		cout << "error: initial velocity must be positive\n";
		err = 1;
	}
	if (mass <= 0) {
		cout << "error: mass must be positive\n";
		err = 1;
	}
	if (angle <= 0 || angle > 1.571) {
		cout << "error: angle must be above 0 and less than pi/2\n";
		err = 1;
	}
	if (dragCoeff < 0) {
		cout << "error: drag coefficient must be nonnegative\n";
		err = 1;
	}
	if (crossArea < 0) {
		cout << "error: cross sectional area must be nonnegative\n";
		err = 1;
	}
	if (err) return -1;

	long double x = 0, y = 0, vx = cos(angle) * vInit, vy = sin(angle) * vInit;
	long double prevx, prevy, peakx = 0, peaky = 0;
	fout << "defaultpen(1);\n";
	vector<pair<double, double>>coords = { {0,0} };
	while (y >= 0) {
		prevx = x;
		prevy = y;
		x += vx / precision;
		y += vy / precision;
		if (y > peaky) {
			peaky = y;
			peakx = x;
		}
		coords.push_back({ x,y });
		vy -= g / precision;
		const long double dragx = 0.5 * airDensity * vx * vx * dragCoeff * crossArea;
		vx > 0 ? vx -= dragx / mass / precision : vx += dragx / mass / precision;
		const long double dragy = 0.5 * airDensity * vy * vy * dragCoeff * crossArea;
		vy > 0 ? vy -= dragy / mass / precision : vy += dragy / mass / precision;
	}

	double scale = 1000 / max(x, peaky);
	for (int i = 1; i < coords.size(); i++) {
		fout << "draw((" << scale * coords[i-1].first << "," << scale * coords[i-1].second << ")..(" << scale * coords[i].first << "," << scale * coords[i].second << "));\n";
	}
	fout.precision(3);
	fout << "label(\"start (0, 0)\", (0,0), SW);\n";
	fout << "label(\"end (" << x << ", 0)\", " << "(" << scale * x << "," << scale * y << "), SE);\n";
	fout << "label(\"peak (" << peakx << ", " << peaky << ")\", " << "(" << scale * peakx << "," << scale * peaky << "), N);\n";
	fout << "dot((0, 0));\n";
	fout << "dot((" << scale * x << ", " << scale * y << "));\n";
	fout << "dot((" << scale * peakx << ", " << scale * peaky << "));\n";
	return 0;
}
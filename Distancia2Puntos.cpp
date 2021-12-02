//Adrian Valdes
//A01720438
//Closest2Points

#include <iostream>
#include <algorithm>
#include <vector>
#include <cfloat>
#include <cmath>

using namespace std;

struct Point{
	float x, y;
	//Constructor
	Point() {
		x = y = 0;
	}
	//local y paramentros
	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

bool compareX(const Point& p1, const Point& p2) {
	return(p1.x < p2.x);
}

bool compareY(const Point &p1, const Point &p2) {
	return (p1.y < p2.y);
}

float dist(Point &p1, Point &p2) {
	float nval = (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
	cout << nval << endl;
	return nval;//sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForce(vector<Point> &P, int ini, int fin) {
	float min2 = FLT_MAX;
	for (int i = ini; i < fin; i++) {
		for (int j = i + 1; j <= fin; j++) {
			min2 = min(min2, dist(P[i], P[j]));
		}
	}
	return min2;
}

float stripClosest(vector<Point> &strip, float dMenor) {
	float minStrip = dMenor;
	sort(strip.begin(), strip.end(), compareY);
	for (int i = 0; i < strip.size() - 1; i++) {
		for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minStrip; j++) {
			minStrip = min(minStrip, dist(strip[i], strip[j]));
		}
	}
	return minStrip;
}

// Complejidad: O(n logn)
float closest_Helper(vector<Point>& P, int ini, int fin) {
	// Si en el rango existen 3 o menos puntos ==> Fuerza Bruta.
	if (fin-ini < 3) {
		return bruteForce(P, ini, fin);
	}
	int mid = (ini + fin) / 2;
	Point midPoint = P[mid];
	// Hago las 2 llamadas recursivas
	float dl = closest_Helper(P, ini, mid);
	float dr = closest_Helper(P, mid+1, fin);
	float dMenor = (dl < dr) ? dl : dr;

	// Construir un vector que contendra los puntos cercanos (menor o igual a dMenor)
	// Del Medio
	vector<Point> strip;
	for (int i = ini; i <= fin; i++) {
		if (abs(P[i].x - midPoint.x) < dMenor) {
			strip.push_back(P[i]);
		}
	}
	// Encontrar la menor distancia en el vector strip.
	float ds = stripClosest(strip, dMenor);

	dMenor = min(dMenor, ds);
	return dMenor;
}

float closest(vector<Point> &P) {
	// Ordenar con respecto al eje X
	sort(P.begin(), P.end(), compareX);
	return closest_Helper(P, 0, P.size()-1);
}

int main() {
	// n = cantidad de puntos
	int n;
	float x, y;
	cin >> n;
	vector<Point> P(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		P[i] = Point(x, y);
	}
	float dist = closest(P);
	cout.precision(2);
	cout << "La distancia menor es: " << fixed << dist << endl;
	return 0;
}

/*
5
5 10
2 30
1 15
10 2
20 5
*/

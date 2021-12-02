//Adrian Valdes Zavala 
//A01720439

#include <iostream>
#include <algorithm>
#include <vector>
#include <cfloat>
#include <cmath>

using namespace std;

string fren1, fren2, afren1, afren2;
float cont = FLT_MAX;
string bff;

struct Point {
	float x, y;
	string s;
	//Constructor
	Point() {
		x = y = 0;
		s = "";
	}
	//local y paramentros
	Point(float x, float y, string s) {
		this->x = x;
		this->y = y;
		this->s = s;
	}
};

bool compareX(const Point& p1, const Point& p2) {
	return(p1.x < p2.x);
}

bool compareY(const Point& p1, const Point& p2) {
	return (p1.y < p2.y);
}

float dist(Point& p1, Point& p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForce(vector<Point>& P, int ini, int fin) {
	float min2 = FLT_MAX;
	for (int i = ini; i < fin; i++) {
		for (int j = i + 1; j <= fin; j++) {
			min2 = min(min2, dist(P[i], P[j]));
		}
	}
	return min2;
}

float stripClosest(vector<Point>& strip, float dMenor) {
	float minStrip = dMenor;
	sort(strip.begin(), strip.end(), compareY);
	for (int i = 0; i < strip.size() - 1; i++) {
		for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minStrip; j++) {
			minStrip = min(minStrip, dist(strip[i], strip[j]));
			if (minStrip < cont) {
				fren1 = strip[i].s;
				fren2 = strip[j].s;
				cont = minStrip;
			}
		}
	}

	if (fren1 > fren2) {
		afren2 = fren1;
		afren1 = fren2;
		fren1 = afren1;
		fren2 = afren2;
	}

	bff = fren1 + " & " + fren2 + " ";
	return minStrip;
}

// Complejidad: O(n logn)
float closest_Helper(vector<Point>& P, int ini, int fin) {
	// Si en el rango existen 3 o menos puntos ==> Fuerza Bruta.
	if (fin - ini < 3) {
		return bruteForce(P, ini, fin);
	}
	int mid = (ini + fin) / 2;
	Point midPoint = P[mid];
	// Hago las 2 llamadas recursivas
	float dl = closest_Helper(P, ini, mid);
	float dr = closest_Helper(P, mid + 1, fin);
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

float closest(vector<Point>& P) {
	// Ordenar con respecto al eje X
	sort(P.begin(), P.end(), compareX);
	return closest_Helper(P, 0, P.size() - 1);
}

int main() {
	// n = cantidad de puntos
	int n;
	string s;
	float x, y;
	cin >> n;
	vector<Point> P(n);
	for (int i = 0; i < n; i++) {
		cin >> s;
		cin >> x >> y;
		P[i] = Point(x, y, s);
	}
	float dist = closest(P);
	cout.precision(2);
	cout << "Best friend in BeagleTown are: " << fixed << bff << "(" << dist << ")" << endl;
	return 0;
}

/*
//sin nombres
5
5 10
2 30
1 15
10 2
20 5

5
Sparko 5 10
Rocky 2 30
prue 1 15
Nico 10 2
Nerea 20 5
==> Best friend in BeagleTown are: Sparko & prue (6.40)

5
Sparko 5 10
Rocky 2 7
Zrue 1 13
Nico 9 24
Nerea 10 52
==> Best friend in BeagleTown are: Rocky & Sparko (4.24)

5
Sparko 5.12547 10.12547
Rocky 2.12547  30.12547
Zrue 1.12547  15.12547
Nico 10.12547  2.12547
Nerea 20.12547  5.12547
==> Best friend in BeagleTown are: Sparko & Zrue (6.40)

5
Sparka 5 10
Rocky 1.83 7
Zrue 9 13.15
Nico 7.19 12
Nerea 10 10058.2
==> Best friend in BeagleTown are: Nico & Zrue (2.14)
*/
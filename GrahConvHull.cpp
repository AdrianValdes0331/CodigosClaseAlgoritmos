// Convex Hull ==> Graham Scan
// Adrian valdes
// A01720439
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

struct Point {
	int x, y;
	Point() {
		x = y = 0;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

// Punto Pivote
Point p0;

int distSq(Point& p1, Point& p2) {
	return  (p1.x - p2.x) * (p1.x - p2.x) +
			(p1.y - p2.y) * (p1.y - p2.y);
}

// 0 = p0, p1 y p2 ==> collineales
// 1 ==> Clockwise
// 2 == CounterClockWise
int orientation(Point& p0, Point& p1, Point& p2) {
	int v = (p1.y - p0.y) * (p2.x - p1.x) - 
			(p1.x - p0.x) * (p2.y - p1.y);
	if (v == 0) {
		return 0;
	}
	return (v > 0) ? 1 : 2;
}

bool compare(Point &p1, Point &p2) {
	// Encontrar la orientacion
	int o = orientation(p0, p1, p2);
	if (o == 0) {
		return (distSq(p0, p2) >= distSq(p0, p1));
	}
	return (o == 2);
}

Point nextToTop(stack<Point>& s) {
	Point p = s.top();
	s.pop();
	Point ans = s.top();
	s.push(p);
	return ans;
}

void convexHull(vector<Point> &points) {
	int n = points.size();
	// Encontrar el punto más abajo
	int ymin = points[0].y, minIdx = 0;
	for (int i = 1; i < n; i++) {
		int y = points[i].y;
		if (y < ymin || (ymin == y && points[i].x < points[minIdx].x)) {
			ymin = points[i].y;
			minIdx = i;
		}
	}
	// intercambio el punto encontrado como minIdx a la posicion 0
	Point temp = points[0];
	points[0] = points[minIdx];
	points[minIdx] = temp;
	// Ordenar los n-1 puntos restantes (sin incluir al 0) con respecto al punto 0.
	// Un punto p1 esta antes de p2, p2 tiene un angulo mayor (en contra de las manecillas)
	// con respecto a p1
	p0 = points[0];
	sort(points.begin() + 1, points.end(), compare);
	// Si más de 1 punto tienen el mismo angulo con respecto a p0;
	// Solo dejo al más lejano.
	int m = 1;
	for (int i = 1; i < n; i++) {
		while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
			i++;
		}
		points[m] = points[i];
		m++;
	}
	// solamente te quedan m puntos (de los n de entrada)
	if (m < 3) {
		return;
	}
	stack<Point> s;
	s.push(points[0]);
	s.push(points[1]);
	s.push(points[2]);
	// procesamos a los m-3 puntos
	for (int i = 3; i < m; i++) {
		//Checar el sig. punto con respecto a los 2 puntos en el que tope
		Point nTT = nextToTop(s);
		while (s.size() > 1 && orientation(nTT, s.top(), points[i]) != 2) {
			s.pop();
			nTT = nextToTop(s);
		}
		s.push(points[i]);
	}
	// Vaciamos el stack porque esos son los puntos  externos del polígono (convex_hull)
	while (!s.empty()) {
		Point p = s.top();
		cout << "(" << p.x << ", " << p.y << ")" << endl;
		s.pop();
	}
}

int main() {
	vector<Point> points;
	// n = cantidad de puntos
	int n, x, y;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		points.push_back(Point(x, y));
	}
	convexHull(points);
	return 0;
}

/*
8
0 3
1 1
2 2
4 4
0 0
1 2
3 1
3 3
*/

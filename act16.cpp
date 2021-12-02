#include <iostream>
#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <cmath>

using namespace std;
const float minn = 0.00000001;
float width, height, door, worker;

struct Node {
    float x, y;
};

// Complejidad O(n^2)
void solve(int a, float b, float c, float eq, 
    float eq2, float eq3, float eq4, float tans) {
    Node ans[999];
    
    for (int i = 0; i < worker; i++) {

        //Division de rectangulo en 4 secciones
        //Seccion 1
        tans = eq;
        //Seccion 2
        if (eq2 > minn) {
            if (tans - minn > eq2) {
                tans -= eq2;
                eq2 = 0;
            }
            else if (fabs(tans - eq2) <= minn) {
                ans[i].x = width; 
                ans[i].y = height;
                eq2 = 0;
                continue;
            }
            else {
                float tri1 = (tans * 2) / (width - door);
                a += tri1;
                ans[i].x = width; 
                ans[i].y = a;
                eq2 -= tans;
                continue;
            }
        }

        //Seccion 3
        if (eq3 > minn) {
            if (tans - minn > eq3) {
                tans -= eq3;
                eq3 = 0;
            }
            else if (fabs(tans - eq3) <= minn) {
                ans[i].x = 0; 
                ans[i].y = height;
                eq3 = 0;
                continue;
            }
            else {
                float tri2 = (tans * 2) / height;
                b -= tri2;
                ans[i].x = b; 
                ans[i].y = height;
                eq3 -= tans;
                continue;
            }
        }

        //Seccion 4
        if (eq4 > minn) {
            if (tans - minn > eq4) {
                tans -= eq4;
                eq3 = 0;
            }
            else if (fabs(tans - eq4) <= minn) {
                ans[i].x = 0; 
                ans[i].y = 0;
                eq4 -= 0;
                continue;
            }
            else {
                float tri3 = (tans * 2) / door;
                c -= tri3;
                ans[i].x = 0; 
                ans[i].y = c;
                eq3 -= tans;
                continue;
            }
        }
    }

    cout << fixed;
    cout << setprecision(3) << ans[0].x << " "  << ans[0].y;
    for (int i = 1; i < worker - 1; i++) {
        cout << " " << setprecision(3) << ans[i].x << " "  << ans[i].y;
    }
    cout << endl;
}

int main() {
    while ((cin >> width >> height >> door >> worker) && 
        (width != 0, height != 0, door != 0, worker != 0)) {
        int a = 0;
        float tans = 0.0;

        float b = width, c = height;
        float eq = (width * height) * 1.0 / worker;
        float eq2 = (width - door) * height * 1.0 / 2.0;
        float eq3 = width * height * 1.0 / 2.0;
        float eq4 = (door) * height * 1.0 / 2.0;
        solve(a, b, c, eq, eq2, eq3, eq4, tans);
    }
    return 0;
}

/*
3 5 2 4
10 10 5 2
10 10 5 4
0 0 0 0
=> 2.500 5.000 1.000 5.000 0.000 3.750
=> 5.000 10.000
=> 10.000 10.000 5.000 10.000 0.000 10.000

4 4 2 8
4 4 2 4
6 6 3 6
6 6 4 3
6 6 2 3
6 6 3 3
0 0 0 0
=> 4.000 2.000 4.000 4.000 3.000 4.000 2.000 4.000 1.000 4.000 0.000 4.000 0.000 2.000
=> 4.000 4.000 2.000 4.000 0.000 4.000
=> 6.000 4.000 5.000 6.000 3.000 6.000 1.000 6.000 0.000 4.000
=> 4.000 6.000 0.000 6.000
=> 6.000 6.000 2.000 6.000
=> 5.000 6.000 1.000 6.000

7 8 9 7
6 8 7 5
1 2 9 7
0 0 0 0
=> 5.000 8.000 3.000 8.000 1.000 8.000 0.000 7.111 0.000 5.333 0.000 3.556
=> 3.600 8.000 1.200 8.000 0.000 6.629 0.000 3.886
=> 0.714 2.000 0.429 2.000 0.143 2.000 0.000 1.968 0.000 1.905 0.000 1.841

1 2 3 4
4 3 2 1
5 8 9 7
7 8 4 1
2 2 2 2
0 0 0 0
=> 0.500 2.000 0.000 2.000 0.000 1.667
=> 0.000 0.000
=> 3.571 8.000 2.143 8.000 0.714 8.000 0.000 7.365 0.000 6.095 0.000 4.825
=> 0.000 0.000
=> 0.000 2.000

*/
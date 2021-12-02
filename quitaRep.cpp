//Profe: Luis Humberto Gonzalez
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 'B' - 'A' = 1
// 'E' - 'A' = 4
// 'A' - 'A' = 0

//Complejidad: O(n)
string quitaRep(string s) {
	vector<bool> let(26, false);
	string sal = "";
	for (int i = 0; i < s.length(); i++) {
		if (!let[s[i] - 'A']) {
			sal += s[i];
			let[s[i] - 'A'] = true;
		}
	}
	return sal;
}

int main() {
	string s;
	cin >> s;
	cout << quitaRep(s) << endl;
}


#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAX 132

using namespace std;

// Complejidad: O(n)
int cantMayorA100(int data[MAX], int n){
	int contador = 0;
	for (int i = 0; i < n; i++) {
		if (data[i] > 100) {
			contador++;
		}
	}
	return contador;
}
//Complejidad: 0(n)
int cantMayA100DyV_helper(int data[MAX], int inf, int sup) {
	if (inf == sup) {
		return(data[inf] > 100) ? 1 : 0; 
		/*? = 
		if (data[inf] > 0)
		return 1;
		else
		return 0;
		*/
	}
	int mit = (inf + sup) / 2;
	return cantMayA100DyV_helper(data, inf, mit) + 
		cantMayA100DyV_helper(data, mit + 1, sup);
}
//Complejidad: O(n)
int cantMayorA100DyV(int data[MAX], int n){
	return cantMayA100DyV_helper(data, 0, n-1);
}
//Complejidad: O(n^2)
int cantMayorM100(int data[MAX][MAX], int n){
	int contador = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (data[i][j] > 100) {
				contador++;
			}
		}
	}
	return contador;
}
//Complejidad: O(n^2) //si no es potencia de 2 se congela
int cantMayM100DyV_helper(int data[MAX][MAX], int rinf, int rsup, int cinf, int csup)
{
	if (cinf == csup && rinf == rsup) {
		return(data[rinf][cinf] > 100) ? 1 : 0;
	}
	int rmit = (rinf + rsup) / 2;
	int cmit = (cinf + csup) / 2;
	return cantMayM100DyV_helper(data, rinf, rmit, cinf, cmit) +
		   cantMayM100DyV_helper(data, rinf, rmit, cmit + 1, csup) +
		   cantMayM100DyV_helper(data, rmit+1, rsup, cinf, cmit) +
		   cantMayM100DyV_helper(data, rmit+1, rsup, cmit+1, csup);
}

int cantMayorM100DyV(int data[MAX][MAX], int n){
	return cantMayM100DyV_helper(data, 0, n - 1, 0, n - 1);
}

void printArr(int arr[MAX], int n){
	for (int i=0; i<n; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

void printMat(int mat[MAX][MAX], int n){
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	int arr[MAX], mat[MAX][MAX], n;
	cin >> n;
	srand (time(NULL));
	for (int i=0; i<n; i++){
		arr[i] = rand() % 400; 
	}
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			mat[i][j] = rand() % 400; 
		}
	}
	cout << "Arreglo:" << endl;
	printArr(arr, n);
	cout << endl;
	cout << "Matriz: " << endl;
	printMat(mat, n);
	cout << endl;
	cout << "Cantidad Mayores 100 arr Iterativo: " << cantMayorA100(arr, n) << endl;
	cout << "Cantidad Mayores 100 arr Div y Ven: " << cantMayorA100DyV(arr, n) << endl;
	cout << "Cantidad Mayores 100 mat Iterativo: " << cantMayorM100(mat, n) << endl;
	cout << "Cantidad Mayores 100 mat Div y Ven: " << cantMayorM100DyV(mat, n) << endl;
}
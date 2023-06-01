#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <cstdlib> // rand
#include <ctime> // time
#include <cmath> // floor

using namespace std;

void imprimirArrya(int array[], int nElements){
    cout << nElements << endl;
    for (int i = 0; i < nElements; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

void leerArray (int array[], int maxElements, int& nElements){
    
    do{
        cout << "Cuantos elementos quiere introducir:  ";
        cin >> nElements;
    }while(nElements < 0 || nElements > maxElements);

    
    for (int i = 0; i < nElements; i++){
        cout << "Ingrese un numero: ";
        cin >> array[i];
    }

}

int buscarMinimoArray(int array[], int inicial, int final){
    int posMin = inicial;
    
    for (int i = inicial; i <= final; i++){
        if (array[i] < array[posMin]){
            posMin = i;
        }
    }
    return posMin;
}

int main(){
    const int maxElements = 100;
    int array[maxElements];
    int nElements=0;
    leerArray(array, maxElements, nElements);
    imprimirArrya(array, nElements);
    int posMin = buscarMinimoArray(array, 0, nElements-1);
    cout << "El numero minimo es: " << array[posMin] << endl;
    return 0;
}


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

void copiarArray(int array[], int array2[], int nElements){
    for (int i = 0; i < nElements; i++){
        array[i] = array2[i];
    }
}
void invertirArray(int array[], int nElements){
    for (int i = 0; i < nElements/2; i++){
        int tmp = array[i];
        array[i] = array[nElements-1-i];
        array[nElements-1-i] = tmp;
    }
}


int main(){
    const int maxElements = 100;
    int array[maxElements];
    int nElements=0;
    leerArray(array, maxElements, nElements);
    imprimirArrya(array, nElements);
    cout << "Array invertido: " << endl;
    int arrayinv[maxElements];
    copiarArray(arrayinv, array, nElements);
    invertirArray(arrayinv, nElements);
    imprimirArrya(arrayinv, nElements);

    
    return 0;
}
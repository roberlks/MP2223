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

int busquedaSecuencial(int array[], int nElements, int elemento, int final, int inicial = 0){
    int pos = -1;
    bool encontrado = false;
    int i = inicial;
    while (!encontrado && i <= final){
        if(array[i] == elemento){
            pos = i;
            encontrado = true;
        }
        else{
            i++;
        }
    }
    return pos;
}


int main(){
    const int maxElements = 100;
    int array[maxElements];
    int nElements=0;
    leerArray(array, maxElements, nElements);
    imprimirArrya(array, nElements);
    int elemento;
    cout << "Ingrese un numero a buscar: ";
    cin >> elemento;
    int pos = busquedaSecuencial(array, nElements, 0, nElements-1, elemento);
    if (pos == -1){
        cout << "No se encontro el numero" << endl;
    }
    else{
        cout << "Se encontro el numero en la posicion " << pos << endl;
    }
 
    return 0;
}
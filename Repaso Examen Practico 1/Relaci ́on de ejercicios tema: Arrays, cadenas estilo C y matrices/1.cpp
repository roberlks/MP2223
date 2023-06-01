#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <cstdlib> // rand
#include <ctime> // time
#include <cmath> // floor

using namespace std;

/*Haz un programa que lea de la entrada est ́andar el n ́umero de elementos que tendr ́a un
array de enteros, y dos enteros para el rango (m ́ınimo, m ́aximo) de posibles valores que
tomar ́an los elementos del array. El programa rellenar ́a el array con n ́umeros aleatorios
enteros en el rango proporcionado, y posteriormente lo mostrar ́a en la salida est ́andar. El
programa contendr ́a las siguientes funciones:
• La funci ́on main para probar que todo funciona de forma correcta.
• La funci ́on imprimirArray para mostrar en la salida est ́andar el n ́umero de elementos
(y un salto de l ́ınea a continuaci ́on) y los elementos de un array de enteros (separados
por espacios en blanco).
• La funci ́on generarArray que recibe un array de enteros, el n ́umero de elementos a
usar y un rango de valores (m ́ınimo, m ́aximo) y lo rellena con n ́umeros aleatorios en
el rango proporcionado.*/



/**
* @brief Genera un valor del intervalo [minimo,maximo] ambos inclusive
* @param minimo el m ́ınimo valor posible a generar aleatoriamente
* @param maximo el m ́aximo valor posible a generar aleatoriamente
* @return Un n ́umero entero aleatorio en el intervalo [minimo,maximo]
* ambos inclusive
*/
int randomi(int minimo, int maximo)
{
    double u01= std::rand() / (RAND_MAX+1.0); // Uniforme01
    return floor(minimo + u01 * (maximo-minimo+1));
}

void generarArray(int array[], int nElements, int minimo, int maximo){
    // Inicializa el generador con el reloj del sistema
    srand ((int) time(0));
    for (int i = 0; i < nElements; i++){
        array[i] = randomi(minimo, maximo);
    }
}

void imprimirArray(int nElements, int array[]){
    cout << nElements << endl;
    for (int i = 0; i < nElements; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}
int main(int argc, char* argv[])
{
    int array[10000];

    int nElements = 0;
    int minimo = 0;
    int maximo = 0;   



    cout << "Numero de elementos: ";
    cin >> nElements;

    cout << "Minimo: ";
    cin >> minimo;

    cout << "Maximo: ";
    cin >> maximo;
    
    generarArray(array, nElements, minimo, maximo);
    imprimirArray(nElements, array);

    
    return 0;
}
#include <iostream>
using namespace std;

void aumentarTamano(int *&v, int tam, int n){
    int * m = new int [tam+n];
    
    for (int i = 0; i < tam; i++){
        m[i] = v[i];
    }
    for (int i = tam; i < tam+n; i++){
        m[i] = 0;
    }
    delete []v;
    v = m;

}

int main(){
    int * v = new int [100];
    for (int i = 0; i < 100; i++){
        v[i] = i;
    }
    aumentarTamano(v, 100, 10);

    for (int i = 0; i < 110; i++){
        cout << v[i] << endl;
    }
    return 0;
}
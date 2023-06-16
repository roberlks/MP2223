
#include "raylib.h"
#include "Asteroide.h"
#include "PoliReg.h"
#include "Punto2D.h"
#include "ConjuntoAsteroides.h"

#include <string>
#include <cmath>

/*
 INFORME DE PROBLEMAS Y SITUACION ACTUAL ANTES DE DEJARLO:
 * 
 * en el eliminaLados no elimina lo qu ees el lado en si cuando lo llamas, digamos
 * que solo lo hace bien si es un triangulo y por tanto lo elimina
 * 
 * cuando eliminas cierto numero de poligonos se genera uno nuevo en una posicion
 * aleatoria cada vez que eliminas otro. por ejemplo si solo quedan 3 y eliminas 
 * uno pues se genera otro en otra posicion aleatoria y si vuelves a eliminar otro 
 * se vuelve a generar uno pero, es extraño porque este poligono es como si no estuviese
 * ya que al chocarse no se elimina, es como un fantasma que se vuelve a generar cada 
 * vez que eliminas uno d elos que quedan
 * 
 * a veces los primero disparos al tocar la base se eliminan
 * 
 * sin razon aparente disparos no desaparecen al tocar los limites
 
 * 
 *  CONCLUSION :: 
 * 
 *  en cuanto solucionemos el eliminaLados (que seguramente sea problema de que trabaja
 * con una copia y no esta modificando realmente el numero de lados) y arreglemos esa generacion
 * extraña que seguramente sea porque no se esta trabajando bien con el numero de elementos del array
 * estariamos listos para empezar a trabajar con las teclas para el poligono que controlamos nosotros
 * y habriamos terminado
 */




/*
const int screenWidth = 1200;
const int screenHeight = 800;

using namespace std;

void pintaPunto(const Punto2D & p, Color c) {
    DrawCircle(p.getX(), p.getY(), 7.0, c);
}

void pintaLinea(const Punto2D & p1, const Punto2D & p2, Color c){
    DrawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), c);
} 

void pintaPoligono(const PoliReg & poligono1, Color c){
    for (int i = 1 ; i < poligono1.getLados() ; i++){
     
        pintaLinea(poligono1.getVertice(i), poligono1.getVertice(i-1), c);
    }
    pintaLinea(poligono1.getVertice(poligono1.getLados()-1), poligono1.getVertice(0), c);
}

void pintaAsteroide(const Asteroide & asteroide1, Color c){
    pintaPoligono(asteroide1.getRoca(), c);
}

bool chocaLimites(Asteroide & asteroide1) const{
    
    bool choca;
    
    choca = (asteroide1.getPosicion().getX() - asteroide1.getRoca().getRadio() <= 0) ||
            (asteroide1.getPosicion().getX() + asteroide1.getRoca().getRadio() >= screenWidth) ||
            (asteroide1.getPosicion().getY() - asteroide1.getRoca().getRadio() <= 0) ||
            (asteroide1.getPosicion().getY() + asteroide1.getRoca().getRadio() >= screenHeight);
    
    return choca;
}

Asteroide mueve(Asteroide otro){
    Asteroide current(otro);       
    
    current.mover();
    current.rotar();
    
    return current;
}

int main(void) {
    // activación de ventana gráfica
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Modulo de prueba");

    // creación de objetos
    float centroY = screenHeight / 2.0;
    float centroX = screenWidth / 2.0;
    //---------------------------------------------------------
    Punto2D veloc_bala(0,-3);
    PoliReg forma_bala;
    
    Asteroide bala;//(forma_bala,veloc_bala, 0 );
    
    ConjuntoAsteroides poligonos;
    ConjuntoAsteroides disparos;
    
    Color paleta[4] = {GREEN, YELLOW, LIME, PINK};
    
    SetTargetFPS(30); // velocidad de la simulación
    //----------------------------------------------------------
    

    // bucle principal
    //---------------------------------------------------------
    int tick = 0;
    int ticks_del_for = 0;
    
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        
        //-----------------------------------------------------
        // pintar los objetos
        //-----------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            //bucles principales
            for (int i = 0 ; i < poligonos.getUtil() ; i++){
                
                //intercambia velocidades si se chocan dos poligonos
                for (int j = 0 ; j < poligonos.getUtil(); j++){
                    
                    if (poligonos.getConjunto(i)->colisiona(poligonos.getConjunto(j))){
                
                        Punto2D velocidad1(poligonos.getVelocidad(i));
                        Punto2D velocidad2(poligonos.getVelocidad(j));
                    
                        poligonos.setVelocidad(j,velocidad1);
                        poligonos.setVelocidad(i,velocidad2);
                    }
                }
//                cambia velocida si chocan limite
                if (chocaLimites(poligonos.getConjunto(i))){
                    
                    Punto2D nueva_vel(-poligonos.getConjunto(i).getVeloc().getY(),poligonos.getConjunto(i).getVeloc().getX());
                    
                    poligonos.setVelocidad(i,nueva_vel);
                }
                //elimina disparos cuando tocan el limite
                if (chocaLimites(disparos.getConjunto(i))){
                    disparos.eliminaLado(i);
                }
                
                //mueve los poligonos
                poligonos.setElemento(i,mueve(poligonos.getConjunto(i)));
                disparos.setElemento(i,mueve(disparos.getConjunto(i)));
            }
            
            //comprueba si un poligono ha chocado un lado y lo elimina
            for (int i = 0 ; i < poligonos.getUtil() ; i++){
                for (int j = 0 ; j < disparos.getUtil() ; j++){
                    if (poligonos.getConjunto(i).colisiona(disparos.getConjunto(j))){
                        poligonos.eliminaLado(i);
                        disparos.eliminaLado(j);
                    }
                }
            }
            //pinta poligonos y disparos
            for (int i = 0 ; i < poligonos.getUtil() ; i++){
                
                pintaAsteroide(poligonos.getConjunto(i), paleta[i%4]);
               
            }
            
            for (int i = 0 ; i < disparos.getUtil() ; i++){
                pintaAsteroide(disparos.getConjunto(i), RED);
            }
            
//            informacion de arriba
            string s = "ticks: " + to_string(tick);
            DrawText(s.c_str(), 10, 10, 10, LIME);
            DrawText("ESC para salir", 60, 10, 20, LIME);
//            DrawText(t.c_str(), 700,10,20 ,LIME);
        
        
        EndDrawing();
        
        tick++;
        //-----------------------------------------------------
    }

    // cerrar ventana
    //---------------------------------------------------------
    CloseWindow(); 
    //----------------------------------------------------------

    
    return 0;
}
*/


/*ESTE MAIN ES LAMENTABLE*/
/*
#include "raylib.h"
#include "Asteroide.h"
#include "PoliReg.h"
#include "Punto2D.h"
#include "ConjuntoAsteroides.h"

#include <string>
#include <cmath>

const int screenWidth = 1200;
const int screenHeight = 800;

using namespace std;

void pintaPunto(const Punto2D & p, Color c) {
    DrawCircle(p.getX(), p.getY(), 7.0, c);
}

void pintaLinea(const Punto2D & p1, const Punto2D & p2, Color c){
    DrawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), c);
} 

void pintaPoligono(const PoliReg & poligono1, Color c){
    for (int i = 1 ; i < poligono1.getLados() ; i++){
     
        pintaLinea(poligono1.getVertice(i), poligono1.getVertice(i-1), c);
        pintaLinea(poligono1.getVertice(poligono1.getLados()-1), poligono1.getVertice(0), c);
    }
}

void pintaAsteroide(Asteroide & asteroide1, Color c){
    pintaPoligono(asteroide1.getRoca(), c);
}
    
void intercambiaVeloc(Asteroide & uno, Asteroide & otro){ //no funciona
                
        Punto2D velocidad1(uno.getVeloc());
        Punto2D velocidad2(otro.getVeloc());
                    
        uno.setVeloc(velocidad2);
        otro.setVeloc(velocidad1);
}

bool chocaLimites(const Asteroide & asteroide1){
    
    bool choca;
    
    choca = (asteroide1.getPosicion().getX() - asteroide1.getRoca().getRadio() <= 0) ||
            (asteroide1.getPosicion().getX() + asteroide1.getRoca().getRadio() >= screenWidth) ||
            (asteroide1.getPosicion().getY() - asteroide1.getRoca().getRadio() <= 0) ||
            (asteroide1.getPosicion().getY() + asteroide1.getRoca().getRadio() >= screenHeight);
    
    return choca;
}

void moverLateral(Asteroide &nave, bool direccion){
    if (!chocaLimites(nave)){ //nave.getPosicion().getX() > 50
        nave.moverLater(direccion);
    }
}

void moverVertical(Asteroide &nave, bool direccion){
    if (!chocaLimites(nave)){ //nave.getPosicion().getX() > 50
        nave.moverVerti(direccion);
    }
}

int main(void){
    // activación de ventana gráfica
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Modulo de prueba");

    // creación de objetos
    float centroY = screenHeight / 2.0;
    float centroX = screenWidth / 2.0;
    float rotar_nave = 0.0;
    
    
    Punto2D centro(centroX,centroY);
    Punto2D posi_nave(centroX, 50);
    PoliReg forma_nave(3,posi_nave,30);
    
    Punto2D veloc_nave(5,0);
    Asteroide nave(forma_nave,veloc_nave,rotar_nave);
    
    
    bool gameover = false;
    int vidas = 3;
    
    const int MAX_DISPAROS = 10;
    
    ConjuntoAsteroides poligonos;
    ConjuntoAsteroides disparos;
    
    Color paleta[4] = {GREEN, YELLOW, LIME, PINK};
    SetTargetFPS(30); // velocidad de la simulación  
    
    int tick = 0;
    
    //creacion de los conjuntos:
    
    for (int i = 0 ; i < 11 ; i++){
    	Punto2D aleatoria;
    
    	poligonos.aniade(aleatoria,true);
    }
    
    
    while (!WindowShouldClose() & !gameover){
	
	//bucle de comprobacion de colisiones.
        for (int i = 0; i < poligonos.getUtil(); i++) {
            // Comprobar colisiones entre los asteroides y los disparos, y con las paredes
            for (int j = 0; j < disparos.getUtil(); j++) {
                if (poligonos.getElemento(i).colisiona(disparos.getElemento(j))){
                    poligonos.eliminaLado(i);
                    disparos.eliminaLado(j);
                }
            }
                //elimina el disparo si choca el limite
                if (chocaLimites(disparos.getElemento(0))){
                    disparos.eliminaLado(i);
                }
                
                //PROVISIONAL: setea una velocidad nueva aleatoria PROVISIONAL
                if (chocaLimites(poligonos.getElemento(i))){
                    Punto2D new_veloc(2 * -sin(poligonos.getElemento(i).getVeloc().getX()),2 * -cos(poligonos.getElemento(i).getVeloc().getY()));
                    poligonos.getElemento(i).setVeloc(new_veloc);
                }
        }
        
        //bucle de movimientos
	for (int i = 0 ; i < disparos.getUtil() ; i++){
         	disparos.getElemento(i).moverLater(true);   	
        }
            
        for (int i = 0 ; i < poligonos.getUtil() ; i++){
            	poligonos.getElemento(i).moverLater(true);
        }
        
        if(IsKeyDown(KEY_LEFT)) {
            moverLateral(nave, false);
        }
        if(IsKeyDown(KEY_RIGHT)) {
            moverLateral(nave, true);
        }
        if(IsKeyDown(KEY_DOWN)) {
            moverVertical(nave, false);
        }
        if(IsKeyDown(KEY_UP)) {
            moverVertical(nave, true);
        }

        // Disparar
        if (IsKeyPressed(KEY_SPACE) && disparos.getUtil() <= MAX_DISPAROS) { //esto es optimizable
        	
            Punto2D posicion(nave.getPosicion());
       	    disparos.aniade(posicion, false);
        }
        
        //comprobacion de colisiones con ellos mismos
        
        for (int i = 0 ; i < poligonos.getUtil() ; i++){
           for (int j = 0 ; j < poligonos.getUtil() ; j++){
           	if (poligonos.getElemento(i).colisiona(poligonos.getElemento(j))){
                	intercambiaVeloc(poligonos.getElemento(i),poligonos.getElemento(j));
                }
       	   }
       	   
       	   // se comprueban colisiones entre los asteroides y la nave
           if (poligonos.getElemento(i).colisiona(nave)) {
                // La nave ha colisionado con un asteroide
                vidas--;
                
                if (vidas == 0) {
                    gameover = true;
                } 
                else {
                    // se reposiciona la nave de momento no se va a hacer
                    nave.setPosicion(posi_nave);
                }
            }
        }
            
       	BeginDrawing();
            
            ClearBackground(BLACK);
            
            for (int i = 0 ; i < disparos.getUtil() ; i++){
            	pintaAsteroide(disparos.getElemento(i), RED);
            }
            
            for (int i = 0 ; i < poligonos.getUtil() ; i++){
            	pintaAsteroide(poligonos.getElemento(i), YELLOW);
            }
            
            pintaAsteroide(nave, BLUE);
            
//            informacion de arriba
            string s = "ticks: " + to_string(tick);
            string t = "nro de poligonos en pantalla: " + to_string(poligonos.getUtil());
            string u = "nro de disparos en pantalla: " + to_string(disparos.getUtil());
            string z = "coordenadas de la nave: (" + to_string(nave.getPosicion().getX()) + "," + to_string(nave.getPosicion().getY());
            
            DrawText(s.c_str(), 10, 10, 10, LIME);
            DrawText(t.c_str(), 100, 100, 10, LIME);
            DrawText(z.c_str(), 150, 150, 15, LIME);
            
//            DrawText("ESC para salir", 60, 10, 20, LIME);
//            DrawText(t.c_str(), 700,10,20 ,LIME);

            EndDrawing();
        
        tick++;
    }	
        //----------------------------------------------------
    // cerrar ventana
    //---------------------------------------------------------
    CloseWindow();
    //----------------------------------------------------------
    return 0;   
}
//g++ RaylibMain.cpp Punto2D.cpp PoliReg.cpp -I. -lraylib -lpthread -ldl -L. -std=c++14 -o RaylibMain4
*/

/*QUIZAS ESTA VAYA A SER LA VERSION FINAL*/

#include "raylib.h"
#include <chrono>
#include <thread>
#include "Asteroide.h"
#include "PoliReg.h"
#include "Punto2D.h"
#include "ConjuntoAsteroides.h"

#include <string>
#include <cmath>

const int screenWidth = 1200;
const int screenHeight = 800;

using namespace std;

/*PLAN: 
 * consistira en un main con 4 partes claramente diferenciadas
 * (*) PARTE PREVIA AL MAIN:
 *      - metodo que intercambie velocidades en caso de colision
 *      - metodo que detecte si estas colisionando con un limite y con que limite estas colisionando
 *      - de momento solo vamos a disparar hacia abajo
 *      - de momento solo nos vamos a mover hacia los lados
 * 
 *  1. Creacion de objetos y asignacion de parametros.
 *      - obj.Asteroides
 *      - obj.Disparos
 *      - obj.Nave
 *      - declaras las vidas que vas a tener, parametrizarlo con una constante.
 *      - declaras la velocidad de movimiento que va a tener la nave.
 *      - declaras la velocidad de movimiento que va a tener los asteroides
 *      - de momento se va a jugar con 10 poligonos y 10 posibles disparos
 * 
 *  2. Movimiento tanto de nave como de todo lo que haya en pantalla
 *      - se llama al mueve de poligono
 *      - se llama al mueve de nave
 *      - se llama al disparo
 *      - se mueve al disparo
 * 
 *  3. Eliminacion en caso de colision.
 *      - colision entre poligonos
 *      - colision entre disparo y poligono
 *      - colision con las pareces
 * 
 *  4. dibujo de poligonos y menus
 *      - dibujo de todos los cueropos en pantalla.
 *  
 *      - un letrero que te ponga poligono: posicion.
 *      - un letrero que te diga disparos en pantalla.
 *      - un letrero que te diga poligonos en pantalla.
 *      - un letrero que te diga las vidas restantes.
 */
 
void pintaPunto(const Punto2D & p, Color c) {
    DrawCircle(p.getX(), p.getY(), 7.0, c);
}

void pintaLinea(const Punto2D & p1, const Punto2D & p2, Color c){
    DrawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), c);
} 

void pintaPoligono(const PoliReg & poligono1, Color c){
    for (int i = 1 ; i < poligono1.getLados() ; i++){
     
        pintaLinea(poligono1.getVertice(i), poligono1.getVertice(i-1), c);
        pintaLinea(poligono1.getVertice(poligono1.getLados()-1), poligono1.getVertice(0), c);
    }
}

void pintaAsteroide(Asteroide & asteroide1, Color c){
    pintaPoligono(asteroide1.getRoca(), c);
}

void pintaConjunto(ConjuntoAsteroides & uno, Color c){
    for (int i = 0 ; i < uno.getUtil() ; i++){
        Asteroide current(uno.getElemento(i));
        
        pintaAsteroide(current, c);
    }
}
//  ESTAS FUNCIONES SON INVIABLES PORQUE AUNQUE EL CODIGO SEA MAS BONITO ASI RAYLIB NO LO TIRA Y SKIPEA LINEAS
//void colisionAsteroides(ConjuntoAsteroides & uno){
//    for (int i = 0 ; i < uno.getUtil() ; i++){
//        for (int j = 0 ; j < uno.getUtil() ; j++){
//            if (uno.getElemento(i).colisiona(uno.getElemento(j))){
//                
//                Punto2D aux(uno.getElemento(i).getVeloc());
//                
//                uno.getElemento(i).setVeloc(uno.getElemento(j).getVeloc());
//                uno.getElemento(j).setVeloc(aux);
//            }
//        }
//    }
//}
//
//void colisionaDisparo(ConjuntoAsteroides & disparos, ConjuntoAsteroides & poligonos){
//    for (int i = 0 ; i < poligonos.getUtil() ; i++){
//        for (int j = 0 ; j < disparos.getUtil() ; j++){
//            if (poligonos.getElemento(i).colisiona(disparos.getElemento(j))){
//                poligonos.eliminaLado(i);
//                disparos.eliminaLado(j);
//            }
//        }
//    }
//}
//parece mucho codigo pero es para optimizar y hacer mas realista el rebote
bool colisionDcha(const Asteroide & uno){
    return (uno.getPosicion().getX() + uno.getRoca().getRadio() >= screenWidth);
}

bool colisionIzda(const Asteroide & uno){
    return (uno.getPosicion().getX() - uno.getRoca().getRadio() <= 0);
}

bool colisionArrib(const Asteroide & uno){
    return (uno.getPosicion().getY() - uno.getRoca().getRadio() <= 0);
}

bool colisionAbaj(const Asteroide & uno){
    return (uno.getPosicion().getY() + uno.getRoca().getRadio() >= screenHeight);
}

void moverAsteroide(Asteroide & nave,bool direccion){
    if (!colisionDcha(nave)){
        nave.mover(direccion);
    }
    
    if (!colisionIzda(nave)){
        nave.mover(direccion);
    }
}

int main(void){
    // activación de ventana gráfica
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Modulo de prueba");
    
    //DECLARACION DE OBJETOS :: conjuntos
    ConjuntoAsteroides asteroides;
    ConjuntoAsteroides disparos;
    
    //DECLARACION DE OBJETOS :: variables de disparos
    const int MAX_DISP_GEN = 5;
    const int MAX_AST_GEN = 60;
    
    
    //DECLARACION DE OBJETOS :: nave
    const int TAMANIO_NAVE = 25;
    
    Punto2D centro_nave(screenWidth/2,screenHeight-50);
    PoliReg forma_nave(8,centro_nave,TAMANIO_NAVE);
    Punto2D vel_nave(5,0);
    
    Asteroide nave(forma_nave,vel_nave,2); //LA NAVE VA A GIRAR
    
    //DECLARACION DE PARAMETROS :: vidas
    
    int nro_vidas = 3;
    Texture2D corazones = LoadTexture("/home/marinoferpe/Pictures/heart_bueno.png");
    corazones.width = 40;
    corazones.height = 40;
    
    int ticks = 0;
    bool game_over = false;
    bool winer = false;
    
    //DECLARACION DE PARAMETROS :: creacion de los asteroides
    
    int generados = 0;
    int eliminados = 0;
    
    srand(time(0));
    
    // SELECTOR DE FONDO BACKGROUND
    
    const int NUM_COLORES = 2;
    int opcion = 0;
    Color colores[] = {BLACK, WHITE};
    Color seleccionado = BLACK;
    
    while(!WindowShouldClose() && opcion == 0){
    	BeginDrawing();

    	ClearBackground(GRAY);

    	// Muestra las opciones de colores
    	for (int i = 0; i <= NUM_COLORES; i++) {
        	if (opcion == i + 1) {
            DrawRectangle(10, 10 + i * 40, 220, 30, colores[i]);
        	}else{
            DrawRectangleLines(10, 10 + i * 40, 220, 30, BLACK);
         }

        DrawText("Seleccione un color:", 10, 10, 20, BLACK);
        DrawText("1. Negro", 20, 20 + 40 * 1, 20, BLACK);
        DrawText("2. Blanco", 20, 20 + 40 * 2, 20, BLACK);
    	}
    	
    	

    	  EndDrawing();
		
		
		
    // Verifica las teclas presionadas para seleccionar el color
    
    	if (IsKeyPressed(KEY_N)){
        	opcion = 1;
        	seleccionado = BLACK;
    	 } else if (IsKeyPressed(KEY_B)){
       	 opcion = 2;
        	seleccionado = WHITE;
		}
	}
    
    SetTargetFPS(40);
    
    while(!WindowShouldClose() && !game_over){
        
        if (generados < MAX_AST_GEN && asteroides.getUtil() < (rand() % 6 + 1)){
        		const int MAX_AST_FRAME = 1;
        		
        	  for (int i = 0 ; i < MAX_AST_FRAME; i++){ // TRUE ASTEROIDE FALSE DISPARO   
        			if (generados < MAX_AST_GEN){
        				Punto2D pos_aleatoria;
        				asteroides.aniade(pos_aleatoria,true); 
        				generados++;
        			}
    	  		}//aqui true porque estamos creando los asteroides.
      	}
      	
        //PARTE DE DETECCION DE TECLAS + MOVIMIENTOS
        
        if(IsKeyDown(KEY_LEFT) && !colisionIzda(nave)){
            moverAsteroide(nave, false);
        }
        
        if(IsKeyDown(KEY_RIGHT) && !colisionDcha(nave)){
            moverAsteroide(nave, true);
        }
        
        if(IsKeyPressed(KEY_UP) && disparos.getUtil() <= MAX_DISP_GEN){
            disparos.aniade(nave.getPosicion(),false);
        }
        
        //PARTE DE LAS COLISIONES
        
        //COLISIONES DE POLIGONOS CON DISPAROS Y CON ELLOS MISMOS
        for (int i = 0 ; i < asteroides.getUtil() ; i++){

            //ESTO LO HAGO PARA AHORRAR BUCLES FOR PORQUE CREO QUE NO LE DA TIEMPO A TODO
            
            //for para todo lo que tiene que ver con los propios asteroides
            for (int j = 0 ; j < asteroides.getUtil() ; j++){
                if (asteroides.getElemento(i).colisiona(asteroides.getElemento(j))){
                
                    Punto2D aux(asteroides.getElemento(i).getVeloc());
                
                    asteroides.getElemento(i).setVeloc(asteroides.getElemento(j).getVeloc());
                    asteroides.getElemento(j).setVeloc(aux);
                }
            }
            
            asteroides.getElemento(i).mover(true);
            asteroides.getElemento(i).rotar();
            

            
            //for para todo lo que tiene que ver con los asteroides
            
            for(int j = 0 ; j < disparos.getUtil() ; j++){
                

                    int util_anterior = asteroides.getUtil();

                    if (asteroides.getElemento(i).colisiona(disparos.getElemento(j))){
                        asteroides.eliminaLado(i);
                        
                        if (asteroides.getUtil() < util_anterior)
                        	eliminados++;
                        
                        disparos.eliminaLado(j);
                    }
            }
            
            disparos.getElemento(i).mover(true);
            asteroides.getElemento(i).rotar();
            
            //COLISIONES DE DISPAROS CON LIMITES:
            
            if (colisionDcha(asteroides.getElemento(i))){
                Punto2D nueva(-asteroides.getElemento(i).getVeloc().getX(),asteroides.getElemento(i).getVeloc().getY());
                asteroides.getElemento(i).setVeloc(nueva);
            }
            
            if (colisionIzda(asteroides.getElemento(i))){
                Punto2D nueva(-asteroides.getElemento(i).getVeloc().getX(),asteroides.getElemento(i).getVeloc().getY());
                asteroides.getElemento(i).setVeloc(nueva);
            }
            
            if (colisionArrib(asteroides.getElemento(i))){
                Punto2D nueva(asteroides.getElemento(i).getVeloc().getX(),-asteroides.getElemento(i).getVeloc().getY());
                asteroides.getElemento(i).setVeloc(nueva);
            }
            
            if (colisionAbaj(asteroides.getElemento(i))){
                Punto2D nueva(asteroides.getElemento(i).getVeloc().getX(),-asteroides.getElemento(i).getVeloc().getY());
                asteroides.getElemento(i).setVeloc(nueva);
            }
            
            if (colisionArrib(disparos.getElemento(0))){
                disparos.eliminaLado(0);
            }
            
            
            
            if (asteroides.getElemento(i).colisiona(nave)){
              	 nro_vidas--;
                
                nave.setPosicion(centro_nave);
                
                if (nro_vidas == 0){
                  game_over = true;
                 }
             }
        }        
        
        //if (asteroides.getUtil() == 0){
          //  winer = true;
        //}
       
        if (eliminados >= 20){
            winer = true;
            DrawText("Has ganado!", screenWidth / 2 - 70, screenHeight / 2 - 10, 30, GREEN);
            EndDrawing();
            continue;
        }

        
        //PARTE DEL DIBUJO :: FUNCIONA CORRECTAMENTE
        BeginDrawing();
            
            ClearBackground(seleccionado);
            
            pintaConjunto(asteroides,RED);
            pintaConjunto(disparos,LIME);
            pintaAsteroide(nave, BLUE);
            
            for (int k = 0; k < nro_vidas; k++)
            	DrawTexture(corazones, 1050 + k*(corazones.width + 5), 10, RED);
            
            //informacion de arriba
            string s = "ticks: " + to_string(ticks);
            //string t = "nro de poligonos en pantalla: " + to_string(asteroides.getUtil());
            //string u = "nro de disparos en pantalla: " + to_string(disparos.getUtil());
            //string z = "coordenadas de la nave: (" + to_string(nave.getPosicion().getX()) + "," + to_string(nave.getPosicion().getY());
            string a = "nro de asteroides eliminados: " + to_string(eliminados);
            
            DrawText(s.c_str(), 10, 10, 10, BLUE);
            //DrawText(t.c_str(), 100, 100, 10, BLUE);
            //DrawText(z.c_str(), 150, 150, 15, BLUE);
            DrawText(a.c_str(), 950, 60, 15, BLUE);
            
            DrawText("ESC para salir", 10, 50, 15, LIME);
            //DrawText(t.c_str(), 700,10,20 ,LIME);
            
				
        EndDrawing();
        ticks++;
        }
    
    UnloadTexture(corazones);    
    CloseWindow();
        
    return 0; 
}

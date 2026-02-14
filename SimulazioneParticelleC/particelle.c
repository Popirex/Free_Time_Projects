#include <math.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <stdlib.h>

//      DEFINITIONS
#define MAX_RGB 255
#define MAX_RADIUS 20
#define MIN_RADIUS 5
#define WIDTH 1300
#define HEIGHT 1000
#define MAX_VEL 5
#define NUM_PARTICLE 200
#define GRAVITY 1
#define RESISTENCE 0.8
#define MIN_VEL 0.5


//      STRUCTURES

typedef struct{
    Vector2 pos;
    Vector2 vel;
    float radius;
    Color color;

} Particella;




//      FUNCTIONS

Color generaColore(){

    Color colore;

    int red = rand() % MAX_RGB;
    int green = rand() % MAX_RGB;
    int blue = rand() % MAX_RGB;

    colore =(Color){red, green, blue, 255};

    return colore;

}

Vector2 generaPosizione(){
    Vector2 posizione;

    int x = MAX_RADIUS + ( rand() % (WIDTH - MAX_RADIUS));
    int y = MAX_RADIUS + (rand() % (HEIGHT - MAX_RADIUS));
    posizione = (Vector2) {x, y};

    return posizione;

}

Vector2 generaVelocita(){
    Vector2 velocita;

    int x = (rand() % (MAX_VEL * 2) ) - MAX_VEL;
    int y = (rand() % (MAX_VEL * 2) ) - MAX_VEL;

    velocita = (Vector2) {x, y};

    return velocita;
}

int generaRaggio(){
    int raggio;

    raggio = MIN_RADIUS + ( rand() % (MAX_RADIUS - MIN_RADIUS));

    return raggio;
}

void DrawParticles(Particella particelle[]){

    for(int i = 0; i < NUM_PARTICLE; i++){
        DrawCircleV(particelle[i].pos, particelle[i].radius, particelle[i].color);
    }

}

void AnimateParticles(Particella particelle[]){
    for(int i = 0; i < NUM_PARTICLE; i++){
        if(particelle[i].pos.x - particelle[i].radius <= 0 || particelle[i].pos.x + particelle[i].radius >= WIDTH) //     asse X
        { 
            particelle[i].vel.x = -(particelle[i].vel.x * RESISTENCE);

            if(fabsf(particelle[i].vel.x) < MIN_VEL){
                particelle[i].vel.x = 0;
            }

        }
        if(particelle[i].pos.y - particelle[i].radius <= 0 || particelle[i].pos.y + particelle[i].radius >= HEIGHT) //     asse Y
        { 
            particelle[i].vel.y = -(particelle[i].vel.y * RESISTENCE);

            if(fabsf(particelle[i].vel.y) < MIN_VEL){
                particelle[i].vel.y = 0;

            }

        }

        if(particelle[i].pos.x - particelle[i].radius < 0){
            particelle[i].pos.x = particelle[i].radius;
        }
        if(particelle[i].pos.x + particelle[i].radius > WIDTH){
            particelle[i].pos.x = WIDTH - particelle[i].radius;
        }
        if(particelle[i].pos.y - particelle[i].radius < 0){
            particelle[i].pos.y = particelle[i].radius;
        }
        if(particelle[i].pos.y + particelle[i].radius > HEIGHT){
            particelle[i].pos.y = HEIGHT - particelle[i].radius;
        }


        particelle[i].pos.x += particelle[i].vel.x;
        particelle[i].pos.y += particelle[i].vel.y;
    }
}

void PerciveGravity(Particella particelle[]){
    for(int i = 0 ; i < NUM_PARTICLE; i++){
        bool aTerra = particelle[i].pos.y + particelle[i].radius >= HEIGHT - 1 ;
        bool ferma = fabsf(particelle[i].vel.y) < MIN_VEL;
        if( !(aTerra && ferma)){
            particelle[i].vel.y += GRAVITY;
        }
    }
}


int main(int argc, char *argv[]){

    //      VARIABILI DEL PROGRAMMA
    Particella particelle[NUM_PARTICLE];

    //inizializzo il seme in modo piu randomico possibile, con l'ora corrente
    srand(time(NULL));

    InitWindow(WIDTH, HEIGHT, "Popirex - Particle Simulation");
    SetTargetFPS(60);


    // genero le palline
    for(int i = 0; i < NUM_PARTICLE; i++){
        particelle[i].pos = generaPosizione();
        particelle[i].vel = generaVelocita();
        particelle[i].color = generaColore();
        particelle[i].radius = generaRaggio();
    }


    
    while (!WindowShouldClose())
    {



        BeginDrawing();
            ClearBackground(BLACK);

            PerciveGravity(particelle);

            AnimateParticles(particelle);
            

            DrawParticles(particelle);


        EndDrawing();
    }

    CloseWindow();


    return 0;
}
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <raylib.h>

const float width = 1000.0f;
const float height = 1000.0f;
const float HandThickness = 3;
const float radius = width * 0.4;
const Vector2 center = { width/2, height/2};

void GetDigitalTime( char *frase, struct tm *tempo){
    sprintf(frase, "%02d:%02d:%02d", tempo->tm_hour, tempo->tm_min, tempo->tm_sec );
}

void DrawDigitalClock(struct tm *tempo){
    char tempoDigitale[1024];
    Vector2 vertice1 = {width/2 - 100, height - 50};
    Vector2 vertice2 = {width/2 + 125, height - 50};
    Vector2 vertice3 = {width/2 - 100, height - 5};
    Vector2 vertice4 = {width/2 + 125, height - 5};


    GetDigitalTime(tempoDigitale, tempo);
    DrawLineV(vertice1, vertice2, WHITE);
    DrawLineV(vertice2, vertice4, WHITE);
    DrawLineV(vertice3, vertice4, WHITE);
    DrawLineV(vertice1, vertice3, WHITE);
   
    DrawText(tempoDigitale, width/2 - 85, height - 50, 50, LIME); 

}

void DrawTicks(){

    float angolo = 0;
    float fattoreInterno;

    for(int i = 0; i < 60; i++){

        if( i % 5 == 0){
            fattoreInterno = 0.75;
        }
        else {
            fattoreInterno = 0.85;
        }


        // internal point
        float xInterna = width/2 + (radius * fattoreInterno *  sinf(angolo * DEG2RAD));

        float yInterna = height / 2 - (radius * fattoreInterno * cosf(angolo * DEG2RAD));

        Vector2 posInterna = {xInterna, yInterna};

        // external point

        float xEsterna =  width/2 + (radius * 0.95 *  sinf(angolo * DEG2RAD));

        float yEsterna =  height / 2 - (radius * 0.95 * cosf(angolo * DEG2RAD));

        Vector2 posEsterna = {xEsterna, yEsterna};

        

        DrawLineV(posInterna, posEsterna, BLACK);

        angolo += 6; 
        
    
    }

}

void DrawSecondHand(struct tm *tempo){

    float angolo = tempo->tm_sec * 6;

    float xEsterna =  width/2 + (radius * 0.84 *  sinf(angolo * DEG2RAD));

    float yEsterna =  height / 2 - (radius * 0.84 * cosf(angolo * DEG2RAD));

    Vector2 posEsterna = {xEsterna, yEsterna};


    DrawLineEx(center, posEsterna, HandThickness, BLUE);

}

void DrawMinuteHand(struct tm *tempo){
    float angolo = tempo->tm_min * 6;
    float offset = tempo->tm_sec * 0.1;

    float xEsterna =  width/2 + (radius * 0.74 *  sinf((angolo + offset) * DEG2RAD));

    float yEsterna =  height / 2 - (radius * 0.74 * cosf((angolo + offset) * DEG2RAD));

    Vector2 posEsterna = {xEsterna, yEsterna};

    DrawLineEx(center, posEsterna, HandThickness, RED);


}

void DrawHourHand(struct tm *tempo){

    float angolo = (tempo->tm_hour % 12) * 30;
    float offset = tempo->tm_min * 0.5f;

    float xEsterna =  width/2 + (radius * 0.60 *  sinf((angolo + offset) * DEG2RAD));

    float yEsterna =  height / 2 - (radius * 0.60 * cosf((angolo + offset) * DEG2RAD));

    Vector2 posEsterna = {xEsterna, yEsterna};

    DrawLineEx(center, posEsterna, HandThickness, LIME);


}

void DrawAnalogClock(struct tm *tempo){

    DrawCircleV(center, radius*1.03f, LIME);
    DrawCircleV(center,  radius, LIGHTGRAY);
    DrawTicks();
    DrawSecondHand(tempo);
    DrawMinuteHand(tempo);
    DrawHourHand(tempo);

}

void DrawDate(struct tm *tempo){

    char data[100];

    sprintf( data ,"%02d %02d %04d", tempo->tm_mday, tempo->tm_mon + 1 ,tempo->tm_year + 1900);

    DrawText(data, width/2 - 130, 10, 60, LIME);
}


int main(int argc, char *argv[]){

    time_t tempo_raw;
    struct tm *tempo;

    InitWindow(width, height, "Popirex - Orologio Analogico");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        tempo_raw = time(NULL);                                                 // getting the new time each iteration
        tempo = localtime(&tempo_raw);                                          // getting the right formatted string for digital clock.

        BeginDrawing();
            ClearBackground(BLACK);

            DrawDigitalClock(tempo);                                            // drawing the digital time with a white contour
            
            DrawAnalogClock(tempo);                                             // drawing the analog clock

            DrawDate(tempo);                                                           // drawing date

        EndDrawing();
    }

    CloseWindow();


    

    return 0;
}
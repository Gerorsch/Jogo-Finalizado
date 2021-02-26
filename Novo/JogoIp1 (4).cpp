#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
//projeto pog -> programacao orientada a gambiarra

int const ScreenWidth = 800, ScreenHeight = 450;
int x = 300, y = 225, decisor = 0, coleta = 0, ppt = 0;

Rectangle zezinhorec = {400, 225, 50, 50};
Rectangle acaua = {600, 200,  35, 40};
Rectangle pena = {600, 200, 10, 10};
Rectangle frameRec = {600, 200,  35, 40};

Vector2 posicaoacaua = { frameRec.x, frameRec.y };
Vector2 posicaozezin = { 300.0f, 225.0f };

float distanciax = posicaoacaua.x - posicaozezin.x;
float distanciay = posicaoacaua.y - posicaozezin.y;


int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 6;

bool zawarudo = 0, penabool = 0, acauafight = 0, inicializar = 0;

bool direita = 0, esquerda = 0, baixo = 0, cima = 0;

bool pedra = 0, papel = 0, tesoura = 0;

void acaualouco(){
    srand(time(NULL));
    int decisor = rand()%2;
    if(posicaoacaua.x == 600 && posicaoacaua.y == 200){
        posicaoacaua.x = 400;
        if(decisor == 0)posicaoacaua.y = 400;
        else posicaoacaua.y = 0;
    }else if(posicaoacaua.x ==  400 && posicaoacaua.y == 0){
        posicaoacaua.y = 200;
        if(decisor == 1)posicaoacaua.x = 200;
        else posicaoacaua.x = 600;
    }else if(posicaoacaua.x == 400 && posicaoacaua.y == 0){
        posicaoacaua.y = 200;
        if(decisor == 0)posicaoacaua.x = 600;
        else posicaoacaua.x = 200;
    }else if(posicaoacaua.x == 200 && posicaoacaua.y == 200){
        posicaoacaua.x = 400;
        if(decisor == 0)posicaoacaua.y = 0;
        else posicaoacaua.y = 400;
    }else if(posicaoacaua.x == 400 && posicaoacaua.y == 400){
        posicaoacaua.y = 200;
        if(decisor == 0)posicaoacaua.x = 600;
        else posicaoacaua.x = 200;
    }
}



void menu(int* tela){
    if(IsKeyPressed(KEY_DOWN) && y < 325)y += 50;
    else if(IsKeyPressed(KEY_UP) && y> 225)y -= 50;

    DrawRectangleLines(x, y, 200, 30, BLACK);

    DrawText("Iniciar aventura", x+20, 235, 10, BLACK);
    DrawText("Configuracoes", x+20, 285, 10, BLACK);
    DrawText("Sobre", x+20, 335, 10, BLACK);

    if(IsKeyPressed(KEY_ENTER)){
        if(y == 225)*tela = 1;
        else if(y == 275)*tela = 2;
        else if(y == 325)*tela = 3;
    }
}

void iniciar(int* tela){
    DrawText("Agora a breve e nem um pouco epica saga de zezinha iniciara", 300, 225, 16, GOLD);
    DrawText("Pressione Enter para prosseguir...", 300, 325, 16, BLACK);
    if(IsKeyPressed(KEY_ENTER))*tela = 4;
}

void selecaodeclasse(int* tela){
    if(IsKeyPressed(KEY_DOWN) && y < 275)y += 50;
    else if(IsKeyPressed(KEY_UP) && y> 125)y -= 50;

    DrawRectangleLines(200, y, 200, 30, BLACK);
    DrawText("Barbaro", 210, 135, 16, MAROON);
    DrawText("Mago", 210, 185, 16, BLUE);
    DrawText("Paladino", 210, 235, 16, RAYWHITE);
    DrawText("Necromancer", 210, 285, 16, DARKPURPLE);

    if(IsKeyPressed(KEY_ENTER))*tela = 5;
}

void fase1(int* tela, Texture2D acauaTex, Rectangle frameRec, Texture2D zezinhoTex, Rectangle zezinhodireita, Texture2D zezinhoEsq, Rectangle zezinhoesquerda, Texture2D zezinhoCim, Rectangle zezinhocima, Texture2D zezinhoBai, Rectangle zezinhobaixo, Texture2D zezinhoJKP, Rectangle zezinhofight, Texture2D background){
       acaua.x = posicaoacaua.x;
       acaua.y = posicaoacaua.y;
       acaua.width = (float)acauaTex.width;
       acaua.height = (float)acauaTex.height/8;
       zezinhorec.x = posicaozezin.x;
       zezinhorec.y = posicaozezin.y;
       zezinhorec.width = (float)zezinhoTex.width;
       zezinhorec.height = (float)zezinhoTex.height/8;


    framesCounter++;

    if (framesCounter >= ((float)30/(framesSpeed))){
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 7) currentFrame = 0;

            frameRec.y = (float)currentFrame*(float)acauaTex.height/8;
            zezinhodireita.y = (float)currentFrame*(float)zezinhoTex.height/8;
        }

     if(IsKeyDown(KEY_DOWN) && posicaozezin.y< ScreenHeight - 50){posicaozezin.y+=5;
        baixo = 1, cima = 0, direita = 0, esquerda = 0;}
     else if(IsKeyDown(KEY_UP) && posicaozezin.y  > 0){posicaozezin.y -=5;
        cima = 1, baixo = 0, direita = 0, esquerda = 0;}
     else if(IsKeyDown(KEY_RIGHT) && posicaozezin.y  < ScreenWidth-50){posicaozezin.x+=5;
        cima = 0, baixo = 0, direita = 1, esquerda = 0;}
     else if(IsKeyDown(KEY_LEFT) && posicaozezin.x > 0){posicaozezin.x-=5;
        cima = 0, baixo = 0, direita = 0, esquerda = 1;}

    if(distanciax < 0)distanciax*-1;
    if(distanciay < 0)distanciay*-1;

     //if( (posicaozezin.x - posicaoacaua.x < 50 || posicaoacaua.x - posicaozezin.x < 50) &&(posicaoacaua.y - posicaozezin.y < 50 || posicaozezin.y - posicaoacaua.y < 50 )&& distanciay < 50 && !zawarudo){
       if(CheckCollisionRecs(acaua, zezinhorec) && !zawarudo){
        penabool = 1;
        pena.x = posicaoacaua.x, pena.y = posicaoacaua.y;
        acaualouco();
     }

     //if((pena.x - posicaozezin.x < 30 || posicaozezin.x - pena.x < 30) && (pena.y - posicaozezin.y < 30 || posicaozezin.y - pena.y < 30)){
       if(CheckCollisionRecs(pena, zezinhorec)){
        penabool = 0;
        pena.x += 1000;
        coleta++;
     }

     if(coleta >= 5){
        if(IsKeyPressed(KEY_E) && !zawarudo)zawarudo = 1;
        else if(IsKeyPressed(KEY_E) && zawarudo)zawarudo = 0;
     }

     if(zawarudo && CheckCollisionRecs(acaua, zezinhorec)){
        posicaoacaua.x = 600, posicaoacaua.y = 350 - acauaTex.height/8;
        posicaozezin.x = 300, posicaozezin.y = 350 - zezinhoJKP.height/8;
        acauafight = 1;
        *tela = 8;
     }

   /* BeginDrawing();
        if(!zawarudo)ClearBackground(RAYWHITE);
        else ClearBackground(PURPLE);



        if(coleta == 0)DrawText("Oh, esta se aproxiamndo de mim Zezinho? Nao da pra lhe quebrar na porrada se nao se aproximar Entao chegue mais perto!",0, 0, 12, BLACK);
        DrawRectangleRec(frameRec, WHITE);
        if(penabool)DrawRectangleRec(pena, RED);
    EndDrawing();*/

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if(!zawarudo)DrawTexture(background, 0, 0, WHITE);
    else DrawTexture(background, 0, 0, PURPLE);


        if(coleta == 0)DrawText("Oh, esta se aproximando de mim Zezinho? Nao da pra lhe quebrar na porrada se nao se aproximar Entao chegue mais perto!",0, 0, 12, BLACK);
            DrawTextureRec(acauaTex, frameRec, posicaoacaua, WHITE);
            if(direita == 1)
                DrawTextureRec(zezinhoTex, zezinhodireita, posicaozezin, WHITE);
            if(esquerda == 1)
                DrawTextureRec(zezinhoEsq, zezinhoesquerda, posicaozezin, WHITE);
            if(baixo == 1)
                DrawTextureRec(zezinhoCim, zezinhodireita, posicaozezin, WHITE);
            if(cima == 1)
                DrawTextureRec(zezinhoBai, zezinhodireita, posicaozezin, WHITE);
            if(penabool)DrawRectangleRec(pena, RED);
    EndDrawing();
}

void fight(int* tela, Texture2D acauaTex, Rectangle frameRec, Texture2D zezinhoJKP, Rectangle zezinhofight, Texture2D background){

        framesCounter++;

        if (framesCounter >= (float)(60/(framesSpeed))){
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 7) currentFrame = 0;

            frameRec.y = (float)currentFrame*(float)acauaTex.height/8;
            zezinhofight.y = (float)currentFrame*(float)zezinhoJKP.height/8;

        }
            if(IsKeyPressed(KEY_F) && ppt < 3)pedra = 1, papel = 0, tesoura = 0, ppt++;
            else if(IsKeyPressed(KEY_G) && ppt < 3)pedra = 0, papel = 1, tesoura = 0, ppt++;
            else if(IsKeyPressed(KEY_H) && ppt < 3)pedra = 0, papel = 0, tesoura = 1, ppt++;

            if(ppt==3 && IsKeyPressed(KEY_ENTER))*tela=9;



    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);

        DrawTextureRec(acauaTex, frameRec, posicaoacaua, WHITE);
        DrawTextureRec(zezinhoJKP, zezinhofight, posicaozezin, WHITE);
        DrawRectangle(0, 350, ScreenWidth, 100, BROWN);
        if(ppt == 0){
            DrawText("Zezinho achou uma boa ideia jogar pedra papel e tesoura para cair na porrada...", 100, 0, 16, BLACK);
            DrawText("E serio isso producao?!?!?!?!?", 100, 25, 16, BLACK);
            DrawText("ugh... Pressione f para pedra, g para papel e h para tesoura...", 100, 50, 16, BLACK);
        }
        if(ppt == 3){
            DrawText("Voce nao percebe tenho uma mao neh...", 100, 150, 16, BLACK);
            DrawText("Bixo burro da peste!", 100, 175, 16, BLACK);
            DrawText("Pressione Enter para vazar disso aqui. Producao toca musica do shrek to bem nao...", 100, 200, 16, BLACK);
        }
    EndDrawing();
}


void creditos(int* tela){
    ClearBackground(GRAY);
    DrawText("Produzido pelos sobreviventes do grupo 2 e nao dupla sertaneja: George e Matheus.", 100, 225, 16, GOLD);
    //PELO AMOR DE DEUS TOCA SOMEBODY ONCE TOLD ME!
}

void aviso(int* tela){
    DrawText("Bom... Digamos que o budget foi todo quase usado para contratar o ator zezinho...", 0, 225, 16, GOLD);
    DrawText("O jovem cobra caro por ser irmao de uma estrela ai da nintendo... Que mala...", 0, 245, 16, GOLD);
    if(IsKeyPressed(KEY_ENTER))*tela = 6;
}

void configuracoes(int*tela){
    DrawText("Desculpe a producao nao teve orcamento. entao teremos apenas ultra low", 200, 225, 16, GOLD);
    DrawText("Pressione backspace para retornar ao menu", 300, 275, 16, GOLD);
    if(IsKeyPressed(KEY_BACKSPACE))*tela = 0;
}

void sobre(int* tela){
    DrawText("Creditos aos sobreviventes do grupo 2 que puderam produzir tal obra...", 200, 225, 16, GOLD);
    DrawText("Press F to pay respect", 300, 325, 16, GOLD);
    if(IsKeyPressed(KEY_F) || IsKeyPressed(KEY_BACKSPACE))*tela = 0;

}
void explicacao(int* tela){
    DrawText("O acaua na terra de zezinho e uma criatura sagrada.", 0, 100, 16, RED);
    DrawText("Por algum motivo quando se aproximam dele ele desaparece ao enves de voar!", 0, 125, 16, RED);
    DrawText("Alguns ate dizem que ouvem um barulho parecido com 'wryyyyy' ou 'ZAWARUDO'.", 0, 150, 16, RED);
    DrawText("Mas isso sao apenas referencias a desenhos japoneses...", 0, 175, 16, RED);
    if(IsKeyPressed(KEY_ENTER))*tela = 7;
    if(IsKeyPressed(KEY_ENTER))*tela = 7;
}

//0 menu, 1 iniciar, 2 configuracoes, 3 sobre, 4 selecao de classe, 5 aviso, 6 fase, 7 fight, 8 creditos;
int main(){
    int tela = 0, horizontalz = 400;

    InitWindow(ScreenWidth, ScreenHeight, "Menu");
    InitAudioDevice();

    Music shrek = LoadMusicStream("./Shrek.mp3");
    Music jojo = LoadMusicStream("./Jojo.mp3");
    Music vapor = LoadMusicStream("./vapor.mp3");

    SetTargetFPS(60);

    Texture2D background = LoadTexture("./background.png");
    Texture2D acauaTex = LoadTexture("./acauaTex.png");
    Texture2D zezinhoTex = LoadTexture("./zezinho_direita.png");
    Texture2D zezinhoEsq = LoadTexture("./zezinho_esquerda.png");
    Texture2D zezinhoBai = LoadTexture("./zezinho_baixo.png");
    Texture2D zezinhoCim = LoadTexture("./zezinho_cima.png");
    Texture2D zezinhoJKP = LoadTexture("./zezinho_JKP.png");

    Rectangle frameRec = {0.0, 0.0, (float)acauaTex.width, (float)acauaTex.height/8};
    Rectangle zezinhodireita = {0.0, 0.0, (float)zezinhoTex.width, (float)zezinhoTex.height/8};
    Rectangle zezinhobaixo = {0.0, 0.0, (float)zezinhoTex.width, (float)zezinhoTex.height/8};
    Rectangle zezinhocima = {0.0, 0.0, (float)zezinhoTex.width, (float)zezinhoTex.height/8};
    Rectangle zezinhoesquerda = {0.0, 0.0, (float)zezinhoTex.width, (float)zezinhoTex.height/8};
    Rectangle zezinhofight = {0.0, 0.0, (float)zezinhoJKP.width, (float)zezinhoJKP.height/8};

    while(!WindowShouldClose()){
        UpdateMusicStream(shrek);
        UpdateMusicStream(jojo);
        UpdateMusicStream(vapor);
        if(tela == 0)PlayMusicStream(vapor),SetMusicVolume(vapor, 0.05);
        else if(tela == 7)StopMusicStream(vapor);
        if(tela==9)PlayMusicStream(shrek), SetMusicVolume(shrek, 0.05), StopMusicStream(jojo);
        if(tela == 7)fase1(&tela, acauaTex, frameRec, zezinhoTex, zezinhodireita, zezinhoEsq, zezinhoesquerda, zezinhoBai, zezinhobaixo, zezinhoCim, zezinhocima,zezinhoJKP, zezinhofight, background), PlayMusicStream(jojo), SetMusicVolume(jojo, 0.05);
        else if(tela == 8)fight(&tela, acauaTex, frameRec, zezinhoJKP, zezinhofight, background);
        else{
            BeginDrawing();
                ClearBackground(GRAY);
                if(tela == 0)menu(&tela);
                else if(tela == 1)iniciar(&tela);
                else if(tela == 2)configuracoes(&tela);
                else if(tela == 3)sobre(&tela);
                else if(tela == 4)selecaodeclasse(&tela);
                else if(tela == 5)aviso(&tela);
                else if(tela == 6)explicacao(&tela);
                else if(tela == 8)creditos(&tela);
            EndDrawing();
        }
    }
}

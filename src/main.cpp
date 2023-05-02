/**
 * Fiz apenas um exercicio da prova
*/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <vector>
#include <iostream>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "Vector2.h"

int screenWidth = 500, screenHeight = 500;
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().

// Eixos 
Vector2 eixoxi = Vector2(-100, 0);
Vector2 eixoxf = Vector2(500, 0);
Vector2 eixoyi = Vector2(0, -100);
Vector2 eixoyf = Vector2(0, 500);

// Posições iniciais do quadrado
Vector2 p1 = Vector2(100, 100);
Vector2 p2 = Vector2(150, 100);
Vector2 p3 = Vector2(150, 150);
Vector2 p4 = Vector2(100, 150);

std::vector<Vector2> quadradoOriginal = {p1, p2, p3, p4};

// Nova atualização transladado
std::vector<Vector2> quadradoTransladado;

// Nava atualização escalonado
std::vector<Vector2> quadradoEscalonado;

// Nova atualização retação
std::vector<Vector2> quadradoRotacionado;

/**
 * Desenha o quadrado usando retas, apenas com os pontos do quadrado
*/
void desenhaQuadrado(std::vector<Vector2> pontos) {
   for(unsigned int i = 0; i < pontos.size(); i++){
      if(i == pontos.size() - 1){
         CV::line(pontos[i], pontos[0]);
      }else{
         CV::line(pontos[i], pontos[i + 1]);
      }
   }
}

/**
 * Recebe um vetor de pontos e move para um destino, depois retorna um novo vetor de pontos
*/
std::vector<Vector2> translada(std::vector<Vector2> pontos, Vector2 destino) {
   // Calcula o centro dos pontos
   Vector2 centroOriginal = Vector2(0, 0);
   for(auto ponto: pontos){
      centroOriginal.x += ponto.x;
      centroOriginal.y += ponto.y;
   }
   centroOriginal.x /= pontos.size();
   centroOriginal.y /= pontos.size();
   
   // Distancia em x e y do destino
   float distx = destino.x - centroOriginal.x;
   float disty = destino.y - centroOriginal.y;

   std::vector<Vector2> vetorAuxliar;
   // Move os pontos e coloca no vetor auxiliar
   for (auto p : pontos) {
      Vector2 pontoAuxiliar;
      pontoAuxiliar.x = p.x + distx;
      pontoAuxiliar.y = p.y + disty; 
      vetorAuxliar.push_back(pontoAuxiliar);
   }

   // Retorna todos os pontos
   return vetorAuxliar;
}

/**
 * Recebe um vetor de pontos e escalona os pontos baseado no fator de escala
*/
std::vector<Vector2> escalona(std::vector<Vector2> pontos, float escala) {
   std::vector<Vector2> vetorAuxiliar;
   for (auto ponto : pontos) {
      Vector2 pontoAux;
      pontoAux.x = ponto.x * escala;
      pontoAux.y = ponto.y * escala; 
      vetorAuxiliar.push_back(pontoAux);
   }
   // Retorna o vetor escalonado
   return vetorAuxiliar;
}

std::vector<Vector2> rotaciona(std::vector<Vector2> pontos, float angulo) {
   // Calcula o centro dos pontos
   Vector2 centro = Vector2(0, 0);
   for(auto ponto: pontos) {
      centro = centro + ponto;
   }
   centro.x /= pontos.size();
   centro.y /= pontos.size();
   // Calcula um vetor de distancia até o centro
   Vector2 distancia = Vector2(0, 0) - centro;
   float cosn = cos(angulo);
   float senn = sin(angulo);

   std::vector<Vector2> vetorAuxiliar;
   for(auto ponto: pontos) {

   }

   // Retorna o vetor auxiliar
   return vetorAuxiliar;
}


void render()
{
   CV::translate(100, 100);
   CV::color(0, 0, 0);
   
   // Printa os eixos
   CV::line(eixoxi, eixoxf);
   CV::line(eixoyi, eixoyf);

   // Printa o quadrado original
   CV::color(1, 0, 0); // Vermelho
   desenhaQuadrado(quadradoOriginal);
   
   // Aplica a translação ao vetor original
   quadradoTransladado.clear();
   quadradoTransladado = translada(quadradoOriginal, Vector2(0, 0));
   CV::color(0, 1, 0); // Verde
   desenhaQuadrado(quadradoTransladado);

   // Aplica a escala ao vetor tranladado
   quadradoEscalonado.clear();
   quadradoEscalonado = escalona(quadradoTransladado, 2);
   CV::color(0, 1, 1); // Verde marinho
   desenhaQuadrado(quadradoEscalonado);

   // Aplica a rotação ao vetor escalonado
   quadradoRotacionado.clear();
   quadradoRotacionado = retaciona(quadradoEscalonado, 45);
   CV::color(1, 0, 1);
   desenhaQuadrado(quadradoEscalonado);
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   //printf("\nTecla: %d" , key);

   switch(key)
   {
   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   //printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

}

int main(void)
{
   CV::init(&screenWidth, &screenHeight, "Execicio de Transformacoes - Deivis");
   CV::run();
}

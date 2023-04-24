/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

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

void render()
{
   CV::translate(100, 100);
   CV::color(0, 0, 0);
   
   // Printa os eixos
   CV::line(eixoxi, eixoxf);
   CV::line(eixoyi, eixoyf);

   // Printa o quadrado original
   CV::color(1, 0, 0);
   desenhaQuadrado(quadradoOriginal);
   
   // Aplica a translação ao vetor original
   quadradoTransladado.clear();
   quadradoTransladado = translada(quadradoOriginal, Vector2(0, 0));
   CV::color(0, 1, 0);
   desenhaQuadrado(quadradoTransladado);

   // Aplica a escala ao vetor tranladado
   quadradoEscalonado.clear();
   quadradoEscalonado = escalona(quadradoTransladado, 2);
   CV::color(0, 1, 1);
   desenhaQuadrado(quadradoEscalonado);
}

void desenhaQuadrado(std::vector<Vector2> pontos) {
   for(unsigned int i = 0; i < pontos.size(); i++){
      if(i == pontos.size() - 1){
         CV::line(pontos[i], pontos[0]);
      }else{
         CV::line(pontos[i], pontos[i + 1]);
      }
   }
}


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

void escala(float escala) {
   Vector2 aux;
   // Coloca os novos pontos no quadradoTransladado
   quadradoEscalonado.clear();
   for (auto p : quadradoTransladado) {
      aux.x = p.x * escala;
      aux.y = p.y * escala; 
      quadradoEscalonado.push_back(aux);
   }
}

void rotaciona(Vector2 ponto, float angulo) {
   float cosn = cos(angulo);
   float senn = sin(angulo);

   
}

int main(void)
{
   CV::init(&screenWidth, &screenHeight, "Execicio de Transformações - Deivis");
   CV::run();
}

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

//variavel global para selecao do que sera exibido na canvas.
int screenWidth = 500, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
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

std::vector<Vector2> quadradooriginal = {p1, p2, p3, p4};

// Nova atualização transladado
std::vector<Vector2> quadradotransladado;

// Nava atualização escalonado
std::vector<Vector2> quadradoEscalonado;

void DrawMouseScreenCoords()
{
    char str[100];
    sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
    CV::text(10,300, str);
    sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
    CV::text(10,320, str);
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void render()
{
   CV::translate(100, 100);
   CV::color(0, 0, 0);
   
   // Printa os eixos
   CV::line(eixoxi, eixoxf);
   CV::line(eixoyi, eixoyf);

   // Printa o quadrado original
   // Cria o vetor de valores dos pontos
   std::vector<float> xpolyor;
   std::vector<float> ypolyor;
   for(auto p : quadradooriginal){
      xpolyor.push_back(p.x);
      ypolyor.push_back(p.y);
   }

   // Printa
   CV::color(1, 0, 0);
   CV::polygon(xpolyor.data(), ypolyor.data(), xpolyor.size());

   // Cria o vetor transladado
   std::vector<float> xpolynovo;
   std::vector<float> ypolynovo;
   for(auto p: quadradotransladado){
      xpolynovo.push_back(p.x);
      ypolynovo.push_back(p.y);
   }

   // Transladado
   CV::color(0, 1, 0);
   CV::polygon(xpolynovo.data(), ypolynovo.data(), xpolynovo.size());

   // Cria o vetor escalado
   std::vector<float> xpolyEscala;
   std::vector<float> ypolyEscala;
   for(auto p: quadradoEscalonado){
      xpolyEscala.push_back(p.x);
      ypolyEscala.push_back(p.y);
   }

   // Escalonado
   CV::color(0, 1, 1);
   CV::polygon(xpolyEscala.data(), ypolyEscala.data(), xpolyEscala.size());
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

void translada() {
   // Calcula o centro
   Vector2 centroOriginal = Vector2((p1.x + p2.x) / 2, (p2.y + p3.y) / 2);
   // Distancia em x e y
   Vector2 origem = Vector2(0, 0);
   float distx = origem.x - centroOriginal.x;
   float disty = origem.y - centroOriginal.y;

   Vector2 aux;
   // Coloca os novos pontos no quadradotransladado
   quadradotransladado.clear();
   for (auto p : quadradooriginal) {
      aux.x = p.x + distx;
      aux.y = p.y + disty; 
      quadradotransladado.push_back(aux);
   }
}

void escala(float escala) {
   Vector2 aux;
   // Coloca os novos pontos no quadradotransladado
   quadradoEscalonado.clear();
   for (auto p : quadradotransladado) {
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
   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   std::cout << std::endl;
   translada();
   escala(2);
   CV::run();
}

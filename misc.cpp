/* Arquivo: misc.cpp
   Autores: João Pedro Winckler Bernardi e Vladimir Belinski
   Descrição: o presente arquivo faz parte da resolução do Trabalho I do CCR Computação Gráfica, 2016-2, do curso de
              Ciência da Computação da Universidade Federal da Fronteira Sul - UFFS, o qual consiste em uma animação
              do símbolo do SO Android (robô) andando de skate.
              --> misc.cpp é o arquivo de miscelâneas do trabalho. Sua única função é meiaEsfera, utilizada para se
              desenhar uma meia esfera.
*/

// Inclusão das bibliotecas necessárias
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include "misc.h"

// A função meiaEsfera é utilizada para se desenhar uma meia esfera
void meiaEsfera(float r, int m, int cut) {
  int i, j;
  float tmp, nx, ny, nz, start_nx, start_ny, a, ca, sa;
  const int n = m * 4;

  float l = 0;
  a = float(M_PI*2.0) / float(n);
  sa = (float) sin(a);
  ca = (float) cos(a);

  start_nx = 0;
  start_ny = 1;
  for (j=0; j < (n / cut); j++) {
    float start_nx2 =  ca * start_nx + sa * start_ny;
    float start_ny2 = -sa * start_nx + ca * start_ny;
    nx = start_nx; ny = start_ny; nz = 0;
    float nx2 = start_nx2, ny2 = start_ny2, nz2 = 0;
    glBegin (GL_TRIANGLE_STRIP);
    for (i = 0; i <= n; i++) {
      glNormal3d(ny2, nz2, nx2);
      glVertex3d(ny2 * r, nz2 * r, l+nx2 * r);
      glNormal3d(ny, nz, nx);
      glVertex3d(ny * r, nz * r, l + nx * r);
      tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
      tmp = ca * ny2 - sa * nz2;
      nz2 = sa * ny2 + ca * nz2;
      ny2 = tmp;
    }
    glEnd();
    start_nx = start_nx2;
    start_ny = start_ny2;
  }
}

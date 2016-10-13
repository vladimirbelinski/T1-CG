#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

GLfloat alpha = 0.0f;

static void meiaEsfera(float r, int m, int cut)
{
    int i, j;
    float tmp, nx, ny, nz, start_nx, start_ny, a, ca, sa;
    const int n = m*4;

    float l = 0;
    a = float(M_PI*2.0)/float(n);
    sa = (float) sin(a);
    ca = (float) cos(a);

    start_nx = 0;
    start_ny = 1;
    for (j=0; j<(n/cut); j++) {
        float start_nx2 =  ca*start_nx + sa*start_ny;
        float start_ny2 = -sa*start_nx + ca*start_ny;
        nx = start_nx; ny = start_ny; nz = 0;
        float nx2 = start_nx2, ny2 = start_ny2, nz2 = 0;
        glBegin (GL_TRIANGLE_STRIP);
        for (i=0; i<=n; i++) {
            glNormal3d (ny2,nz2,nx2);
            glVertex3d (ny2*r,nz2*r,l+nx2*r);
            glNormal3d (ny,nz,nx);
            glVertex3d (ny*r,nz*r,l+nx*r);
            tmp = ca*ny - sa*nz;
            nz = sa*ny + ca*nz;
            ny = tmp;
            tmp = ca*ny2- sa*nz2;
            nz2 = sa*ny2 + ca*nz2;
            ny2 = tmp;
        }
        glEnd();
        start_nx = start_nx2;
        start_ny = start_ny2;
    }
}

// Função callback chamada para fazer o desenho
void draw(void) {
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // gluLookAt(xC, yC, zC, xP, yP, zP, xU, yU, zU)
	// Se o vetor up é z então yC parece z e zC parece y
  // gluLookAt(12.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	// gluLookAt(0.0, 4.0, -2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	gluLookAt(0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  glPushMatrix();
    glRotatef(alpha+=3.0f, 1.0f, 0.0f, 0.0f);

  	// Definindo a cor corrente como branco
  	glColor3f(1.0f, 1.0f, 1.0f);

  	// Rotinas que definem os atributos das quádricas
  	gluQuadricDrawStyle(qobj, GLU_FILL);
  	gluQuadricNormals(qobj, GLU_SMOOTH);
  	gluQuadricOrientation(qobj, GLU_OUTSIDE);
    gluQuadricTexture(qobj, GLU_FALSE);

  	// Cilindro que forma o pescoço do robô
  	glPushMatrix();
  	gluCylinder(qobj, 0.45, 0.45, 0.08, 200, 200);
  	glPopMatrix();

  	// Cilindro que junta o braço direito do robô ao tronco
  	glPushMatrix();
  	glTranslatef(-0.65f, 0.0f, -0.1f);
  	glRotatef(90, 0.0f, 1.0f, 0.0f);
  	gluCylinder(qobj, 0.05, 0.05, 0.2, 100, 100);
  	glPopMatrix();

  	// Cilindro que junta o braço esquerdo do robô ao tronco
  	glPushMatrix();
  	glTranslatef(0.45f, 0.0f, -0.1f);
  	glRotatef(90, 0.0f, 1.0f, 0.0f);
  	gluCylinder(qobj, 0.05, 0.05, 0.2, 100, 100);
  	glPopMatrix();

  	// Olho direito
  	glPushMatrix();
  	glTranslatef(-0.23f, 0.35f, 0.24f);
  	gluSphere(qobj, 0.07, 100, 100);
  	glPopMatrix();

  	// Olho esquerdo
  	glPushMatrix();
  	glTranslatef(0.23f, 0.35f, 0.24f);
  	gluSphere(qobj, 0.07, 100, 100);
  	glPopMatrix();

  	// Definindo a cor corrente como verde
  	glColor3ub(164, 199, 57);

  	// Antena direita do robô
  	glPushMatrix();
  	glTranslatef(-0.2f, 0.0f, 0.5f);
  	glRotatef(-45, 0.0f, 1.0f, 0.0f);
  	gluCylinder(qobj, 0.02, 0.02, 0.17, 100, 100);
  	glPopMatrix();

  	// Meia esfera que irá compor a topo da antena direita do robô
  	glPushMatrix();
  	glTranslatef(-0.32f, 0.0f, 0.62);
  	glRotatef(-45, 0.0f, 1.0f, 0.0f);
  	meiaEsfera(0.02, 100, 4);
  	glPopMatrix();

  	// Antena esquerda do robô
  	glPushMatrix();
  	glTranslatef(0.2f, 0.0f, 0.5f);
  	glRotatef(45, 0.0f, 1.0f, 0.0f);
  	gluCylinder(qobj, 0.02, 0.02, 0.17, 100, 100);
  	glPopMatrix();

  	// Meia esfera que irá compor a topo da antena esquerda do robô
  	glPushMatrix();
  	glTranslatef(0.32f, 0.0f, 0.62);
  	glRotatef(45, 0.0f, 1.0f, 0.0f);
  	meiaEsfera(0.02, 100, 4);
  	glPopMatrix();

  	// Meia esfera que irá compor a cabeça do robô
  	glPushMatrix();
  	glTranslatef (0.0f, 0.0f, 0.07f);
  	meiaEsfera(0.5, 100, 4);
  	glPopMatrix();

  	// Disco sob a meia esfera para fechá-la
  	glPushMatrix();
  	glTranslatef(0.0f, 0.0f, 0.07f);
    // Rotacionado para funcionar a iluminação (devido a posição do vetor normal)
    glRotatef(180, 1.0f, 0.0f, 0.0);
  	gluDisk(qobj, 0.45, 0.503, 30, 30);
  	glPopMatrix();

  	// Disco que fecha a parte superior do cilindro que forma o tronco do robô
  	glPushMatrix();
  	gluDisk(qobj, 0.45, 0.503, 30, 30);
  	glPopMatrix();

  	// Cilindro que forma o tronco do robô
  	glPushMatrix();
  	glTranslatef(0.0f, 0.0f, -0.75f);
  	gluCylinder(qobj, 0.5, 0.5, 0.75, 200, 200);
  	glPopMatrix();

  	// Meia esfera que fecha a parte inferior do cilindro que forma o tronco do robô
  	glPushMatrix();
  	glTranslatef(0.0f, 0.0f, -0.75f);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    meiaEsfera(0.5, 100, 27);
  	glPopMatrix();

    // Disco que fecha a base do tronco
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.85f);
    // Rotacionado para funcionar a iluminação (devido a posição do vetor normal)
    glRotatef(180, 1.0f, 0.0f, 0.0);
    gluDisk(qobj, 0.0, 0.49, 30, 30);
    glPopMatrix();

  	// Braço direito do robô
  	glPushMatrix();
  	glTranslatef(-0.63f, 0.0f, -0.55f);
  	gluCylinder(qobj, 0.09, 0.09, 0.45, 100, 100);
  	glPopMatrix();

  	// Meia esfera que irá compor a topo do braço direito do robô
  	glPushMatrix();
  	glTranslatef(-0.63f, 0.0f, -0.1f);
  	meiaEsfera(0.09, 20, 4);
  	glPopMatrix();

  	// Meia esfera que irá compor a base do braço direito do robô
  	glPushMatrix();
  	glTranslatef(-0.63f, 0.0f, -0.55f);
  	glRotatef(180, 1.0f, 0.0f, 0.0f);
  	meiaEsfera(0.09, 100, 4);
  	glPopMatrix();

  	// Braço esquerdo do robô
  	glPushMatrix();
  	glTranslatef(0.63f, 0.0f, -0.55f);
  	gluCylinder(qobj, 0.09, 0.09, 0.45, 100, 100);
  	glPopMatrix();

  	// Meia esfera que irá compor a topo do braço esquerdo do robô
  	glPushMatrix();
  	glTranslatef(0.63f, 0.0f, -0.1f);
  	meiaEsfera(0.09, 100, 4);
  	glPopMatrix();

  	// Meia esfera que irá compor a base do braço esquerdo do robô
  	glPushMatrix();
  	glTranslatef(0.63f, 0.0f, -0.55f);
  	glRotatef(180, 1.0f, 0.0f, 0.0f);
  	meiaEsfera(0.09, 100, 4);
  	glPopMatrix();

    // Perna esquerda do robô
  	glPushMatrix();
    glScalef(1.0f, 1.5f, 1.0f);
  	glTranslatef(0.20f, 0.0f, -1.15f);
  	gluCylinder(qobj, 0.1, 0.1, 0.4, 100, 100);
  	glPopMatrix();

    // Meia esfera que irá compor a base da perna esquerda do robô
    glPushMatrix();
    glScalef(1.0f, 1.5f, 1.0f);
    glTranslatef(0.20f, 0.0f, -1.15f);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    meiaEsfera(0.1, 100, 4);
    glPopMatrix();

    // Perna direita do robô
    glPushMatrix();
    glScalef(1.0f, 1.5f, 1.0f);
    glTranslatef(-0.20f, 0.0f, -1.15f);
    gluCylinder(qobj, 0.1, 0.1, 0.4, 100, 100);
    glPopMatrix();

    // Meia esfera que irá compor a base da perna direita do robô
    glPushMatrix();
    glScalef(1.0f, 1.5f, 1.0f);
    glTranslatef(-0.20f, 0.0f, -1.15f);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    meiaEsfera(0.1, 100, 4);
    glPopMatrix();

  glPopMatrix();

	// Executa os comandos OpenGL
  glutSwapBuffers();
  glFinish();
}

void initialize(void) {
    GLfloat model_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_specular[] = {0.8, 0.8, 0.8, 1.0};          // capacidade de brilho do material
    GLfloat mat_shininess[] = { 90.0 };

		GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };	    // "cor"
		GLfloat light0_specular[] = { 0.8, 0.8, 0.8, 1.0 };     // "brilho"
		GLfloat light0_position[] = { -20.0, 20.0, 40.0, 1.0 };

		// Definição da cor de fundo da janela de visualização como preta
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Habilitação do modelo de colorização de Gouraud
		glShadeModel(GL_SMOOTH);

		// Definição da refletância  e concentração do brilho do material
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

		// Ativação do uso da luz ambiente
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

		// Definição dos parâmetros da luz de número 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

		// Habilitação da definição da cor do material a partir da cor corrente
		glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);

		// Habilitação do uso de iluminação e das luzes
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

    // Habilitação da normalização
    glEnable(GL_NORMALIZE);
    glEnable(GL_RESCALE_NORMAL);

		// Habilitação do depth-buffering e indicação da função de teste
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
}

void reshape(GLsizei w, GLsizei h) {
	// Evita a divisão por zero
	if (h == 0) h = 1;
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

  // gluPerspective(GLdouble fov, GLdouble aspect, GLdouble near, GLdouble far)
	gluPerspective(45, w/h, 1, 100);
}

//void redraw(int) {
void redraw() {
  glutPostRedisplay();
  draw();
  //glutTimerFunc(20,redraw,1);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
  // GLUT_DEPTH para alocar Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 1200);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Android Robot");
  glutIdleFunc(redraw);
  //glutTimerFunc(20,redraw,1);
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	initialize();
	glutMainLoop();
}

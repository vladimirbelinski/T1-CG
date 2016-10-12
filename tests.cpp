#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

static void meiaEsfera(float r, int m)
{
    int capped_cylinder_quality = m;
    int i, j;
    float tmp, nx, ny, nz, start_nx, start_ny, a, ca, sa;
    const int n = capped_cylinder_quality*4;

    float l = 0;
    a = float(M_PI*2.0)/float(n);
    sa = (float) sin(a);
    ca = (float) cos(a);

    // draw first cylinder cap
    start_nx = 0;
    start_ny = 1;
    for (j=0; j<(n/4); j++) {
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
	gluLookAt(0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	// Definindo a cor corrente como branco
	glColor3f(1.0f, 1.0f, 1.0f);

	// Cilindro que forma o pescoço do robô
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluCylinder(qobj, 0.45, 0.45, 0.08, 200, 200);
	glPopMatrix();

	// Cilindro que junta o braço direito do robô ao tronco
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	glTranslatef(-0.65f, 0.0f, -0.1f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	gluCylinder(qobj, 0.05, 0.05, 0.2, 100, 100);
	glPopMatrix();

	// Cilindro que junta o braço esquerdo do robô ao tronco
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	glTranslatef(0.45f, 0.0f, -0.1f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	gluCylinder(qobj, 0.05, 0.05, 0.2, 100, 100);
	glPopMatrix();

	// Definindo a cor corrente como verde
	glColor3f(0.0f, 1.0f, 0.0f);

	// Meia esfera que irá compor a cabeça do robô
	glPushMatrix();
	glTranslatef (0.0f, 0.0f, 0.07f);
	//meia_esfera(p, 0.5, 20);
	meiaEsfera(0.5, 20);
	glPopMatrix();

	// Disco sob a meia esfera para fechá-la
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	glTranslatef(0.0f, 0.0f, 0.07f);
	gluDisk(qobj, 0.45, 0.5, 30, 30);
	glPopMatrix();

	// Disco que fecha a parte superior do cilindro que forma o tronco do robô
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	//gluQuadricDrawStyle(qobj, GLU_LINE);
	//gluQuadricNormals(qobj, GLU_NONE);
	gluDisk(qobj, 0.45, 0.5, 30, 30);
	glPopMatrix();

	// Cilindro que forma o tronco do robô
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	// gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
	// gluQuadricNormals(qobj, GLU_NONE);
	glTranslatef(0.0f, 0.0f, -0.8f);
	gluCylinder(qobj, 0.5, 0.5, 0.8, 200, 200);
	glPopMatrix();

	// Esfera que fecha a parte inferior do cilindro que forma o tronco do robô
	// glPushMatrix();
	// gluQuadricDrawStyle(qobj, GLU_FILL);
	// gluQuadricNormals(qobj, GLU_SMOOTH);
	// gluQuadricOrientation(qobj, GLU_OUTSIDE);
	// //gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
	// //gluQuadricNormals(qobj, GLU_NONE);
	// glScalef(1.7f, 1.0f, 1.0f);
	// glTranslatef(0.0f, 0.0f, -0.78f);
	// gluSphere(qobj, 0.3, 30, 30);
	// glPopMatrix();

	// Braço direito do robô
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	glTranslatef(-0.63f, 0.0f, -0.5f);
	gluCylinder(qobj, 0.08, 0.08, 0.4, 100, 100);
	glPopMatrix();

	// Meia esfera que irá compor a topo do braço direito do robô
	glPushMatrix();
	glTranslatef(-0.63f, 0.0f, -0.1f);
	meiaEsfera(0.08, 20);
	glPopMatrix();

	// Meia esfera que irá compor a base do braço direito do robô
	glPushMatrix();
	glTranslatef(-0.63f, 0.0f, -0.5f);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	meiaEsfera(0.08, 20);
	glPopMatrix();

	// Braço esquerdo do robô
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	glTranslatef(0.63f, 0.0f, -0.5f);
	gluCylinder(qobj, 0.08, 0.08, 0.4, 100, 100);
	glPopMatrix();

	// Meia esfera que irá compor a topo do braço esquerdo do robô
	glPushMatrix();
	glTranslatef(0.63f, 0.0f, -0.1f);
	meiaEsfera(0.08, 20);
	glPopMatrix();

	// Meia esfera que irá compor a base do braço esquerdo do robô
	glPushMatrix();
	glTranslatef(0.63f, 0.0f, -0.5f);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	meiaEsfera(0.08, 20);
	glPopMatrix();

	// Executa os comandos OpenGL
  glutSwapBuffers();
  glFinish();
}

void initialize(void) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);

		GLfloat luzAmbiente[4] = { 0.3,0.3,0.3,1.0 };
		GLfloat luzDifusa[4] = { 0.2,0.2,0.2,1.0 };	   // "cor"
		GLfloat luzEspecular[4] = { 0.7,0.7,0.7, 1.0 };// "brilho"
		GLfloat posicaoLuz[4] = { 0.0, 20.0, 20.0, 1.0 };
		// Capacidade de brilho do material
		GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
		GLint especMaterial = 10;

		// Define a cor de fundo da janela de visualização como preta
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Habilita o modelo de colorização de Gouraud
		glShadeModel(GL_SMOOTH);

		// Define a refletância do material
		glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
		// Define a concentração do brilho
		glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

		// Ativa o uso da luz ambiente
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

		// Define os parâmetros da luz de número 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
		glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
		glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

		// Habilita a definição da cor do material a partir da cor corrente
		glEnable(GL_COLOR_MATERIAL);
		//Habilita o uso de iluminação
		glEnable(GL_LIGHTING);
		// Habilita a luz de número 0
		glEnable(GL_LIGHT0);
		// Habilita o depth-buffering
		glEnable(GL_DEPTH_TEST);
	  // Indica a função de teste
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

// void redraw() {
//   glutPostRedisplay();
// }

int main(int argc, char **argv) {
	glutInit(&argc, argv);
  // GLUT_DEPTH para alocar Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 1200);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Android Robot");
  //glutIdleFunc(Redraw);
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	initialize();
	glutMainLoop();
}

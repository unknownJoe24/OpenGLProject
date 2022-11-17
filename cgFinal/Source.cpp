#include <glut.h>
#include <stdio.h>
#include <math.h>

bool bwire = true;
bool bsolid = false;
bool baxis = true;
bool bpath = false;
bool banim = false;
bool blight = true;
bool blinePath = false;
bool bsquarePath = false;

float lx = 0.0f, lz = -1.0f; //camera direction
float x = 0.0f, z = 10.0f, y; //position for camera
float angle = 0.0f; //angle for camera
float tireAngle = 0.0f;
float xpos = 0.0, zpos = 0.0, tireRotation = 0.0;
float spec = 1, diff = 1, amb = 1, shiny = 1;
float deltaAngle = 0.0f;

int xOrigin = -1;
int animCycle = 0; //how far along animation is
int animCount = 0; //times animation played
int yRot = 0;


void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
	glPushMatrix();
	glScalef(width, height, depth);
	glutWireCube(1.0);
	glPopMatrix();
}

void wireTire(GLdouble iradius, GLdouble oradius, GLint sides, GLint rings) {
	glPushMatrix();
	glutWireTorus(iradius, oradius, sides, rings);
	glPopMatrix();
}

void solidBox(GLdouble width, GLdouble height, GLdouble depth) {
	glPushMatrix();
	glScalef(width, height, depth);
	glutSolidCube(1.0);
	glPopMatrix();
}

void solidTire(GLdouble iradius, GLdouble oradius, GLint sides, GLint rings) {
	glPushMatrix();
	glutSolidTorus(iradius, oradius, sides, rings);
	glPopMatrix();
}

void drawWire() {
	glPushMatrix();
	glColor3f(1, 0, 1);
	glRotatef(yRot, 0, 1, 0);
	glTranslatef(xpos, 0, zpos);
	
	wireBox(6, 5, 6); //main part of car
	//front part of car
	glTranslatef(0, -1, 4.5);
	//glTranslatef(0, 0, zpos);
	wireBox(6, 3, 3);
	//trunk of car
	glTranslatef(0, 0, -9);
	//glTranslatef(0, 0, zpos);
	wireBox(6, 3, 3);
	//right rear tire
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, -2, 3);
	glRotatef(tireRotation, 0, 0, 1);
	wireTire(0.2, 1, 16, 16);
	//left rear tire
	glTranslatef(0, 0, -6);
	glRotatef(tireRotation, 0, 0, 1);
	wireTire(0.2, 1, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(xpos, 0, zpos);
	//left front tire
	glRotatef(90, 0, 1, 0);
	glTranslatef(-4, -3, -3);
	glRotatef(tireRotation, 0, 0, 1);
	wireTire(0.2, 1, 16, 16);
	//right front tire
	glTranslatef(0, 0, 6);
	glRotatef(tireRotation, 0, 0, 1);
	wireTire(0.2, 1, 16, 16);
	glPopMatrix();
	//head lights/tail lights
	glPushMatrix();
	glTranslatef(xpos, 0, zpos);
	//right head light
	glTranslatef(2, -0.25, 6);
	wireTire(0.2, 0.4, 16, 16);
	//left head light
	glTranslatef(-4, 0, 0);
	wireTire(0.2, 0.4, 16, 16);
	//left tail light
	glTranslatef(0, 0, -12);
	wireTire(0.2, 0.4, 16, 16);
	//right tail light
	glTranslatef(4, 0, 0);
	wireTire(0.2, 0.4, 16, 16);
	glPopMatrix();
}

void drawSolid() {
	glPushMatrix();
	glTranslatef(xpos, 0, zpos);
	solidBox(6, 5, 6); //main part of car
	//front part of car
	glTranslatef(0, -1, 4.5);
	//glTranslatef(0, 0, zpos);
	solidBox(6, 3, 3);
	//trunk of car
	glTranslatef(0, 0, -9);
	//glTranslatef(0, 0, zpos);
	solidBox(6, 3, 3);
	//right rear tire
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, -2, 3);
	glRotatef(tireRotation, 0, 0, 1);
	solidTire(0.2, 1, 16, 16);
	//left rear tire
	glTranslatef(0, 0, -6);
	glRotatef(tireRotation, 0, 0, 1);
	solidTire(0.2, 1, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(xpos, 0, zpos);
	//left front tire
	glRotatef(90, 0, 1, 0);
	glTranslatef(-4, -3, -3);
	glRotatef(tireRotation, 0, 0, 1);
	solidTire(0.2, 1, 16, 16);
	//right front tire
	glTranslatef(0, 0, 6);
	glRotatef(tireRotation, 0, 0, 1);
	solidTire(0.2, 1, 16, 16);
	glPopMatrix();
	//head lights/tail lights
	glPushMatrix();
	glTranslatef(xpos, 0, zpos);
	//right head light
	glTranslatef(2, -0.25, 6);
	solidTire(0.2, 0.4, 16, 16);
	//left head light
	glTranslatef(-4, 0, 0);
	solidTire(0.2, 0.4, 16, 16);
	//left tail light
	glTranslatef(0, 0, -12);
	solidTire(0.2, 0.4, 16, 16);
	//right tail light
	glTranslatef(4, 0, 0);
	solidTire(0.2, 0.4, 16, 16);
	glPopMatrix();
}

void wireTree() {
	//draw a tree
	glPushMatrix();
	glColor3f(0.588, 0.294, 0);
	glutWireCube(2);
	glColor3f(0, 1, 0);
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glutWireCone(3, 7, 20, 5);
	glClearColor(1, 1, 1, 1);
	glPopMatrix();
}

void solidTree() {
	//draw a tree
	glPushMatrix();
	glColor3f(0.588, 0.294, 0);
	glutSolidCube(2);
	glColor3f(0, 1, 0);
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glutSolidCone(3, 7, 20, 5);
	glPopMatrix();
}

//create straight line path
void linePath() {
	glBegin(GL_LINES);
	glColor3f(0, 1, 1);
	glVertex3f(0, -3, 0);
	glVertex3f(0, -3, 12);
	glEnd();
}

//create square path
void squarePath() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(0, -3, 0);
	glVertex3f(0, -3, 12);
	glVertex3f(0, -3, 12);
	glVertex3f(12, -3, 12);
	glVertex3f(12, -3, 12);
	glVertex3f(12, -3, 0);
	glVertex3f(12, -3, 0);
	glVertex3f(0, -3, 0);
	glEnd();
}

void drawAxes()
{
	glDisable(GL_LIGHTING);
	// Draw a red x-axis, a green y-axis, and a blue z-axis.  
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(5, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 5, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 5);
	glEnd();
}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, GLfloat(w) / GLfloat(h), 1.0, 20.0);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);


	GLfloat lightPosition[] = { 0, 5, 0 };
	GLfloat lightAmbient[] = { 0,0.1,0.1,1 };
	GLfloat lightDiffuse[] = { 1,1,1,1 };

	GLfloat matAmbient[] = { 1,1,1,1 };
	GLfloat matDiffuse[] = { 1,1,1,1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	glEnable(GL_LIGHT0);

	//spotlight
	GLfloat spotLightPos[] = { 0,2,0,1 };
	GLfloat spotLightAmbient[] = { 0,1,1,1 };
	GLfloat spotLightDiffuse[] = { 1,1,1,1 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, spotLightAmbient);
	//glLightf(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);

	glLoadIdentity();
	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);

	glColor3f(0, 0.5, 0);
	glBegin(GL_QUADS);
	glVertex3f(-100.0, 0.0, -100.0);
	glVertex3f(-100.0, 0.0, 100.0);
	glVertex3f(100.0, 0.0, 100.0);
	glVertex3f(100.0, 0.0, -100.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	if (bwire) {
		glDisable(GL_LIGHTING);
		drawWire(); // draw a car
		glPushMatrix();
		 //first tree
		glTranslatef(15.0, -5.2, -8.0);
		wireTree();
		//second tree
		glTranslatef(0.0, 0.0, -6.0);
		wireTree();
		//third tree
		glTranslatef(0.0, 0.0, 10.0);
		wireTree();
		glPopMatrix();
	}
	if (bsolid) {
		glEnable(GL_LIGHTING);
		if (blight)
			glEnable(GL_LIGHT1);
		if (!blight)
			glDisable(GL_LIGHT1);

		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);

		glPushMatrix();
		//first tree
		glTranslatef(15.0, -5.2, 3.0);
		solidTree();
		//second tree
		glTranslatef(0.0, 0.0, -6.0);
		solidTree();
		//third tree
		glTranslatef(0.0, 0.0, 10.0);
		solidTree();
		glPopMatrix();

		//menu for changing materials on car
		//set materials
		GLfloat matSpecular[] = { spec, spec, spec, 1 };
		GLfloat matDiffuse[] = { diff, diff, diff, 1 };
		GLfloat matAmbient[] = { amb, amb, amb, 1 };
		GLfloat matShiny[] = { shiny };

		//apply materials
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShiny);
		glClearColor(0, 0, 0, 0);

		drawSolid();

	}
	glPopMatrix();

	if (baxis)
		drawAxes(); // draw axes

	if (blinePath)
		linePath();

	if (bsquarePath)
		squarePath();

	glFlush();
}
void init() {
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void menu(int option) {
	switch (option) {
	case 1: spec = 0; break;
	case 2: spec = 0.5; break;
	case 3: spec = 1; break;
	case 4: diff = 0; break;
	case 5: diff = 0.5; break;
	case 6: diff = 1; break;
	case 7: amb = 0; break;
	case 8: amb = 0.5; break;
	case 9: amb = 1; break;
	case 10: shiny = 0; break;
	case 11: shiny = 0.5; break;
	case 12: shiny = 1; break;
	}
}

void timer(int v) {
	//animation timer
	if (banim) {
		tireRotation += 5;
		if (blinePath) {
			if (animCount <= 60) {
				// move forward
				zpos += 0.4;
			}
			animCount++;
		}

		if (bsquarePath) {
			if (animCount <= 30) {
				zpos += 0.4;
			}
			else if (animCount == 30) {
				//rotate car
				yRot += 90;
			}
			else if (animCount >= 31 && animCount <= 60) {
				xpos += 0.4;
			}
			else if (animCount == 60) {
				//rotate car again
				yRot += 90;
			}
			else if (animCount >= 61 && animCount <= 90) {
				zpos -= 0.4;
			}
			else if (animCount == 90) {
				//rotate car again
				yRot += 90;
			}
			else if (animCount >= 91 && animCount <= 120) {
				xpos -= 0.4;
			}
			else if (animCount == 120) {
				//rotate one last time
				yRot += 90;
			}
			animCount++;
		}

		glutPostRedisplay();
	}

	glutTimerFunc(100, timer, v);
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
	}

	float fraction = 0.5f;

	if (button == 3) { //scroll up
		if (state == GLUT_UP) return;
		x += lx * fraction;
		z += lz * fraction;
	}
	else if (button == 4) { //scroll down
		if (state == GLUT_UP) return;
		x -= lx * fraction;
		z -= lz * fraction;
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void procKeys(unsigned char key, int x, int y) {
	switch (key) {
	case '1': bwire = !bwire; glutPostRedisplay(); break;
	case '2': bsolid = !bsolid; glutPostRedisplay(); break;
	case '3': baxis = !baxis; break;
	case '4': bpath = !bpath; break;
	case '5':
		xpos = 0.0;
		zpos = 0.0;
		tireRotation = 0.0;
		animCount = 0;
		glutPostRedisplay();
		break; //reset position
	case 'a': banim = !banim; break;
	case 'p': 
		if (blinePath) {
			blinePath = false;
			bsquarePath = true;
		}
		else {
			blinePath = true;
			bsquarePath = false;
		}
		break; //toggle paths
	case 's': blight = !blight; glutPostRedisplay(); break;
	case 27: exit(0); break;
	}
}

void special(int key, int, int) {
	float fraction = 0.5f;
	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	default: return;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	printf("\n\
----------------------------------------------------\n\
	OpenGL Sample Program for a car:\n\
	- '1': display wireframe models \n\
	- '2': display solid models \n\
	- '3': toggle on off to draw axes \n\
	- '4': toggle car path \n\
	- '5': reset car position \n\
	- 'a': toggle animation \n\
	- 'p': toggle diferent paths \n\
	- 's': toggle spotlight \n\
	- ESC to quit \n\
**mouse zoom on scroll wheel due to menu being mapped to right click \n\
----------------------------------------------------\n");
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Final");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(procKeys);
	glutSpecialFunc(special);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	//menu options for specular
	int subMenu1 = glutCreateMenu(menu);
	glutAddMenuEntry("0", 1);
	glutAddMenuEntry("0.5", 2);
	glutAddMenuEntry("1", 3);
	//menu options for difuse
	int subMenu2 = glutCreateMenu(menu);
	glutAddMenuEntry("0", 4);
	glutAddMenuEntry("0.5", 5);
	glutAddMenuEntry("1", 6);
	//menu options for ambient
	int subMenu3 = glutCreateMenu(menu);
	glutAddMenuEntry("0", 7);
	glutAddMenuEntry("0.5", 8);
	glutAddMenuEntry("1", 9);
	//menu options for shininess
	int subMenu4 = glutCreateMenu(menu);
	glutAddMenuEntry("0", 10);
	glutAddMenuEntry("0.5", 11);
	glutAddMenuEntry("1", 12);

	glutCreateMenu(menu);
	glutAddSubMenu("Specular", subMenu1);
	glutAddSubMenu("Diffuse", subMenu2);
	glutAddSubMenu("Ambient", subMenu3);
	glutAddSubMenu("Shininess", subMenu4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//glEnable(GL_DEPTH_TEST);
	init();
	glutTimerFunc(10, timer, 0);
	glutMainLoop();
	return 0;
}
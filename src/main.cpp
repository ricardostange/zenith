#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <vector>

#define PI 3.14159264
#define TORAD 2*PI/360
#define GM 398600.441
#define EARTHRADIUS 6341.0

using namespace std;

float scale = 1/EARTHRADIUS;

typedef struct elements{
	float e;	// Eccentricity [0,1)
	float a;	// Semimajor axis
	float i;	// Inclination
	float omega;	// Longitude of the ascending node
	float w;	// Argument of Periapsis
	float m;	// Mean anomaly at epoch
	float n0;	// Orbital period in revolutions per day
}elements;

double semimajorAxis(float orbitalPeriod){ // orbital period given in revolutions per day
	double nSeconds = (1/orbitalPeriod)*24.0*60*60;	// number of seconds that each revolution takes
	return(pow((nSeconds*nSeconds*GM)/(4*PI*PI), 1.0/3)); // terceira lei de kepler
}


vector<elements> orbits;


void calculaTrajetoria(){
    float posicao[3],velocidade[3],L[3],modulo_L,W[3],inc,incgrau,omega,a,modulo_v,modulo_r,aux,p,e,prod_interno,E,n,u,v,w;

    int i;

    prod_interno = 0;

    printf("Digite a posicao inical do satelite no sistema equatorial de coordenadas \n");

    for (i = 0; i <= 2; i++)

    {

        scanf("%f", &posicao[i]);

    }

    printf("Digite a velocidade inical do satelite no sistema equatorial de coordenadas \n");

    for (i = 0; i <= 2; i++)

    {

        scanf("%f", &velocidade[i]);

        prod_interno = prod_interno + posicao[i]*velocidade[i];

    }

    modulo_r = sqrt(pow(posicao[0],2) + pow(posicao[1],2) + pow(posicao[2],2));

    modulo_v = sqrt(pow(velocidade[0],2) + pow(velocidade[1],2) + pow(velocidade[2],2));

    L[0] = posicao[1]*velocidade[2] - posicao[2]*velocidade[1];

    L[1] = posicao[2]*velocidade[0] - posicao[0]*velocidade[2];

    L[2] = posicao[0]*velocidade[1] - posicao[1]*velocidade[0];

    modulo_L = sqrt(pow(L[0],2) + pow(L[1],2) + pow(L[2],2));

    for (i = 0; i <= 2; i++)

    {

        W[i] = L[i]/modulo_L;

    }

    inc = atan((sqrt(pow(W[0],2) + pow(W[1],2)))/W[2])*180/3.1415926535;

    if(inc < 0)

    inc = inc + 180;

    omega = (atan(W[0]/(-W[1])))*180/3.1415926535;

    if (omega < 0)

    omega = omega + 180;

    aux = (2/modulo_r) - ((pow(modulo_v,2))/GM);

    a = 1/aux;

    p = (pow(modulo_L,2))/GM;

    e = sqrt(1 - (p/a));

        if (e >= 1)

        {

              printf("A trajetoria do satelite sera uma hiperbole ou parabola");

        }

        else

        {

            n = sqrt(GM/pow(a,3));

            E = atan(prod_interno/(a*n*(a - modulo_r)));

            if (E < 0)

            E = E + 3.1415926535;

            u = atan(posicao[2]/(posicao[1]*W[0] - posicao[0]*W[1]))*180/3.1415926535;

            v = atan(sqrt(1 - e*e)*sin(E)/(cos(E) - e))*180/3.1415926535;

            w = u - v;

            printf("i = %f\nomega = %f\na = %f\ne = %f\nw = %f",inc,omega,a,e,w);

        }
	elements ele;
	printf("Digite a excentricidade [0,1):");
	printf("Digite a inclinacao: ");
	printf("Digite o argumento da periapsis: ", &ele.w);
	ele.e = e;
	ele.i = i;
	ele.w = omega;
	orbits.push_back(ele);
	glutPostRedisplay();
}

void display(void)
{
/*  clear all pixels  */
//glClearDepth(1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*  draw white polygon (rectangle) with corners at
 *   *  (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
 *    */
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
	/*
        glVertex3f (0.25, 0.25, 0.0);
        glVertex3f (0.75, 0.25, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.95,0.5,0.0);
	glVertex3f(0.75,0.75,0.0);
        glVertex3f (0.25, 0.75, 0.0);
	*/
    glEnd();

glLineWidth(2.5);
glColor3f(1.0, 0.0, 0.0);
//float omega = 318.15;
//float e = 0.9;
//float w = 318.15;
//float i = 5.16;

for(int i=0; i<orbits.size(); i++){
	glBegin(GL_LINE_STRIP);
		double sma =  semimajorAxis(orbits[i].n0);
		for(float v = 0; v < 360; v++){
			elements orb = orbits[i];
			float u = 2*PI*(v+orb.w)/360;
			float r = 1.0/(1+orb.e*cos(u))*scale*sma;
			float x = r*((cos(u)*cos(orb.w*TORAD)-sin(u)*cos(orb.i*TORAD)*sin(orb.w*TORAD)));
			float y = r*(cos(u)*sin(orb.w*TORAD)+sin(u)*cos(orb.i*TORAD)*cos(orb.w*TORAD));
			float z = r*sin(u)*sin(orb.i*TORAD);
			glVertex3f(x,y,z);
			//glVertex3f(r*(cos(u)-sin(u)*cos(i))*cos(w),(cos(u)*sin(w)+sin(u)*cos(i)*cos(w))*r , r*sin(u)*sin(i));
		}
	glEnd();
}
glBegin(GL_LINE_STRIP);
	glColor3f(0.0,1.0,1.0);
	for(float theta = 0; theta < 360; theta++){
	glVertex3f(0.0,sin(PI*2*theta/360)*0.5,cos(PI*2*theta/360)*0.5);
	}
glEnd();
glBegin(GL_LINES);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(1.0,.0,.0);
	glVertex3f(.0,.0,.0);
	glVertex3f(0.0,1.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,0.0,1.0);
glEnd();


/*  don't wait!  
 *   *  start processing buffered OpenGL routines 
 *    */
    glutSolidSphere(0.5*scale*EARTHRADIUS, 200, 200);
    glFlush ();
}

void init (void) 
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(0.0, 10.0, 0.0, 10.0, -10.0, 10.0);
    glEnable(GL_DEPTH_TEST);
glDepthMask(GL_TRUE);
glDepthFunc(GL_LEQUAL);
//glDepthRange(0.0f, 1.0f);
}

/* 
 *  *  Declare initial window size, position, and display mode
 *   *  (single buffer and RGBA).  Open window with "hello"
 *    *  in its title bar.  Call initialization routines.
 *     *  Register callback function to display graphics.
 *      *  Enter main loop and process events.
 *       */


void adicionarOrbita(){
	elements ele;
	printf("Digite a excentricidade [0,1):");
	scanf("%f", &ele.e);
	printf("Digite a inclinacao: ");
	scanf("%f", &ele.i);
	printf("Digite o argumento da periapsis: ", &ele.w);
	scanf("%f", &ele.w);
	printf("Digite o numero de revolucoes por dia", &ele.n0);
	scanf("%f", &ele.n0);

	orbits.push_back(ele);
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
switch(key) {
case 'a':
glRotatef(1.0,1.0,0.0,0.0);
break;
case 'd':
glRotatef(1.0,-1.0,0.0,0.0);
break;
case 'w':
glRotatef(1.0,0.0,1.0,.0);
break;
case 's':
glRotatef(1.0,0.0,-1.0,.0);
break;
case 'q':
glRotatef(1.0,0.0,0.0,1.0);
break;
case 'e':
glRotatef(1.0,0.0,0.0,-1.0);
break;
case '+':
scale*=1.1;
break;
case '-':
scale*=0.9;
break;
case 'i':
adicionarOrbita();
break;
case 'c':
calculaTrajetoria();
break;
break;

default:
break;
}
glutPostRedisplay(); /* this redraws the scene without
waiting for the display callback so that any changes appear
instantly */
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1000, 1000); 
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("hello");
    init ();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display); 
    glutMainLoop();
    printf("lalalalalalala\n");
    return 0;   /* ISO C requires main to return int. */
}

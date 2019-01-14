#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;
#define PI 3.14
GLint WindW = 800;
GLint WindH = 600;

class  Node
{
public:
	float x, y, z;
	float directiony, directionz;
	//float directionx;
	Node(){}
};

string way[3]; //提供生成规则 
string rule, temprule;

float len; //单步长
float len1;
//float Alphax;
float Alphay;
float Alphaz;
int k;   //树干树
int n;  //迭代次数

Node   stack[150];
int    stackpointer;

void LSystemRule()
{
	//初始化
	way[0] = "FA[+X][-&X]-%XB";
	len = 5;
	Alphaz = 30;
	Alphay = 60;
	n = 6;   //稀疏程度
	k = 0;
	stackpointer = 0;//栈顶指针
	for (int i = 0; i <150; i++)
	{
		stack[i].x = 0.0;
		stack[i].y = 0.0;
		stack[i].z = 0.0;
		stack[i].directionz = 0;
		stack[i].directiony = 0;
	}
	temprule = way[0];
	for (int i = 1; i <= n; i++)
	{
		int curlen = temprule.length();
		int pos = 0, j = 0;
		while (j < curlen)
		{
			if (temprule[j] == 'X')//迭代，将其中的F替换成文法模型
			{
				rule +=  way[0];
				j++;
				pos = rule.length() - 1;
			}
			else//保留转角
			{
				rule += temprule[j];
				pos++;
				j++;
			}
		}
		temprule = rule;
		rule.clear();
	}
	rule = temprule;//迭代好之后的文法规则
} 

void drawGrass()
{
	Node  Nextnode, Curnode;
	Curnode.x = 0.0;
	Curnode.y = 0.0;
	Curnode.z = 0.0;
	Curnode.directionz = 85;
	Curnode.directiony = 0;
	int length = rule.length();
	int  i = 0;
	
	glTranslatef(0.0, -15.0, 0.0);

	glPushMatrix();
	while (i < length)
	{
		switch (rule[i])
		{
		case 'F':
			if(len<=0.9)
			{
				glLineWidth(2);
				glColor3f(1,1,1);
				//glColor3f((float)34/255, (float)139/255, (float)34/255);
			}
			else if(len>0.9&&len<4.0)
			{
				glLineWidth(2);
				//glColor3f((float)210/255, (float)180/255, (float)140/255);
				glColor3f(0.8,0.8,0.8);
			}
			//else if(len>1.8&&len<3)
				//glColor3f((float)34/255, (float)139/255, (float)34/255);
			else
			{
				glLineWidth(10);
				glColor3f(0.8,0.8,0.8);
			}
			Nextnode.x = Curnode.x + len * cos(Curnode.directionz * PI / 180) * cos(Curnode.directiony * PI / 180);
			Nextnode.y = Curnode.y + len * sin(Curnode.directionz * PI / 180);
			Nextnode.z = Curnode.z - len * cos(Curnode.directionz * PI / 180) * sin(Curnode.directiony * PI / 180);
			Nextnode.directionz = Curnode.directionz;
			Nextnode.directiony = Curnode.directiony;
			glBegin(GL_LINES);
			glVertex3f(Curnode.x, Curnode.y, Curnode.z);
			glVertex3f(Nextnode.x, Nextnode.y, Nextnode.z);
			glEnd();
			Curnode = Nextnode;
			k++;
			break;
		case 'X':
			glColor3f(1,0,1);
			glLineWidth(1);
			Nextnode.x = Curnode.x + len1 * cos(Curnode.directionz * PI / 180) * cos(Curnode.directiony * PI / 180);
			Nextnode.y = Curnode.y + len1 * sin(Curnode.directionz * PI / 180);
			Nextnode.z = Curnode.z - len1 * cos(Curnode.directionz * PI / 180) * sin(Curnode.directiony * PI / 180);
			Nextnode.directionz = Curnode.directionz;
			Nextnode.directiony = Curnode.directiony;
			glBegin(GL_LINES);
			glVertex3f(Curnode.x, Curnode.y, Curnode.z);
			glVertex3f(Nextnode.x, Nextnode.y, Nextnode.z);
			glEnd();
			Curnode = Nextnode;
			break;
		case 'A':
			len=len*7/10;
			len1=len;
			break;
		case 'B':
			len=len*10/7;
			break;
		case '[':
			stack[stackpointer] = Curnode;
			stackpointer++;
			break;
		case ']':
			Curnode = stack[stackpointer - 1];
			stackpointer--;
			break;
		case '+':
			Curnode.directionz = Curnode.directionz + Alphaz;
			break;
		case '-':
			Curnode.directionz = Curnode.directionz - Alphaz;
			break;
		case '&':
			Curnode.directiony = Curnode.directiony + Alphay;
			break;
		case '%':
			Curnode.directiony = Curnode.directiony - Alphay;
			break;
		default:
			;
		}
		i++;
	}
	glPopMatrix();
	
}
void  init()
{
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
	glMatrixMode(GL_MODELVIEW);
	//glEnable(GL_DEPTH_TEST);
	
	LSystemRule();
	glDisable(GL_BLEND);
}

static int times = 0;  
void  display()
{  
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLoadIdentity();
	//glColor4f(1.0, 1.0, 1.0, 1.0);
	//glPushMatrix();
	//drawGrass();
	//glPopMatrix();
   static float rotate = 0;  
	 times++;  
    if(times > 100)  
    {  
        times = 0;  
    }  
  
    if(times % 100 == 0)  
    {  
        rotate += 6;  
    }  
      
    glRotatef(rotate, 0, 1,0); 
	drawGrass();  
    //glRotatef(rotate, 1, 0, 0);  
  
     
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	GLfloat f = 25.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-f, f, -f*(GLfloat)h / (GLfloat)w,
		f*(GLfloat)h / (GLfloat)w, -f, f);
	else
		glOrtho(-f*(GLfloat)w / (GLfloat)h,
		f*(GLfloat)w / (GLfloat)h, -f, f, -f, f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int  main(int  argc, char  **argv)
{
	glutInit(&argc, argv);    
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cayley tree 3D");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);  
	 glutIdleFunc(display);  
	init();	 
	glutMainLoop(); 
	
	return 0;
	system("pause");
}

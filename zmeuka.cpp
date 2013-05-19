#include <stdlib.h>
#include "textur.h"
#include <ctime>
typedef unsigned short small;
small Kvv = 24;
small KvSh = 18, KvDl = 22;
small Sh = float(KvSh * Kvv) , Dl = float(KvDl * Kvv);
small kyrs;
bool down = true;
bool a = true;
bool fr = true;
small HP = 2;


class Kv
{
public:
  small t;
	Kv()
	{
		t = rand() % 5;
	}
	void KvDraw();
	small x;
	small y;
};

void Kv::KvDraw()
{
	glBegin(GL_POLYGON);
	glTexCoord2f(0.05 * t, 0);
	glVertex2f(float(x), float(y + Kvv));
	glTexCoord2f((float(0.05 * t) + 0.05), 0);
	glVertex2f(float(x + Kvv), float(y + Kvv));
	glTexCoord2f((float(0.05 * t) + 0.05), 1);
	glVertex2f(float(x + Kvv), float(y));
	glTexCoord2f(0.05 * t, 1);
	glVertex2f(float(x), float(y));
	glEnd();
}
Kv pol[18][22];
Kv Frut;

class Zm : public Kv
{
public:
 void GO();
};

Zm zmeuka[50];

void Zm::GO()
{
	for(small i = 1; i <= HP; ++i)
	{
	if(((x == zmeuka[i].x) && (y == zmeuka[i].y)) || ((x < 0) || (x > Dl) || (y < 0) || (y > Sh)))
	{
		a = true;
	   HP = 2;
	   down = true;
	   fr = true;
	}
	}
}

void Pole()
{
	for(small y = 0; y < KvSh; y++)
	{
		for(small x = 0; x < KvDl; x++)
		{
		  pol[y][x].KvDraw();
		}
	}
}

void Kyr2();

small c = 1;
void Zm1()
{
	if(a)
	{
		zmeuka[0].x = Dl/2;
		zmeuka[0].y = Sh/2;
		a = false;
		zmeuka[0].t = 7;
	}
	if(down)
	{
	for(c; c <= HP; c++)
	{
		zmeuka[c].t = zmeuka[c-1].t;
		zmeuka[c].x = zmeuka[c - 1].x;
		zmeuka[c].y = zmeuka[c - 1].y - Kvv;
	}
	down = false;
	}
}


void zmeu()
{
	Zm1();
    Kyr2();
   zmeuka[0].GO();
  for(small i = 0; i <= HP; i++)
	{
		zmeuka[i].KvDraw();
   }
}

void frut()
{
  srand(time(0));
  if(fr)
  {
  small Nomery = rand() % int(KvSh);
  small Nomerx = rand() % int(KvDl);
  Frut.t = 6;
  Frut.x = pol[Nomery][Nomerx].x;
  Frut.y = pol[Nomery][Nomerx].y;
  fr = false;
  }
   Frut.KvDraw();
}

void Kyr2()
{
	if((zmeuka[0].x == Frut.x) && (zmeuka[0].y == Frut.y))
	{
		HP++;
		fr = true;
		down = true;
	}

	for(small i = HP; i > 0; --i)
    {
	 if(zmeuka[i].y - zmeuka[i - 1].y < 0)
		 zmeuka[i].t = 11;
	 if(zmeuka[i].y - zmeuka[i - 1].y > 0)
	 		 zmeuka[i].t = 13;
	 if(zmeuka[i].x - zmeuka[i - 1].x < 0)
			 zmeuka[i].t = 12;
	 if(zmeuka[i].x - zmeuka[i - 1].x > 0)
	 		 zmeuka[i].t = 14;
	 zmeuka[i].x = zmeuka[(i-1)].x;
	 zmeuka[i].y = zmeuka[(i-1)].y;
	}
if((kyrs == 0) || (kyrs == 1) || (kyrs == 2) || (kyrs == 3))
		{
	         switch(kyrs)
			{
			  case 0: zmeuka[0].y += Kvv; zmeuka[0].t = 7;
			  break;
			  case 1: zmeuka[0].x += Kvv; zmeuka[0].t = 8;
			  break;
			  case 2: zmeuka[0].y -= Kvv; zmeuka[0].t = 9;
			  break;
			  case 3: zmeuka[0].x -= Kvv; zmeuka[0].t = 10;
			  break;
	        }
		}
		else
			zmeuka[0].y += Kvv;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_ALPHA_TEST);     //разрешаем альфа-тест
  glAlphaFunc(GL_GREATER,0.0);  // устанавливаем параметры
  glEnable (GL_BLEND);         //Включаем режим смешивания цвето
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; //параметры смешивания
  Pole();
  frut();
  zmeu();
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}

void Timer(int)
{
	glutPostRedisplay();
    glutTimerFunc(125, Timer, 0);
}

void Keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
  case 'w': kyrs = 0;
  break;
  case 'd': kyrs = 1;
   break;
  case 'a': kyrs = 3;
   break;
  case 's': kyrs = 2;
  break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(float(Dl), float(Sh));
  glutInitWindowPosition(100, 740);
  glutCreateWindow("zmeuka(alpha)");
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, float(Dl), 0.0, float(Sh), -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glutDisplayFunc(display);
  glutTimerFunc(125, Timer, 0);
  glutKeyboardFunc(Keyboard);
  loadTextur1();
  for(small y = 0; y < KvSh; y++)
  {
	for(small x = 0; x < KvDl; x++)
	{
	  pol[y][x].y = float(y * Kvv);
	  pol[y][x].x = float(x * Kvv);
	}
  }
  glutMainLoop();
}

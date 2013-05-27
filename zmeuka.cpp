//============================================================================
// Name        : zmeu.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdlib.h>
#include "textur.h"
#include <ctime>

typedef unsigned short small;

class Kv // Квадраты, на которые разделено поле
{
public:	Kv()
	{
		k = 0;
	}
	small t; // номер текстуры
	small k;
	void KvDraw(); // метод рисования объетка, т.е. квадрата
	small x; // координаты х и у (самые маленькие, т.е. нижнего левого края квадрата)
	small y;

};

class Zm : public Kv
{
public:
	Zm()
    {
		k = 0;
    }
 void GO(); // метод проверки смерти змейки
};

small Kvv = 24; // Размер сторон квадрата
small KvSh = 18, KvDl = 22; // Квадраты по ширине и длине
small Sh = KvSh * Kvv , Dl = KvDl * Kvv; // общая ширина и длина в пикселях
small kyrs = 0; // курс змейки
small HP = 0; // жизни
small i; // переменная для создание циклов
small c = 1; //переменная отвечающая за номер последней части змейки
small roc = 0; // переменная, которая хранит в себе старый курс змейки
bool down = true; // переменая для создание новых частей змейки
bool a = true; // переменая, которая при положительном значение позволяет начать игру, при смерти змейки оно становиться тру, при начале игры - фалс
bool e = true;

Zm zmeuka[50]; // массив частей змейки, можно сделать и векторный

Kv pol[18][22]; // массив квадратов поля, т.к. поле разделено на квадраты
Kv Frut; // объект - фрукт

void Kv::KvDraw()
{
	switch(k)
	{
	case 0:
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(float(t * 0.1), 0.0);
		glVertex2f(float(x), float(y + Kvv));
		glTexCoord2f(float(t * 0.1 + 0.1), 0.0);
	    glVertex2f(float(x + Kvv), float(y + Kvv));
	    glTexCoord2f(float(t * 0.1 + 0.1), 1.0);
     	glVertex2f(float(x + Kvv), float(y));
    	glTexCoord2f(float(t * 0.1), 1.0);
		glVertex2f(float(x), float(y));
		glEnd();
		break;
	}
	case 1:
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(float(t * 0.1), 1);
		glVertex2f(float(x), float(y + Kvv));
		glTexCoord2f(float(t * 0.1), 0);
		glVertex2f(float(x + Kvv), float(y + Kvv));
		glTexCoord2f(float(t * 0.1 + 0.1), 0);
		glVertex2f(float(x + Kvv), float(y));
		glTexCoord2f(float(t * 0.1 + 0.1), 1);
		glVertex2f(float(x), float(y));
		glEnd();
        break;
	}
	case 2:
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(float(t * 0.1 + 0.1), 1);
		glVertex2f(float(x), float(y + Kvv));
		glTexCoord2f(float(t * 0.1), 1);
		glVertex2f(float(x + Kvv), float(y + Kvv));
		glTexCoord2f(float(t * 0.1), 0);
		glVertex2f(float(x + Kvv), float(y));
		glTexCoord2f(float(t * 0.1 + 0.1), 0);
		glVertex2f(float(x), float(y));
		glEnd();
		break;
	}
	case 3:
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(float(t * 0.1 + 0.1), 0);
	    glVertex2f(float(x), float(y + Kvv));
	    glTexCoord2f(float(t * 0.1 + 0.1), 1);
		glVertex2f(float(x + Kvv), float(y + Kvv));
		glTexCoord2f(float(t * 0.1), 1);
		glVertex2f(float(x + Kvv), float(y));
		glTexCoord2f(float(t * 0.1), 0);
		glVertex2f(float(x), float(y));
		glEnd();
		break;
	}
	}
}

void Zm::GO()
{
	for(i = 1; i <= HP; ++i)	// проверяет каждую часть
	{
	if(((x == zmeuka[i].x) && (y == zmeuka[i].y)) || ((x < 0) || (x > Dl) || (y < 0) || (y > Sh))) // если змейка выйдет за пределы поля или же координаты одной головы будут равны координаты любой другой части
	{
		a = true; //ставим начальные значения переменых для новой игры
	   HP = 2;
	   down = true;
	   e = true;
	}
	}
}

void Pole() // рисуем квадраты
{
	for(i = 0; i < KvSh; i++) // рисуем каждый объект-квадрат поля поотдельности
	{
		for(small x = 0; x < KvDl; x++)
		{
		  pol[i][x].KvDraw();
		}
	}
}

void Kyr2(); // объявляем функцию
void zmeu()
{
	if(a)
	{
		zmeuka[0].t = 6;
    	zmeuka[0].x = Dl/2; // присваеваем переменным х и у головки змеи координаты середины поля и текстуры номер 7 (голова)
    	zmeuka[0].y = Sh/2;
		a = false;
	}
    Kyr2(); // движение и смена текстуры при поворотах, а так же проверка еды на съедение
   zmeuka[0].GO(); // проверка змейки на смерть
  for(i = 0; i <= HP; i++) // рисуем каждый объект поочередно
	{
		zmeuka[i].KvDraw();
   }
}

void frut() // создание фрукта
{
  srand(time(0));
  if(e)
  {
  small Nomery = rand() % int(KvSh); // рандомно выбираеться номер любого квадрата на карте и забираеться его х и у, а потом присваеваем переменной "доне" значение фалс, но оно измениться после съедение фрукта змейкой
  small Nomerx = rand() % int(KvDl);
  Frut.t = 7;
  Frut.x = pol[Nomery][Nomerx].x;
  Frut.y = pol[Nomery][Nomerx].y;
  e = false;
  }
   Frut.KvDraw(); // рисуем фрукт
}

void Kyr2()
{
	if((zmeuka[0].x == Frut.x) && (zmeuka[0].y == Frut.y)) // проверка фрутка на съедение
	{
		HP++; // увеличиваем ХП, т.е. количество частей тела
		down = true; // разрешаем создать новый фрукт, а точнее новые его координаты
		e = true;
	}

	for(i = HP; i > 0; --i) // пробигаемся по всем частям тела, кроме как головы, т.к. от неё все зависит
    {
	 if(zmeuka[i].y - zmeuka[i - 1].y < 0) // назначаем нужную текстуру при поворотах
		 zmeuka[i].k = 0;
	 if(zmeuka[i].y - zmeuka[i - 1].y > 0)
		 zmeuka[i].k = 2;
	 if(zmeuka[i].x - zmeuka[i - 1].x < 0)
		 zmeuka[i].k = 1;
	 if(zmeuka[i].x - zmeuka[i - 1].x > 0)
 		 zmeuka[i].k = 3;
	 zmeuka[i].t = 5;
	 zmeuka[i].x = zmeuka[(i-1)].x;
	 zmeuka[i].y = zmeuka[(i-1)].y;
	}

	if(((kyrs - 2) == roc) || ((kyrs + 2 == roc))) // если, во время движения вверх змейки повернет вниз, то у неё это не получиться
		kyrs = roc;

	switch(kyrs) // передвижение головки
	{
	case 0: zmeuka[0].y += Kvv; zmeuka[0].k = 0;
	break;
	case 1: zmeuka[0].x += Kvv; zmeuka[0].k = 1;
	break;
	case 2: zmeuka[0].y -= Kvv; zmeuka[0].k = 2;
	break;
	case 3: zmeuka[0].x -= Kvv; zmeuka[0].k = 3;
	break;
	}
	roc = kyrs;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);

  Pole();
  glEnable(GL_ALPHA_TEST);     //разрешаем альфа-тест
  glAlphaFunc(GL_GREATER,0.0);  // устанавливаем параметры
  glEnable (GL_BLEND);         //Включаем режим смешивания цвето
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; //параметры смешивания
  frut();
  zmeu();
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}

void Timer(int) // обновляем экран каждые 0.125 секунды + пробигаемся по функции диспреля
{
	glutPostRedisplay();
    glutTimerFunc(125, Timer, 0);
}

void Keyboard(unsigned char key, int x, int y) // клавишы клавиатуры
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
  glutInitWindowPosition(1700, 950);
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
  srand(time(0));
  for(i = 0; i < KvSh; i++) // опр. координаты каждого элемента + её текстуры
  {
	for(small x = 0; x < KvDl; x++)
	{
	  pol[i][x].t = rand() % 5;
	  pol[i][x].y = float(i * Kvv);
	  pol[i][x].x = float(x * Kvv);
	}
  }
  kyrs = 0;
  glutMainLoop();
}

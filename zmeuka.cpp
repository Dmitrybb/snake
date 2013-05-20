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
small Kvv = 24; // Размер сторон квадрата
small KvSh = 18, KvDl = 22; // Квадраты по ширине и длине
small Sh = KvSh * Kvv , Dl = KvDl * Kvv; // общая ширина и длина в пикселях
small kyrs = 0; // курс змейки
bool down = true; // переменая для создание новых частей змейки
bool a = true; // переменая, которая при положительном значение позволяет начать игру, при смерти змейки оно становиться 
//тру, при начале игры - фалс
small HP = 2; // жизни


class Kv
{
public:
	small t; // номер текстуры
	void KvDraw(); // метод рисования объекта, т.е. квадрата
	small x; // координаты х и у (самые маленькие, т.е. нижнего левого края квадрата)
	small y;
};

void Kv::KvDraw()
{
	glBegin(GL_POLYGON); // создаем полигон 
	glTexCoord2f(0.05 * t, 0);// координаты текстуры
	glVertex2f(float(x), float(y + Kvv));
	glTexCoord2f((float(0.05 * t) + 0.05), 0);
	glVertex2f(float(x + Kvv), float(y + Kvv));
	glTexCoord2f((float(0.05 * t) + 0.05), 1);
	glVertex2f(float(x + Kvv), float(y));
	glTexCoord2f(0.05 * t, 1);
	glVertex2f(float(x), float(y));
	glEnd();
}
Kv pol[18][22]; // двухмерный массив квадратов поля, т.к. поле разделено на квадраты
Kv Frut; // объект - фрукт

class Zm : public Kv
{
public:
 void GO(); // метод проверки смерти змейки
};

Zm zmeuka[50]; // массив частей змейки, можно сделать и векторный

void Zm::GO()
{
	for(small i = 1; i <= HP; ++i)	// проверяет каждую часть
	{
	if(((x == zmeuka[i].x) && (y == zmeuka[i].y)) || ((x < 0) || (x > Dl) || (y < 0) || (y > Sh))) // если змейка выйдет за пределы 
	//поля или же координаты одной головы будут равны координаты любой другой части
	{
		a = true; //ставим начальные значения переменых для новой игры
	   HP = 2; 
	   down = true;
	}
	}
}

void Pole()
{
	for(small y = 0; y < KvSh; y++) // рисуем каждый объект-квадрат поля поотдельности
	{
		for(small x = 0; x < KvDl; x++)
		{
		  pol[y][x].KvDraw();
		}
	}
}

void Kyr2();
 
small c = 1; //переменная отвечающая за номер последней части змейки
void Zm1()
{
	if(a) 
	{
	 zmeuka[0].x = Dl/2; // присваеваем переменным х и у головки змеи координаты 
	 //середины поля и текстуры номер 7 (голова)
	 zmeuka[0].y = Sh/2;
	 a = false;
	 zmeuka[0].t = 7;
	}
	if(down)
	for(c; c <= HP; c++) // цикл, который отвечает за назначение новым частям 
	//тела координаты х и у, за счет старых частей тела + текстур
	{
	 zmeuka[c].t = zmeuka[c - 1].t;
	 zmeuka[c].x = zmeuka[c - 1].x;
	 zmeuka[c].y = zmeuka[c - 1].y - Kvv;
	}
}


void zmeu()
{
	Zm1(); // функция создает части тела и опр. их координаты
    Kyr2(); // движение и смена текстуры при поворотах, а так же проверка еды на съедение
   zmeuka[0].GO(); // проверка змейки на смерть
  for(small i = 0; i <= HP; i++) // рисуем каждый объект поочередно
	{
		zmeuka[i].KvDraw();
   }
}

void frut() // создание фрукта
{
  srand(time(0));
  if(down)
  {
  small Nomery = rand() % int(KvSh); // рандомно выбираеться номер любого 
  //квадрата на карте и забираеться его х и у, а потом присваеваем переменной "доне" значение фалс, но оно измениться после съедение фрукта змейкой
  small Nomerx = rand() % int(KvDl);
  Frut.t = 6;
  Frut.x = pol[Nomery][Nomerx].x;
  Frut.y = pol[Nomery][Nomerx].y;
  down = false;
  }
   Frut.KvDraw(); // рисуем фрукт
}
small roc = 0; // переменная, которая хранит в себе старый курс змейки
void Kyr2()
{
	if((zmeuka[0].x == Frut.x) && (zmeuka[0].y == Frut.y)) // проверка фрутка на съедение
	{
		HP++; // увеличиваем ХП, т.е. количество частей тела
		down = true; // разрешаем создать новый фрукт, а точнее новые его координаты
	}

	for(small i = HP; i > 0; --i) // пробигаемся по всем частям тела, кроме как головы, т.к. от неё все зависит
    {
	 if(zmeuka[i].y - zmeuka[i - 1].y < 0) // назначаем нужную текстуру при поворотах
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
	if(((kyrs - 2) == roc) || ((kyrs + 2 == roc))) // если, во время движения вверх змейки повернет вниз,
	//то у неё это не получиться
	kyrs = roc;
	switch(kyrs) // передвижение головки
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
  srand(time(0));
  for(small y = 0; y < KvSh; y++) // опр. координаты каждого элемента + её текстуры
  {
	for(small x = 0; x < KvDl; x++)
	{
	  pol[y][x].t = (rand() % 5);
	  pol[y][x].y = float(y * Kvv);
	  pol[y][x].x = float(x * Kvv);
	}
  }
  glutMainLoop();
}

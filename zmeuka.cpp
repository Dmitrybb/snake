//============================================================================
// Name        : zmeu.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : zmeu.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//===========================================================================
#include <stdlib.h>
#include "textur.h"
#include <ctime>
#include <iostream>

using namespace std;

typedef unsigned short small;



class Kv // Квадраты, на которые разделено поле
{
public:

	small t; // Параметр, отвечающий за номер текстуры
	virtual void KvDraw(); // метод рисования объетка, т.е. квадрата
	small x; // координаты х и у (самые маленькие, т.е. нижнего левого края квадрата)
	small y;

};

class Zm : public Kv
{
public:
	small k; // курс
	Zm()
    {
		k = 0;
    }
	void KvDraw();
 void GO(); // метод проверки смерти змейки
};
class Knopka : public Kv
{
public:

	bool s; // булевой параметр, отвечающий за нажатие кнопки. Сначала кнопка не нажата, т.е. он фалс

	Knopka()
	{
		s = false;
	}
	void Draw(); // Рисуем
	void Proverkas(); // Проверяем на нажатие
};

// Переменные и массивы для меню:
small nomer_min = 0; // Перем., отвечающая за начальную кнопку на опр. странице в меню
small nomer_max = 2; // Перем., отвечающая за последнию кнопку на опр. странице в меню
small Xm; // координата х мышки
small Ym; // коориданат у мышки
small Dlo = 150; // длинна кнопки
small Vyso = 50; // высота кнопки
bool g1 = false; // перем., отвечающая за вызов меню во время игры
bool down2 = false; // перем., отвечающая за нажатие мышки
bool g = false; // перем., отвечающая за работу игры.

Knopka kn[8]; // массив, хранящий в себе 9 кнопок (0 + 8)

// Переменные и массивы для игры:
small HP = 0; // жизни
small i; // переменная для создание циклов
small c = 1; //переменная отвечающая за номер последней части змейки
small roc = 0; // переменная, которая хранит в себе старый курс змейки
bool down = true; // переменая для создание новых частей змейки
bool e = true;
small Kvv = 24; // Размер сторон квадрата
small KvSh = 18, KvDl = 22; // Квадраты по ширине и длине
small Sh = KvSh * Kvv , Dl = KvDl * Kvv; // общая ширина и длина в пикселях
small kyrs; // курс змейки
bool a = true; // переменая, которая при положительном значение позволяет начать игру, при смерти змейки оно становиться тру, при начале игры - фалс


Zm zmeuka[50]; // массив частей змейки, можно сделать и векторный

Kv pol[18][22]; // массив квадратов поля, т.к. поле разделено на квадраты
Kv Frut; // объект - фрукт

void Knopka::Draw()
{
	glBegin(GL_POLYGON);
//	glTexCoord2f(float(t * 0.1), 0.0);
	glVertex2f(float(x), float(y + Vyso));
//	glTexCoord2f(float(t * 0.1 + 0.1), 0.0);
    glVertex2f(float(x + Dlo), float(y + Vyso));
//    glTexCoord2f(float(t * 0.1 + 0.1), 1.0);
 	glVertex2f(float(x + Dlo), float(y));
//	glTexCoord2f(float(t * 0.1), 1.0);
	glVertex2f(float(x), float(y));
	glEnd();
}

void Knopka::Proverkas()
{
	if((Xm >= x) && (Xm <= x + Dlo) && (Ym >= y) && (Ym <= y + Vyso))
	// Проверяем координаты мышки.
	{
		s = true;
	}
}

void Kv::KvDraw()
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
}

void Zm::KvDraw() // рисуем с разных ракурсов
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

void Proverka()
{
	if(HP != 0)
	for(i = 1; i <= HP; ++i)	// проверяет каждую часть
	{
	if(((zmeuka[0].x == zmeuka[i].x) && (zmeuka[0].y == zmeuka[i].y)) || ((zmeuka[0].x < 0) || (zmeuka[0].x > Dl) || (zmeuka[0].y < 0) || (zmeuka[0].y > Sh))) // если змейка выйдет за пределы поля или же координаты одной головы будут равны координаты любой другой части
	{
		a = true; //ставим начальные значения переменых для новой игры
	   HP = 0;
	   down = true;
	   e = true;
	}
	}
	else
	{
		if((zmeuka[0].x < 0) || (zmeuka[0].x > Dl) || (zmeuka[0].y < 0) || (zmeuka[0].y > Sh))
		{
			a = true; //ставим начальные значения переменых для новой игры
		    HP = 0;
			down = true;
		    e = true;
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
    Proverka(); // проверка змейки на смерть
}

void frut() // создание фрукта
{
  srand(time(0));
  if(e)
  {
  small Nomery = rand() % int(KvSh); // рандомно выбираеться номер любого квадрата на карте и забираеться его х и у, а потом присваеваем переменной "доне" значение фалс, но оно измениться после съедение фрукта змейкой
  small Nomerx = rand() % int(KvDl);
  Frut.x = pol[Nomery][Nomerx].x;
  Frut.y = pol[Nomery][Nomerx].y;
  Frut.t = 7;
  e = false;
  }
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

void game()
{
  glEnable(GL_TEXTURE_2D);
  for(i = 0; i < KvSh; i++) // рисуем каждый объект-квадрат поля поотдельности
  {
  	for(small x = 0; x < KvDl; x++)
  	{
  	  pol[i][x].KvDraw();
  	}
  }
  glEnable(GL_ALPHA_TEST);     //разрешаем альфа-тест
  glAlphaFunc(GL_GREATER,0.0);  // устанавливаем параметры
  glEnable (GL_BLEND);         //Включаем режим смешивания цвето
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; //параметры смешивания
  Frut.KvDraw(); // рисуем фрукт
  for(i = 0; i <= HP; i++) // рисуем каждый объект змеи поочередно
  {
	  zmeuka[i].KvDraw();
  }
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_TEXTURE_2D);
}

void begin() // функция, отвечающая за начало игры.
{
  loadTextur1(); // загружаем текстуры
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
  kyrs = 0; // задаем начальный курс, равным 0 (вверх)
  for(small i = nomer_min; i <= nomer_max; i++)
  {
	  kn[i].x = 189;
	  kn[i].y = kn[i - 1].y + 75;
	  kn[6].y = 60;
  }
  a = true;
  g1 = true;
  g = true;
}

void menu1()
{
	if(down2)
	for(small i = nomer_min; i <= nomer_max; i++)
	{
		kn[i].Proverkas();
	}
	if(nomer_min == 0)
	{
	if(kn[0].s)
		exit(0);
	if(kn[2].s)
	{
		kn[2].s = false;
		nomer_min = 3; nomer_max = 5;
		for(small i = 0; i <= 2; i++)
			kn[i].s = false;
		Xm = 0;
		Ym = 0;
		glColor3ub(0, 250, 0);
	}
	}
	else
	{
	if(kn[3].s)
	{
		kn[3].s = false;
		glColor3ub(250, 0, 0);
		nomer_min = 0; nomer_max = 2;
		for(small i = 3; i <= 5; i++)
           kn[i].s = false;
		Xm = 0;
		Ym = 0;
	}
	if(kn[4].s)
	{
		kn[4].s = false;
		Xm = 0;
		Ym = 0;
	}
	if(kn[5].s)
	{
		kn[5].s = false;
		g = true;
		nomer_min = 6;
		nomer_max = 8;
		begin();
	}
	}
}

void menu2_logic()
{
	if(down2)
	for( i = nomer_min; i <= nomer_max; i++)
	{
		kn[i].Proverkas();
	}
	if(kn[6].s)
		exit(0);
	if(kn[7].s)
	{
		g = false;
		g1 = false;
		nomer_min = 0;
		nomer_max = 2;
		kn[7].s = false;
		glColor3ub(250, 0, 0);
	}
	if(kn[8].s)
	{
		kn[8].s = false;
		g1 = true;
		g = true;
		glColor3ub(0, 250, 0);
	}
}

void logic()
{
	if(g)
		if(g1)
		{
			frut();
			zmeu();
		}
		else
		{
			menu2_logic();
		}
	else
		menu1();
}

void display() // функция, которая все рисует
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(g)
		if(g1)
	 game();
    	else
	 for(i = nomer_min; i <= nomer_max; i++)
	{
		glColor3ub(250, 0, 0);
		kn[i].Draw();
	}
    else
    for(i = nomer_min; i <= nomer_max; i++)
	{
		kn[i].Draw();
	}
	glutSwapBuffers();
}

void MousePressed(int button, int state, int ax, int ay)
{
    down2 = button== GLUT_LEFT_BUTTON && state ==GLUT_LEFT;
    if(down2)
    {
    	Xm= ax;
        Ym= Sh - ay;
    }
}


void Timer(int)
{
	logic(); // функция, которая обрабатывает все данные, т.е. отвечает за логику игры
	display(); // функция, которая все рисует
    glutTimerFunc(125, Timer, 0);
}

void Keyboard(unsigned char key, int x, int y) // клавишы клавиатуры
{
  switch(key)
  {
  case 87:
  case 119: kyrs = 0;
  break;
  case 68:
  case 100: kyrs = 1;
   break;
  case 65:
  case 97: kyrs = 3;
   break;
  case 83:
  case 115: kyrs = 2;
  break;
  case 27: g1 = false; nomer_min = 6; nomer_max = 8; // если нажимается Esc, то выводится меню3
  break;
  }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(float(Dl), float(Sh));
    glutInitWindowPosition(700, 950);
    glutCreateWindow("zmeuka(alpha)");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, float(Dl), 0.0, float(Sh), -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutTimerFunc(125, Timer, 0);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MousePressed);
    for(small i = 0; i <= 2; i++)
	{
    	kn[i].x = 189;
    	kn[i].y = kn[i - 1].y + 75;
    	kn[0].y = 60;
	}

   for(small i = 3; i <= 5; i++)
    {
      	kn[i].x = 189;
        kn[i].y = kn[i - 1].y + 75;
       	kn[3].y = 60;
    }
    glColor3ub(250, 0, 0);
    glutMainLoop();
} * Kvv);
	}
  }
  kyrs = 0;
  glutMainLoop();
}

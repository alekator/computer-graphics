#include <glut.h>
#include <math.h>
#include <windows.h>
GLint Width = 620, Height = 480;//Разрешение окна программы
const double cell = 0.050;//Длина стороны псевдопикселя
const double cellDiv = 1 / cell;//Делитель для преобразования координат в подходящие для
//диапазона от - 1 до 1
double x01 = 2, y01 = -2;//Координаты начальной точки отрезка
double x02 = 6, y02 = -4;//Координаты конечной точки отрезка
bool visualPainted = false;//Переменная для защёлки визулизации
int speedVisual = 400;
void coordAxes() {//Изображение координатных осей
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
	glVertex2f(-1, 0); glVertex2f(1, 0);//Ось X
	glVertex2f(0, 1); glVertex2f(0, -1);//Ось Y
	glEnd();
	glLineWidth(1);
}
void pixelGrid() {//Изображение сетки псевдопикселов
	glBegin(GL_LINES);
	for (double i = 0; i < 1; i += cell) {
		glColor3ub(10, 10, 10);
		glVertex2f(-1, i); glVertex2f(1, i);//Горизонтальные линии
		glVertex2f(-1, -i); glVertex2f(1, -i);//Горизонтальные линии
		glVertex2f(i, -1); glVertex2f(i, 1);//Вертикальные
		glVertex2f(-i, -1); glVertex2f(-i, 1);//Вертикальные
	}
	glEnd();
}
void paintPixel(double x, double y, int Red, int Green, int Blue) { //Закрашивание данного
	//пекселя
	glColor3ub(Red, Green, Blue);
	glBegin(GL_QUADS);
	glVertex2f(x + cell, y + cell);
	glVertex2f(x, y + cell);
	glVertex2f(x, y);
	glVertex2f(x + cell, y);
	glEnd();
	if (!visualPainted) { glFinish(); Sleep(speedVisual); }
}
int sign(double a) {//Функция возвращающая знак данного числа
	if (a > 0) return 1;
	if (a < 0) return -1;
	return 0;
}
void ddaLine(int x1, int y1, int x2, int y2) {  //Коричневый
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	double x = x1, y = y1;//Координаты точки растра (точки, от которой будет изображаться
	//закрашенный пиксель)
	double dx = 0, dy = 0;//Для приращения координат на каждом шаге
	double lengthLine;
	if (abs(deltaX) >= abs(deltaY))//Определение того к какой оси ближе расположен отрезок
		lengthLine = abs(deltaX);
	else
		lengthLine = abs(deltaY);
	dx = deltaX / lengthLine;//Вычисление приращения
	dy = deltaY / lengthLine;
	x = floor(x1 + 0.5 * sign(dx));//Чтобы первый пиксель отрезка изображался не строго в (0,0),
	y = floor(y1 + 0.5 * sign(dy));//а в том же квадранте, в каком проходит этот отрезок
	for (int i = 0; i <= lengthLine; i++) {//Построение отрезка
		paintPixel(floor(x) / cellDiv, floor(y) / cellDiv, 210, 105, 30); //Закрашивание псевдопикселя в коричневый
		x += dx;
		y += dy;
	}
}
void brezenhamLine(int x1, int y1, int x2, int y2) {  // Розовый
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int x = floor(x1 + 0.5 * sign(dx));
	if ((x2 - x1) <= 0)
		x = -1;
	int y = floor(y1 + 0.5 * sign(dy));
	if ((y2 - y1) <= 0)
		y = -1;
	int s1 = sign(x2 - x1);//Приращение, учитывающее знак, по оси X
	int s2 = sign(y2 - y1);//и по оси Y
	bool swap = false;//Был ли обмен значений dx и dy?
	if (dy > dx) {// Обмен значений dx и dy в зависимости от углового коэффициента отрезка
		int temp = dx;//этот обмен нужен чтобы алгоритм был пригоден для любой октанты
		dx = dy;
		dy = temp;
		swap = 1;
	}
	else swap = 0;
	double e = 2 * dy - dx;//e это "Ошибка" - расстояние между реальным положением отрезка и
	//ближайшей точкой растра
	for (int i = 0; i <= dx; i++) {//Построение отрезка
		paintPixel(x / cellDiv, y / cellDiv, 255, 0, 255);
		//Когда отрезок проходит выше середины стороны пикселя
		while (e >= 0) {
			if (swap == 1)
				x += s1;
			else
				y += s2;
			e -= 2 * dx;
		}
		//Когда отрезок проходит ниже середины стороны пикселя
		if (swap == 1)
			y += s2;
		else
			x += s1;
		e += 2 * dy;
	}
}
void realLine(double x0, double y0, double x, double y) {  //Черный
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
	glVertex2f(x0 / cellDiv, y0 / cellDiv); glVertex2f(x / cellDiv, y / cellDiv);
	glEnd();
	glLineWidth(1);
}
void Display() {
	glClearColor(255, 255, 255, 1);//Устанавливает цвет, которым будет заполнен буфер кадра
	glClear(GL_COLOR_BUFFER_BIT);//Отчистка буфера кадров
	coordAxes();
	pixelGrid();
	ddaLine(x01, y01, x02, y02);
	realLine(x01, y01, x02, y02);
	brezenhamLine(x01, y01, x02, y02);
	realLine(x01, y01, x02, y02);
	pixelGrid();
	glFinish();
}
void main(int argv, char* argc[]) {
	glutInit(&argv, argc); //Инициализацию библиотеки GLUT
	glutInitWindowSize(Width, Height); //Задание начальных размеров окна
	glutInitDisplayMode(GLUT_RGB); //Инициализирует буфер кадра и настраивает
	//полноцветный(непалитровый) режим RGB.
	glutCreateWindow("CHANCHIKOV_LAB1");//Задает заголовок окна и визуализирует само окно на экране.
	glutDisplayFunc(Display);//Вызов функции Display
	glutMainLoop();//Бесконечный цикл
}
#define _USE_MATH_DEFINES
#include<iostream>
#include<windows.h>
using namespace std;

#define delimiter "\n-----------------------\n"
//enum (Enumeration - Перечисление) - это набор именованных целочисленных констант
enum Color
{
	red = 0x000000FF,
	green=0x0000FF00,
	blue=0x00FF0000,
	yellow=0x0000FFFF,
	magenta=0x00FF00FF,
	cyan=0x00FFFF00,
	white=0x00FFFFFF
};

#define SHAPE_TAKE_PARAMETERS Color color, int start_x, int start_y, int line_width
#define SHAPE_GIVE_PARAMETERS color, start_x, start_y, line_width

class Shape
{
protected:

	static const int MIN_START_X = 10;
	static const int MAX_START_X = 800;	

	static const int MIN_START_Y = 10;
	static const int MAX_START_Y = 500;

	static const int MIN_LINE_WIDTH = 1;
	static const int MAX_LINE_WIDTH = 30;

	static const int MIN_DIMENSION = 25;
	static const int MAX_DIMENSION = 500;

	Color color;
	int start_x;
	int start_y;
	int line_width;
public:
	Color get_color()const
	{
		return color;
	}
	int get_start_x()const
	{
		return start_x;
	}
	int get_start_y()const
	{
		return start_y;
	}
	int get_line_width()const
	{
		return line_width;
	}
	void set_color(Color color)
	{
		this->color = color;
	}
	void set_start_x(int start_x)
	{
		if (start_x < MIN_START_X)start_x = MIN_START_X;
		if (start_x > MAX_START_X)start_x = MAX_START_X;
		this->start_x = start_x;
	}
	void set_start_y(int start_y)
	{
		if (start_y < MIN_START_Y)start_y = MIN_START_Y;
		if (start_y > MAX_START_Y)start_y = MAX_START_Y;
		this->start_y = start_y;
	}
	void set_line_width(int line_width)
	{
		if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
		if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
		this->line_width = line_width;
	}
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	void draw(WINGDIAPI BOOL(__stdcall *DrawFunction)(HDC, int, int, int, int), double horizontal, double vertical)const
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		DrawFunction(hdc, start_x, start_y, start_x + horizontal, start_y + vertical);

		DeleteObject(hPen);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}
	Shape(SHAPE_TAKE_PARAMETERS)
	{
		set_color(color);
		set_start_x(start_x);
		set_start_y(start_y);
		set_line_width(line_width);
	}
	~Shape(){}
	void info()const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimeter() << endl;
		draw();
	}
};

#ifdef SQUARE_INDEPENDENT
class Square :public Shape
{

	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		this->side = side;
	}
	double get_area()const override
	{
		return side * side;
	}
	double get_perimeter()const override
	{
		return side * 4;
	}
	void draw()const override
	{
		/*for (int i = 0; i < side; i++)
		{
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}*/
		//1) Получаем окно консоли: HWND - обращаемся к окну Windows
		HWND hwnd = GetConsoleWindow();
		//2) Получаем контекст устройства для окна консоли
		HDC hdc = GetDC(hwnd);
		//3) Карандаш для рисования контура фигуры
		HPEN hPen = CreatePen(PS_SOLID, line_width,color);
		//4) Кисть для заливки фигуры
		HBRUSH hBrush = CreateSolidBrush(color);
		//5) Выбираем, чем и на чем рисовать. На контексте устройства используем Карандаш и Кисть
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		//6) Рисуем прямоугольник. Для его рисования указываем координаты левого верхнего угла и правого нижнего
		Rectangle(hdc, start_x, start_y, start_x+side, start_y+side);
		//7) После рисования удаляем из памяти инструменты
		DeleteObject(hBrush);
		DeleteObject(hPen);
		//8) Освобождаем контекст устройства
		ReleaseDC(hwnd, hdc);
		//Контекст устройства и все инструменты занимают ресурсы, нужно освобождать в конце работы
	}
	Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_side(side);
	}
	~Square() {}
	void info()const
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина стороны: " << get_side() << endl;
		Shape::info();
	}
};
#endif //SQUARE_INDEPENDENT

class Rectangle :public Shape
{
	 double side_a;
	 double side_b;
public:
	 double get_side_a()const
	 {
		 return side_a;
	 }
	 double get_side_b()const
	 {
		 return side_b;
	 }
	 void set_side_a(double side_a)
	 {
		 if (side_a < MIN_DIMENSION) side_a = MIN_DIMENSION;
		 if (side_a > MAX_DIMENSION) side_a = MAX_DIMENSION;
		 this->side_a = side_a;
	 }
	 void set_side_b(double side_b)
	 {
		 if (side_b < MIN_DIMENSION) side_b = MIN_DIMENSION;
		 if (side_b > MAX_DIMENSION) side_b = MAX_DIMENSION;
		 this->side_b = side_b;
	 }
	 double get_diagonal()const
	 {
		 return sqrt(side_a * side_a + side_b * side_b);
	 }
	 double get_area()const override
	 {
		 return side_a * side_b;
	 }
	 double get_perimeter()const override
	 {
		 return (side_a + side_b) * 2;
	 }
	 void draw()const override
	 {
		 Shape::draw(::Rectangle, get_side_a(), get_side_b());
	}
	Rectangle(double side_a, double side_b, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_color(color);
		set_start_x(start_x);
		set_start_y(start_y);
		set_side_a(side_a);
		set_side_b(side_b);
	}
	~Rectangle(){}
	void info()const
	{
		cout << typeid(*this).name() << endl;
		cout << "Сторона А: " << get_side_a() << endl;
		cout << "Сторона B: " << get_side_b() << endl;
		cout << "Диагональ: " << get_diagonal() << endl;
		Shape::info();
	}
};
class Square :public Rectangle
{
public:
	Square(double side, SHAPE_TAKE_PARAMETERS):Rectangle(side,side,SHAPE_GIVE_PARAMETERS){}
	~Square(){}
};
class Circle :public Shape
{
private:
	double radius;
public:
	double get_radius()const
	{
		return radius;
	}
	void set_radius(double radius)
	{
		if (radius < MIN_DIMENSION) radius = MIN_DIMENSION;
		if (radius > MAX_DIMENSION) radius = MAX_DIMENSION;
		this->radius = radius;
	}
	double get_area()const override
	{
		return M_PI*pow(radius,2);
	}
	double get_diameter()const
	{
		return 2 * radius;
	}
	double get_perimeter()const override
	{
		return M_PI * 2 * radius;
	}
	void draw()const override
	{
		Shape::draw(::Ellipse, get_diameter(), get_diameter());
	}
	Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_radius(radius);
	}
	~Circle(){}
	void info()const
	{
		cout<<typeid(*this).name() << endl;
		cout << "Радиус круга: " << get_radius() << endl;
		cout << "Диаметр круга: " << get_diameter() << endl;
		Shape::info();
	}
};

class Triangle :public Shape
{

public:
	virtual double get_height()const = 0;
	Triangle(SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS){}
	~Triangle() {}
	void draw(WINGDIAPI BOOL (__stdcall *Polygon)(HDC, const POINT*, int), const POINT* vertex)const
	{
		//__stdcall - конвенция вызовов для WinAPI-функций
		//для С/С++ функций, по умолчанию используется конвенция __cdecl
		//x64 для функций используется __fastcall
		/*
		-----------------------------------------------
			type [calling_conversion] name(parameters)
			{
				...;
			}
		-----------------------------------------------
		*/
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		/*POINT vertex[3] =
		{
			{start_x,start_y},
			{start_x + side,start_y},
			{start_x + side / 2,start_y - get_height()}
		};*/
		Polygon(hdc, vertex, 3);

		DeleteObject(hPen);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}
	void info()const
	{
		cout << "Высота треугольника: " << get_height() << endl;
		Shape::info();
	}

};
class EquilateralTriangle :public Triangle
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		if (side < MIN_DIMENSION) side = MIN_DIMENSION;
		if (side > MAX_DIMENSION) side = MAX_DIMENSION;
		this->side = side;
	}
	double get_height()const override
	{
		return sqrt(pow(side, 2) - pow(side / 2, 2));
	}
	double get_area()const override
	{
		return pow(get_height(),2)*sqrt(3);
	}
	double get_perimeter()const override
	{
		return side * 3;
	}
	void draw()const override
	{
		POINT vertex[3] = 
		{ 
			{start_x,start_y},
			{start_x + side,start_y},
			{start_x + side / 2,start_y-get_height()}
		};
		Triangle::draw(::Polygon, vertex);
	}
	EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
	{
		set_side(side);
	}
	~EquilateralTriangle(){}
	void info()
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина стороны: " << side << endl;
		Triangle::info();
	}
};
class IsoscelesTriangle : public Triangle
{
	//https://www-formula.ru/bisectormedianheightisoscelestriangle
	double hip;
	double base;
public:
	double get_hip()const
	{
		return hip;
	}
	double get_base()const
	{
		return base;
	}
	void set_hip(double hip)
	{
		if (hip < MIN_DIMENSION) hip = MIN_DIMENSION;
		if (hip > MAX_DIMENSION) hip = MAX_DIMENSION;
		this->hip = hip;
	}
	void set_base(double base)
	{
		if (base < MIN_DIMENSION) base = MIN_DIMENSION;
		if (base > MAX_DIMENSION) base = MAX_DIMENSION;
		this->base = base;
	}
	double get_height()const override
	{
		return sqrt(pow(hip, 2) - pow(base, 2) / 4);
	}
	double get_area()const override
	{
		return base * get_height() / 2;
	}
	double get_perimeter()const override
	{
		return hip * 2 + base;
	}
	void draw() const override
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		POINT vertex[3] =
		{
			{start_x,start_y},
			{start_x + base/2,start_y+get_height()},
			{start_x + base,start_y}
		};
		::Polygon(hdc, vertex, 3);

		DeleteObject(hPen);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}
	IsoscelesTriangle(double hip, double base, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
	{
		set_hip(hip);
		set_base(base);
	}
	~IsoscelesTriangle(){}
	void info()
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина стороны: " << hip << endl;
		cout << "Длина основания: " << base << endl;
		Triangle::info();
	}
};
class RightTriangle :public Triangle
{
	//https://www-formula.ru/heightrectangulartriangle
	double leg_a;
	double leg_b;
public:
	double get_leg_a()
	{
		return leg_a;
	}
	double get_leg_b()
	{
		return leg_b;
	}
	void set_leg_a(double leg_a)
	{
		if (leg_a < MIN_DIMENSION) leg_a = MIN_DIMENSION;
		if (leg_a > MAX_DIMENSION) leg_a = MAX_DIMENSION;
		this->leg_a = leg_a;
	}
	void set_leg_b(double leg_b)
	{
		if (leg_b < MIN_DIMENSION) leg_b = MIN_DIMENSION;
		if (leg_b > MAX_DIMENSION) leg_b = MAX_DIMENSION;
		this->leg_b = leg_b;
	}
	double get_hypotenuse() const
	{
		return sqrt(pow(leg_a, 2) + pow(leg_b, 2));
	}
	double get_height() const override
	{
		return (leg_a * leg_b) / get_hypotenuse();
	}
	double get_area() const override
	{
		return leg_a * leg_b / 2;
	}
	double get_perimeter() const override
	{
		return leg_a + leg_b + get_hypotenuse();
	}
	void draw() const override
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		POINT vertex[3] =
		{
			{start_x,start_y},
			{start_x + leg_a,start_y},
			{start_x + leg_a,start_y-leg_b}
		};
		::Polygon(hdc, vertex, 3);

		DeleteObject(hPen);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}
	RightTriangle(double leg_a, double leg_b, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
	{
		set_leg_a(leg_a);
		set_leg_b(leg_b);
	}
	~RightTriangle(){}
	void info()
	{
		cout << typeid(*this).name() << endl;
		cout << " Катет А: " << leg_a << endl;
		cout << " Катет B: " << leg_b << endl;
		Triangle::info();
	}
};

class Parallelogramm :public Shape
{
	double side_a;
	double side_b;
	double angle;
public:
	double get_side_a()const
	{
		return side_a;
	}
	double get_side_b()const
	{
		return side_b;
	}
	double get_angle()const
	{
		return angle;
	}
	void set_side_a(double side_a)
	{
		if (side_a < MIN_DIMENSION) side_a = MIN_DIMENSION;
		if (side_a > MAX_DIMENSION) side_a = MAX_DIMENSION;
		this->side_a = side_a;
	}
	void set_side_b(double side_b)
	{
		if (side_b < MIN_DIMENSION) side_b = MIN_DIMENSION;
		if (side_b > MAX_DIMENSION) side_b = MAX_DIMENSION;
		this->side_b = side_b;
	}
	void set_angle(double angle)
	{
		angle = abs(angle);
		while (angle > 180) angle -= 180;
		this->angle = angle;
	}
	double get_diagonal()const
	{
		return sqrt(side_a * side_a + side_b * side_b);
	}
	double get_area()const override
	{
		return side_a * side_b*sin(angle);
	}
	double get_perimeter()const override
	{
		return (side_a + side_b) * 2;
	}
	double get_height()const
	{
		return side_a * sin(angle);
	}
	void draw() const override
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		POINT vertex[4] =
		{
			{start_x,start_y},
			{start_x+side_a*sin(angle),start_y + get_height()},
			{start_x + side_b + side_a * sin(angle),start_y+get_height()},
			{start_x + side_b,start_y}
		};
		::Polygon(hdc, vertex, 4);

		DeleteObject(hPen);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}
};

#define SQUARE
#define RECTANGLE
#define CIRCLE
#define TRIANGLE
void main()
{
	setlocale(LC_ALL, "");
#ifdef SQUARE
	Square square(150, Color::red,300,10,5);
	square.info();
	cout << delimiter << endl;
#endif //SQUARE
#ifdef RECTANGLE
	class Rectangle rect(250, 150,Color::blue,300,210,5);
	rect.info();
	cout << delimiter << endl;
#endif //RECTANGLE
#ifdef CIRCLE
	Circle circle(150, Color::yellow, 700, 10, 5);
	circle.info();
	cout << delimiter << endl;
#endif //CIRCLE
#ifdef TRIANGLE
	class EquilateralTriangle et(150, Color::green, 570, 300, 15);
	et.info();
#endif //TRIANGLE
}
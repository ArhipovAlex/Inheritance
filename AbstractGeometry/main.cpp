#include<iostream>
#include<windows.h>
using namespace std;

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
	static const int MIN_START_X = 10;
	static const int MAX_START_X = 800;	

	static const int MIN_START_Y = 10;
	static const int MAX_START_Y = 500;

	static const int MIN_LINE_WIDTH = 1;
	static const int MAX_LINE_WIDTH = 30;
protected:
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
	Shape(SHAPE_TAKE_PARAMETERS)
	{
		set_color(color);
		set_start_x(start_x);
		set_start_y(start_y);
		set_line_width(line_width);
	}

};

class Square :public Shape
{
private:
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
	Square(double side,SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_side(side);
	}
	~Square(){}

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
};
class Rectangle :public Shape
{
private:
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
		 this->side_a = side_a;
	 }
	 void set_side_b(double side_b)
	 {
		 this->side_b = side_b;
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
		 HWND hwnd = GetConsoleWindow();
		 HDC hdc = GetDC(hwnd);

		 HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		 HBRUSH hBrush = CreateSolidBrush(color);

		 SelectObject(hdc, hPen);
		 SelectObject(hdc, hBrush);

		 ::Rectangle(hdc, start_x, start_y, start_x + side_a, start_y + side_b);

		 DeleteObject(hPen);
		 DeleteObject(hBrush);

		 ReleaseDC(hwnd, hdc);
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
		this->radius = radius;
	}
	double get_area()const override
	{
		return 3.14*radius*radius;
	}
	double get_perimeter()const override
	{
		return 3.14 * 2 * radius;
	}
	void draw()const override
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		Ellipse(hdc, start_x, start_y, start_x + radius, start_y + radius);

		DeleteObject(hPen);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}
	Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_color(color);
		set_start_x(start_x);
		set_start_y(start_y);
		set_radius(radius);
	}
	~Circle(){}
};
class Triangle :public Shape
{
private:
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
		return side * side * sqrt(3) / 4;
	}
	double get_perimeter()const override
	{
		return side * 3;
	}
	void draw()const override
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		POINT polygon[3] = { {start_x,start_y},{start_x + side,start_y},{start_x+side/2,side * sqrt(3)/2 + start_y}};
		::Polygon(hdc, polygon,3);

		DeleteObject(hPen);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}
	Triangle(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_side(side);
	}
	~Triangle() {}
};

//#define SQUARE
//#define RECTANGLE
//#define CIRCLE
#define TRIANGLE
void main()
{
	setlocale(LC_ALL, "");
#ifdef SQUARE
	Square square(150, Color::red,200,200,5);
	cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Периметр:\t" << square.get_perimeter() << endl;
	cout << "Площадь:\t" << square.get_area() << endl;
	square.draw();
#endif //SQUARE
#ifdef RECTANGLE
	class Rectangle rect(200, 150,Color::blue,200,500,5);
	cout << "Сторона А:\t" << rect.get_side_a() << endl;
	cout << "Сторона B:\t" << rect.get_side_b() << endl;
	cout << "Площадь:\t" << rect.get_area() << endl;
	cout << "Периметр:\t" << rect.get_perimeter() << endl;
	rect.draw();
#endif //RECTANGLE
#ifdef CIRCLE
	Circle circle(150, Color::green, 200, 200, 5);
	cout << "Радиус круга: " << circle.get_radius() << endl;
	cout << "Периметр:\t" << circle.get_perimeter() << endl;
	cout << "Площадь:\t" << circle.get_area() << endl;
	circle.draw();
#endif //CIRCLE
#ifdef TRIANGLE
	class Triangle triang(150, Color::yellow, 300, 300, 5);
	cout << "Длина стороны: " << triang.get_side() << endl;
	cout << "Периметр:\t" << triang.get_perimeter() << endl;
	cout << "Площадь:\t" << triang.get_area() << endl;
	triang.draw();
#endif //TRIANGLE
}
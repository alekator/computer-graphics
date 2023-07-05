#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
int main()
{
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(210, 105), "SFML Works!");
	RenderWindow Squb(VideoMode(510, 510), "POLE");
	
	while (Squb.isOpen())
	{
		// ������������ ������� � �����
		Event event;
		while (Squb.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				Squb.close();
		}
		// ��������� ����� ���� - �����
		Squb.clear(Color::White);
		// ��������� ��������������
	
		Texture Qub;
		// ���������� ���� �������� �� ����� texture.png
		Qub.loadFromFile("D:\\Qube.png");
		Sprite sprite20(Qub);
		sprite20.move(0, 0);
		Squb.draw(sprite20);

		// ����� � �������� ��������
		RectangleShape line_with_thickness(Vector2f(700.f, 5.f));

		// ������������ � �� 45 ��������
		line_with_thickness.rotate(5.f);

		// ������������� ����
		line_with_thickness.setFillColor(Color(255, 0, 0));

		// ���������� ����� � ������ ��� ������ �� ��������������
		line_with_thickness.move(5, 0);

		// ��������� �����
		Squb.draw(line_with_thickness);

		//// ����� � �������� ��������
		//RectangleShape line_with_thickness1(Vector2f(700.f, 5.f));

		//// ������������ � �� 45 ��������
		//line_with_thickness1.rotate(25.f);

		//// ������������� ����
		//line_with_thickness1.setFillColor(Color(255, 20, 147));

		//// ���������� ����� � ������ ��� ������ �� ��������������
		//line_with_thickness1.move(5, 0);

		//// ��������� �����
		//Squb.draw(line_with_thickness1);

		// ��������� ����
		Squb.display();
	}

	int a = 0;
	std::cin >> a;
	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();
		}
		// ��������� ����� ���� - �����
		window.clear(Color::White);

		// ������� ���������� ��������
		Texture texture;

		// ���������� ���� �������� �� ����� texture.png
		texture.loadFromFile("D:\\texture.png");

		// ������� 7 �������� ��� �������
		Sprite sprite1(texture);
		Sprite sprite2(texture);
		Sprite sprite3(texture);
		Sprite sprite4(texture);
		Sprite sprite5(texture);
		Sprite sprite6(texture);
		Sprite sprite7(texture);
		Sprite sprite8(texture);
		Sprite sprite9(texture);
		Sprite sprite10(texture);
		Sprite sprite11(texture);
		Sprite sprite12(texture);
		Sprite sprite13(texture);
		Sprite sprite14(texture);
		Sprite sprite15(texture);
		Sprite sprite16(texture);
		Sprite sprite0(texture);

		sprite0.move(5, 0);

		if (a == 1)
		{
			sprite1.move(105, 0);

			sprite1.setColor(Color(255, 255, 255, 15));
		}
		if (a == 2)
		{
			sprite2.move(105, 0);
			sprite2.setColor(Color(255, 255, 255, 30));
		}
		if (a == 3)
		{
			sprite3.move(105, 0);
			sprite3.setColor(Color(255, 255, 255, 45));
		}
		if (a == 4)
		{
			sprite4.move(105, 0);
			sprite4.setColor(Color(255, 255, 255, 60));
		}
		if (a == 5)
		{
			sprite5.move(105, 0);
			sprite5.setColor(Color(255, 255, 255, 75));
		}
		if (a == 6)
		{
			sprite6.move(105, 0);
			sprite6.setColor(Color(255, 255, 255, 90));
		}
		if (a == 7)
		{
			sprite7.move(105, 0);
			sprite7.setColor(Color(255, 255, 255, 105));
		}
		if (a == 8)
		{
			sprite8.move(105, 0);
			sprite8.setColor(Color(255, 255, 255, 120));
		}
		if (a == 9)
		{
			sprite9.move(105, 0);
			sprite9.setColor(Color(255, 255, 255, 135));
		}
		if (a == 10)
		{
		sprite10.move(105, 0);
		sprite10.setColor(Color(255, 255, 255, 150));
		}
		if (a == 11)
		{
		sprite11.move(105, 0);
		sprite11.setColor(Color(255, 255, 255, 165));
		}
		if (a == 12)
		{
		sprite12.move(105, 0);
		sprite12.setColor(Color(255, 255, 255, 180));
		}
		if (a == 13)
		{
		sprite13.move(105, 0);
		sprite13.setColor(Color(255, 255, 255, 195));
		}
		if (a == 14)
		{
		sprite14.move(105, 0);
		sprite14.setColor(Color(255, 255, 255, 210));
		}
		if (a == 15)
		{
		sprite15.move(105, 0);
		sprite15.setColor(Color(255, 255, 255, 225));
		}
		if (a == 16)
		{
		sprite16.move(105, 0);
		sprite16.setColor(Color(255, 255, 255, 240));
		}

		// ��������� ���� ��������	

		window.draw(sprite0);
		window.draw(sprite1);
		window.draw(sprite2);
		window.draw(sprite3);
		window.draw(sprite4);
		window.draw(sprite5);
		window.draw(sprite6);
		window.draw(sprite7);
		window.draw(sprite8);
		window.draw(sprite9);
		window.draw(sprite10);
		window.draw(sprite11);
		window.draw(sprite12);
		window.draw(sprite13);
		window.draw(sprite14);
		window.draw(sprite15);
		window.draw(sprite16);

		// ��������� ����
		window.display();
	}

	return 0;
}
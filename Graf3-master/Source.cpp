﻿#include <windows.h>
#include <glut.h>
#include <iostream>

float points[100][100];

const int window_side_size = 900;
const int view_side_size = 40;
const int period = 40;

struct color_t
{
    double r, g, b, a;
    void setThis() const
    {
        const color_t &color = *this;
        glColor4d(color.r, color.g, color.b, color.a);
    }
};

const color_t black = { 0, 0, 0, 1 };
const color_t blue = { 0, 0.1, 0.8, 1 };
const color_t green = { 0.5, 1.0, 0.0, 1 };
const color_t red = { 1, 0, 0, 1 };
const color_t orange = { 1, 0.5, 0.0, 1 };
const color_t grey = { 0.1, 0.1, 0.9, 0.9 };

void DrawFatPixel(int x, int y, color_t color = black)
{
    color.setThis();
    glBegin(GL_POLYGON);
    glVertex2d(x - 0.5, y - 0.5);
    glVertex2d(x - 0.5, y + 0.5);
    glVertex2d(x + 0.5, y + 0.5);
    glVertex2d(x + 0.5, y - 0.5);
    glEnd();
}

void DrawCell()
{
    glLineWidth(1);
    black.setThis();

    for (int i = -view_side_size; i <= view_side_size; ++i)
    {
        glBegin(GL_LINES);
        glVertex2f(i + 0.5f, -view_side_size + .0f);
        glVertex2f(i + 0.5f, view_side_size + .0f);
        glVertex2f(-view_side_size + .0f, i + 0.5f);
        glVertex2f(view_side_size + .0f, i + 0.5f);
        glEnd();
    }
}

void DrawAxes()
{
    glLineWidth(2);
    red.setThis();
    glBegin(GL_LINES);
    glVertex2i(-view_side_size, 0);
    glVertex2i(view_side_size, 0);
    glVertex2i(0, -view_side_size);
    glVertex2i(0, view_side_size);
    glEnd();
}

void DrawBrezenhemLine(int x1, int x2, int y1, int y2, color_t color = red)
{
    int error = 0, lasty = -100, x = x1, y = y1;
    int px = abs(x2 - x1);
    int py = abs(y2 - y1);
    int deltaerr = (px >= py) ? py : px;
    while (((x2 >= x1 && x <= x2) || (x2 < x1 && x >= x2)) && ((y2 >= y1 && y <= y2) || (y2 < y1 && y >= y2)))
    {
        for (int a = x + 50; a < 100; a++)
        {
            if (a > x + 50)
            {
                if (lasty == y)
                {
                    break;
                }
                if (x2 < x1 && y2 < y1 && y == y1)
                {
                    break;
                }
                if (points[a][y + 50] == 1) points[a][y + 50] = 0;
                else  points[a][y + 50] = 1;
            }
        }

        lasty = y;

        DrawFatPixel(x, y, color);
        error = error + deltaerr;
        if (px >= py)
        {
            if (2 * error >= deltaerr)
            {
                if (y2 < y1)
                {
                    y--;
                }
                else y++;
                error = error - px;
            }
            if (x2 > x1) x++;
            else if (x2<x1) x--;
        }
        else
        {
            if (2 * error >= deltaerr)
            {
                if (x2 > x1) x++;
                else if (x2 < x1) x--;
                error = error - py;
            }
            if (y2 > y1) y++;
            else if (y2 < y1) y--;
        }
    }
}

void DrawPolygon(const int tick)
{
    for (int y = 0; y < 100 && y < tick; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            if (points[x][y] == 1)
            {
                DrawFatPixel(x - 50, y - 50, green);
            }
            else
            {
                DrawFatPixel(x - 50, y - 50, grey);
            }
        }
    }
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int x1 = -10, y1 = -10,
        x2 = -10, y2 = 15,
        x3 = 10, y3 = 10,
        x4 = 30, y4 = 20,
        x5 = 30, y5 = 0,
        x6 = 14, y6 = -20;
    static int tick = 0;
    tick++;
    DrawBrezenhemLine(x1, x2, y1, y2);
    DrawBrezenhemLine(x2, x3, y2, y3);
    DrawBrezenhemLine(x3, x4, y3, y4);
    DrawBrezenhemLine(x4, x5, y4, y5);
    DrawBrezenhemLine(x5, x6, y5, y6);
    DrawBrezenhemLine(x6, x1, y6, y1 - 1);
    DrawPolygon(tick);
    DrawBrezenhemLine(x1, x2, y1, y2, red);
    DrawBrezenhemLine(x2, x3, y2, y3, red);
    DrawBrezenhemLine(x3, x4, y3, y4, red);
    DrawBrezenhemLine(x4, x5, y4, y5, red);
    DrawBrezenhemLine(x5, x6, y5, y6, red);
    DrawBrezenhemLine(x6, x1, y6, y1 - 1, red);
    DrawAxes();
    DrawCell();

    glFlush();
}

void timf(int value)
{
    glutPostRedisplay();
    glutTimerFunc(period, timf, 0);
}

void Initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-view_side_size, view_side_size, -view_side_size, view_side_size, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_side_size, window_side_size);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Labwork 3. Polygons");
    Initialize();
    glutDisplayFunc(Display);
    glutTimerFunc(period, timf, 0);
    glutMainLoop();
    return 0;
}

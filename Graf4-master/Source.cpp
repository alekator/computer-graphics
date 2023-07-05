#include <windows.h>
#include <glut.h>
#include <iostream>

using std::cin;
using std::cout;

const int window_side_size = 900;
const int view_side_size = 25;
const int period = 10;

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
const color_t grey = { 0.2, 0.2, 0.2, 0.5 };

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

void Initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-view_side_size, view_side_size, -view_side_size, view_side_size, -1.0, 1.0);
}

void DrawRegin(int x, int y, int tikcs)
{
    int bitmap[20][20] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 1, 1, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    int xs[100000], ys[100000];
    int i = 1, p = 0;

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (bitmap[i][j] == 1)
            {
                DrawFatPixel(10 - i, j - 10, red);
            }
        }
    }

    do
    {
        if (!bitmap[x][y])
        {
            bitmap[x][y] = 2;
            DrawFatPixel(10 - x, y - 10, orange);
        }
        else
        {
            x = xs[p];
            y = ys[p];
            p++;
            continue;
        }

        if (!bitmap[x][y - 1])
        {
            xs[i - 1] = x;
            ys[i - 1] = y - 1;
            i++;
        }
        if (!bitmap[x - 1][y])
        {
            xs[i - 1] = x - 1;
            ys[i - 1] = y;
            i++;
        }
        if (!bitmap[x + 1][y])
        {
            xs[i - 1] = x + 1;
            ys[i - 1] = y;
            i++;
        }
        if (!bitmap[x][y + 1])
        {
            xs[i - 1] = x;
            ys[i - 1] = y + 1;
            i++;
        }

        x = xs[p];
        y = ys[p];
        p++;
    } while (tikcs-- && p != i);
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int x = 6, y = 15;
    static int ticks = 0;
    ticks++;
    DrawRegin(x, y, ticks);
    DrawCell();
    DrawAxes();
    glFlush();
}

void OnTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(period, OnTimer, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_side_size, window_side_size);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Antonov AVT-041");
    Initialize();
    glutDisplayFunc(Draw);
    glutTimerFunc(period, OnTimer, 0);
    glutMainLoop();
    return 0;
}

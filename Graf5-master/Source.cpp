#include <windows.h>
#include <glut.h>

#define SLEEP 1500
#define PIXSIZE 15
#define S_WIDTH 1024
#define S_HEIGHT 768

const int minX = -10, maxX = 10, minY = -10, maxY = 10;

void Initialize()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glLineWidth(3.0);
}

float getX(int inp)
{
    if (inp > 0)
    {
        return 0.5 + (1.0 / S_WIDTH)*(inp*PIXSIZE);
    }
    else if (inp < 0)
    {
        inp *= (-1);
        if (inp > int(inp)) inp += 1.0;
        return  0.5 - (1.0 / S_WIDTH)*(inp*PIXSIZE);
    }
    else return 0.5;
}

float getY(float inp)
{
    if (inp >= 0)
    {
        return 0.5 + (1.0 / S_HEIGHT)*(int(inp)*PIXSIZE);
    }
    else if (inp < 0)
    {
        inp *= (-1);
        if (inp > int(inp)) inp += 1.0;
        return  0.5 - (1.0 / S_HEIGHT)*(int(inp)*PIXSIZE);
    }
    else return 0.5;
}

void draw_polygon(float px, float py)
{
    glBegin(GL_POLYGON);
    glVertex2d(getX(px), getY(py));
    glVertex2d(getX(px), getY(py + 1));
    glVertex2d(getX(px + 1), getY(py + 1));
    glVertex2d(getX(px + 1), getY(py));
    glEnd();
    glFlush();
}

void draw_coords()
{
    glLineWidth(3.0);
    for (int a = -50; a <= 50; a++)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2d(getX(-100), getY(a));
        glVertex2d(getX(100), getY(a));
        glVertex2d(getX(a), getY(-100));
        glVertex2d(getX(a), getY(100));
        glEnd();
        glFlush();
    }
    glLineWidth(1.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(getX(-100), getY(0));
    glVertex2d(getX(100), getY(0));
    glVertex2d(getX(0), getY(-100));
    glVertex2d(getX(0), getY(100));
    glEnd();
    glFlush();
    glLineWidth(3.0);
}

void drawBR(int x1, int x2, int y1, int y2, int par)
{
    int px, py, error, lasty = -100;
    int  x, y, deltaerr;
    x = x1;
    y = y1;
    px = abs(x2 - x1);
    py = abs(y2 - y1);
    error = 0;
    if (px >= py) deltaerr = py;
    else deltaerr = px;
    while (((x2 >= x1 && x <= x2) || (x2 < x1 && x >= x2)) && ((y2 >= y1 && y <= y2) || (y2 < y1 && y >= y2)))
    {
        if (par == 0) glColor3f(1.0, 0.0, 1.0);
        else
        {
            glColor3f(0.0, 1, 0.2);
            if (x >= minX && x < maxX && y >= minY && y < maxY)  glColor3f(0.0, 0.5, 1.0);
        }
        draw_polygon(x, y);
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

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_coords();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex2d(getX(minX), getY(minY));
    glVertex2d(getX(minX), getY(maxY));

    glVertex2d(getX(minX), getY(maxY));
    glVertex2d(getX(maxX), getY(maxY));

    glVertex2d(getX(maxX), getY(maxY));
    glVertex2d(getX(maxX), getY(minY));

    glVertex2d(getX(maxX), getY(minY));
    glVertex2d(getX(minX), getY(minY));

    glEnd();
    glFlush();

    int X2 = 20, Y1 = 5,
        X1 = -30, Y2 = -20;


    drawBR(X1, X2, Y1, Y2, 0);
    Sleep(SLEEP);
    drawBR(X1, X2, Y1, Y2, 1);
    X2 = -15, Y1 = 10,
    X1 = -30, Y2 = 2;
    drawBR(X1, X2, Y1, Y2, 1);
    X1 = -6; Y1 = -5;
    X2 = 6; Y2 = 5;
    drawBR(X1, X2, Y1, Y2, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(S_WIDTH, S_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Labwork 5. Intersection");
    Initialize();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}

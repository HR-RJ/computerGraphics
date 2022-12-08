// Compileren:
//
// Op MacOS:
// c++ -std=c++11 -o rastering -framework OpenGL -framework GLUT rastering.cpp
//
// Op Linux en Windows:
// g++ -std=c++11 -o rastering rastering.cpp -l GL -l glut

#include <list>

#define GL_SILENCE_DEPRECATION
// #include <GL/gl.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define GRID_SIZE 10

using namespace std;

class Point
{
public:
    int x, y;
    Point(int, int);
};

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

class Grid
{
    int sizeX, sizeY;
    list<Point> points;

public:
    Grid(int, int);
    void addPoint(int, int);
    void rasterline(int, int, int, int);
    void draw();
    void display();
};

Grid *currentInstance;

void display()
{
    currentInstance->display();
}

void end(unsigned char key, int x, int y)
{
    exit(0);
}

Grid::Grid(int x, int y)
{
    sizeX = x;
    sizeY = y;
}

void Grid::display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    for (auto &point : points)
    {
        glRecti(point.x * GRID_SIZE, point.y * GRID_SIZE, (point.x + 1) * GRID_SIZE, (point.y + 1) * GRID_SIZE);
    }
    glColor3f(.5, .5, .5);
    glBegin(GL_LINES);
    for (int i = 1; i < sizeX; i++)
    {
        glVertex2f(i * GRID_SIZE, 0);
        glVertex2f(i * GRID_SIZE, sizeY * GRID_SIZE);
    }
    for (int i = 1; i < sizeY; i++)
    {
        glVertex2f(0, i * GRID_SIZE);
        glVertex2f(sizeX * GRID_SIZE, i * GRID_SIZE);
    }
    glEnd();
    glFlush();
}

void Grid::draw()
{
    int argc = 0;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(sizeX * GRID_SIZE, sizeY * GRID_SIZE);
    glutCreateWindow("Raster");
    glOrtho(0, sizeX * GRID_SIZE, sizeY * GRID_SIZE, 0, -1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    currentInstance = this;
    glutDisplayFunc(::display); // Cannot use instance function here, so must use function in global namespace
    glutKeyboardFunc(end);
    glutMainLoop();
}

void Grid::addPoint(int x, int y)
{
    if (x < sizeX && y < sizeY && x >= 0 && y >= 0)
    {
        points.emplace_back(x, y);
    }
}

void Grid::rasterline(int x0, int y0, int x1, int y1)
{
    //calculates the delta x and y
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1; //calculates the steps on the x-axis
    int sy = (y0 < y1) ? 1 : -1; //calculatse the steps on the y-axis
    int err = dx - dy; //calculates the error in the line to find the closest pixel that the line passes through

    while (true) {
        addPoint(x0, y0);

        //stops drawing the line if the points are the same
        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;//if the line is closer to the current pixel error is decremented
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;//if the line is closer to the next pixel error is incremented
            y0 += sy;
        }
    }

    addPoint(x0, y0);
    addPoint(x1, y1);
}
int main()
{
    // testcode
    // let op: de beoordeling wordt gedaan op basis van andere waarden
    Grid grid(20, 20);
    grid.rasterline(0, 0, 19, 19);
    grid.rasterline(0, 10, 19, 0);
    grid.rasterline(0, 19, 19, 0);
    grid.rasterline(10, 0, 10, 19);
    grid.rasterline(0, 10, 19, 10);
    grid.draw();
    return 0; // never reached
}
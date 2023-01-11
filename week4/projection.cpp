// Compileren:
//
// Op MacOS:
// c++ -std=c++11 -o projection -framework OpenGL -framework GLUT projection.cpp
//
// Op Linux en Windows:
// g++ -std=c++11 -o projection projection.cpp -l GL -l glut

#include <list>

#define GL_SILENCE_DEPRECATION
// #include <GL/gl.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

using namespace std;

class Line {
    public:
        int x1, y1, x2, y2;
        Line(int, int, int, int);
};

Line::Line(int x1, int y1, int x2, int y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

class Lines {
    int sizeX, sizeY;
    list<Line> lines;
    public:
        Lines(int, int);
        void addLine(int, int, int, int);
        void draw();
        void display();
};

Lines *currentInstance;

void display() {
    currentInstance->display();
}

void end(unsigned char key, int x, int y) {
    exit(0);
}

Lines::Lines(int x, int y) {
    sizeX = x;
    sizeY = y;
}

void Lines::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    for (auto &line: lines) {
        glVertex2i(line.x1, line.y1);
        glVertex2i(line.x2, line.y2);
    }
    glEnd();
    glFlush();
}

void Lines::draw() {
    int argc = 0;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(sizeX, sizeY);
    glutCreateWindow("Lines");
    glOrtho(0, sizeX, sizeY, 0, -1, 1);
    currentInstance = this;
    glutDisplayFunc(::display); // Cannot use instance function here, so must use function in global namespace
    glutKeyboardFunc(end);
    glutMainLoop();
}

void Lines::addLine(int x1, int y1, int x2, int y2) {
        if (x1 < sizeX && y1 < sizeY && x1 >= 0 && y1 >= 0 && x2 < sizeX && y2 < sizeY && x2 >= 0 && y2 >= 0) {
        lines.emplace_back(x1, y1, x2, y2);
    }
}

int main() {
    // testcode!
    Lines lines(640, 480);
    lines.addLine(100, 100, 200, 100);
    lines.addLine(100, 200, 200, 200);
    lines.addLine(100, 100, 100 , 200);
    lines.addLine(200, 100, 200 , 200);
    // lines.addLine(100)
    // lines.addLine(100, 100, 500, 300);
    // for (int i = 100; i < 600; i += 50) {
    //     lines.addLine(100, 200, i, 400);
    // }
    lines.draw();
    return 0; // never reached
}
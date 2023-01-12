#include <GLUT/glut.h>

float angle = 0.0;
void display()
{
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the viewport and perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Rotate the cube
    glRotatef(angle, 1.0, 1.0, 1.0);
    angle += 0.1; // increment angle for the next frame

    // Set the color of the cube
    glColor3f(1.0, 0.0, 0.0);

    // Draw the cube
    glutSolidCube(3);

    // Swap the front and back buffers
    glutSwapBuffers();
}


void timer(int value)
{
    angle += 0.5; // increment angle
    glutPostRedisplay(); // request redraw
    glutTimerFunc(1000/60, timer, 0); // call timer function again after 60 frames per second
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set the window size and position
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);

    // Set the display mode to use a double-buffered window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create the window
    glutCreateWindow("Rotating Cube");

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Set the clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Set the display function
    glutDisplayFunc(display);

    // Set the timer function
    glutTimerFunc(1000/60, timer, 0);

    // Run the event loop
    glutMainLoop();

    return 0;
}

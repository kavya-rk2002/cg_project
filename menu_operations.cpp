#include<stdio.h>
#include <GL/glut.h>
#include<math.h>
#include<stdlib.h>

bool visible = true;
float angle = 0.0f;
float scale = 1.0f;
bool rotate_fast = false;
bool rotate_anticlockwise = false;
int current_shape = 1; // 1: Square, 2: Rectangle, 3: Triangle, 4: Circle
float color[3] = {1.0f, 0.0f, 0.0f}; // Initial color is red

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (visible) {
        glPushMatrix();
        glScalef(scale, scale, 1.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glColor3f(color[0], color[1], color[2]);

        switch (current_shape) {
        case 1: // Square
            glBegin(GL_QUADS);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.5f,  0.5f);
            glVertex2f(-0.5f,  0.5f);
            glEnd();
            break;
        case 2: // Rectangle
            glBegin(GL_QUADS);
            glVertex2f(-0.6f, -0.4f);
            glVertex2f( 0.6f, -0.4f);
            glVertex2f( 0.6f,  0.4f);
            glVertex2f(-0.6f,  0.4f);
            glEnd();
            break;
        case 3: // Triangle
            glBegin(GL_TRIANGLES);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.0f,  0.5f);
            glEnd();
            break;
        case 4: // Circle
            glBegin(GL_POLYGON);
            for (int i = 0; i < 360; i++) {
                float rad = i * 3.14159 / 180;
                glVertex2f(cos(rad) * 0.5, sin(rad) * 0.5);
            }
            glEnd();
            break;
        }
        glPopMatrix();
    }
    glutSwapBuffers();
}

void timer(int) {
    if (rotate_fast) {
        angle += (rotate_anticlockwise ? 2.0f : -2.0f);
    } else {
        angle += (rotate_anticlockwise ? 0.5f : -0.5f);
    }
    if (angle > 360.0f) angle -= 360.0f;
    if (angle < -360.0f) angle += 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        scale+=0.1f;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        scale-=0.1f;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        scale += 0.1f;
        break;
    case '-':
        scale -= 0.1f;
        break;
    case 'r':
        rotate_fast = !rotate_fast;
        break;
	case 'v':
		visible=!visible;
		break;
    }
    glutPostRedisplay();
}

void menu(int option) {
    switch (option) {
    case 1: color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f; break; // Red
    case 2: color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f; break; // Green
    case 3: color[0] = 1.0f; color[1] = 1.0f; color[2] = 0.0f; break; // Yellow
    case 4: current_shape = 1; break; // Square
    case 5: current_shape = 2; break; // Rectangle
    case 6: current_shape = 3; break; // Triangle
    case 7: current_shape = 4; break; // Circle
    case 8: rotate_anticlockwise = false; break; // Clockwise rotation
    case 9: rotate_anticlockwise = true; break; // Anticlockwise rotation
    case 10: scale += 0.1f; break; // Increase size
    case 11: scale -= 0.1f; break; // Decrease size
    }
    glutPostRedisplay();
}

void createMenu() {
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Yellow", 3);

    int shapeMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Square", 4);
    glutAddMenuEntry("Rectangle", 5);
    glutAddMenuEntry("Triangle", 6);
    glutAddMenuEntry("Circle", 7);

    int rotationMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Clockwise", 8);
    glutAddMenuEntry("Anticlockwise", 9);

    int sizeMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Increase", 10);
    glutAddMenuEntry("Decrease", 11);

    glutCreateMenu(menu);
    glutAddSubMenu("Color", colorMenu);
    glutAddSubMenu("Shape", shapeMenu);
    glutAddSubMenu("Rotation", rotationMenu);
    glutAddSubMenu("Size", sizeMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Menu Functions");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    createMenu();
    glutMainLoop();
    return 0;
}

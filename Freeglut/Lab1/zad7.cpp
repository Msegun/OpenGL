#include <iostream>
#include <GL/freeglut.h>
#include <time.h>

clock_t last_t = 0;
bool increase_alpha = false;
float alpha = 1.0;

void DrawingFunc(){
    glClear( GL_COLOR_BUFFER_BIT );

    if(increase_alpha)
        alpha += 0.005;
    else
        alpha -= 0.005;
    glBegin(GL_TRIANGLES);

    glColor4f(1,0,0, alpha );
    glVertex2f(-1.0, -1.0 );
    glColor4f(0,1,0, alpha );
    glVertex2f( 1.0, -1.0);
    glColor4f(0,0,1, alpha );
    glVertex2f(0, 1.0);
    glEnd();
    glutSwapBuffers();
}

//void Animation(int key){
//    if (alpha < 0){
//        increase_alpha = true;
//    }
//    if (alpha > 1){
//        increase_alpha = false;
//    }
//    glutPostRedisplay();
//    glutTimerFunc(10, Animation, 0);
//}

void Animation(){
    clock_t now_t = clock();
    long delta_t = now_t - last_t;
    if (delta_t > 3000){
        if (alpha < 0){
            increase_alpha = true;
        }
        if (alpha > 1){
            increase_alpha = false;
        }
        glutPostRedisplay();
        last_t = now_t;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    if (glutCreateWindow("Hello world!") < 1)
    {
        printf("glutCreateWindow() failed!\n");
        exit(1);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(DrawingFunc);
//    glutTimerFunc(10, Animation, 0);
    glutIdleFunc(Animation);

    glutMainLoop();

    return 0;
}




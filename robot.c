//opengl cross platform includes (final draft)
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <iostream>
#include <ctime>
using namespace std;

int main_id, moveMenu, turnMenu;
int size = 0; //Board dimensions will be size x size.
int pointx, pointy, updatex, updatey;
int headx, heady, updateHeadx, updateHeady;
int headPos; //1 = right
			 //2 = left
			 //3 = up
			 //4 = down.

/* creates the grid the robot moves along */
void createGrid(){

	glPointSize(1.0);
	glColor3f(0,0,0);

	glBegin(GL_POINTS);
	for (float i = 0; i <= size + 1; i+=0.01){
		for (float j = 0; j <= size + 1; j++){
			glVertex2f(i,j);
		}
	}
	for (float i = 0; i <= size + 1; i++){
		for (float j = 0; j <= size + 1; j+=0.01){
			glVertex2f(i,j);
		}
	}
	glEnd();
}

/* colours square to screen (robot head and body) */
void colourSquare(int x, int y, float r, float g, float b){
	glColor3ub(r, g, b);
	glPointSize(1.0);
	glBegin(GL_POINTS);
	for (float i = 0.03; i < 0.9799; i+=0.01){
			for (float j = 0.03; j < 0.98; j+=0.01){
					glVertex2f(x+i,y+j); 
			}
		}
	glEnd();
}

/* displays UI to user */
void display(void){
	glClearColor(1.0,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	createGrid();
	colourSquare(updatex, updatey, 0.0, 255.0, 0.0); 	    //Body, coloured green
	colourSquare(updateHeadx, updateHeady, 255.0, 0.0, 0.0);  //Head, coloured red
	glFlush();
}

/* rotates robot depending on input */
void rotateRobot(int rot){

	if(rot == 1){ //Turn right.
		if(headPos == 1){
			if(updatey == 0)
				printf("Invalid Input! Please try again.\n");
			else{
				updateHeadx--;
				updateHeady--;
				display();
				headPos = 4;
			}
		}
		else if(headPos == 2){
			if (updatey == size)
				printf("Invalid Input! Please try again.\n");
			else{
				updateHeadx++;
				updateHeady++;
				display();
				headPos = 3;
			}
		}
		else if(headPos == 3){
			if (updatex == size)
				printf("Invalid Input! Please try again.\n");
			else{
				updateHeadx++;
				updateHeady--;
				display();
				headPos = 1;
			}
		}
		else{
			if (updatex == 0)
				printf("Invalid Input! Please try again.\n");
			else{
				updateHeadx--;
				updateHeady++;
				display();
				headPos = 2;
			}
		}
	}
	else{
		if(headPos == 1){
			if(updatey == size)
				printf("Invalid Input! Please try again.\n");
			else{
				updateHeadx--;
				updateHeady++;
				display();
				headPos = 3;
			}
		}
		else if(headPos == 2){
			if (updatey == 0)
				printf("Invalid Input! Please try again.\n");
			else{
				updateHeadx++;
				updateHeady--;
				display();
				headPos = 4;
			}
		}
		else if(headPos == 3){
			if (updatex == 0)
				printf("Invalid Input! Please try again.\n");
			else{
				updateHeadx--;
				updateHeady--;
				display();
				headPos = 2;
			}
		}
		else{
			if (updatex == size)
				printf("Invalid Input! Please try again.\n");
			else{
				updateHeadx++;
				updateHeady++;
				display();
				headPos = 1;
			}
		}
	}
}

/* moves robot depending on input */
void moveRobot(int dir){
	
	if (dir == 1){
		if(headPos == 1){
			if(updateHeadx == size)
				printf("Invalid Input! Please try again.\n");
			else{
				updatex++;
				updateHeadx++;
				display();
			}
		}
		else{
			if(updatex == size)
				printf("Invalid Input! Please try again.\n");
			else{
				updatex++;
				updateHeadx++;
				display();
			}
		} 		//Move right.
	}
	else if (dir == 2){
		if(headPos == 2){
			if(updateHeadx == 0)
				printf("Invalid Input! Please try again.\n");
			else{
				updatex--;
				updateHeadx--;
				display();
			}
		}
		else{
			if(updatex == 0)
				printf("Invalid Input! Please try again.\n");
			else{
				updatex--;
				updateHeadx--;
				display();
			}
		}	//Move left.
	}
	else if (dir == 3){
		if(headPos == 3){
			if(updateHeady == size)
				printf("Invalid Input! Please try again.\n");
			else{
				updatey++;
				updateHeady++;
				display();
			}
		}
		else{
			if(updatey == size)
				printf("Invalid Input! Please try again.\n");
			else{
				updatey++;
				updateHeady++;
				display();
			}
		}	//Move up.
	}
	else{
		if(headPos == 4){
			if(updateHeady == 0)
				printf("Invalid Input! Please try again.\n");
			else{
				updatey--;
				updateHeady--;
				display();
			}
		}
		else{
			if(updatey == 0)
				printf("Invalid Input! Please try again.\n");
			else{
				updatey--;
				updateHeady--;
				display();
			}
		} //Move down.
	};
}

/* resets robot to original position */
void reset(){
	updatex = pointx;
	updatey = pointy;
	updateHeadx = headx;
	updateHeady = heady;
	headPos = 1;
	display();
	printf("Successfully reset!\n");
}

/* gives functionality to certain keyboard inputs */
void keyboard(unsigned char key, int xIn, int yIn){

	switch (key){
		case 'Q':
		case 'q':
		case 27:
			exit(0);
			break;
		case 'r':
		case 'R':
			reset();
			break;
	}
}

/* process that creates second sub menu */
void menuProc3(int value){

	rotateRobot(value);
}

/* process that creates first sub menu */
void menuProc2(int value){

	moveRobot(value);
}

/* process that creates main menu */
void menuProc(int value){

	//The main menu has no functionality other than containing sub menus. 
}

/* creates the main and sub menus */
void createMenu(){

	printf("\n          OPTIONS\n");
	printf("*******************************\n");
	printf("* Press 'r' to reset board.   *\n");
	printf("* Press 'q' to quit.          *\n");
	printf("*******************************\n");

	/* set up a submenu for moving, which will be contained in menuProc */
	moveMenu = glutCreateMenu(menuProc2);
	glutAddMenuEntry("Right",1);
	glutAddMenuEntry("Left",2);
	glutAddMenuEntry("Up",3);
	glutAddMenuEntry("Down",4);

	/* set up a submenu for turning, which will be contained in menuProc */
	turnMenu = glutCreateMenu(menuProc3);
	glutAddMenuEntry("Turn Right",1);
	glutAddMenuEntry("Turn Left",2);

	/* set up a simple menu, which will be handled by menuProc */
	main_id = glutCreateMenu(menuProc);
	glutAddSubMenu("Move", moveMenu);
	glutAddSubMenu("Turn", turnMenu);

	// attach the menu to the right button
	glutAttachMenu(GLUT_LEFT_BUTTON);
}

/* sets initial values for all values */
void setDefaults(){

	srand(time(NULL)); 	//Guarantee rand() to produce a succession of random numbers.
	pointx = rand() % (int)(size - 1);
	pointy = rand() % (int)(size - 1);
	headx = pointx + 1;
	heady = pointy;
	updatex = pointx; 
	updatey = pointy;
	updateHeadx = headx;
	updateHeady = heady;
	headPos = 1;
}

/* main function - program entry point */
int main(int argc, char** argv){
	
	while (size < 10 || size > 50){
		cout << "Please type in how many rows/columns you would like, between 10 and 50:" << endl;
		scanf("%d", &size);
	}

	setDefaults();
	glutInit(&argc, argv);		//starts up GLUT
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Robot");	//creates the window
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	gluOrtho2D(0, size + 1, 0, size + 1);
	createMenu();
	glutMainLoop();			//starts the event loop

	return(0);			//return may not be necessary on all compilers
}
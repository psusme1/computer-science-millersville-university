/********************************************************************************
*           CS375 Graphics & Virtual Reality OpenGL Sample Code    
*********************************************************************************
* 		Filename	    :	main.cpp
*		StudentName		:	Shawn Englerth
*		Website URL		:	http://home.dejazzd.com/psusme74/Graphics
*		written By		:   Roger Webster, Ph.D.
*						:   Department of Computer Science
*						:   D&E Communications Inc.Computer Science Wing
*						:   Caputo Hall 
*			            :   Millersville University
*      Class			:   CS375 Computer Graphics and Virtual Reality
*      Graphics Package	:   OpenGL
*    - Info can be found on Internet World Wide Web server (WWW) site:
*                      http://cs.millersville.edu/~webster/cs375/
*modifications:
09-27-2002 RWW added Camera.cpp class from www.gametutorial.com
09-27-2002 RWW added reshape callback instead of Windows stuff
10-03-2002 RWW added load 3ds stuff 
11-05-2002 RWW and Dan Hollinger testing 3ds load in the muopengl.lib
11-07-2002 RWW made some fixes
11-12-2002 RWW reversed the normals in muvli.lib
11-14-2002 RWW added Dan Hollinger's 3ds model stuff
11-15-2002 RWW added mouse to muopengl.lib
03-13-2003 RWW recompiled with new muopengl.lib
04-18-2003 RWW recompiled with new muopengl.lib with cross product fixed
09-08-2003 RDS added Display class stuff, recompiled w/ new muopengl.lib
01-21-2005 RDS converted to work with VS.NET 2003, recompiled w/ new muopengl.lib
******************************************************************************/

#include "muopengl.h"

LCamera muopengl_camera; //muopengl camera object
muopengl_info muopengl; // data structure that holds all muopengl info
MUopengl_MouseState ms;
Display display;

MUmovnode_collide Model1;  //Room
MUmovnode_collide Model2;  //Mug

bool  g_bLighting = true;	// Turn lighting on initially

float tilt = PI;
float g_RotateX	= 0.0f;							
float g_RotationSpeed = 0.8f;			
float light_pos[] = {0.0, -60.0, 0.0, 1.0};
float aspect_ratio;
float fps;
bool mugFlag = false; //used to toggle mug rotation on and off

int actual_screen_width;	//actual screen resolution
int actual_screen_height; //actual screen resolution
int font1, font2, font3, font4;


// most of this lights function from OpenGL PG 3rd ed. AW press Mason Woo,et.al.

void 
add_lights (void)
{

	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lmodel_ambient[] = {0.30, 0.30, 0.30, 1.0};
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);

	glClearColor (1.0,1.0,1.0,0.0);  	

	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glMatrixMode (GL_MODELVIEW); 
	glLoadIdentity ();
	glLightfv (GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv (GL_LIGHT0, GL_SPECULAR, white_light);
	glLightfv (GL_LIGHT0, GL_AMBIENT, lmodel_ambient);
	glEnable (GL_COLOR_MATERIAL);
}

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void 
myInit (void)
 {
	LVector4 pos, rot;
	glShadeModel (GL_SMOOTH);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_NORMALIZE);
	ms.SetMouseSensitivity (2.0);

	// Change current directory so textures can be stored in  
	// directory with the models and 3ds loader can find them
	SetCurrentDirectory ("models/");
		Model1.LoadObject ("myRoom.3ds");  //Load my room
		Model2.LoadObject ("myMug.3ds");   //Load my mug

	SetCurrentDirectory ("../");

	Model1.setPosition (0, 0, 0);
	Model2.setPosition (17.23, -16.0, -96.73735);
    Model1.Make_collidable ();
	Model2.Make_collidable ();
	
	glEnable (GL_CULL_FACE);     //RWW to increase fps performance
	glCullFace (GL_BACK);

	glClearColor (1.0,1.0,1.0,0.0);       // set white background color
    glColor3f (0.0f, 0.0f, 0.0f);          // set the drawing color 
 	glPointSize (1.0);		       // a ‘dot’ is 4 by 4 pixels

	add_lights ();
						      
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	rot.x = 0;
	rot.y = 0;
	rot.z = 0;

	muopengl_camera.SetPosition (pos);
	light_pos[X] = pos.x;
	light_pos[Y] = pos.y;
	light_pos[Z] = pos.z;

	Model1.SetDrawBoundary (!Model1.GetDrawBoundary());
	
	font1 = display.LoadFont ("Bookman",30,5,1);
	font2 = display.LoadFont ("Times");
	font3 = display.LoadFont ("Arial", 22);
	font4 = display.LoadFont ("Papyrus",30);
	display.ListLoadedFonts ();
	display.CreateTexture ("textures/mu.tga", 42);

}

//<<<<<<<<<<<<<<<<<<<<<<<< ACTION >>>>>>>>>>>>>>>>>
void 
action() 
{
	fps = muopengl_get_framerate ();
	LVector4 campos;
	LVector4 rotpos;
	
	ms.Check_MouseState (muopengl, &muopengl_camera);

	muopengl_camera.GetPosition (campos);
	light_pos[X] = campos.x;
	light_pos[Y] = campos.y;
	light_pos[Z] = campos.z;
	glLightfv (GL_LIGHT0, GL_POSITION, light_pos);\
	
	if (mugFlag)
	{
		Model2.Yaw (120 / fps);
	}
	
	glutPostRedisplay ();
}
	
void 
draw_window_items()
{
	LVector4 camPos, camRot;
	char mystring[100];
	//disable lighting and depth test for drawing text, etc. on the screen
	glDisable (GL_LIGHTING);
	glDisable (GL_DEPTH_TEST);
	glLoadIdentity ();

	glColor3f (0.7 ,0.0, 0.0);
	display.DrawBox (0.35, 0.019, 0.65, 0.065);
	glColor3f (0, 0, 0);
	display.DrawBox (0.35, 0.019, 0.65, 0.065, 2);

	//current position printed in upper left of screen
	//muopengl_camera.GetPosition (camPos);
    //sprintf (mystring, "Current Position, x = %f, y = %f, z = %f", camPos.x, camPos.y, camPos.z);
	//display.DrawText (0.03, 0.15, 1, mystring);

	//current rotation printed in upper left of screen
	//muopengl_camera.GetRotation (camRot);
	//sprintf (mystring, "Current Rotation, x = %f, y = %f, z = %f", camRot.x, camRot.y, camRot.z);
	//display.DrawText (0.03, 0.20, 1, mystring);
	
	//glColor3f (0,0.7,0.2);
	//display.DrawArc (0.5, 0.75, 0.05, tilt);
	//glColor3f (1,0,0);
	//display.DrawCircle (0.5, 0.75, 0.05, 2);

	//glColor3f (0,0,0);
	//display.DrawText (0.5, 0.85, 0, "Left and right arrow keys tilt arc");

	sprintf (mystring, "Shawn Englerth");
	glColor3f (1, 0, 0);
	display.SetFont (font2);
	display.DrawText (0.5, 0.05, 0, mystring);

	glEnable (GL_BLEND);
	glColor4f (0.2 ,0, 1, 0.3);
	display.DrawCircle (0.9, 0.895, 0.05); 
	glDisable (GL_BLEND);

	glColor3f (0, 0, 0.3);
	display.DrawCircle (0.9, 0.895, 0.05, 4);

	
	sprintf (mystring, "%d FPS", (int)fps);
	display.SetFont (font3);
	glColor3f (0, 0, 0);
	display.DrawText (0.902, 0.902, 0, mystring);
	glColor3f (0, 1, 0.4);
	display.DrawText (0.9, 0.9, 0, mystring);

	sprintf (mystring, "Use Mouse To Navigate");
	display.SetFont (font4);
	glColor3f (0, 0, 1);
	display.DrawTextVertical (0.97, 0.1, mystring);

	//display.SetFont (font2);
	//sprintf (mystring, "Movements: f = (Forward), b = (Backward)");
	//display.DrawText (0.03, 0.1, 1, mystring);

	display.DrawTexture (0.01, 0.89 , 0.2, 0.95, 42);

	// reenable that what you disabled
	glEnable (GL_LIGHTING);
	glEnable (GL_DEPTH_TEST);

	glutSwapBuffers (); 
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void 
myDisplay (void)
{
	LMatrix4 m_matrix;
	LVector4 mypos;

	glMatrixMode (GL_MODELVIEW);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	muopengl_camera.Render ();

	Model1.Render ();
	Model2.Render ();
	
	draw_window_items ();

}

void 
myspecialkybd (int theKey, int mouseX, int mouseY)
{
		GLint x = mouseX;
		GLint y = mouseY;
		

		
		switch (theKey)
		{		 
			  case GLUT_KEY_UP: 
                  ms.SetMouseSensitivity(ms.GetMouseSensitivity() + 0.10);
                  
				  if (ms.GetMouseSensitivity () >= 2.0)
					ms.SetMouseSensitivity (2.0);
				  
				  break;
			  
			  case GLUT_KEY_DOWN:
				  ms.SetMouseSensitivity (ms.GetMouseSensitivity () - 0.10);
				  
				  if (ms.GetMouseSensitivity () <= 0.20)
					ms.SetMouseSensitivity (0.20);
				
				  break;

			  case GLUT_KEY_LEFT:
					tilt += PI / 90;
					//muopengl_camera.MoveX(-1.0);
					break;
			  
			  case GLUT_KEY_RIGHT: 
					tilt -= PI/90;
					//muopengl_camera.MoveX(1.0);
					break;
			  
			  case GLUT_KEY_F1: 
						g_RotationSpeed++;
					break;
			  
			  case GLUT_KEY_F2: 
						g_RotationSpeed--;
					break;
			  
			  case GLUT_KEY_F3: 
						muopengl_camera.MoveY(1.0);
					break;
			
			  case GLUT_KEY_F4: 
						muopengl_camera.MoveY(-1.0);
						break;
	  		
			  default: 
						//printf ("key hit is %d\n", theKey);
	
						break;  // do nothing
		}
}

void myKeyboard (unsigned char theKey, int mouseX, int mouseY)
{
		GLint x = mouseX;
		GLint y = mouseY; 
		//printf ("key hit is %c\n", theKey);
		if ((int)theKey == 27)
			exit (-1);	
		switch (theKey)
		{		 			

		case '1':  //In bed
			muopengl_camera.SetPosition (LVector4 (11.028, -7.786, 109.141));
			muopengl_camera.SetRotation (LVector4 (0, 360, 0));
			break;

		case '2':  //VF-2 Poster
			muopengl_camera.SetPosition (LVector4 (31.953, 17.679, 53.764));
			muopengl_camera.SetRotation (LVector4 (0, 270, 360));
			break;

		case '3':  //Looking in from doorway
			muopengl_camera.SetPosition (LVector4 (78.89, -1.2177, -67.983));
			muopengl_camera.SetRotation (LVector4 (0, 90, 0));
			break;

		case '4':  //Sitting at PC
			muopengl_camera.SetPosition (LVector4 (-34.948, -14.3211, -54.277));
			muopengl_camera.SetRotation (LVector4 (180, 67.93, 180));
			break;

		case '5':  //Looking at TV
			muopengl_camera.SetPosition (LVector4 (9.907, -11.162, -0.475));
			muopengl_camera.SetRotation (LVector4 (0, 270.265, 360));
			break;

		case '6':  //Looking to the rear room
			muopengl_camera.SetPosition (LVector4 (2.1849, -2.9900, -101.7471));
			muopengl_camera.SetRotation (LVector4 (180, 356.9067, 180));
			break;

		case '7':  //Looking at mug
			muopengl_camera.SetPosition (LVector4 (15.9783, -2.7013, -50.0502));
			muopengl_camera.SetRotation (LVector4 (0, .188385, 360));
			break;

		case 'c':
			mugFlag = !mugFlag;
			break;

		case 'r':
			muopengl_camera.SetPosition (LVector4 (0, 0, 0));
			muopengl_camera.SetRotation (LVector4 (0, 0, 0));			
			break;
		
		case 'q':
			exit(-1);		//terminate the program		
	  		
		default: 
			break;		      // do nothing
		}
}

void passiveMouseMove(int x, int y) { 
  ms.x = x; ms.y = y;
}

void activeMouseMove(int x, int y) { 
  ms.x = x; ms.y = y;
}


void mouse(int button, int state, int x, int y) {
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  switch(button) {
  case GLUT_LEFT_BUTTON:
    switch(state) {
    case GLUT_UP:
      ms.btnOne = MUopengl_MouseState::UP;
      break;
    case GLUT_DOWN:
      ms.btnOne = MUopengl_MouseState::DOWN;
      break;
    }
    break;
  case GLUT_MIDDLE_BUTTON:
    switch(state) {
    case GLUT_UP:
      ms.btnTwo = MUopengl_MouseState::UP;
      break;
    case GLUT_DOWN:
      ms.btnTwo = MUopengl_MouseState::DOWN;
      break;
    }
    break;
  case GLUT_RIGHT_BUTTON:
    switch(state) {
    case GLUT_UP:
      ms.btnThree = MUopengl_MouseState::UP;
      break;
    case GLUT_DOWN:
      ms.btnThree = MUopengl_MouseState::DOWN;
      break;
    }
    break;
  }
  if (state==GLUT_DOWN) action();
}

/* Tell GLUT what to do if the window is reshaped: */
void reshape(int width, int height) 
{
	actual_screen_width = width;
	actual_screen_height = height;
	aspect_ratio = actual_screen_width/actual_screen_height;	
	glViewport(0, 0, (GLsizei) width, (GLsizei) height); 
    muopengl_init(&muopengl, width, height);
	muopengl_camera.Initialize(75.0, aspect_ratio, 0.1, 850);
	printf ("Actual Window width is %d height is %d \n", width, height);
	display.Initialize(width, height);
}


int main(int argc, char** argv)
{	
	glutInit(&argc, argv);          // initialize the GLUT toolkit
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Roger's 3D OPENGL Double Buffering Test"); // open the screen window
	glutDisplayFunc(myDisplay);     // setup the draw function callback
	glutMotionFunc(activeMouseMove);
	glutIdleFunc(action);
	glutPassiveMotionFunc(passiveMouseMove);
	glutMouseFunc(mouse); 
	glutSpecialFunc(myspecialkybd);			//setup the esc f1 keys
	glutKeyboardFunc(myKeyboard);	//setup the keyboard callback
	glutReshapeFunc(reshape); 
	glutFullScreen();
	myInit();                   
	glutMainLoop(); 		     // go into a infinite event loop
	return 0;
}


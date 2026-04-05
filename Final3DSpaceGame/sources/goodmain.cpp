/********************************************************************************
*           CS375 Graphics & Virtual Reality OpenGL Sample Code    
********************************************************************************
* 		Filename	    :	md3demo.cpp
*		written By	    :   Roger Webster, Ph.D.
*                      :    Department of Computer Science
*                      :    D&E Communications Inc.Computer Science Wing
*                      :    Caputo Hall 
*			            :   Millersville University
*      Class           :   CS375 Computer Graphics and Virtual Reality
*      Graphics Package:   OpenGL
*    - Info can be found on Internet World Wide Web server (WWW) site:
*                      http://cs.millersville.edu/~webster/cs375/
*modifications:
10-01-2003 rww made this demo
01-31-2005 rds converted to .net
03-29-2005 RWW added supprt in muopengltoolkit for MD3 animation files
******************************************************************************/
#pragma comment (lib, "glaux.lib")

#include <ctime>
#include <vector>
#include "muopengl.h"
#include "fmod.h"
#include "path.h"

void loadModels ();
void JoyFunc (unsigned int button, int leftRight, int upDown, int throttle);
void keepMoving (int leftRight, int upDown);
void loadLevel1 ();
void loadLevel2 ();
void initializeLevel ();
int RetrieveObjectID ();
void mouseMove ();

float cameraXrot = 0;
LVector4 campos;
LVector4 camrot;
LVector4 prevPos;
LVector4 currPos;
float deltaZ;
float deltaX;
int BEGIN_ITER = 0;
int END_ITER = 10;

MyPath A ("path1.txt");
MyPath B ("path2.txt");
MyPath C ("path3.txt");
MyPath D ("path4.txt");
MyPath E ("path5.txt");
MyPath F ("path6.txt");
MyPath G ("path7.txt");
MyPath H ("path8.txt");
MyPath I ("path9.txt");
MyPath J ("path10.txt");

bool playing = false;
bool shooting = false;

bool PATH1 = false;
bool PATH2 = false;
bool PATH3 = false;
bool PATH4 = false;
bool PATH5 = false;
bool PATH6 = false;
bool PATH7 = false;
bool PATH8 = false;
bool PATH9 = false;
bool PATH10 = false;
bool PAUSE = false;
bool moveDown = true;
bool moveUp = false;
bool boolaction = true;
bool printPointsEarned = false;

int level = 1;
int counter = 0;
int dispObjNum = 0;
int picked;
int foundObj = 0;
int objectsFound = 0;

MUmovnode_collide City;
MUmovnode_collide World;
MUmovnode_collide Earth;
MUmovnode_collide bluePinkBot;

const int MAXENEMY = 20;
MUmovnode_collide enemyArr [MAXENEMY];
vector <bool> activeArr (MAXENEMY, false); 
vector <bool> killed (MAXENEMY, false);
vector <int> enemyHealth (MAXENEMY, 10); 
vector <int> pointValue (MAXENEMY, 100);
vector <int> myDamageCaused (MAXENEMY, 5);
int score = 0;
int scorePrint;

const int MAXNAMES = 20;
CModelMD3 models [MAXNAMES];
LPSTR MODEL_NAMES [MAXNAMES];
LPSTR MODEL_PATH [MAXNAMES];
LPSTR GUN_NAME [MAXNAMES];

float fps;
float frameSpeed = 0; 
int frame = 0;
int framesToLive = 0;
int multiplier = 1;
float kSpeed = .020;


//JOYSTICK DECLARATIONS
int joystick_x;
int joystick_y;
int joystick_z;
int deadrange = 100;
bool joystick_buttonA = false;
bool joystick_buttonB = false;
bool joystick_buttonC = false;
bool joystick_buttonD = false;

int font1;
int font2;
int font3;
int font4;
int font5;

int pathNum = 0;
int total_num_textures = 0;

MUopengl_MouseState ms;
Display display;
LCamera muopengl_camera; 
muopengl_info muopengl;
GLdouble aspect_ratio;
GLfloat light_pos[] = {0.0, 60.0, -80.0, 1.0};
int actual_screen_width;
int actual_screen_height;
UINT g_Texture[MAX_TEXTURES] = {0};
LTGA crosshair;
Tga_anim explode;
unsigned char *tga_pixels;
float tilt = PI;




//=============================================================================
void 
add_lights (void)
{
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {50.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat lmodel_ambient[] = {0.30, 0.30, 0.30, 1.0};
  glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
  glClearColor (1.0, 1.0, 1.0, 0.0);  	
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




//==============================================================================
//JOYSTICK FUNCTION
//==============================================================================
void 
JoyFunc(unsigned int button, int leftRight, int upDown, int throttle)
{	 
  joystick_buttonA = false;
	joystick_buttonB = false;
	joystick_buttonC = false;
	joystick_buttonD = false;
  
  //BUTTON A PRESSED (#1 BUTTON OR 'TRIANGLE' ON GAMEPAD)
  if (button == GLUT_JOYSTICK_BUTTON_A)
  {
    joystick_buttonA = true;
  }

  //BUTTON B PRESSED (#2 BUTTON OR 'CIRCLE' ON GAMEPAD)
  else if (button == GLUT_JOYSTICK_BUTTON_B)
  {
    joystick_buttonB = true;
    LVector4 currentRotation;
    muopengl_camera.GetRotation (currentRotation);

    //if (currentRotation.x % 180)180
    muopengl_camera.SetRotation (LVector4 (0.0, currentRotation.y, 0.0));
  }

  //BUTTON C PRESSED (#3 BUTTON OR 'X' ON GAMEPAD)
  else if (button == GLUT_JOYSTICK_BUTTON_C)
  {
    joystick_buttonC = true;
    shooting = true;
  }
  
  //BUTTON D PRESSED (#4 BUTTON OR 'SQUARE' ON GAMEPAD)
  else if (button == GLUT_JOYSTICK_BUTTON_D)
  {
    joystick_buttonD = true;
  }

  keepMoving (leftRight, upDown);

  joystick_x = leftRight;
	joystick_y = upDown;
	joystick_z = throttle;
}



//==============================================================================
//ALLOW THE ACTION TO CONTINUE MOVING WHEN A BUTTON IS PRESSED
//==============================================================================
void
keepMoving (int leftRight, int upDown)
{
  
  if (abs(leftRight) > abs(upDown))
  {
   //MOVE X DIRECTION IF JOYSTICK IS OUTSIDE OF X DEADRANGE
   if (leftRight > deadrange)
   {
     muopengl_camera.RotateY ((frameSpeed * (-(float)leftRight / 800)));
	 } 
   else if (leftRight < -deadrange)  
   {
	   muopengl_camera.RotateY ((frameSpeed * (-(float)leftRight / 800)));
	 }
  }
  else
  {
   //MOVE Y DIRECTION IF JOYSTICK IS OUTSIDE OF Y DEADRANGE
   if (upDown > deadrange)
   {
     muopengl_camera.Pitch ((frameSpeed * (-(float)upDown / 800)));
   } 
   else if (upDown < -deadrange)  
   {
	   muopengl_camera.Pitch ((frameSpeed * (-(float)upDown / 800)));
	 }
  }
}



//=============================================================================
void 
myInit (void)
{
  glColor3f (0.0f, 0.0f, 0.0f);          // set the drawing color 
 	glPointSize (1.0);		       // a ‘dot’ is 4 by 4 pixels
	add_lights ();

  //loadModels ();

  printf ("SetCurrentDirectory to Images\n");
  SetCurrentDirectory ("Images/");

  printf ("Loading Objects\n");
	City.LoadObject ("tooncity48.3DS");
	City.Make_collidable ();
  World.LoadObject ("world.3ds");
  World.Make_collidable ();
  Earth.LoadObject ("earth.3ds");
  Earth.Make_collidable ();
    
  crosshair.LoadFromFile ("crosshairs.tga");
  crosshair.createKeyedMask (0, 0, 0);

  explode.load_tga_files ("image", 11);

  for (int i = 0; i < MAXENEMY; i++)
  {
    if (i % 10 == 0 || i % 10 == 9 || i % 10 == 5)
      enemyArr[i].LoadObject ("bluepinkbot.3ds");
    else if (i % 10 == 2 || i % 10 == 4)
      enemyArr[i].LoadObject ("redyellowbot.3ds");
    else if (i % 10 == 1 || i % 10 == 7)
      enemyArr[i].LoadObject ("greenredbot.3ds");
    else if (i % 10 == 3)
      enemyArr[i].LoadObject ("bluebucktooth.3ds");
    else if (i % 10 == 6)
      enemyArr[i].LoadObject ("redbucktooth.3ds");
    else if (i % 10 == 8)
      enemyArr[i].LoadObject ("greenbucktooth.3ds");
  }

  City.Make_collidable ();
  City.setPosition (0, .1, 0);
  World.setPosition (0, 0, 0);
  Earth.setPosition (0, 0, 0);

  muopengl_camera.SetPosition (LVector4 (-2611, 30, 797));
	muopengl_camera.SetRotation (LVector4 (0, 270, 0));
   
  font1 = display.LoadFont ("Arial", 28);
	font2 = display.LoadFont ("Arial", 26);
	font3 = display.LoadFont ("Arial", 22);
  font4 = display.LoadFont ("Arial", 32);
  font5 = display.LoadFont ("Arial", 42);
	display.ListLoadedFonts ();

	glShadeModel (GL_SMOOTH);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_NORMALIZE);
  glutSetCursor (GLUT_CURSOR_NONE);
  glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glEnable (GL_BLEND);
  
  //
  //FSOUND_Init (44100, 32, 0);
	//explosion = FSOUND_Sample_Load (1, "shotgun.wav", FSOUND_NORMAL, 0);
	//ak47 = FSOUND_Sample_Load (2, "ak47.wav", FSOUND_NORMAL, 0);
  
  SetCurrentDirectory ("../");
  PATH1 = true;
  glutJoystickFunc (JoyFunc, 0);
}



void
renderEnemyFunc ()
{
  for (int myIterator = BEGIN_ITER; myIterator < END_ITER; myIterator++)
  {
    LVector4 enemyPosition;
    enemyArr[myIterator].GetPosition (enemyPosition);

    if ((muopengl_euclidean_dist (campos, enemyPosition) > 235))
    {
      enemyArr[myIterator].SetRenderEnable (false);
      activeArr[myIterator] = false;
    }
    else if ((muopengl_euclidean_dist (campos, enemyPosition) > 50)  && (!killed[myIterator]))
    {
      enemyArr[myIterator].SetRenderEnable (true);
      activeArr[myIterator] = true;
    }
    else
    {
      enemyArr[myIterator].SetRenderEnable (false);
      activeArr[myIterator] = false;
      killed[myIterator] = true;
    }
  } 
}


void
moveActiveEnemy ()
{
  LVector4 enemyPosition, enemyRotation;

  for (int myIterator = BEGIN_ITER; myIterator <END_ITER; myIterator++)
  {
    muopengl_camera.GetRotation (camrot);
    muopengl_camera.GetPosition (campos);
    enemyArr[myIterator].GetPosition (enemyPosition);

    if (enemyArr[myIterator].active = true && myIterator % 10 != 3 
      && myIterator % 10 != 6 && myIterator % 10 != 8)
    {
      if (enemyPosition.y > 50.0)
      {
        moveDown = true;
        moveUp = false;
      }

      if (enemyPosition.y < 4.0)
      {
        moveDown = false;
        moveUp = true;
      }

      if (moveDown)
      {
        enemyPosition.y -= 1;
        enemyRotation.y -= .75;
      }

      if (moveUp) 
      {
        enemyPosition.y += 1;
        enemyRotation.y += .75;
      }
      enemyArr[myIterator].SetPosition (enemyPosition);
      enemyArr[myIterator].SetRotation (enemyRotation);
    }
    else if (enemyArr[myIterator].active = true && (myIterator % 10 == 3 
      || myIterator % 10 == 6 || myIterator % 10 == 8))
    {
      float euclidDistance = muopengl_euclidean_dist (campos, enemyPosition);
      float deltaXCamEnemy = campos.x - enemyPosition.x;
      float deltaZCamEnemy = campos.z - enemyPosition.z;

      enemyPosition.x += (deltaXCamEnemy / euclidDistance);
      enemyPosition.z += (deltaZCamEnemy / euclidDistance);


      enemyRotation.y = (360 - camrot.y);
      
      enemyRotation.x = (camrot.x + 180);
      if (camrot.x == 360)
        enemyRotation.x = 0;
      
      enemyRotation.z = (camrot.z + 180);
      if (camrot.z == 360)
        enemyRotation.z = 0;

      enemyArr[myIterator].SetPosition (enemyPosition);
      enemyArr[myIterator].SetRotation (enemyRotation);
      enemyArr[myIterator].Apply ();

      enemyArr[myIterator].Yaw (-90);

    }
  }
}


void
shootingFunc ()
{
  picked = RetrieveObjectID ();
  dispObjNum = picked;
  picked -= 100;
  shooting = false;
  LVector4 target;

  if (picked >= BEGIN_ITER && picked < END_ITER)
    if (activeArr[picked]) 
    {
      enemyHealth[picked] -= 10;
      if (!enemyHealth[picked])
      {
        score += pointValue[picked];
        enemyArr[picked].GetPosition (target);
        explode.set_size (128, 128);
        explode.set_position (target);
        explode.start ();
        enemyArr[picked].SetRenderEnable (false);
        activeArr[picked] = false;
        killed[picked] = true;
        scorePrint = picked;
        frame = 0;
        printPointsEarned = true;
      }
    }
}

void
calculateRateOfChange ()
{
  //CALCULATES THE CHANGE IN POSITION OF THE CAMERA FROM THE PREV FRAME TO THE CURR FRAME
  deltaZ = (campos.z - prevPos.z);
  deltaX = (campos.x - prevPos.x);
}


void
pauseFunc ()
{
  if (campos.y > 400)
    campos.y = prevPos.y;
  if (campos.y < 3.8)
    campos.y = prevPos.y;

  muopengl_camera.SetPosition (campos);
  muopengl_camera.SetRotation (camrot);
  PAUSE = false;
}
    
      
//=============================================================================
//
//ACTION ACTION ACTION ACTION ACTION ACTION ACTION ACTION
//
//=============================================================================
void 
action () 
{
  mouseMove ();
  if (boolaction)
  {
    muopengl_camera.GetPosition (prevPos);
    glutForceJoystickFunc ();
    World.RotateZ (.04);

    ms.Check_MouseState (muopengl, &muopengl_camera);
    muopengl_camera.Apply ();

    muopengl_camera.GetRotation (camrot);
    muopengl_camera.GetPosition (campos);
   
    
    if (PATH1)
    {
      if (counter == 0)
      {
        A.readPath ();
        loadLevel1 ();
      }
    
      A.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == A.getPathSize () - 1)
      {
        PATH1 = false;
        PATH2 = true;
        PAUSE = true;
        counter = 0;
      }
    }


    if (PATH2 && !PAUSE)
    {
      if (counter == 0)
      {
        B.readPath ();
        loadLevel2 ();
       
      }

      mouseMove ();
      B.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (B.getPathSize () - 1))
      { 
        PATH2 = false;
        //PATH3 = true;
        PAUSE = true;
        counter = 0;
      }
    }

    if (PATH3 && !PAUSE)
    {
      if (counter == 0)
        C.readPath ();
     
      C.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (C.getPathSize () - 1))
      { 
        PATH3 = false;
        PATH4 = true;
        PAUSE = true;
        counter = 0;
      }
    }

    if (PATH4 && !PAUSE)
    {
      if (counter == 0)
        D.readPath ();

      D.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (D.getPathSize () - 1))
      { 
        PATH4 = false;
        PATH5 = true;
        PAUSE = true;
        counter = 0;
      }
    }

    if (PATH5 && !PAUSE)
    {
      if (counter == 0)
        E.readPath ();

      E.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (E.getPathSize () - 1))
      { 
        PATH5 = false;
        PATH6 = true;
        PAUSE = true;
        counter = 0;
      }
    }

    if (PATH6 && !PAUSE)
    {
      if (counter == 0)
        F.readPath ();

      F.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (F.getPathSize () - 1))
      { 
        PATH6 = false;
        PATH7 = true;
        PAUSE = true;
        counter = 0;
      }
    }

    if (PATH7 && !PAUSE)
    {
      if (counter == 0)
        G.readPath ();

      G.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (G.getPathSize () - 1))
      { 
        PATH7 = false;
        PATH8 = true;
        PAUSE = true;
        counter = 0;
      }
    }


    if (PATH8 && !PAUSE)
    {
      if (counter == 0)
        H.readPath ();

      H.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (H.getPathSize () - 1))
      { 
        PATH8 = false;
        PATH9 = true;
        PAUSE = true;
        counter = 0;
      }
    }


    if (PATH9 && !PAUSE)
    {
      if (counter == 0)
        I.readPath ();

      I.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (I.getPathSize () - 1))
      { 
        PATH9 = false;
        PATH10 = true;
        PAUSE = true;
        counter = 0;
      }
    }   

    if (PATH10 && !PAUSE)
    {
      if (counter == 0)
        J.readPath ();

      J.getPosRot (campos);
      muopengl_camera.SetPosition (campos);
      counter++;
      if (counter == (J.getPathSize () - 1))
      { 
        PATH10 = false;
        PAUSE = true;
        counter = 0;
      }
    }

    if (PAUSE)
      pauseFunc ();

    renderEnemyFunc ();
    calculateRateOfChange ();

    if (shooting == true)
      shootingFunc ();

    moveActiveEnemy ();

    light_pos[X] = campos.x;
    light_pos[Y] = campos.y + 20;
    light_pos[Z] = campos.z;
    glLightfv (GL_LIGHT0, GL_POSITION, light_pos);

    //muopengl_camera.SetRotation (camrot);
    muopengl_camera.GetRotation (camrot);
    muopengl_camera.GetPosition (campos);
    frame++;
       
   glutPostRedisplay ();
  }
}



//
void 
draw_window_items ()
{
  LVector4 campos, camrot;
  char mystring[100];
  float y = 0.10;

  crosshair.drawFullScreenImage();

  fps = muopengl_get_framerate ();
  framesToLive = fps * multiplier; //MULTIPLIER IS A POSITIVE INTEGER; USED FOR DISPLAYING POINTS ON SCREEN
  frameSpeed = fps * kSpeed;

  glDisable (GL_LIGHTING);
  glDisable (GL_DEPTH_TEST);
  glLoadIdentity ();

  glColor3f (1, 1, 0);

  sprintf (mystring, "%d fps", (int)fps);
  display.SetFont (font3);
  display.DrawText (0.902, 0.902, 0, mystring);

  muopengl_camera.GetPosition (campos);
  sprintf (mystring, "x %f y %f z %f", campos.x, campos.y, campos.z);
  display.DrawText (0.04, y, 1, mystring);
  y = y + 0.03;

	muopengl_camera.GetRotation (camrot);
	sprintf (mystring, "rotation: x %f y %f z%f", camrot.x, camrot.y, camrot.z);
	display.DrawText (0.04, y, 1, mystring);
	y = y + 0.03;
	
  sprintf (mystring, "SCORE: %d", score);
  display.DrawText (0.04, y, 1, mystring);
	y = y + 0.03;

  sprintf (mystring, "Object Picked: %i", dispObjNum);
	display.DrawText (0.04, y, 1, mystring);
	y = y + 0.03;

  
  if (printPointsEarned)
  {
    glColor3f (1, 0, 0);
    sprintf (mystring, "%d POINTS", pointValue[scorePrint]);
    display.SetFont (font5);
	  display.DrawText (0.40, 0.45, 1, mystring);
    if ((frame % framesToLive) == 0)
      printPointsEarned = false;
  }
  
  glEnable (GL_LIGHTING);
	glEnable (GL_DEPTH_TEST);

	glutSwapBuffers (); 
}



//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void 
myDisplay (void)
{
  glMatrixMode (GL_MODELVIEW);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
  muopengl_camera.Render ();
	

  glInitNames();									
	glPushName(0);
	
	glLoadName (99);
  City.Render ();
	glEnd ();
  
  for (int myIterator = BEGIN_ITER; myIterator <END_ITER; myIterator++)
	{
    glLoadName (100 + myIterator);
	  enemyArr[myIterator].Render ();
    glEnd ();
	}
	
  glPopName ();
  
  Earth.Render ();
  World.Render ();
  explode.update (&muopengl_camera); 

  //models [0].DrawModel ();						
	//models [1].DrawModel ();
  //models [2].DrawModel ();
	
  draw_window_items ();
}



//==============================================================================
//PICK THE OBJECT THAT WE WANT TO SHOOT
//==============================================================================
int 
RetrieveObjectID ()
{
  float x = actual_screen_width / 2;
  float y = actual_screen_height / 2;
  
  //WE NEED TO HOLD OUR VIEW PORT COORDINATES
  int viewPortCoords[4] = {0};
  unsigned int selectBuffer[32] = {0};
  objectsFound = 0;

  //SETUP OUR SELECTION BUFFER TO ACCEPT OBJECT ID'S
  glSelectBuffer (32, selectBuffer);

  //GET THE CURRENT VIEW PORT COORDINATES
  glGetIntegerv (GL_VIEWPORT, viewPortCoords);

  //WE NOW WANT TO EFFECT OUR PROJECTION MATRIX
  glMatrixMode (GL_PROJECTION);

  //WE PUSH ON A NEW MATRIX SO WE DON'T EFFECT OUR 3D PROJECTION
  glPushMatrix ();

  //ALLOWS US TO RENDER THE OBJECTS, BUT NOT CHANGE THE FRAME BUFFER
  glRenderMode (GL_SELECT);

  //RESET OUR PROJECTION MATRIX
  glLoadIdentity ();
  gluPickMatrix (x, viewPortCoords[3] - y, 2, 2, viewPortCoords);
  gluPerspective (90.0f, aspect_ratio, 0.10, 10000.0f);

  //GO BACK INTO OUR MODEL VIEW MATRIX
  glMatrixMode (GL_MODELVIEW);

  //NOW WE RENDER INTO OUR SELECTIVE MODE TO PINPOINT CLICKED OBJECTS
  myDisplay ();

  //RETURN TO RENDER MODE AND GET THE NUMBER OF OBJECTS FOUND
  objectsFound = glRenderMode (GL_RENDER);
  
  //WEBSTER - NO IDEA WHY?  PROBABLY DUE TO THE CAMERA OBJECT
  objectsFound--;

  //PUT OUR PROJECTION MATRIX BACK TO NORMAL
  glMatrixMode (GL_PROJECTION);

  //STOP EFFECTING OUR PROJECTION MATRIX
  glPopMatrix ();

  //GO BACK TO OUR NORMAL MODEL VIEW MATRIX
  glMatrixMode (GL_MODELVIEW);

  if (objectsFound > 0)
	{		
		unsigned int lowestDepth = selectBuffer[1];

		//SET THE SELECTED OBJECT TO THE FIRST OBJECT TO START IT OFF.
		//3 IS THE FIRST OBJECT'S OBJECT ID WE PASSED TO glLoadName ().
		int selectedObject = selectBuffer[3];

		// GO THROUGH ALL OF THE OBJECTS FOUND, BUT START AT THE SECOND ONE
		for (int i = 1; i < objectsFound; i++)
		{
			//CHECK IF THE CURRENT OBJECTS DEPTH IS LOWER THAN THE CURRENT LOWEST
			//NOTICE WE TIMES i BY 4 (4 values for each object) AND ADD 1 FOR THE DEPTH.
			if (selectBuffer[(i * 4) + 1] < lowestDepth)
			{
				//SET THE CURRENT LOWEST DEPTH
				lowestDepth = selectBuffer[(i * 4) + 1];

				//SET THE CURRENT OBJECT ID
				selectedObject = selectBuffer[(i * 4) + 3];
			}
		}
			
		// RETURN THE SELECTED OBJECT
		return (selectedObject);
	}

  //NO OBJECTS FOUND IN PATH OF BULLET
  return (0);
}




void 
myspecialkybd (int theKey, int mouseX, int mouseY)
{
  GLint x = mouseX;
  GLint y = mouseY; 
		
  switch (theKey)
  {		 
    case GLUT_KEY_UP: 	  
      if (ms.GetMouseSensitivity () < 7)
		    ms.SetMouseSensitivity (ms.GetMouseSensitivity () + 0.40);
		  if (kSpeed < .05)
		    kSpeed += .002;
     break;
		
    case GLUT_KEY_DOWN:
		  if (ms.GetMouseSensitivity () > .4)
        ms.SetMouseSensitivity (ms.GetMouseSensitivity () - 0.40);
      if (kSpeed > 0.002)
        kSpeed -= .002;
    break;
    
    case GLUT_KEY_LEFT:
    break;
		
    case GLUT_KEY_RIGHT: 
    break;
		
    default: 
		break;	
  }
}


void 
myKeyboard (unsigned char theKey, int mouseX, int mouseY)
{
  LVector4 pos, rot;
  GLint x = mouseX;
	GLint y = mouseY; 
		
  if ((int) theKey == 27)
	{
		FSOUND_Close ();
		exit (-1);	
	}
		
  switch (theKey)
	{		 			
    case ' ':
      cout << "SPACE BAR PRESSED\n";    
      shooting = true;      
    break;

    case 'q':
		  exit (-1);		//terminate the program	
		break;
		
		case 'p':
		  boolaction = !boolaction;
    break;
 
    default: 
    break;
  }
}



void 
passiveMouseMove (int x, int y) 
{
  ms.x = x; 
  ms.y = y;
}


void 
activeMouseMove (int x, int y) 
{ 
  ms.x = x; 
  ms.y = y;
}



void 
mouse (int button, int state, int x, int y) 
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  switch (button) 
  {
    case GLUT_LEFT_BUTTON:
      switch (state) 
      {
        case GLUT_UP:
          ms.btnOne = MUopengl_MouseState::UP;          
        break;
    
        case GLUT_DOWN:
          shooting = true;
          ms.btnOne = MUopengl_MouseState::DOWN;
        break;
      }
    break;
  
    case GLUT_MIDDLE_BUTTON:
      switch (state) 
      {
        case GLUT_UP:
          ms.btnTwo = MUopengl_MouseState::UP;
        break;
    
        case GLUT_DOWN:
          ms.btnTwo = MUopengl_MouseState::DOWN;
        break;
      }
    break;
  
    case GLUT_RIGHT_BUTTON:
      switch (state) 
      {
        case GLUT_UP:
          ms.btnThree = MUopengl_MouseState::UP;
        break;
    
        case GLUT_DOWN:
          ms.btnThree = MUopengl_MouseState::DOWN;
        break;
      }
    break;
  }
  
  if (state == GLUT_DOWN) 
    action ();
}



void 
mouseMove ()
{
  float middleX = actual_screen_width / 2;
  float middleY = actual_screen_height / 2;
  LVector4 originalRot, tempRot, tempRot2, newRot;
  const float MAX_ANGLE = 60.0;
  float xRot = 0.0;
  float yRot = 0.0;

  muopengl_camera.GetRotation (originalRot);
  tempRot = originalRot;
  tempRot2 = originalRot;

  POINT mousePos;
  GetCursorPos (&mousePos);
  if  ((mousePos.x == middleX) && (mousePos.y == middleY))
    return;

  SetCursorPos (middleX, middleY);
  xRot = (float) (middleX - mousePos.x) / 50.0;
  yRot = (float) (middleY - mousePos.y) / 50.0;

  if (mousePos.x != middleX)
  {
    tempRot.x = 0;
    muopengl_camera.SetRotation (tempRot);
    muopengl_camera.RotateY(xRot);
    muopengl_camera.GetRotation(newRot);
    newRot.x = originalRot.x;
    muopengl_camera.SetRotation(newRot);
    muopengl_camera.Apply();
  }

  if  (cameraXrot >= MAX_ANGLE && yRot > 0)
  {
    //DO NOT ROTATE IF THIS CONDITION IS MET
  }
  else if (cameraXrot <= -MAX_ANGLE && yRot < 0)
  {
    //DO NOT ROTATE IF THIS CONDITION IS MET
  }
  else
  {
    if((cameraXrot + yRot) > MAX_ANGLE)
    {
      yRot = (MAX_ANGLE - cameraXrot);
    }
    else if((cameraXrot + yRot) < -MAX_ANGLE)
    {
      yRot = (-MAX_ANGLE - cameraXrot);
    }
    cameraXrot += yRot;
  }
}



/* Tell GLUT what to do if the window is reshaped: */
void 
reshape
(int width, int height) 
{
	actual_screen_width = width;
	actual_screen_height = height;
	aspect_ratio = actual_screen_width / actual_screen_height;	
	glViewport (0, 0, (GLsizei) width, (GLsizei) height); 
  muopengl_init (&muopengl, width, height);
	muopengl_camera.Initialize (75.0, aspect_ratio, 0.1, 10000);
	printf ("Actual Window width is %d height is %d \n", width, height);
	display.Initialize (width, height);
}


int 
main (int argc, char** argv)
{	
  srand ( time (0) );
	glutInit (&argc, argv);          // initialize the GLUT toolkit
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition (0, 0); // set window position on screen
	glutCreateWindow ("FINAL PROJECT"); // open the screen window
	glutDisplayFunc (myDisplay);     // setup the draw function callback
	glutMotionFunc (activeMouseMove);
	glutIdleFunc (action);
	glutPassiveMotionFunc (passiveMouseMove);
	glutMouseFunc (mouse); 
	glutSpecialFunc (myspecialkybd);			//setup the esc f1 keys
	glutKeyboardFunc (myKeyboard);	//setup the keyboard callback
	glutReshapeFunc (reshape); 
	myInit ();                   
  ms.SetMouseSensitivity (ms.GetMouseSensitivity () + 0.70);
	glutFullScreen ();	
	glutMainLoop (); 		     // go into a infinite event loop
	return (0);
}

void
loadLevel1 ()
{
  level = 1;
  enemyArr[0].setPosition (-1862, 28, 909);
  enemyArr[0].SetRotation (LVector4 (0, 76, 0));

  enemyArr[1].setPosition (-2317, 24, 772);
  enemyArr[1].SetRotation (LVector4 (180, 76, 180));
  
  enemyArr[2].setPosition (-2038, 23, 770);
  enemyArr[2].SetRotation (LVector4 (180, 74, 180));
  
  enemyArr[3].setPosition (-2286, 27, 830);
  enemyArr[3].SetRotation (LVector4 (0, 359, 0));
  
  enemyArr[4].setPosition (-2305, 20, 616);
  enemyArr[4].SetRotation (LVector4 (180, 305, 180));
  
  enemyArr[5].setPosition (-2145, 20, 555);
  enemyArr[5].SetRotation (LVector4 (180, 21, 180));
  
  enemyArr[6].setPosition (-1700, 27, 563);
  enemyArr[6].SetRotation (LVector4 (180, 0, 180));
  
  enemyArr[7].setPosition (-2500, 20, 796);
  enemyArr[7].SetRotation (LVector4 (180, 70, 180));
  
  enemyArr[8].setPosition (-2409, 27, 901);
  enemyArr[8].SetRotation (LVector4 (180, 0, 180));
  
  enemyArr[9].setPosition (-2150, 25, 830);
  enemyArr[9].SetRotation (LVector4 (180, 87, 180));
  
  initializeLevel ();
}


void
loadLevel2 ()
{
 
  level = 2;

  enemyArr[10].setPosition (-2095, 20, 458);
  enemyArr[10].SetRotation (LVector4 (180, 355, 180));

  enemyArr[11].setPosition (-2200, 30, 150);
  enemyArr[11].SetRotation (LVector4 (180, 301, 180));//ROTATATION?

  enemyArr[12].setPosition (-2253, 20, 436);
  enemyArr[12].SetRotation (LVector4 (180, 301, 180));
  
  enemyArr[13].setPosition (-2318, 27, 278);
  enemyArr[13].SetRotation (LVector4 (180, 0, 180));

  enemyArr[14].setPosition (-2447, 30, 380);
  enemyArr[14].SetRotation (LVector4 (0, 311, 0));

  enemyArr[15].setPosition (-2552, 20, 315);
  enemyArr[15].SetRotation (LVector4 (180, 287, 180));

  enemyArr[16].setPosition (-2662, 27, 408);
  enemyArr[16].SetRotation (LVector4 (0, 0, 0));

  enemyArr[17].setPosition (-2682, 25, 273);
  enemyArr[17].SetRotation (LVector4 (180, 294, 180));

  enemyArr[18].setPosition (-2693, 27, 346);
  enemyArr[18].SetRotation (LVector4 (180, 0, 180));

  enemyArr[19].setPosition (-2168, 20, 237);
  enemyArr[19].SetRotation (LVector4 (180, 270, 180));
  
  initializeLevel (); 
}



void
initializeLevel ()
{
  if (BEGIN_ITER < 90 && level > 1)
    {
      BEGIN_ITER += 10;
      END_ITER += 10;
    }

  for (int myIterator = BEGIN_ITER; myIterator < END_ITER; myIterator++)
  {
    enemyArr[myIterator].SetRenderEnable (false);
    killed[myIterator] = false;
    activeArr[myIterator] = false;
    enemyHealth[myIterator] = level * 10; 
    pointValue[myIterator] = level * (BEGIN_ITER + 50);
  }
}
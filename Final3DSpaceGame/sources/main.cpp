/********************************************************************************
*           CS375 Graphics & Virtual Reality OpenGL Sample Code    
********************************************************************************
*
* shawn englerth
* game turned in on CD ROM
* also can be found at http://mucspc.millersville.edu/smenglerth/FINAL_GAME.zip


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
void enemyChaseMe (int& myIterator, LVector4& enemyPosition, LVector4& enemyRotation, LVector4& campos);
void loadLevel1 ();
void loadLevel2 ();
void loadLevel3 ();
void loadLevel4 ();
void initializeLevel (int BEGIN, int END);
int RetrieveObjectID ();
void mouseMove ();
void moveActiveFireBall (int myIterator);

float cameraXrot = 0;
LVector4 campos;
LVector4 camrot;
LVector4 prevPos;
LVector4 currPos;
LVector4 fireBallPos;
float deltaZ;
float deltaX;
int BEGIN_ITER = 0;
int END_ITER = 0;

MyPath A ("path1.txt");
MyPath B ("path2.txt");
MyPath C ("path3.txt");
MyPath D ("path4.txt");

bool playing = false;
bool shooting = false;

bool PATH1 = false;
bool PATH2 = false;
bool PATH3 = false;
bool PATH4 = false;

bool WINNER = false;
bool GAMEOVER = false;
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
vector <int> enemyStrength (MAXENEMY, 1);
vector <LVector4> enemyPrevPos (MAXENEMY, LVector4 (0, 0, 0));
int score = 0;
int myHealth = 100;
int scorePrint;

float fps = 1;
float frameSpeed = 0; 
int frame = 0;
int framesToLive = 0;
int multiplier = 3;
float kSpeed = 1.0;
int camSpeedAdjuster = .5;

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

FSOUND_SAMPLE *themeSong = NULL;
FSOUND_SAMPLE *explosion = NULL;
FSOUND_SAMPLE *shotgun = NULL;
FSOUND_SAMPLE *winner = NULL;

MUopengl_MouseState ms;
Display display;
LCamera Camera; 
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
    Camera.GetRotation (currentRotation);

    //if (currentRotation.x % 180)180
    Camera.SetRotation (LVector4 (0.0, currentRotation.y, 0.0));
  }

  //BUTTON C PRESSED (#3 BUTTON OR 'X' ON GAMEPAD)
  else if (button == GLUT_JOYSTICK_BUTTON_C)
  {
    joystick_buttonC = true;
    shooting = true;
    shooting = true;
    FSOUND_PlaySound (12, shotgun);
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
     Camera.RotateY ((frameSpeed * (-(float)leftRight / 800)));
	 } 
   else if (leftRight < -deadrange)  
   {
	   Camera.RotateY ((frameSpeed * (-(float)leftRight / 800)));
	 }
  }
  else
  {
   //MOVE Y DIRECTION IF JOYSTICK IS OUTSIDE OF Y DEADRANGE
   if (upDown > deadrange)
   {
     Camera.Pitch ((frameSpeed * (-(float)upDown / 800)));
   } 
   else if (upDown < -deadrange)  
   {
	   Camera.Pitch ((frameSpeed * (-(float)upDown / 800)));
	 }
  }
}


//=============================================================================
void 
myInit (void)
{
  cout << "HELLO" << endl;
  glColor3f (0.0f, 0.0f, 0.0f);          // set the drawing color 
 	glPointSize (1.0);		       // a ‘dot’ is 4 by 4 pixels
	add_lights ();

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
    
    enemyArr[i].SetRotation (LVector4 (0, 0, 0));
    enemyArr[i].SetPosition (LVector4 (0, 0, 0));
    enemyArr[i].Make_collidable ();
    enemyArr[i].SetRenderEnable (false);
  }

  BEGIN_ITER = 0;
  END_ITER = MAXENEMY;

  City.Make_collidable ();
  City.setPosition (0, .1, 0);
  World.setPosition (0, 0, 0);
  Earth.setPosition (0, 0, 0);

  Camera.SetPosition (LVector4 (-2611, 30, 797));
  Camera.SetRotation (LVector4 (0, 270, 0));

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

  SetCurrentDirectory ("../");

  FSOUND_Init (44100, 32, 0);
  themeSong = FSOUND_Sample_Load (1, "IMstarwars.mp3", FSOUND_LOOP_NORMAL, 0);
  explosion = FSOUND_Sample_Load (2, "implosion2.wav", FSOUND_NORMAL, 0);
  shotgun = FSOUND_Sample_Load (3, "q3sg.wav", FSOUND_NORMAL, 0);
  winner = FSOUND_Sample_Load (4, "mainthemeSW.mp3", FSOUND_NORMAL, 0);

  FSOUND_PlaySound (13, themeSong);
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

    float thisDistance = muopengl_euclidean_dist (campos, enemyPosition);

    if (thisDistance > 200 && !killed[myIterator])
    {
      enemyArr[myIterator].SetRenderEnable (false);
      activeArr[myIterator] = false;
    }
    else if (thisDistance < 200 && thisDistance > 50 && !killed[myIterator])
    {
      enemyArr[myIterator].SetRenderEnable (true);
      activeArr[myIterator] = true;
    }
    else
    {
      enemyArr[myIterator].SetRenderEnable (false);
      activeArr[myIterator] = false;
      killed[myIterator] = true;
      enemyArr[myIterator].SetPosition (LVector4 (0, 500, 0));
    }
  } 
}


void
moveActiveEnemy ()
{
  LVector4 enemyPosition, enemyRotation;

  for (int myIterator = BEGIN_ITER; myIterator <END_ITER; myIterator++)
  {
    Camera.GetRotation (camrot);
    Camera.GetPosition (campos);
    enemyArr[myIterator].GetPosition (enemyPosition);

    if (activeArr[myIterator] && myIterator % 10 != 3 
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
        enemyPosition.y -= (kSpeed * camSpeedAdjuster);
        enemyRotation.y -= (kSpeed * .75);
      }

      if (moveUp) 
      {
        enemyPosition.y += (kSpeed * camSpeedAdjuster);
        enemyRotation.y += (kSpeed * .75);
      }
      enemyArr[myIterator].SetPosition (enemyPosition);
      enemyArr[myIterator].SetRotation (enemyRotation);
      enemyArr[myIterator].Yaw (-90);
    }
    else if (activeArr[myIterator] && !killed[myIterator] && (myIterator % 10 == 3 
      || myIterator % 10 == 6 || myIterator % 10 == 8))
    {
      float euclidDistance = muopengl_euclidean_dist (campos, enemyPosition);
      float deltaXCamEnemy = campos.x - enemyPosition.x;
      float deltaZCamEnemy = campos.z - enemyPosition.z;

      enemyPosition.x += ((camSpeedAdjuster * kSpeed) * (deltaXCamEnemy / euclidDistance));
      enemyPosition.z += ((camSpeedAdjuster * kSpeed) * (deltaZCamEnemy / euclidDistance));


      enemyRotation.y = (360 - camrot.y);

      enemyRotation.x = (camrot.x + 180);
      if (camrot.x == 360)
        enemyRotation.x = 0;

      enemyRotation.z = (camrot.z + 180);
      if (camrot.z == 360)
        enemyRotation.z = 0;

      enemyArr[myIterator].SetPosition (enemyPosition);
      enemyArr[myIterator].SetRotation (enemyRotation);


      if (enemyArr[myIterator].Check_collision (City))
        enemyArr[myIterator].SetPosition (enemyPrevPos[myIterator]);

      enemyArr[myIterator].Apply ();
      enemyArr[myIterator].Yaw (-90);

    }
  }
}



void
enemyChaseMe (int& myIterator, LVector4& enemyPosition, LVector4& enemyRotation, LVector4& campos)
{
   LVector4 enemyCurrPos;
   enemyArr[myIterator].GetPosition (enemyCurrPos);

   float euclidDistance = muopengl_euclidean_dist (campos, enemyPosition);
   float deltaXCamEnemy = campos.x - enemyPosition.x;
   float deltaZCamEnemy = campos.z - enemyPosition.z;
  
   //CHASING AI CODE WRITTEN EXCLUSIVELY BY SHAWN ENGLERTH
  if (activeArr[myIterator] && !killed[myIterator] && (myIterator % 10 == 3 
    || myIterator % 10 == 6 || myIterator % 10 == 8))
  {
    enemyPosition.x += (kSpeed * (deltaXCamEnemy / euclidDistance));
    enemyPosition.z += (kSpeed * (deltaZCamEnemy / euclidDistance));
    enemyArr[myIterator].SetPosition (enemyPosition);
  }
}

void
checkForHealth ()
{
 for (int myIterator = BEGIN_ITER; myIterator < END_ITER; myIterator++)
  {
    if (!killed[myIterator])
    {
      LVector4 enemyPosition;
      enemyArr[myIterator].GetPosition (enemyPosition);

      float enemyDistance = muopengl_euclidean_dist (campos, enemyPosition);

      if (enemyDistance > 50 && enemyDistance < 55)
      {
        if (myHealth > 0)
            myHealth -= (.5 * level);
      }

      if (myHealth <= 0)
        GAMEOVER = true;
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
        if (myHealth < 90)
        myHealth += level;
        FSOUND_PlaySound (11, explosion);
        score += pointValue[picked];
        enemyArr[picked].GetPosition (target);
        explode.set_size (128, 128);
        explode.set_position (target);
        explode.start ();
        enemyArr[picked].SetRenderEnable (false);
        activeArr[picked] = false;
        killed[picked] = true;
        enemyArr[picked].SetPosition (LVector4 (0, 1500, 0));
        scorePrint = picked;
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
setCamSpeedAdjuster ()
{
  if (fps <= 50)
    camSpeedAdjuster = 1;
  else if (fps < 56)
    camSpeedAdjuster = .9;
  else if (fps < 61)
    camSpeedAdjuster = .8;
  else if (fps < 66)
    camSpeedAdjuster = .75;
  else if (fps < 71)
    camSpeedAdjuster = .7;
  else if (fps < 76)
    camSpeedAdjuster = .65;
  else if (fps < 81)
    camSpeedAdjuster = .6;
  else if (fps < 86)
    camSpeedAdjuster = .55;
  else
    camSpeedAdjuster = .5;
}


//=============================================================================
//
//ACTION ACTION ACTION ACTION ACTION ACTION ACTION ACTION
//
//=============================================================================
void 
action () 
{
    if (frame % 600 == 0)
      setCamSpeedAdjuster ();

    Camera.GetPosition (prevPos);
    glutForceJoystickFunc ();
    World.RotateZ (.04);

    ms.Check_MouseState (muopengl, &Camera);
    Camera.Apply ();

    Camera.GetRotation (camrot);
    Camera.GetPosition (campos);

    mouseMove ();


  if (!GAMEOVER && !WINNER)
  {
    if (PATH1)
    {
      if (counter == 0)
      {
        A.readPath ();
        loadLevel1 ();
      }
      mouseMove ();
      A.getPosRot (campos);
      if (frame % 2 == 0)
      Camera.SetPosition (campos);
      counter++;
      if (counter == A.getPathSize () - 1)
      {
        PATH1 = false;
        PATH2 = true;
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
      Camera.SetPosition (campos);
      counter++;
      if (counter == (B.getPathSize () - 1))
      { 
        PATH2 = false;
        PATH3 = true;
        counter = 0;
      }
    }

    if (PATH3 && !PAUSE)
    {
      if (counter == 0)
      {
        C.readPath ();
        loadLevel3 ();
      }
     
      mouseMove ();
      C.getPosRot (campos);
      Camera.SetPosition (campos);
      counter++;
      if (counter == (C.getPathSize () - 1))
      { 
        PATH3 = false;
        PATH4 = true;
        counter = 0;
      }
    }

    if (PATH4 && !PAUSE)
    {
      if (counter == 0)
      {
        D.readPath ();
        loadLevel4 ();
      }
      
      mouseMove ();
      D.getPosRot (campos);
      Camera.SetPosition (campos);
      counter++;
      if (counter == (D.getPathSize () - 1))
      { 
        PATH4 = false;
        WINNER = true;
        FSOUND_StopSound (13);
        FSOUND_PlaySound (13, winner);
        counter = 0;
      }
    }

    renderEnemyFunc ();

    if (shooting == true)
      shootingFunc ();

    moveActiveEnemy ();
    checkForHealth ();
  }
   
    light_pos[X] = campos.x;
    light_pos[Y] = campos.y + 20;
    light_pos[Z] = campos.z;
    glLightfv (GL_LIGHT0, GL_POSITION, light_pos);

    //Camera.SetRotation (camrot);
    Camera.GetRotation (camrot);
    Camera.GetPosition (campos);
    frame++;
       
   glutPostRedisplay ();
  
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

  sprintf (mystring, "SHAWN ENGLERTH - MILLERSVILLE UNIVERSITY");
  display.SetFont (font3);
  display.DrawText (0.45, .10, 0, mystring);

  sprintf (mystring, "SCORE: %d", score);
  display.SetFont (font5);
  display.DrawText (0.45, .20, 0, mystring);
	
  glColor3f (0, 0, 1);
  if (GAMEOVER)
  {
    sprintf (mystring, "GAMEOVER");
    display.SetFont (font5);
    display.DrawText (0.45, .45, 0, mystring);
  }
  
  if (WINNER)
  {
    sprintf (mystring, "PLANET SAVED");
    display.SetFont (font5);

    display.DrawText (0.45, .45, 0, mystring);
  }
	

  //display.BarGraph (left, top, right, bot, fill%, horizontal = 0, border = 1;
  glColor3f (1.0, 0, 0);
  display.BarGraph (.30, .87, .70, .90, myHealth, 1, 3);
  
  if (printPointsEarned)
  {
    glColor3f (1, 0, 0);
    sprintf (mystring, "%d POINTS", pointValue[scorePrint]);
    display.DrawText (0.45, 0.45, 0, mystring);
      if (frame % framesToLive == 0)
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
  Camera.Render ();
	

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
  explode.update (&Camera); 

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
      if (ms.GetMouseSensitivity () < 20)
		    ms.SetMouseSensitivity (ms.GetMouseSensitivity () + 0.02);
		  if (kSpeed <= 20)
		    kSpeed += .02;
     break;
		
    case GLUT_KEY_DOWN:
		  if (ms.GetMouseSensitivity () > .02)
        ms.SetMouseSensitivity (ms.GetMouseSensitivity () - 0.02);
      if (kSpeed > 0.02)
        kSpeed -= .02;
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
      FSOUND_PlaySound (12, shotgun);
        shooting = true;      
    break;

    case 'q':
		  exit (-1);		//terminate the program	
		break;
		
		case 'p':
		  boolaction = !boolaction;
      cout << "CameraPosition: x: " << campos.x << "  y: " << campos.y << "  z: " << campos.z << endl;
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
          FSOUND_PlaySound (12, shotgun);
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

  Camera.GetRotation (originalRot);
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
    Camera.SetRotation (tempRot);
    Camera.RotateY(xRot);
    Camera.GetRotation(newRot);
    newRot.x = originalRot.x;
    Camera.SetRotation(newRot);
    Camera.Apply();
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
	Camera.Initialize (75.0, aspect_ratio, 0.1, 10000);
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
  enemyArr[0].setPosition (-1952, 28, 909);
  enemyArr[0].SetRotation (LVector4 (0, 76, 0));
  enemyArr[1].setPosition (-2317, 24, 772);
  enemyArr[1].SetRotation (LVector4 (180, 76, 180));
  enemyArr[2].setPosition (-2038, 23, 770);
  enemyArr[2].SetRotation (LVector4 (180, 74, 180));
  enemyArr[3].setPosition (-2286, 34, 830);
  enemyArr[3].SetRotation (LVector4 (0, 359, 0));
  enemyArr[4].setPosition (-2305, 20, 616);
  enemyArr[4].SetRotation (LVector4 (180, 305, 180));
  enemyArr[5].setPosition (-2145, 20, 555);
  enemyArr[5].SetRotation (LVector4 (180, 21, 180));
  enemyArr[6].setPosition (-1890, 34, 570);
  enemyArr[6].SetRotation (LVector4 (180, 0, 180));
  enemyArr[7].setPosition (-2500, 20, 796);
  enemyArr[7].SetRotation (LVector4 (180, 70, 180));
  enemyArr[8].setPosition (-2409, 34, 901);
  enemyArr[8].SetRotation (LVector4 (180, 0, 180));
  enemyArr[9].setPosition (-2150, 25, 830);
  enemyArr[9].SetRotation (LVector4 (180, 87, 180));
 
  initializeLevel (0, 10);
}



void
loadLevel2 ()
{
 
  level = 2;

  enemyArr[0].setPosition (-2095, 20, 458);
  enemyArr[0].SetRotation (LVector4 (180, 355, 180));
  enemyArr[1].setPosition (-2200, 30, 245);
  enemyArr[1].SetRotation (LVector4 (180, 301, 180));
  enemyArr[2].setPosition (-2253, 20, 390);
  enemyArr[2].SetRotation (LVector4 (180, 301, 180));
  enemyArr[3].setPosition (-2318, 34, 278);
  enemyArr[3].SetRotation (LVector4 (180, 0, 180));
  enemyArr[4].setPosition (-2347, 30, 380);
  enemyArr[4].SetRotation (LVector4 (0, 311, 0));
  enemyArr[5].setPosition (-2400, 20, 315);
  enemyArr[5].SetRotation (LVector4 (180, 287, 180));
  enemyArr[6].setPosition (-2450, 34, 408);
  enemyArr[6].SetRotation (LVector4 (0, 0, 0));
  enemyArr[7].setPosition (-2500, 25, 273);
  enemyArr[7].SetRotation (LVector4 (180, 294, 180));
  enemyArr[8].setPosition (-2600, 34, 270);
  enemyArr[8].SetRotation (LVector4 (180, 0, 180));
  enemyArr[9].setPosition (-2168, 20, 290);
  enemyArr[9].SetRotation (LVector4 (180, 270, 180));
  
  initializeLevel (0, 10); 
}



void
loadLevel3 ()
{
 
  level = 3;

  enemyArr[0].setPosition (-1980, 20, 290);
  enemyArr[0].SetRotation (LVector4 (180, 84, 180));
  enemyArr[1].setPosition (-1860, 30, 405);
  enemyArr[1].SetRotation (LVector4 (0, 78, 0));
  enemyArr[2].setPosition (-1740, 20, 290);
  enemyArr[2].SetRotation (LVector4 (180, 84, 180));
  enemyArr[3].setPosition (-1620, 34, 405);
  enemyArr[3].SetRotation (LVector4 (0, 78, 0));
  enemyArr[4].setPosition (-1500, 30, 290);
  enemyArr[4].SetRotation (LVector4 (180, 84, 180));
  enemyArr[5].setPosition (-1449, 20, -131);
  enemyArr[5].SetRotation (LVector4 (180, 333, 180));
  enemyArr[6].setPosition (-1110, 34, -92);
  enemyArr[6].SetRotation (LVector4 (180, 38, 180));
  enemyArr[7].setPosition (-937, 25, 143);
  enemyArr[7].SetRotation (LVector4 (0, 56, 0));
  enemyArr[8].setPosition (-800, 34, -119);
  enemyArr[8].SetRotation (LVector4 (0, 86, 0));
  enemyArr[9].setPosition (-800, 106, 75);
  enemyArr[9].SetRotation (LVector4 (180, 86, 180));

  enemyArr[10].setPosition (-1329, 20, 120);
  enemyArr[10].SetRotation (LVector4 (180, 04, 180));
  enemyArr[11].setPosition (-1245, 30, 120);
  enemyArr[11].SetRotation (LVector4 (180, 8, 180));
  enemyArr[12].setPosition (-1359, 20, 0);
  enemyArr[12].SetRotation (LVector4 (180, 4, 180));
  enemyArr[13].setPosition (-1286, 34, 405);
  enemyArr[13].SetRotation (LVector4 (180, 8, 180));
  enemyArr[14].setPosition (-1225, 30, 0);
  enemyArr[14].SetRotation (LVector4 (180, 84, 180));
  enemyArr[15].setPosition (-1510, 20, 390);
  enemyArr[15].SetRotation (LVector4 (180, 88, 180));
  enemyArr[16].setPosition (-1615, 34, 350);
  enemyArr[16].SetRotation (LVector4 (180, 88, 180));
  enemyArr[17].setPosition (-1206, 25, 350);
  enemyArr[17].SetRotation (LVector4 (0, 88, 0));
  enemyArr[18].setPosition (-1000, 34, -100);
  enemyArr[18].SetRotation (LVector4 (0, 86, 0));
  enemyArr[19].setPosition (-900, 106, 25);
  enemyArr[19].SetRotation (LVector4 (180, 86, 180));
 
  initializeLevel (0, 20); 
}



void
loadLevel4 ()
{
 
  level = 4;

  enemyArr[0].setPosition (-501, 20, 35);
  enemyArr[0].SetRotation (LVector4 (0, 75, 0));
  enemyArr[1].setPosition (-419, 30, 323);
  enemyArr[1].SetRotation (LVector4 (0, 15, 0));
  enemyArr[2].setPosition (-362, 20, 512);
  enemyArr[2].SetRotation (LVector4 (0, 15, 0));
  enemyArr[3].setPosition (-538, 34, 567);
  enemyArr[3].SetRotation (LVector4 (0, 345, 0));
  enemyArr[4].setPosition (-347, 30, 633);
  enemyArr[4].SetRotation (LVector4 (0, 16, 180));
  enemyArr[5].setPosition (-475, 20, 618);
  enemyArr[5].SetRotation (LVector4 (0, 345, 0));
  enemyArr[6].setPosition (-350, 34, 520);
  enemyArr[6].SetRotation (LVector4 (0, 16, 0));
  enemyArr[7].setPosition (-434, 25, 410);
  enemyArr[7].SetRotation (LVector4 (0, 345, 0));
  enemyArr[8].setPosition (-327, 34, 390);
  enemyArr[8].SetRotation (LVector4 (0, 75, 0));
  enemyArr[9].setPosition (-131, 20, 275);
  enemyArr[9].SetRotation (LVector4 (0, 75, 0));

  enemyArr[10].setPosition (-37, 20, 386);
  enemyArr[10].SetRotation (LVector4 (0, 75, 0));
  enemyArr[11].setPosition (74, 30, 290);
  enemyArr[11].SetRotation (LVector4 (0, 75, 0));
  enemyArr[12].setPosition (187, 20, 376);
  enemyArr[12].SetRotation (LVector4 (0, 75, 0));
  enemyArr[13].setPosition (560, 34, 254);
  enemyArr[13].SetRotation (LVector4 (0, 75, 0));
  enemyArr[14].setPosition (312, 30, 400);
  enemyArr[14].SetRotation (LVector4 (0, 75, 0));
  enemyArr[15].setPosition (350, 20, 205);
  enemyArr[15].SetRotation (LVector4 (180, 15, 180));
  enemyArr[16].setPosition (575, 34, 230);
  enemyArr[16].SetRotation (LVector4 (180, 15, 180));
  enemyArr[17].setPosition (400, 25, 120);
  enemyArr[17].SetRotation (LVector4 (180, 15, 180));
  enemyArr[18].setPosition (555, 34, 175);
  enemyArr[18].SetRotation (LVector4 (180, 15, 180));
  enemyArr[19].setPosition (390, 28, 125);
  enemyArr[19].SetRotation (LVector4 (180, 16, 180));
 
  initializeLevel (0, 20); 
}


void
initializeLevel (int BEGIN, int END)
{
  BEGIN_ITER = BEGIN;
  END_ITER = END;

  for (int myIterator = BEGIN_ITER; myIterator < END_ITER; myIterator++)
  {
    enemyArr[myIterator].SetRenderEnable (false);
    killed[myIterator] = false;
    activeArr[myIterator] = false;
    enemyHealth[myIterator] = level * 10; 
    pointValue[myIterator] = level * 50;
    enemyStrength[myIterator] = level;
  }

  
  for (int myIterator = END_ITER; myIterator < MAXENEMY; myIterator++)
  {
    enemyArr[myIterator].SetRenderEnable (false);
  }


}

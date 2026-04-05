/********************************************************************************
*           CS375 Graphics & Virtual Reality OpenGL Sample Code    
********************************************************************************
* 		STUDENT NAME     :   SHAWN ENGLERTH
*         Filename	   :   First Person Shooter Assignment
*		   written By      :   Roger Webster, Ph.D.
*                      :   Department of Computer Science
*                      :   D&E Communications Inc.Computer Science Wing
*                      :   Caputo Hall 
*			                 :   Millersville University
*      Class           :   CS375 Computer Graphics and Virtual Reality
*      Graphics Package:   OpenGL
*    - Info can be found on Internet World Wide Web server (WWW) site:
*                      http://cs.millersville.edu/~webster/cs375/
*modifications:
10-01-2003 rww made this demo
01-31-2005 rds converted to .net
******************************************************************************/
#include <ctime>
#include "muopengl.h"
#include "fmod.h"
#include <cctype>

//FUNCTION PROTOTYPES
void setGunsPosition ();
int RetrieveObjectID ();
void Shoot ();
void JoyFunc (unsigned int button, int leftRight, int upDown, int throttle);

//FRAME BASED SPEED
//#define kSpeed .04f;
float kSpeed = .020f; 
float fps;
bool directions = false;
					
MUmovnode_collide city48;
MUmovnode_collide Guns [3];
MUmovnode_collide Box;
MUmovnode_collide World;
const int MAXTARGETS = 15;
MUmovnode_collide Targets [MAXTARGETS];

//GUN SELECTED
int selected = 0;
bool shooting;
int targetsRemaining = MAXTARGETS;

//PRINTING MESSAGES TO SCREEN VARIABLES
int rivalsKilled = 0;

//BOOL FOR COLLISION DETECTION ON SCREEN DISPLAY
bool isCollision = false;

//FOR PLAYING SOUNDS PER FRAMES
int framesModFPS = 0;

//GUN UP AND DOWN MOVEMENT VARIABLES
bool moveDown = false;
bool moveUp = false;
int movement = 0;
int shotsRemaining = 45;
bool clipEmpty = false;
bool gameOver = false;
bool missionComplete = false;
int soundPlayCounter = 0;

//MOTION FOR GUN KICK VARIABLES
bool moveBack = false;
bool moveForward = false;
bool kick = false;
int gunMovement = 0;
bool BEGINMOVEMENT = true;

//PICKING VARIABLES
int foundObj = 0;
int objectsFound = 0;
int actual_screen_width;
int actual_screen_height;
bool killed [MAXTARGETS] = {false};	
int dispObjNumKilled = 0;

//IMAGE FILES VARIABLES
Tga_anim blood;
UINT tga_texture [MAX_TEXTURES] = {0};	
LTGA crosshair;
LTGA splash;
int splashTime = 0;

//JOYSTICK VARIABLES
float frameSpeed = 0; 
int joystick_x;
int joystick_y;
int joystick_z;
int deadrange = 100;
bool joystick_buttonA = false;
bool joystick_buttonB = false;
bool joystick_buttonC = false;
bool joystick_buttonD = false;

//SOUND POINTERS
FSOUND_SAMPLE *heartbeat = 0;
FSOUND_SAMPLE *machine = 0;
FSOUND_SAMPLE *glock = 0;
FSOUND_SAMPLE *shotgun = 0;
FSOUND_SAMPLE *death = 0;
FSOUND_SAMPLE *explosion = 0;
FSOUND_SAMPLE *clipempty = 0;
FSOUND_SAMPLE *missionComp = 0;

//SKYBOX DECLARATION
Skybox mySkybox;

//MUOPEN GL CAMERA OBJECT
LCamera muopengl_camera;

//DATA STRUCTURE THAT HOLDS MUOPENGL INFO
muopengl_info muopengl;

//TURN LIGHTING ON INITIALLY
bool  g_bLighting = true;		
float g_RotateX	= 0.0f;							
float g_RotationSpeed = 0.8f;			
int total_num_textures = 0;
GLdouble aspect_ratio;
GLfloat light_pos[] = {0.0, -60.0, 0.0, 1.0};

unsigned char *tga_pixels;
MUopengl_MouseState ms;

Display display;

int font1;
int font2;
int font3;
int font4;
int font5;
float tilt = PI;

//===============================================================================
//LIGHTING FUNCTIONS FOUND IN OpenGL PG 3rd ED. AW PRESS Mason Woo, et.al.
//===============================================================================
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
//ALLOW THE ACTION TO CONTINUE MOVING WHEN A BUTTON IS PRESSED
//==============================================================================
void
keepMoving (int leftRight, int upDown)
{
  //MOVE X DIRECTION IF JOYSTICK IS OUTSIDE OF X DEADRANGE
	    if (leftRight > deadrange)
      {
	      muopengl_camera.Yaw (-(frameSpeed * ((float)leftRight / 1000)));
	    } 
      else if (leftRight < -deadrange)  
      {
	      muopengl_camera.Yaw (-(frameSpeed * ((float)leftRight / 1000)));
	    }
	
      //MOVE Y DIRECTION IF JOYSTICK IS OUTSIDE OF Y DEADRANGE
	    if (upDown > deadrange)
      {
	      muopengl_camera.MoveForward ((frameSpeed * ((float)upDown / 1000)));
	    } 
      else if (upDown < -deadrange)  
      {
	      muopengl_camera.MoveForward ((frameSpeed * ((float)upDown / 1000)));
	    }		
}



//===============================================================================
//RENDER THE GUN OF CURRENT CHOICE
//===============================================================================
void 
renderProperGun ()
{
  for (int i = 0; i < 3; i++)
  {
    Guns[i].SetRenderEnable (false);
  }
  
  Guns[selected].SetRenderEnable (true);
}



//===============================================================================
//SET GUNS POSITION WITH RESPECT TO PERSPECTIVE BOX OF 1ST PERSON VIEW
//===============================================================================
void 
setGunsPosition ()
{
  for (int i = 0; i < 3; i++)
  {
    Guns[i].MoveX (-.15);
    Guns[i].MoveY (-1);
    Guns[i].MoveZ (-2);
  }
}


//==============================================================================
//GET RANDOM ROTATION FOR TARGETS PLACEMENT
//==============================================================================
float 
getRandomRotation ()
{
  return (rand () % 360);
}



//==============================================================================
//LOAD AND POSITION THE TARGETS TO SHOOT AT 
//==============================================================================
void 
loadTargets ()
{
 float rotation = getRandomRotation ();
 
 Targets[0].LoadObject ("gangster.3ds");
 Targets[0].setPosition (-295, 13.5, -185);
 Targets[0].SetRotation (LVector4 (0, (rand () % 360), 0));
 
 Targets[1].LoadObject ("gangster.3DS");
 Targets[1].setPosition (-61, 13.5, 231);
 Targets[1].SetRotation (LVector4 (0, rotation, 0));
 
 Targets[2].LoadObject ("gangster.3ds");
 Targets[2].setPosition (374, 13.5, -182);
 Targets[2].SetRotation (LVector4 (0, rotation, 0));
 
 Targets[3].LoadObject ("gangster.3DS");
 Targets[3].setPosition (527, 13.5, -492);
 Targets[3].SetRotation (LVector4 (0, rotation, 0));
 
 Targets[4].LoadObject ("gangster.3ds");
 Targets[4].setPosition (-45, 13.5, -618);
 Targets[4].SetRotation (LVector4 (0, rotation, 0));
 
 Targets[5].LoadObject ("gangster.3DS");
 Targets[5].setPosition (-540, 13.5, -612);
 Targets[5].SetRotation (LVector4 (0, rotation, 0));
 
 Targets[6].LoadObject ("gangster.3ds");
 Targets[6].setPosition (-150, 13.5, -635);
 Targets[6].SetRotation (LVector4 (0, rotation, 0));
 
 Targets[7].LoadObject ("gangster.3DS");
 Targets[7].setPosition (-567, 13.5, 671);
 Targets[7].SetRotation (LVector4 (0, rotation, 0));
 
 Targets[8].LoadObject ("gangster.3ds");
 Targets[8].setPosition (692, 13.5, -95);
 Targets[8].SetRotation (LVector4 (0, rotation, 0));
 
 Targets[9].LoadObject ("gangster.3DS");
 Targets[9].setPosition (563, 13.5, 609);
 Targets[9].SetRotation (LVector4 (0, rotation, 0));

 Targets[10].LoadObject ("gangster.3DS");
 Targets[10].setPosition (39, 13.5, -381);
 Targets[10].SetRotation (LVector4 (0, rotation, 0));

 Targets[11].LoadObject ("gangster.3DS");
 Targets[11].setPosition (50, 13.5, 180);
 Targets[11].SetRotation (LVector4 (0, rotation, 0));

 Targets[12].LoadObject ("gangster.3DS");
 Targets[12].setPosition (205, 13.5, 774);
 Targets[12].SetRotation (LVector4 (0, rotation, 0));

 Targets[13].LoadObject ("gangster.3DS");
 Targets[13].setPosition (-281, 13.5, 134);
 Targets[13].SetRotation (LVector4 (0, rotation, 0));

 Targets[14].LoadObject ("gangster.3DS");
 Targets[14].setPosition (-316, 13.5, -304);
 Targets[14].SetRotation (LVector4 (0, rotation, 0));
}



//===============================================================================
//MY INIT
//===============================================================================
void 
myInit (void)
{
	LVector4 pos;
  LVector4 rot;

  printf ("SetCurrentDirectory to Images\n");
  SetCurrentDirectory ("Images/");
  
  printf ("Loading Splash Screen\n");
	splash.LoadFromFile ("GhettoRageous.tga");

  printf ("Loading Objects\n");
	city48.LoadObject ("city.3DS");
  //World.LoadObject ("world.3ds");
  Box.LoadObject ("box.3ds");
	Guns[0].LoadObject ("glock.3DS");
  Guns[1].LoadObject ("uzi.3DS");
  Guns[2].LoadObject ("w_xm1014.3ds");

  printf ("Loading Targets\n");
  loadTargets ();
  for (int i = 0; i < MAXTARGETS; i++)
  {
    Targets[i].Make_collidable ();
  }
  
  printf ("SetCurrentDirectory to Images\n");
  SetCurrentDirectory ("../Images/");

  blood.load_tga_files ("blood", 5);
  crosshair.LoadFromFile ("crosshairs.tga");
  crosshair.createKeyedMask (0, 0, 0);

  Box.Make_collidable ();
  city48.Make_collidable ();
  
  city48.setPosition (0, 0, 0);
  //World.setPosition (0, 2, 0);
  setGunsPosition ();
  
  for (int j = 0; j < 3; j++)
  {
    Guns[j].Attach (&Box);
  }
  
  renderProperGun ();
  
  Box.setPosition (0, 17.5, 70);
  Box.SetRotation (LVector4 (0, 270, 0));

  glClearColor (0.0,0.0,0.0,0.0);       // set white background color
  glColor3f (0.0f, 0.0f, 0.0f);          // set the drawing color 
 	glPointSize (1.0);		       // a ‘dot’ is 4 by 4 pixels
	add_lights ();
						      
	pos.x = 0;
	pos.y = 17.5;
	pos.z = 70.0;
	rot.x = 0;
  rot.y = 270;
  rot.z = 0;

	muopengl_camera.SetPosition (pos);
  muopengl_camera.SetRotation (rot);
	light_pos [X] = pos.x;
	light_pos [Y] = pos.y;
	light_pos [Z] = pos.z;

	font1 = display.LoadFont ("Times", 30, 5, 1);
  font2 = display.LoadFont ("Arial", 30);
	font3 = display.LoadFont ("Arial", 20);
	font4 = display.LoadFont ("Arial", 40);
  font5 = display.LoadFont ("Arial", 64);
 	display.ListLoadedFonts ();
  
	//display.CreateTexture ("mu.tga", 42);
  
	glShadeModel (GL_SMOOTH);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_NORMALIZE);
	glutSetCursor (GLUT_CURSOR_CROSSHAIR);
	//glEnable (GL_COLOR_MATERIAL);
	//glEnable (GL_TEXTURE_2D);
	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glEnable (GL_BLEND);

	glPointSize (1.0);
	//mySkybox.LoadImages ("front.tga","back.tga","right.tga", "left.tga", "top.tga", "bottom.tga");
  mySkybox.LoadImages ( "neg_x.tga",  "pos_x.tga", "neg_z.tga", "pos_z.tga", "pos_y.tga", "neg_y.tga");
	mySkybox.SetSize (1600, 350, 1600);
	mySkybox.SetCenter (0, 175, 0);

  printf ("SetCurrentDirectory to Sounds\n");
  SetCurrentDirectory ("../Sounds/");
	FSOUND_Init (44100, 32, 0);
	heartbeat = FSOUND_Sample_Load (0, "heartbeat.wav", FSOUND_LOOP_NORMAL, 0);
  glock = FSOUND_Sample_Load (1, "singlegunshot.wav", FSOUND_NORMAL, 0);
  machine = FSOUND_Sample_Load (2, "metalmachinegun.wav", FSOUND_NORMAL, 0);
  shotgun = FSOUND_Sample_Load (3, "q3sg.wav", FSOUND_NORMAL, 0);
  death = FSOUND_Sample_Load (4, "malescream.wav", FSOUND_NORMAL, 0);
  explosion = FSOUND_Sample_Load (5, "implosion2.wav", FSOUND_NORMAL, 0);
  clipempty = FSOUND_Sample_Load (6, "clipempty.wav", FSOUND_NORMAL, 0);
  missionComp = FSOUND_Sample_Load (7, "miscom.wav", FSOUND_NORMAL, 0);
  glutJoystickFunc (JoyFunc, 0);
  
  FSOUND_PlaySound (10, heartbeat);
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
  
  if (button == GLUT_JOYSTICK_BUTTON_A)
  {
    joystick_buttonA = true;
    shooting = true;
    kick = true;
    //IF STATEMENT PREVENTS SOUND FROM OVERLAPPING TOO MUCH
    if (clipEmpty && framesModFPS > 15)
      FSOUND_PlaySound (16, clipempty);
  }

  //GLOCK
  else if (button == GLUT_JOYSTICK_BUTTON_B)
  {
    joystick_buttonB = true;
    selected = 0;
  }

  //MACHINE GUN
  else if (button == GLUT_JOYSTICK_BUTTON_C)
  {
    joystick_buttonC = true;
    selected = 1;
  }
  
  //SHOTGUN
  else if (button == GLUT_JOYSTICK_BUTTON_D)
  {
    joystick_buttonD = true;
    selected = 2;
  }

  keepMoving (leftRight, upDown);
 
	joystick_x = leftRight;
	joystick_y = upDown;
	joystick_z = throttle;
}



//==============================================================================
//CHECK TO SEE IF COLLIDING WITH CITY BOUNDS / SKYBOX WALLS
//==============================================================================
bool 
checkCityBounds (LVector4 campos)
{
  return (abs (campos.x) >= 5500 || abs (campos.z) >= 5500);    
}



//===============================================================================
//MAKE THE GUN MOVE WITH THE MOTION OF THE PERSON
//===============================================================================
void 
runMovement ()
{
  if (movement == 35)
  {
    moveDown = true;
    moveUp = false;
  }
  
  if (movement == 0)
  {
    moveUp = true;
    moveDown = false;
  }
  
    
  if (moveDown)
  {
    Guns[selected].MoveY(-.00099);
	  movement--;
	}
	
  if (moveUp) 
  {
    Guns[selected].MoveY(.00099);
	  movement++;
	}
}



//==============================================================================
//MAKE THE GUN KICK
//==============================================================================
void 
gunKick ()
{
 
    if (gunMovement == 1)
    {
      if (selected == 0)
        FSOUND_PlaySound (11, glock);
      else if (selected == 1)
        FSOUND_PlaySound (11, machine);
      else 
        FSOUND_PlaySound (11, shotgun);

      shotsRemaining--;
    }

  if (gunMovement == 0)
    BEGINMOVEMENT = true;
  else
    BEGINMOVEMENT = false;
  
  if (gunMovement == 16)
  {
    kick = false;
    gunMovement = 0;
    shooting = false;
  }
  
  if (kick)
  {
     if (gunMovement > 7)
     {
       moveBack = false;
       moveForward = true;
     }
  
     if (gunMovement <= 7)
     {
       moveBack = true;
       moveForward = false;
     }
      
     if (moveForward)
     {
       Guns[selected].MoveZ (-.039);
       Guns[selected].MoveY (-.020);
	     gunMovement++;
     }
	
     if (moveBack) 
     {
       Guns[selected].MoveZ (.039);
       Guns[selected].MoveY (.020);
	     gunMovement++;
	   }
  }
}



//===============================================================================
//ACTION  ACTION  ACTION  ACTION  ACTION  ACTION  ACTION  ACTION  ACTION  ACTION
//===============================================================================
void 
action () 
{
  LVector4 campos, prevpos, camrot;
  isCollision = false;
  
  //USED FOR PLAYING SOUNDS AND PREVENTING THEM FROM 
  //OVERLAPPING WHILE ONE IS PLAYING
  framesModFPS++;
  framesModFPS = framesModFPS % ((int) fps + 1);
  
  if (shotsRemaining <= 0)
  {
    //NO BULLETS LEFT MEANS CLIP IS EMPTY
    clipEmpty = true;
    
    //KEEPS THE AMMO REMAINING ON SCREEN FROM GOING NEGATIVE
    shotsRemaining = 0;
  }
   
  muopengl_camera.GetPosition (prevpos);
  glutForceJoystickFunc ();
  
  renderProperGun ();
   
  ms.Check_MouseState (muopengl, &muopengl_camera);
  muopengl_camera.Apply ();
  
  muopengl_camera.GetRotation (camrot);
  muopengl_camera.GetPosition (campos);
    
  Box.SetPosition (campos);
	Box.SetRotation (camrot);

  if (Box.Check_collision (city48) || checkCityBounds (campos))
	{
	  muopengl_camera.SetPosition (prevpos);
    Box.SetPosition (prevpos);
    muopengl_camera.Apply ();
    isCollision = true;
  }
  

  for (int i = 0; i < MAXTARGETS; i++)
  {
    if (Box.Check_collision (Targets[i]) && Targets[i].GetRenderEnable () == true)
    {
      muopengl_camera.SetPosition (prevpos);
      Box.SetPosition (prevpos);
      muopengl_camera.Apply ();
      isCollision = true;
    }
  }
  
  if (!(prevpos == campos) && kick == false)
	  runMovement ();
   
   if (shooting && !clipEmpty)
	 {
      gunKick ();

	    if (gunMovement == BEGINMOVEMENT) 
      {
	      int picked = RetrieveObjectID ();
	      dispObjNumKilled = picked;
	      picked -= 100;
	      LVector4 targetPosition;
	
           if (picked >= 0 && picked < MAXTARGETS)
	          if (!killed [picked]) 
            {
              Targets [picked].GetPosition (targetPosition);
              if (picked % 3 == 0)
                FSOUND_PlaySound (14, death);
              if (selected == 1)
                blood.set_size (128, 128);
              else if (selected == 2)
              {
                blood.set_size (256, 256);
                FSOUND_PlaySound (15, explosion);
              }
              else
                blood.set_size (64, 64);
	            
              blood.set_position (targetPosition);
	            blood.start ();
	            Targets [picked].RotateZ (90);
              Targets [picked].SetRenderEnable (false);
	            killed [picked] = true;
              targetsRemaining--;
              rivalsKilled++;
            }
	        //FSOUND_PlaySound(10, SoundShot);
	    } 
   }

    if (missionComplete)
    {
      soundPlayCounter++;
    }

   if (missionComplete && soundPlayCounter == 25)
   {
     FSOUND_PlaySound (16, missionComp);
   }
    
  light_pos [X] = campos.x;
	light_pos [Y] = campos.y;
	light_pos [Z] = campos.z;
	glLightfv (GL_LIGHT0, GL_POSITION, light_pos);
 
  glutPostRedisplay ();
}


//===============================================================================
//DRAW WINDOW ITEMS
//===============================================================================
void 
draw_window_items ()
{
	char mystring [100];

  if (splashTime < 200)
  {
    splash.drawFullScreenImage ();
    splashTime++;
  }
  
  else
  {
    glDisable (GL_LIGHTING);
	  glDisable (GL_DEPTH_TEST);
	  glLoadIdentity ();
	  glColor3f (1.0, 1.0, 0.0);

    if (!directions)
    {
      display.SetFont (font2);
      sprintf (mystring, "PRESS 'D' FOR ACTIONS MENU");
      display.DrawText (0.32, 0.10, 1, mystring);
    }

    fps = muopengl_get_framerate ();
    frameSpeed = fps * kSpeed;

    sprintf (mystring, "%d fps", (int)fps);
    display.SetFont (font3);
    glColor3f (0, 0, 0);
    display.DrawText (0.902, 0.902, 0, mystring);
    glColor3f (0, 1, 0.4);
    display.DrawText (0.9, 0.9, 0, mystring);
    
    display.SetFont (font3);
    if (directions)
    {
      display.SetFont (font3);

      sprintf (mystring, "'F1' GLOCK");
      display.DrawText (0.01, 0.06, 1, mystring);
  
      sprintf (mystring, "'F2' UZI");
      display.DrawText (0.01, 0.09, 1, mystring);

      sprintf (mystring, "'F3' SHOTGUN");
      display.DrawText (0.01, 0.12, 1, mystring);
    
      sprintf (mystring, "'Q' QUIT GAME");
      display.DrawText (0.01, 0.15, 1, mystring);

      sprintf (mystring, "'UP/DOWN ARROW = SPEED");
      display.DrawText (0.01, 0.18, 1, mystring);

      sprintf (mystring, "JOYSTICK BUTTONS");
      display.DrawText (0.01, 0.24, 1, mystring);

      sprintf (mystring, "'A' or '1' SHOOT SELECTED WEAPON");
      display.DrawText (0.01, 0.27, 1, mystring);

      sprintf (mystring, "'B' or '2' SELECT GLOCK");
      display.DrawText (0.01, 0.30, 1, mystring);

      sprintf (mystring, "'C' or '3' SELECT UZI");
      display.DrawText (0.01, 0.33, 1, mystring);

      sprintf (mystring, "'D' or '4' SELECT SHOTGUN");
      display.DrawText (0.01, 0.36, 1, mystring);

    }

    glColor3f (1.0, 1.0, 0.0);

    sprintf (mystring, "REMAINING: %d", targetsRemaining);
    display.DrawText (0.5, 0.75, 0, mystring);
    
    sprintf (mystring, "RIVAL MEMBERS KILLED: ");
    display.DrawText (0.15, 0.75, 0, mystring);
    
    sprintf (mystring, "AMMO REMAINING");
    display.DrawText (.83, 0.75, 0, mystring);
    
    display.SetFont (font4);
    glColor3f (1.0, 0.0, 0.0);
    //glEnable (GL_BLEND);

     float xPosMess = .15;
     float xPosMess2 = .15;
     float xPosMess3 = .15;
     char myChar = 'X';

    for (int count = 0; count < rivalsKilled; count++)
    {
      if (count < 5)
      {
        display.DrawCircle (xPosMess, .80, 0.02, 8);
        sprintf (mystring, "%c", myChar);
        display.DrawText (xPosMess, .815, 0, mystring);
        xPosMess += .05;
      }

      if (count > 4 && count < 10)
      {
        display.DrawCircle (xPosMess2, .87, 0.02, 8);
        sprintf (mystring, "%c", myChar);
        display.DrawText (xPosMess2, .885, 0, mystring);
        xPosMess2 += .05;
      }
    
      if (count > 9 && count < 15)
      {
        display.DrawCircle (xPosMess3, .94, 0.02, 8);
        sprintf (mystring, "%c", myChar);
        display.DrawText (xPosMess3, .955, 0, mystring);
        xPosMess3 += .05;
      }
    }
   
    //glDisable (GL_BLEND);

    if (shotsRemaining > 20)
      glColor3f (0.60, .20, 1.0);
    else if (shotsRemaining > 10)
      glColor3f (1.0, 1.0, 0.0);
    else
      glColor3f (1.0, 0.0, 0.0);

    sprintf (mystring, " %d ", shotsRemaining);
    display.DrawText (0.85, 0.80, 0, mystring);
    display.SetFont (font5);

    if (shotsRemaining == 0 && targetsRemaining > 0)
    {
      sprintf (mystring, "OUT OF AMMO");
      display.DrawText (0.51, 0.49, 0, mystring);
      sprintf (mystring, " MISSION FAILED");
      display.DrawText (0.51, 0.57, 0, mystring);
    }
    
    glColor3f (0.02, 1.0, 0.05);

    if (shotsRemaining >= 0 && targetsRemaining == 0)
    {
      sprintf (mystring, "MISSION COMPLETED");
      display.DrawText (0.47, 0.49, 0, mystring);
      sprintf (mystring, "YOU RECLAIMED THE HOOD");
      display.DrawText (0.45, 0.57, 0, mystring);
      missionComplete = true;      
    }

    display.SetFont (font4);
    glColor3f (1.0, 1.0, 0.0);        
    
	  sprintf (mystring, "SHAWN ENGLERTH - THE GHETTO");
	  display.DrawText (0.5, 0.05, 0, mystring);

    crosshair.drawFullScreenImage();
    //display.DrawTexture (0.01, 0.89 , 0.2, 0.95, 42);
	  glEnable (GL_LIGHTING);
	  glEnable (GL_DEPTH_TEST);
  }

	glutSwapBuffers (); 
}



//===============================================================================
//MYDISPLAY 
//===============================================================================
void 
myDisplay (void)
{
  LVector4 myPosition;
  muopengl_camera.GetPosition (myPosition);

	glMatrixMode (GL_MODELVIEW);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	muopengl_camera.Render ();

  glInitNames();									
	glPushName(0);
	
	glLoadName (99);
	city48.Render ();
	glEnd ();
	
  for (int i = 0; i < MAXTARGETS; i++)
	{
    glLoadName (100 + i);
	  Targets[i].Render ();
    glEnd ();
	}
	
  glPopName ();

  Box.Render ();
  //World.Render ();
	mySkybox.Render ();
  
  blood.update (&muopengl_camera);

  draw_window_items ();
  //glutSwapBuffers ();
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



//===============================================================================
//MY SPECIAL KEYBOARD
//===============================================================================
void 
myspecialkybd (int theKey, int mouseX, int mouseY)
{
		GLint x = mouseX;
		GLint y = mouseY; 
		
		switch (theKey)
		{		 
			  case GLUT_KEY_UP:
          if (ms.GetMouseSensitivity () < 5)
				    ms.SetMouseSensitivity (ms.GetMouseSensitivity () + 0.40);
				  if (kSpeed < .05)
				    kSpeed += .002;
				break;
			  
			  case GLUT_KEY_DOWN:
           if (ms.GetMouseSensitivity () > 0)
				     ms.SetMouseSensitivity (ms.GetMouseSensitivity () - 0.40);
				   if (kSpeed > 0)
				     kSpeed -= .002;
				break;
			  
			  case GLUT_KEY_LEFT:
				  tilt += PI / 90;
				  //muopengl_camera.MoveX(-1.0);
			  break;
			  
			  case GLUT_KEY_RIGHT: 
				  tilt -= PI / 90;
				  //muopengl_camera.MoveX(1.0);
			  break;
			  
			  case GLUT_KEY_F1: 
					selected = 0;
				break;
			  
			  case GLUT_KEY_F2: 
				  selected = 1;
				break;
			  
			  case GLUT_KEY_F3: 
					selected = 2;
				break;
	  		
	  		default: 
					//printf ("key hit is %d\n", theKey);
		  break;		      // do nothing
		}
}



//===============================================================================
//MY KEYBOARD
//===============================================================================
void 
myKeyboard (unsigned char theKey, int mouseX, int mouseY)
{
  GLint x = mouseX;
	GLint y = mouseY; 
	
  //HIT THE ESCAPE KEY TO QUIT
  if ( (int)theKey == 27)
			exit (-1);	


		switch (theKey)
		{		 		
      //HIT THE SPACE BAR TO SHOOT THE GUN
      case ' ':
			  printf ("The Space Bar was Hit");
        shooting = true;
        kick = true;
        if (clipEmpty && framesModFPS > 15)
          FSOUND_PlaySound (16, clipempty);
     
      break;
      
      //TERMINATE THE PROGRAM ABRUPTLY
      case 'Q':
        exit (-1);  
      
      //TERMINATE THE PROGRAM ABRUPTLY
      case 'q':
			  exit(-1);		
      
      //TERMINATE THE PROGRAM ABRUPTLY
      case 'D':
        directions = !directions; 
      break;
      
      //TERMINATE THE PROGRAM ABRUPTLY
      case 'd':
			  directions = !directions; 		
      break;

      //DO NOTHING
      default:      
        break;		      	
		}
}



//===============================================================================
//PASSIVE MOUSE MOVE
//===============================================================================
void 
passiveMouseMove (int x, int y) 
{ 
  ms.x = x; ms.y = y;
}



//===============================================================================
//ACTIVE MOUSE MOVE
//===============================================================================
void 
activeMouseMove (int x, int y) 
{ 
  ms.x = x; ms.y = y;
}



//===============================================================================
//MOUSE
//===============================================================================
void 
mouse (int button, int state, int x, int y) 
{
   //RESPOND TO MOUSE BUTTON PRESSES.
  //IF BUTTON1 PRESSED, MARK THIS STATE SO WE KNOW IN MOTION FUNCTION.
  switch (button) 
  {
    case GLUT_LEFT_BUTTON:
      switch (state) 
      {
        case GLUT_UP:
          ms.btnOne = MUopengl_MouseState::UP;
          break;
        case GLUT_DOWN:
          ms.btnOne = MUopengl_MouseState::DOWN;
          break;
      }
      break;
  
    case GLUT_MIDDLE_BUTTON:
      switch (state) 
      {
        case GLUT_UP:
          //ms.btnTwo = MUopengl_MouseState::UP;
          break;
        case GLUT_DOWN:
          //ms.btnTwo = MUopengl_MouseState::DOWN;
          break;
      }
      break;
      
    case GLUT_RIGHT_BUTTON:
      switch (state) 
      {
        case GLUT_UP:
          //ms.btnThree = MUopengl_MouseState::UP;
          break;
        case GLUT_DOWN:
          //ms.btnThree = MUopengl_MouseState::DOWN;
          break;
      }
      break;
  }
  
  if (state == GLUT_DOWN) 
    action ();
}



//===============================================================================
//RESHAPE
//===============================================================================
/* Tell GLUT what to do if the window is reshaped: */
void 
reshape (int width, int height) 
{
	actual_screen_width = width;
	actual_screen_height = height;
	aspect_ratio = actual_screen_width / actual_screen_height;	
	glViewport(0, 0, (GLsizei) width, (GLsizei) height); 
  muopengl_init (&muopengl, width, height);
	muopengl_camera.Initialize (90.0, aspect_ratio, 0.1, 10000);
	printf ("Actual Window width is %d height is %d \n", width, height);
	display.Initialize (width, height);
}



//===============================================================================
//MAIN
//===============================================================================
int 
main (int argc, char** argv)
{	
  srand ( time (0) );
	glutInit (&argc, argv);          // initialize the GLUT toolkit
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow ("Shawn Englerth Path Game"); // open the screen window
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


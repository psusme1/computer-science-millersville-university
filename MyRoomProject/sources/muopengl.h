/***********************************************************************
				muopengl API 
************************************************************************
*  Filename  muopengl.h
*  Authors:  Roger Webster, Ph.D. 
*  Place: MILLERSVILLE UNIVERSITY
*  Graphics Package:   OpenGL
*  Info can be found on Internet World Wide Web server (WWW) site:
*	 http://cs.millersville.edu/~webster/cs375/
*  Modification history
10-21-2002 RWW created this muopengl.h 
10-21-2002 RWW added Josh Boyd's camera class to muopengl (first extra credit!)
11-03-2002 RWW added Lev Povalahev's Lmatrix, LMoveable, LVector classes
11-03-2002 RWW made some modifications
11-05-2002 RWW and Dan Hollinger added the 3ds loader stuff
11-07-2002 RWW added 3ds create_texture for TGAs and BMPs
11-10-2002 RWW made some modifications to createtexture and load3ds
11-15-2002 RWW added Josh Boyd's mousestate to this
12-04-2002 RWW added Rod Shenks LODnode and Monique Heneke's Stretch
12-06-2002 RWW added Julie Sumpf's path class
02-07-2003 NEC merged Nate Good's collidable object
09-05-2003 RdS added Display class
*************************************************************************/
#ifndef		__muopengl_H__
# define	__muopengl_H__

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>


#include "../gl/glut.h"

#include "MUArray.h"
#include "coldet_headers/coldet.h"

using namespace std;

#define MAX(a,b) ((a < b) ? (b) : (a))
#define SQR(a) ((a)*(a))
#define RADIANS 57.29577951
#define X 0
#define Y 1
#define Z 2
#ifndef PI
#define PI 3.1415926535897932384626433832795028841971
#endif
#define FALSE 0
#define TRUE 1


typedef unsigned int UINT;

/*************************************************************************/
//------------------------------------------------
//  Math functions
//------------------------------------------------
//originally written by Lev Povalahev
float Clamp(float value, float min, float max);
void Swap(float &a, float &b);
float Det2x2(float a1, float a2, float b1, float b2);
float Det3x3(float a1, float a2, float a3,
             float b1, float b2, float b3,
             float c1, float c2, float c3);

/*************************************************************************/
//originally written by Lev Povalahev
struct LVector2
{
    LVector2();
    LVector2(const LVector2 &v);
    LVector2(const float newx, const float newy);
    LVector2(const float *xy);
    bool operator==(const LVector2 &v);
    LVector2 & operator*=(const float &value);
    LVector2 & operator+=(const LVector2 &v);
    LVector2 & operator-=(const LVector2 &v);
    float & operator[](int i);
    const float operator[](int i) const;
    union 
    {
        struct 
        {
            float x, y;
        };
        struct
        {       
            float u, v;
        };
        struct
        {
            float s, t;    
        };
        float array[2];
    };
};

/*************************************************************************/
// a 3-dimensional vector
//originally written by Lev Povalahev
struct LVector3
{
    LVector3();
    LVector3(const LVector3 &v);
    LVector3(const float newx, const float newy, const float newz);
    LVector3(const float *xyz);
    bool operator==(const LVector3 &v);
    LVector3 & operator*=(const float &value);
    LVector3 & operator+=(const LVector3 &v);
    LVector3 & operator-=(const LVector3 &v);
    float & operator[](int i);
    const float operator[](int i) const;
    LVector3 & Normalize();
    LVector3 GetNormalized();
    float Length();
    float DotProduct(LVector3 &v);
    LVector3 CrossProduct(LVector3 &v);
    LVector3 operator+(const LVector3 &v);
    LVector3 operator-(const LVector3 &v);
	LVector3 Vector(LVector3 vPoint1, LVector3 vPoint2);
	LVector3 CrossProduct(LVector3 &v1, LVector3 &v2);
	LVector3 operator /(float amount) const;

   union 
    {
        struct 
        {
            float x, y, z;
        };
        struct
        {       
            float u, v, w;
        };
        struct
        {
            float s, t, r;    
        };
        struct
        {
            float red, green, blue;
        };
        float array[3];
    };
};

/*************************************************************************/
// a 4-dimensional vector (used for 3d homogenous coordinates)
//originally written by Lev Povalahev
struct LVector4
{
    LVector4();
    LVector4(const LVector4 &v);
    LVector4(const float newx, const float newy, const float newz, const float neww = 1);
    LVector4(const float *xyzw);
    bool operator==(const LVector4 &v);
    LVector4 & operator*=(const float &value);
    LVector4 operator*(const float &value);
    LVector4 & operator+=(const LVector4 &v);
    LVector4 & operator-=(const LVector4 &v);
    float & operator[](int i);
    operator const float*() const;
    operator float*();
    const float operator[](int i) const;
    LVector4 & Normalize();
    LVector4 GetNormalized();
    float Length();
    float DotProduct(LVector4 &v);
    LVector4 CrossProduct(LVector4 &v);
    LVector4 operator+(const LVector4 &v);
    LVector4 operator-(const LVector4 &v);
	LVector4 operator+(const LVector4 &v) const;
	LVector4 operator-(const LVector4 &v) const;
    LVector4 &Homogenize();
	LVector4 operator/(const float &value);
	LVector4 operator+(const float &value);
	LVector4 operator-(void);
    union 
    {
        struct 
        {
            float x, y, z, w;
        };
        struct
        {
            float s, t, r, q;    
        };
        struct
        {
            float red, green, blue, alpha;
        };
        float array[4];
    };
};

/*************************************************************************/
//originally written by Lev Povalahev
struct LMatrix4
{
    LMatrix4();
    LMatrix4(const LMatrix4 &m);
    LMatrix4(const float *m);
    float & operator[](int i);
    LMatrix4 & operator=(const float *m);
    const float operator[](int i) const;
    operator const float*() const;
    operator float*();
    LMatrix4 & operator*=(const LMatrix4 &m);
    LMatrix4 operator*(const LMatrix4 &m) const;
    LVector4 operator*(const LVector4 &v) const;
    LVector4 & Transform(LVector4 &v) const;
    LMatrix4 operator+(const LMatrix4 &m);
    LMatrix4 operator-(const LMatrix4 &m);
    LMatrix4 & BuildFromEuler(const LVector4 &angles);
    int ConvertToEuler(LVector4 &angles) const;
    LMatrix4 & SetIdentity();
    LMatrix4 & Transpose();
    LMatrix4 GetInverse();
    LMatrix4 & Inverse();
    LMatrix4 & Translate(const LVector4 &v);
    LMatrix4 & SetTranslation(const LVector4 &v);
    float Det();
    union
    {
        struct
        {
            float a00, a10, a20, a30,
                  a01, a11, a21, a31,
                  a02, a12, a22, a32,
                  a03, a13, a23, a33;
        };
        float array[16];
    };
};

/*************************************************************************/
//originally written by Lev Povalahev
struct LMatrix3
{
    LMatrix3();
    LMatrix3(const LMatrix3 &m);
    LMatrix3(const float *m);
    float & operator[](int i);
    LMatrix3 & operator=(const float *m);
    const float operator[](int i) const;
    operator const float*() const;
    operator float*();
    LMatrix3 & operator*=(const LMatrix3 &m);
    LMatrix3 operator*(const LMatrix3 &m);
    LVector3 operator*(const LVector3 &v);
    LVector3 & operator*(LVector3 &v);
    LMatrix3 operator+(const LMatrix3 &m);
    LMatrix3 operator-(const LMatrix3 &m);
    LMatrix3 & BuildFromEuler(const LVector3 &angles);
    int ConvertToEuler(LVector3 &angles);
    LMatrix3 & SetIdentity();
    LMatrix3 & Transpose();
    LMatrix3 GetInverse();
    LMatrix3 & Inverse();
    float Det();
    union 
    {
        struct
        {
            float a00, a10, a20,
                  a01, a11, a21,
                  a02, a12, a22;
        };
        float array[9];
    };
};

/*************************************************************************/
//originally written by Lev Povalahev
class LMoveable
{
public:
    // default construtor
    LMoveable();
    // copy constuctor
    LMoveable(const LMoveable &m);
    // destructor
    virtual ~LMoveable();
    // resets the position for (0, 0, 0) and rotation to (0, 0, 0)
    void Reset();
    // moves the object along the local Z axis
    void MoveZ(float value);
    // moves the object along the local Y axis
    void MoveY(float value);
    // moves the object along the local X axis
    void MoveX(float value);
    void Move(const LVector4 &v);

	//RWW added these, they do what u think they should do!
	void Pitch(float angle);
 	void Yaw(float angle);
	void Roll(float angle);
	void MoveForward(float value);
    void RotateX(float angle);
    // rotates the object around the y axis
    void RotateY(float angle);
    // rotates the object arounf the z axis
    void RotateZ(float angle);
    void Rotate(const LVector4 &angles);
    virtual LVector4 & GetRotation(LVector4 &v) const;
    virtual LVector4 & GetPosition(LVector4 &v) const;
    void SetRotation(const LVector4 &angles);
    void SetPosition(const LVector4 &pos);
    void SetMatrix(const LMatrix4 &m);
    virtual LMatrix4 & GetMatrix(LMatrix4 &m) const;
    // finally, this method applies all the operations
    void Apply();
    // returns true if gimbal lock has occured last frame
    bool GetGimbalLock() const;
protected:
    // the position(translation) of the object
    LVector4 m_position;
    // the rotation of the object
    LVector4 m_rotation;
    // the position(translation) change for the next frame
    LVector4 m_newPosition;
    // the rotation change for the next frame
    LVector4 m_newRotation;
    // the matrix describing the position/rotation
    LMatrix4 m_matrix;
    // used internally
    bool m_gimbalLock;
};

/*************************************************************************/
//originally written by Lev Povalahev
class LCamera : public LMoveable
{
public: 
    // the default constuctor 
    LCamera();
    virtual ~LCamera();

	LVector4 NormalVectorForward(); // Ryan Brown added 12-03-2002 
    void Initialize(float fov, float aspect, float near_p, float far_p);
    void SetFov(float value);
    void Render();
    void BindToObject(LMoveable *object);
    LMatrix4 & GetMatrix(LMatrix4 &m) const;
    LVector4 & GetRotation(LVector4 &v) const;
    LVector4 & GetPosition(LVector4 &v) const;
protected: 
    float m_farplane;
    float m_nearplane;
    float m_aspect;
    float m_fov;
    LMoveable *m_object;
protected: 
};

LCamera *ActiveCamera();

/*************************************************************************/
//Originally Written by Ryan Brown
class MUnode : public LMoveable
{
	public:
		int numHits;	//Number of collisions
		bool active;				
		float speed,	// Individual speed  
			  radius;	//The radius of the MUnode (bounding sphere) for collision detect

		MUnode();
		bool  AddHit(void);
		void  setHits(int n);
		int   getHits(void);
		bool  get_isactive(void);
		void  set_isactive(bool a);
		void  getPosition(float *x, float *y, float *z);
		void  setPosition(float x, float y,float z);
		float getSpeed(void);
		void  setSpeed(float sp);
		float getRadius(void);
		void  setRadius(float myradius);
};

/*************************************************************************/
typedef struct muopengl_struct {

	float actual_screen_width;
	float actual_screen_height;

} muopengl_info;

/*************************************************************************/
void muopengl_init(muopengl_info *muopengl, float width, float height);
float muopengl_get_framerate(void);

double muopengl_degrees2radians(double numdegrees);
double muopengl_radians2degrees(double radians);
void muopengl_version_date(char *build);

float muopengl_euclidean_dist(LVector4 pos1, LVector4 pos2);
float muopengl_sumofsquares_dist(LVector4 pos1, LVector4 pos2);
bool muopengl_spherical_collision_detect(MUnode munode1, MUnode munode2);

/*************************************************************************/
//RWW added Josh Boyd's mouse 11-15-2002
class MUopengl_MouseState{
public:

	enum BS {DOWN, UP};
	BS btnOne, btnTwo, btnThree;
	int x, y;
	float move_amount; //movement sensitivity
	float rot_amount;  //rotation sensitivity

	MUopengl_MouseState();
	void Check_MouseState(muopengl_info muopengl, LCamera *muopengl_camera);
	void SetMouseSensitivity(float s);
	float GetMouseSensitivity(void);
};

/*************************************************************************/
// 3ds stuff 11-05-2002
#define MAX_TEXTURES 100			// The maximum amount of textures to load
// This is our face structure.  This is is used for indexing into the vertex 
// and texture coordinate arrays.  From this information we know which vertices
// from our vertex array go to which face, along with the correct texture coordinates.
struct tFace
{
	int vertIndex[3];			// indicies for the verts that make up this triangle
	int coordIndex[3];			// indicies for the tex coords to texture this face
};

// This holds the information for a material.  It may be a texture map of a color.
// Some of these are not used, but I left them because you will want to eventually
// read in the UV tile ratio and the UV tile offset for some models.
struct tMaterialInfo
{
	char  strName[255];			// The texture name
	char  strFile[255];			// The texture file name (If this is set it's a texture map)
	BYTE  color[3];				// The color of the object (R, G, B)
	int   texureId;				// the texture ID
	float uTile;				// u tiling of texture  (Currently not used)
	float vTile;				// v tiling of texture	(Currently not used)
	float uOffset;			    // u offset of texture	(Currently not used)
	float vOffset;				// v offset of texture	(Currently not used)
} ;

// This holds all the information for our model/scene. 
// You should eventually turn into a robust class that 
// has loading/drawing/querying functions like:
// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
struct t3DObject 
{
	int  numOfVerts;			// The number of verts in the model
	int  numOfFaces;			// The number of faces in the model
	int  numTexVertex;			// The number of texture coordinates
	int  materialID;			// The texture ID to use, which is the index into our texture array
	bool bHasTexture;			// This is TRUE if there is a texture map for this object
	char strName[255];			// The name of the object
	LVector3  *pVerts;			// The object's vertices
	LVector3  *pNormals;		// The object's normals
	LVector2  *pTexVerts;		// The texture's UV coordinates
	tFace *pFaces;				// The faces information of the object
};

// This holds our model information.  This should also turn into a robust class.
// We use STL's (Standard Template Library) vector class to ease our link list burdens. :)
struct t3DModel 
{
	int numOfObjects;					// The number of objects in the model
	int numOfMaterials;					// The number of materials for the model
	vector<tMaterialInfo> pMaterials;	// The list of material information (Textures and colors)
	vector<t3DObject> pObject;			// The object list for our model
};

//>------ Primary Chunk, at the beginning of each file
#define PRIMARY       0x4D4D

//>------ Main Chunks
#define OBJECTINFO    0x3D3D				// This gives the version of the mesh and is found right before the material and object information
#define VERSION       0x0002				// This gives the version of the .3ds file
#define EDITKEYFRAME  0xB000				// This is the header for all of the key frame info

//>------ sub defines of OBJECTINFO
#define MATERIAL	  0xAFFF				// This stored the texture info
#define OBJECT		  0x4000				// This stores the faces, vertices, etc...

//>------ sub defines of MATERIAL
#define MATNAME       0xA000				// This holds the material name
#define MATDIFFUSE    0xA020				// This holds the color of the object/material
#define MATMAP        0xA200				// This is a header for a new material
#define MATMAPFILE    0xA300				// This holds the file name of the texture

#define OBJECT_MESH   0x4100				// This lets us know that we are reading a new object

//>------ sub defines of OBJECT_MESH
#define OBJECT_VERTICES     0x4110			// The objects vertices
#define OBJECT_FACES		0x4120			// The objects faces
#define OBJECT_MATERIAL		0x4130			// This is found if the object has a material, either texture map or color
#define OBJECT_UV			0x4140			// The UV texture coordinates

// Here is our structure for our 3DS indicies (since .3DS stores 4 unsigned shorts)
struct tIndices {							

	unsigned short a, b, c, bVisible;		// This will hold point1, 2, and 3 index's into the vertex array plus a visible flag
};

// This holds the chunk info
struct tChunk
{
	unsigned short int ID;					// The chunk's ID		
	unsigned int length;					// The length of the chunk
	unsigned int bytesRead;					// The amount of bytes read within that chunk
};

// This class handles all of the loading code
class CLoad3DS
{
public:
	CLoad3DS();								// This inits the data members

	// This is the function that you call to load the 3DS
	bool Import3DS(t3DModel *pModel, char *strFileName);

private:
	// This reads in a string and saves it in the char array passed in
	int GetString(char *);

	// This reads the next chunk
	void ReadChunk(tChunk *);

	// This reads the next large chunk
	void ProcessNextChunk(t3DModel *pModel, tChunk *);

	// This reads the object chunks
	void ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *);

	// This reads the material chunks
	void ProcessNextMaterialChunk(t3DModel *pModel, tChunk *);

	// This reads the RGB value for the object's color
	void ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk);

	// This reads the objects vertices
	void ReadVertices(t3DObject *pObject, tChunk *);

	// This reads the objects face information
	void ReadVertexIndices(t3DObject *pObject, tChunk *);

	// This reads the texture coodinates of the object
	void ReadUVCoordinates(t3DObject *pObject, tChunk *);

	// This reads in the material name assigned to the object and sets the materialID
	void ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk);
	
	// This computes the vertex normals for the object (used for lighting)
	void ComputeNormals(t3DModel *pModel);

	// This frees memory and closes the file
	void CleanUp();
	
	// The file pointer
	FILE *m_FilePointer;
	
	// These are used through the loading process to hold the chunk information
	tChunk *m_CurrentChunk;
	tChunk *m_TempChunk;
};

//----------------------------------------------------------------------
//RWW 11-07-2002
//----------------------------------------------------------------------
void muopengl_Create_TGA_Texture(UINT textureArray[], char *strFileName, int textureID);

//------------------------------------------------------------
//    Error Codes
//------------------------------------------------------------
#define ERR_FILE_OPEN_ERR           2000
#define ERR_FILE_ALREADY_OPENED     2001
#define ERR_FILE_CLOSE_ERR          2002
#define ERR_FILE_READ_ERR           2003
#define ERR_FILE_WRITE_ERR          2004
#define ERR_WRONG_FILE_FORMAT       2005
#define ERR_UNSUPPORTED_IMAGE_TYPE  2006
#define ERR_NO_FILENAME_SPECIFIED   2007
#define ERR_FATAL_ERR               2008
//------------------------------------------------------------
//    if this is defined warnings are treated as errors
//------------------------------------------------------------
//#define WARNINGS_AS_ERRORS
//------------------------------------------------------------
//    File format identifiers
//------------------------------------------------------------
#define LMESH                       4000
#define LTRIANGULATION              4001
#define LSHADER                     4002
#define LLIGHT                      4003
#define LMATERIAL                   4004
#define LSKYBOX                     4005
//------------------------------------------------------------
//    Global functions
//------------------------------------------------------------
void StatusMsg(const char *fmt, ...);
void WarningMsg(const char *fmt, ...);
void ErrorMsg(const char *fmt, ...);
unsigned int GetNextTextureName();
unsigned int GetNextDisplayListID();
int GetWarningCount();

/*************************************************************************/
//originally written by Lev Povalahev
class LString
{
public: 
    //  a default constructor 
    LString();
    // a destructor, frees the "real" string 
    virtual ~LString();
    // a copy constructor 
    LString(const LString &s);
    // Construct a string from a char * 
    LString(const char *value);
    // Constucts a string containing only the character 
    LString(char c);
 	//RWW added method 
	void Print() const;
	// returns the length of the string 
    int Length() const;
    // returns a pointer to a C string 
    const char* c_str() const;
    // Assigns a copy of str to the string 
    LString& operator=(const char *str);
    // Assign a copy of str to the string 
    LString& operator=(const LString &str);
    // appends str to the string 
    LString& operator+=(const LString &str);
    // returns the char at position i or 0 if i is beyond the end of the string 
    char operator[](int i) const;
    // Truncates the string so that newlen is the new length, if newlen is beyond the 
    // string nothing happenes 
    void Truncate(int newlen);
    // Fills len first characters of the string with c if len is -1 or beyond the
    //    string length the entire string is filled 
    void Fill(char c, int len = -1);
    // Appends str to the string, the same as operator+= 
    LString& Append(const LString& str);
    // returns the char at position i or 0 if i is beyond the string length 
    char At(int i) const;
    // returns true if the string is empty, false if not, so
    // you can write if (!s) 
    bool operator!() const;
    // compared str with the string and returns 0, >0 or <0, see
    // strcmp for details 
    int Compare(const LString & str) const;
    // Compares the strings and returns 0, <0 or >0 the same as strcmp 
    static int Compare(const LString &s1, const LString &s2);
    // inserts str into string at position pos, if pos extends 
    // the length of the string the string is appended
    LString& Insert(int pos, const LString & str);
    // Insert c at position pos 
    LString& Insert(int pos, char c);
    // The same as insert(0, c) 
    LString& Prepend(char c);
    // the same as Insert(0, str) 
    LString& Prepend(const LString & str);
    // find the first occureance of str in the string and return its position, or
    // -1 if str was not found in the string 
    int Find(const LString &str, int index=0) const;
    // same as Find ((LString)str,index) 
    int Find(const char *str, int index=0) const;
    // returns the len charachters starting from the left 
    LString Left(int len) const;
    // returns len rightmost characters of the string 
    LString Right(int len) const;
    // returns the characters startting from pos and of len length 
    LString Mid(int pos, int len) const;
    // replace characters starting from pos using str,
    // if pos is beyond the length of the string str is appended
    LString& Replace(int pos, const LString &str);
    // removes characters from pos to pos+len, if pos is beyond the string end
    // nothing happens, if len is too large the string is truncated to pos length 
    LString& Remove(int pos, int len);
    // converts all alphabet characters to lower case (no international
    // characters support, only latin characters are supported ( codes 
    LString& LowerCase();
	// converts all alphabet characters to upper case (no international
    // characters support, only latin characters are supported ( codes 
    LString& UpperCase();
    // builds a formatted string 
    static LString sprintf(char *fmt, ...);
protected: // Protected attributes
    // This is the actual string 
    char *m_string;
    // This variable holds the number of allocated bytes for m_string 
    int m_allocatedbytes;
};

//-------------------------------------------------------
LString operator+(const LString &s1, const LString &s2);
LString operator+(const char *s1, const LString &s2);
LString operator+(const LString &s1, const char *s2);
//-------------------------------------------------------
bool operator==(const LString &s1, const LString &s2);
bool operator==(const char *s1, const LString &s2);
bool operator==(const LString &s1, const char *s2);
//-------------------------------------------------------
bool operator!=(const LString &s1, const LString &s2);
bool operator!=(const char *s1, const LString &s2);
bool operator!=(const LString &s1, const char *s2);
//-------------------------------------------------------
bool operator<=(const char *s1, const LString &s2);
bool operator<=(const LString &s1, const char *s2);
//-------------------------------------------------------
bool operator>=(const char *s1, const LString &s2);
bool operator>=(const LString &s1, const char *s2);
//-------------------------------------------------------
bool operator<(const char *s1, const LString &s2);
bool operator<(const LString &s1, const char *s2);
//-------------------------------------------------------
bool operator>(const char *s1, const LString &s2);
bool operator>(const LString &s1, const char *s2);
LString GetFullFileName(const LString &filename);       
LString GetFileExtention(const LString &filename);
LString GetFilePath(const LString &filename);
LString GetRelativeFilePath(const LString &from, const LString &to);

//RWW added these enum types 11-08-2002
enum LOpenMode {LOpenRead, LOpenWrite, LOpenWriteAppend, LOpenReadWrite};
enum LSeekMode {LSeekStart, LSeekEnd, LSeekCursor};
typedef unsigned int uint;

/*************************************************************************/
class LIOStream
{
public:
    // default constructor
    LIOStream();
    // constructor with a filename
    LIOStream(LString filename, LOpenMode mode = LOpenRead);	 
    // destructor
    ~LIOStream();
    /** returns Opened */
    bool IsOpened();
    /** opens the file filename (binary mode) */
    int Open(LString filename, LOpenMode mode);
    /** closes the file stream */
    int Close();
    /** assign stream to the object, if there is an opened file ERR_FILE_ALREADY_OPENED is returned */
    int AssignStream(FILE *stream);
    /** returns the current cursor position */
    long Pos();
    /** Seek sets the file position cursor. mode is either
    Start, End or Cursor, respectively setting position from the
    beginning of the file, the end of the file and from the current cursor position
    returns -1 upon error */
    int Seek(long offset, LSeekMode mode = LSeekCursor);
    /** returns true if EOF is set */
    bool Eof();
    /** reads size*count bytes from the file into ptr
    returns false if something has gone wrong, true upon success */
    bool Read(void *ptr, uint size, uint count);
    /** writes size*count bytes from ptr to file */
    bool Write(const void *ptr, uint size, uint count);
    /** reads an integer and returns it */
    int ReadInt();
    /** writes i to file, returns true upon success */
    bool WriteInt(const int i);
    /** reads the character from the file and returns it */
    char ReadChar();
    /** write c to the file and returns true upon success */
    bool WriteChar(const char c);
    /** reads a 16 bit value from the file and returns it */
    short ReadShort();
    /** writes a 2 byte value to the file */
    bool WriteShort(const short s);
    /** writes d to the file and returns true upon success */
    bool WriteDouble(const double d);
    /** reads a double value from te file and returns it */
    double ReadDouble();
    /** writes f to the file and returns true upon success */
    bool WriteFloat(const float f);
    /** reads the float value from the file and returns it */
    float ReadFloat();
    /** write a long double value to the file and returns true upon success */
    bool WriteLongDouble(const long double d);
    /** reads a long double value from the file and returns it */
    long double ReadLongDouble();
    /** writes a long long value to the file and returns true upon success */
//RWW    bool WriteLongLong(const int64 l);
    /** reads a long long from the file and returns it */
//RWW    int64 ReadLongLong();
    /** reads the string from the file and returns it */
    LString ReadString();
    /** reads the string from the file and returns it */
    bool WriteString(const LString s);
    /** writes c characters from s to the file and returns true upon success */
    bool WriteString(const LString s, uint c);
    /** reads c chars from the file and builds a string from them */
    LString ReadString(uint c);
    /** returns the file size in bytes */
    uint GetFileSize();
protected: // Protected attributes
    /** true if the file was opened in the constructor of in the open function */
    bool m_opened;
    /** the file stream */
    FILE* m_file;
private:
    // copy constructor is not good, so prohibit it
    LIOStream(const LIOStream &s)
    {
        // simply nothing
    }
    // assignment operator is also bad for files
    LIOStream& operator=(const LIOStream &s)
    {
        return *this;
    }
};

/*************************************************************************/
//originally written by Lev Povalahev
class LLoadable
{
public: 
    LLoadable();
    virtual ~LLoadable();
    int LoadFromFile(LString filename);
    virtual int LoadFromStream(LIOStream &s) = 0;
    int Reload();
    virtual void Unload() = 0;
    bool IsLoaded();
protected: // Protected attributes
    /** this is the last filename the object was loaded from */
    LString m_loadFilename;
    /** true if the object has been loaded */
    bool m_loaded;
};

/*************************************************************************/
//RWW added these
enum LImageType {LImageUndefined, LImageRGB, LImageRGBA, LImageGrayscale};
//originally written by Lev Povalahev
class LImage : public LLoadable
{
public: 
    LImage();
    virtual ~LImage();
    /** reimplemented from LLoadable */
    void Unload();
    int GetAlphaBits();
    byte* GetPixels();
    int GetImageHeight();
    int GetImageWidth();
    int GetPixelDepth();
    LImageType GetImageType();
    // converts the image 8 bit greyscale image
    void Greyscale();
    // converts teh image to the normal map as needed by per-pixel lighting
    void ConvertToNormalMap();
    // scales the normal map down by 1/2 (used for mipmapping)
    void ScaleDownNormalMap();
    // returns a pixel at a given position
    inline byte* GetPixel(int w, int h);
    // smoothes the image 
    void Smooth();
protected: // Protected attributes
    /** this is the pixel buffer -> the image */
    byte *m_pixels;
    /** the pixel depth of the image, including the alpha bits */
    int m_pixelDepth;
    /** the depth of the alpha bitplane */
    int m_alphaBits;
    /** the image height */
    int m_height;
    /** the width of the image */
    int m_width;
    /** image type, either rgb, rgba or greyscale */
    LImageType m_type;
};

/*************************************************************************/
//originally written by Lev Povalahev
class LTGA : public LImage
{
public: 
    LTGA();
    LTGA(LString filename);
    virtual ~LTGA();
    // reimplemented from LLoadable 
   int LoadFromStream(LIOStream &s);

   //rds put into toolkit 09-03-2003
   void LoadTgaFile(char * strFileName);

   //rww and Josh Boyd added these 12-03-2002
   void tgaLoadFromFile(LString filename);
   void drawFullScreenImage();
   void createKeyedMask(GLubyte r, GLubyte g, GLubyte b);
   bool keyedmask; // initially set to false
   GLubyte * mask;
   //NEC, SJS, KAB added 03-10-2003
   void createTransparency(int value);
};

/*************************************************************************/
//originally written by Dan Hollinger
typedef struct MURectangle {
	float fleft;
	float fright;
	float fnear;
	float ffar;
	float flow;
	float fhigh;
} MURect;

/*************************************************************************/
//originally written by Dan Hollinger
class Model3DS : public MUnode
{
public:
	Model3DS(char *strFileName);
	Model3DS();
	bool LoadObject(char *strFileName);
	bool LoadObject(char *strFileName, GLubyte r, GLubyte g, GLubyte b);
	bool LoadObjectTransparent(char *strFileName, int transparent_amount);
	bool Render(GLint blend_mode = GL_MODULATE);
	void SetViewMode(int mode) {m_ViewMode = mode;};
	int GetViewMode() const {return m_ViewMode;};

	void SetBoundRect(float leftBound, float rightBound, float nearBound, float farBound, float lowerBound, float upperBound);
	void SetBoundRect(const MURect& src);
	void SetMinBoundRect();
	MURect& GetBoundRect();
	void SetScale(double amt) {m_Scale = amt;};
	double GetScale() const {return m_Scale;};
	void SetDrawBoundary(bool db); //RWW here
	bool GetDrawBoundary(void); //RWW here
	bool drawBounds;
	void SetRenderEnable(bool enable);
	bool GetRenderEnable();
	void SetWireMode(bool wm);
	bool GetWireMode();

	static const enum NormalMode{WEIGHTED_AVERAGE, AVERAGE, STRAIGHT, SKELETON};
	void SetDrawNormals(bool dn);
	bool GetDrawNormals();
	void SetNormalMode(NormalMode m);
	NormalMode GetNormalMode();
	void FlipNormals();	
	int GetNumberofObjects();	//RWW 01-21-2004
	int GetNumberofVertices(int object_number);	//RWW 01-21-2004
	void SetVertexPosition(int object_number, int index, float x, float y, float z);
	void SetVertexPosition(int object_number, int index, LVector4 pos);
	void GetVertexPosition(int object_number, int index, LVector4 &pos);//RWW 01-21-2004
	LVector3 GetFaceVertices(int object_number, int face_num);
	int GetNumberofFaces(int object_number);
	void SetDrawNormals_Length(float len);	//RWW 01-27-2004
	float GetDrawNormals_Length();	//RWW 01-27-2004
	void Render_Skeleton_Normals() ;

protected:
	static const enum LoadType{NORMAL, KEYMASKED, TRANSLUCENT};
	bool LoadObject(char *strFileName, LoadType type, void *params);
	double m_Scale;
	MURect m_BoundRect;
	bool CreateTexture(UINT textureArray[], char * strFileName, int textureID);
	bool CreateTextureTransparent(UINT textureArray[], char * strFileName, int textureID, int amount);
	bool CreateTexture_alpha(UINT textureArray[], char *strFileName, int textureID, GLubyte r, GLubyte g, GLubyte b);
	bool CreateTexture_alphaTransparent(UINT textureArray[], char *strFileName, int amount, int textureID, GLubyte r, GLubyte g, GLubyte b);
	void SetAverageNormals(void);
	void SetWeightedAverageNormals(void);
	void SetSkeletonNormals(void);
	void SetStraightNormals();

	UINT m_Textures[MAX_TEXTURES];

	t3DModel m_t3DModel;

	CLoad3DS m_Model;

	int m_ViewMode;
	//this indicates whether the object will be rendered: it is set to true by default
	bool render_enable;
	bool draw_normals;
	NormalMode norm_mode;
	bool wire_mode;
	float draw_normals_len; //RWW 1-27-2004
private:
	bool m_Valid;
};

/*************************************************************************/
//originally written by Ryan Brown
bool Model3DSphericalCollision(Model3DS& src1, Model3DS& src2);

/*************************************************************************/
class Skybox
{
public:
	
	Skybox();
	void LoadImages(char * front_file, char * back_file, char * right_file, char * left_file,  char * top_file, char * bottom_file);
	void SetSize(float swidth, float sheight, float slength);
	void SetCenter(float cx, float cy, float cz);
	bool CreateTexture(UINT textureArray[], char * strFileName, int textureID);
	void Render();

protected:
	
	float x;
	float y;
	float z;
	float width;
	float height;
	float length;
	UINT sky_textures[6];

};

/*************************************************************************/
//written by Monique Heyneke 12-04-2002
class MUstretch : public LMoveable
{
	public:
		
	MUstretch();
	void  scale(float x, float y, float z);
	void  stretchX(float value);
    void  stretchY(float value);
	void  stretchZ(float value);
};

/*************************************************************************/
// Path record,play,stop,create, tool
//originally written by Julie Sumpf
    class Underflow { };
    class Overflow  { };
    class OutOfMemory { };
    class BadIterator { };

class Path;     // Incomplete declaration.
class PathItr;     // Incomplete declaration.
typedef struct path_info{
	LVector4 position;
	LVector4 orientation;
 }pathinfo;

class PathElement
{
    PathElement(pathinfo info = pathinfo( ), PathElement * e = NULL)
    : posi_orie( info ), element( e ){ }

	pathinfo posi_orie;
    PathElement *element;

    friend class Path;
    friend class PathItr;
};

class Path
{
   public:
	bool playing, recording, playCont;
	float rate;
	int frames_per_element;

    Path( );
    Path( const Path & rhs );
    ~Path( );

    bool isEmpty( ) const;
    void makeEmpty( );
    PathItr zeroth( ) const;
    PathItr getelements( ) const;
	int numelements();
    void insert(pathinfo x, PathItr p );
	void stop();
	void recordPath(pathinfo pathpos, PathItr theItr);
	int getsamples();
	float getsamplesrate();
	void setsamplesrate(float samplesrate);
	void setsamples(float fps);
	pathinfo playPath(PathItr Itr);
	bool frameCheck(int frame);
	bool savePath(char *strFileName);
	bool loadPath(char *strFileName);
	bool isrecording() const;
	bool isplaying() const;
	bool isplayingCont() const;
    PathItr find(  pathinfo x ) const;
    PathItr findPrevious(pathinfo x ) const;
    void remove(pathinfo x );
    const Path & operator=( const Path & rhs );
   private:
      PathElement *header;
};
bool operator==(const pathinfo & x, const pathinfo & y);
bool operator!=(const pathinfo & x, const pathinfo & y);
void pathinfo_set(pathinfo *x, LVector4 pos, LVector4 ori);

class PathItr
{
   public:
      PathItr( ) : current( NULL ) { }
      bool isPastEnd( ) const
	  { return current == NULL; }

      void advance( )
      { if( !isPastEnd( ) ) current = current->element; }

      pathinfo retrieve( ) 
      { if( isPastEnd( ) ) throw BadIterator( );
      return current->posi_orie; }

   private:
      PathElement *current;    // Current position

      PathItr( PathElement *theElement )
      : current( theElement ) { }

      friend class Path; // Grant access to constructor
};

/*************************************************************************/
class SaveImage
{
public:
	// actual images per second saved will be somewhat less than images_per_second
	SaveImage(int set_screen_width, int set_screen_height, int images_per_second, string base_file_name);
	~SaveImage();
	void StartSaving();
	void StopSaving();
	void WriteFiles();
	void SaveFunction();
protected:
	void Save_bmp(const GLubyte *pixel_data);

	bool save_images;
	int screen_width;
	int screen_height;
	int ips;
	string file_name;
	vector<GLubyte*> images;
};

/*************************************************************************/
class MUmovnode : public Model3DS
{
public:
	//Constructor	
	MUmovnode();						
	//Attaches the node for which the function was called to the node
	//refrenced by parent.
	void Attach(MUmovnode *parent);	
	void Detach(MUmovnode *parent); //RdS 06-06-2003
	//Renders the parent node (for which the function was called) and
	//all of its children.
	void Render(GLint blend_mode = GL_MODULATE);
	//returns the child id to its parent
	int Getchild_id();
	//returns the number of children for the given parent
	int GetAttachments(); 				//returns number or children node has
	LVector4 Getoriginal_rotation();
	void Setoriginal_rotation(LVector4 q);
	LVector4 Getoriginal_position();
	void Setoriginal_position(LVector4 pos);

	void GetWorldMatrix(LMatrix4 &m);
	void GetWorldPosition(LVector4 &v);
	void GetWorldRotation(LVector4 &v);
	void UpdateMyWorldMatrix();
	void ParentUpdateWorldMatrices();

	friend vector<MUmovnode*> PickNodes(LCamera cam, vector<MUmovnode*> parent_nodes, double center_x, double center_y, double width, double height);
protected:
	// Do not call directly (see ParentUpdateWorldMatrices)
	void ChildUpdateWorldMatrices(const LMatrix4 &parent_matrix);
	// Do not call directly (see PickNodes)
	void PickingRender(int name);

	//refrence array of child nodes
	MUArray<MUmovnode*, MUmovnode*> children;
	//reference to immediate parent
	MUmovnode* my_parent;
	//reference to top level parent
	MUmovnode* top_parent;
	//number of attachments to parent
	int attachmentnum;
	//child id to its parent
	int child_id;
	LVector4 original_rotation;
	LVector4 original_position;
	LMatrix4 worldm;
};

/*************************************************************************/
//NEC added 02/05/03
class MUmovnode_collide : public MUmovnode
{
public:
	//Constructor
	MUmovnode_collide();
	//Destructor
	~MUmovnode_collide();

	void Make_collidable();
	static void GetCollisionMatrix(float world[16], MUmovnode_collide *the_node);
	bool Check_collision(MUmovnode_collide &other);
	bool Check_ray_collision(float length, const LVector3 &ray_start, const LVector3 &direction, bool closest_collision = false);
	bool Check_ray_collision(const LVector3 &ray_start, const LVector3 &ray_end, bool closest_collision = false);
protected:
	CollisionModel3D *coldet_model;
};

/*************************************************************************/
// written by  Rod Shenk 12-03-2002
// LODnode - an extension of the Model3DS class
//           to provide level of detail nodes.
// 10-19-2003 RdS updated to provide collision detection

class LODnode : public MUmovnode_collide
{
public:
	LODnode();
	virtual ~LODnode();

	void Make_collidable();

	// Set the distance where each LOD model is visible.  Pass an
	// array of ranges, from near to far, one for each model.  
	// numberOfRanges is the size of the array.
	void setRanges(float rangeValues[], int numberOfRanges);

	// Add a 3ds model to the LOD node.  Call once for each 
	// 3ds file, in order of decreasing complexity.
	// For now the limit is 6 models.
	bool addLODnode(char *strFileName);

	// This Render function is faster, but partially visible models that 
	// are near and to the side of the camera can pop to the lowest detail.
	void Render(GLint blend_mode = GL_MODULATE);

	// Pass the camera to the Render function to avoid the above problem.
	// Somewhat slower, though.
	void Render(const LCamera & cam, GLint blend_mode = GL_MODULATE);

protected:
	void SetMinBoundRect(int x);
	t3DModel m_t3DModel[6];
	t3DModel *modelptr;
	list<t3DModel*> modelList;
	list<t3DModel*>::iterator iter;
	float *rangeList;
	int numRanges;
	bool m_Valid;

};

/*************************************************************************/
// RdS added Display class

typedef struct 
    {
    GLuint base;        
    int    widths[256]; 
    int    height;      
    } GLFONT;

// all screen coords from (0,0) to (1,1) -- top left to bottom right
class Display
{
public:
	Display();
	~Display();

	// Call this before other Display class functions, or each time screen is reshaped
	void Initialize(muopengl_info *muopengl);
	void Initialize(int screen_width, int screen_height);

/***** Font stuff *****/

	int LoadFontNames(void); // Returns number of fonts

	// Load a font by name or by the font's number generated during LoadFontNames.
	// Returns the font's index number to be passed to SetFont.
	int LoadFont(char *font_name, int size=20, int weight=5, DWORD italic=0);
	int LoadFont(int font_number, int size=20, int weight=5, DWORD italic=0);

	// returns font_index, or -1 if unsuccessful
	int SetFont(int font_index);

	void ListAllFontNames(void);
	void ListLoadedFonts(void);

	// Draw text to screen at xpos and ypos: (0,0) is top left, (1,1) is bottom right.
	// align text at drawing position: 1=left, -1=right, 0=centered
	void DrawText(float xpos, float ypos, const int align, const char *string);
	void DrawTextVertical(float xpos, float ypos, const char *string);

	static int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme,
											DWORD FontType, LPARAM lParam);
/***** Drawing stuff *****/

	void BarGraph(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y, 
				  float percent_full, int horizontal = 0, int border = 1);

	// fill = 0 for filled, or line width for hollow
	void DrawBox(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y,
				 float fill = 0);
	void DrawCircle(float x, float y, float radius, float fill = 0, int slices = 60);

	void DrawArc(float x, float y, float radius, float start_ang,
				 float fill = 0, float sweep_rad = PI, int slices = 30);

	void DrawLine(float x1, float y1, float x2, float y2, float width = 1);

	bool button(float x1, float y1, float x2, float y2, int buttonID, int buttonDownID, int mouseX, int mouseY, bool mouseClick);
	bool mouseOverButton(float x1, float y1, float x2, float y2, int buttonID, int buttonOverID, int mouseX, int mouseY);

//	void TextBoxFill(float r, float g, float b, float transparency);
//	void TextBoxBorder(float r, float g, float b, float width = 1, float transparency = 1);
//	void TextBox(float xpos, float ypos, const int align, const char *string);

	bool CreateTexture(LPSTR strFileName, int textureID);
	bool CreateTextureWithKeyMask(LPSTR strFileName, int textureID, int r, int g, int b);

	void DrawTextureKeyMask(float top_left_x, float top_left_y, 
						  float bottom_right_x, float bottom_right_y, int textureID);
	void DrawTexture(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y,
					 int textureID);

private:
	bool initialized;
	bool init_msg;

	GLFONT *FontCreate(HDC hdc, const char *typeface, int height, int weight, DWORD italic);
	void FontDelete(GLFONT *font);
	void FontPuts(GLFONT *font, const char *s);
	void FontPrintf(GLFONT *font,int align, const char *format, ...);
	void FontPrintfVert(int x, int y, GLFONT *font, const char *format, ...);
	GLFONT *Font;  
	GLFONT *Fonts[512];
	char *fontNames[512];
	char *loadedNames[1];
	int fontID, Width, Height;
	bool newfont;
	bool fontNamesLoaded;
	bool font_msg;
	int numFontsLoaded;
	int numFontNames;

	UINT screen_textures[100];
	float fill_r, fill_g, fill_b;
	float fill_trans;
	float bord_r, bord_g, bord_b;
	float bord_width, bord_trans;
	float box_x1, box_y1, box_x2, box_y2;
}; 

/*************************************************************************/
// KAB added scroll bar class 08-09-2004
class ScrollBar
{
public:
	ScrollBar();
	~ScrollBar();

	void load6Textures(Display *display,int startID, bool isHorizontal);
	void setScrollStartID(int startID, bool isHorizontal);
	
	void setPosition(float setX1, float setY1, float setX2, float setY2, int setScreenWidth, int setScreenHeight);
	float update(int updateMouseX, int updateMouseY, bool updateMouseClick);
	void drawScrollBar(Display *display);
	void drawScrollBarBackwards(Display *display);
	void drawLabel(Display *display, char *scrollLabel);

private:

	bool horizontal;
	bool mouseClick;

	float scrollPercent;

	float x1;
	float y1;
	float x2;
	float y2;

	int mouseX;
	int mouseY;
	int screenWidth;
	int screenHeight;
	int startID;
};


/*************************************************************************/
// Targa animation class added by RdS
class Tga_anim
{
public:
	Tga_anim(void);
	~Tga_anim(void);

	void load_tga_files(char * basename, int num, GLubyte r=0, GLubyte g=0, GLubyte b=0);
	void start(int ms_per_frame = 50, int loop = 1); // 0 = infinity
	void update(LCamera *myCam, bool use_depth_test = true);
	void set_position(LVector4 pos);
	LVector4 get_position(void) { return position; };
	void set_size(float width, float height);
	bool is_playing(void) { return playing; };

protected:
	void tgaload(char * strFileName, GLubyte r, GLubyte g, GLubyte b);
	int numframes;
	int frametime;
	int currentframe;
	int currentloop;
	int totalloops;
	bool playing;
	int framestarted;
	LTGA tga;
	GLuint texName[100];
	LVector4 position;
	float tga_width, tga_height;
	bool has_valid_alpha[100];
	bool no_depth_test;

};


/*************************************************************************/
struct skeletonPoint
{
	LVector3 theSkeletonPoint;
	LVector3 currentPosition;
	LVector3 restingPosition;
	int num_verts;
	vector<vector<int> > vertexIndexes;

};

//SkeletonClass begun work on 03 23 04 by MCH
class SkeletonNode : public MUmovnode_collide
{
public:
	SkeletonNode();
	virtual ~SkeletonNode();

	bool loadSkeleton(char *strFileName);

	void attachModelToSkeleton();//for every vertex in 3ds assigns vertex with skelpt

	void drawSkeletonPoint(skeletonPoint *thePoint);

	void setDrawSkeletonPoints(bool theBool)	{drawSkeletonPoints = theBool;};
	void setDrawSkeletonSprings(bool theBool)	{drawSkeletonSprings = theBool;};

	bool getDrawSkeletonPoints()				{return drawSkeletonPoints;};
	bool getDrawSkeletonSprings()				{return drawSkeletonSprings;};
	int getNumberOfSkeletonPoints()				{return skeletonPoints.size();};


	skeletonPoint* getSkeletonPoint(int index)	{return &skeletonPoints[index];};
	skeletonPoint* getVertexSkeletonPoint(int object, int vertIndex);
	
	LVector3 getSkeletonPointLocalPos(int object, int vertIndex);
	LVector3 getSkeletonPointLocalPos(skeletonPoint *thePoint);
	
	LVector3 getSkeletonPointWorldPos(int object, int vertIndex);
	LVector3 getSkeletonPointWorldPos(skeletonPoint *thePoint);

	LVector3 getLocalPosition(LMatrix4 theMatrix);
	LVector3 getLocalPosition(LVector4 thePoint);

	//draw the skeleton
	void Render(GLint blend_mode = GL_MODULATE);

protected:


private:
	vector<skeletonPoint> skeletonPoints;
	vector<vector<int> > skeletonIndexes;	//for every vertex, this is the index of the skeleton point it is attached to
	bool drawSkeletonPoints;
	bool drawSkeletonSprings;
	bool modelLoaded;
};


#endif

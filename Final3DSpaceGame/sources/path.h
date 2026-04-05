#ifndef MYPATH_H		
#define	MYPATH_H

#include "muopengl.h"

class MyPath
{
public:
  MyPath (string fileName);
  ~MyPath ();

  void setPosRot (LVector4 thisPos, LVector4 thisRot);
  void getPosRot (LVector4& thisPos);
  
  void savePath ();
  void readPath ();
  
  int getPathPos () const;
  int getPathSize () const;
  
  
  void resetVectorPos ();
  void erasePath ();
  
private:
  vector <LVector4> position;
  vector <LVector4> rotation;
  string fileName;
  int vectorPos;
  
  
  
};

#endif
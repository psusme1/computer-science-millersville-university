#include <fstream>
#include "path.h"

  
MyPath::MyPath (string fName) :  fileName (fName), vectorPos (0)
{
  position.reserve (1000000);
  rotation.reserve (1000000);
  //savePath ();
}

MyPath::~MyPath () {}

void 
MyPath::setPosRot (LVector4 thisPos, LVector4 thisRot)
{
  position.push_back (thisPos);
  rotation.push_back (thisRot); 
}

void 
MyPath::resetVectorPos ()
{
   vectorPos = 0;
}
  
void 
MyPath::getPosRot (LVector4& thisPos)
{
  thisPos = position [vectorPos];
  //thisRot = rotation [vectorPos];
  vectorPos++;
}
  
int
MyPath::getPathPos () const
{
  return (vectorPos);
}

int
MyPath::getPathSize () const
{
  return (position.size ());
}

  
void 
MyPath::savePath ()
{
  int pathSize = getPathSize ();
  ofstream out;
  out.open (fileName.c_str ());

  out << pathSize;
 
  for (int i = 0; i < pathSize; i++)
  {
    out << position [i].x << " " << position [i].y << " " << position [i].z << "\n"
        << rotation [i].x << " " << rotation [i].y << " " << rotation [i].z << "\n\n" ;
  }
  out.close ();
}

  
void 
MyPath::readPath ()
{
  int pathSize;
  ifstream in;
  LVector4 temppos, temprot;
 
  erasePath ();
  resetVectorPos ();

  in.open (fileName.c_str ());
  in.seekg (0);
  
  in >> pathSize;
 
  for (int counter = 0; counter < pathSize; counter++)
  {
    in >> temppos.x >> temppos.y >> temppos.z
       >> temprot.x >> temprot.y >> temprot.z; 
       
    setPosRot (temppos, temprot);
   }
  
  resetVectorPos ();
  
}

void 
MyPath::erasePath ()
{
  while (!position.empty ())
  {
    position.pop_back ();
    rotation.pop_back ();
  }
}

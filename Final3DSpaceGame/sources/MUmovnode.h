/* MUmovnode.h
Created by:		Nate Good
Date:			12-3-02
*/

#include "MUArray.h"
#include "muopengl.h"
#include "coldet_headers/coldet.h"

//using namespace std;

class MUmovnode : public Model3DS
{
public:
	//Constructor	
	MUmovnode();						
	//Attaches the node for which the function was called to the node
	//refrenced by parent.
	void Attach(MUmovnode *parent);		
	//Renders the parent node (for which the function was called) and
	//all of its children.
	void Render(bool parent = true);
	//returns the child id to its parent
	int Getchild_id();
	//returns the number of children for the given parent
	int GetAttachments(); 				//returns number or children node has
	LVector4 Getoriginal_rotation();
	void Setoriginal_rotation(LVector4 q);
	LVector4 Getoriginal_position();
	void Setoriginal_position(LVector4 pos);

	void GetWorldPosition(LVector4 &v);
	void GetWorldRotation(LVector4 &v);
	void UpdateChildrenWorldMatrices();

protected:
	void UpdateWorldMatrix(LMatrix4 m);

	//refrence array of child nodes
	MUArray<MUmovnode*, MUmovnode*> children;
	//number of attachments to parent
	int attachmentnum;
	//child id to its parent
	int child_id;
	LVector4 original_rotation;
	LVector4 original_position;
	LMatrix4 worldm;

};

//NEC added 02/05/03
class MUmovnode_collide : public MUmovnode
{
public:
	//Constructor
	MUmovnode_collide();
	//Destructor
	~MUmovnode_collide();

	bool Check_collision(const MUmovnode_collide &other);
protected:
	CollisionModel3D *coldet_model;
};

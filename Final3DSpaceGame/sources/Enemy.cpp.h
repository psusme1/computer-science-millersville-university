#include "Enemy.h"

Enemy::Enemy () : life (50), pointValue (100), damage (5), active (false)
{
  L
}

    void setLife (int thisLife);
    void setpointValue (int thisPoint);
    void setDamage (int thisDamage);
    void setEnemyPos (LVector4 thisPos);
    void setEnemyRot (LVector4 thisRot);
    void setActive (bool thisActive);

    int getLife ();
    int getpointValue ();
    int getDamage ();
    LVector4 getEnemyPos ();
    LVector4 getEnemyRot ();
    bool isActive (); 


	

	private:
    int life;
    int pointValue;
    int damage;
    LVector4 enemyCurrPos;
    LVector4 enemyPrevPos;
   	bool active;
};	

#endif
 
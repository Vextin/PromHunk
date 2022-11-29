#pragma once
#include "Bullet.h"
class CEnemyBullet :
    public CBullet
{
    public:
        void CEnemyBullet::CollisionResponse(const Vector2& norm, float d, CObject* pObj);
};


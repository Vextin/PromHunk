
#include "Bullet.h"
class CEnemyBullet :
    public CBullet
{       
protected:
    void CEnemyBullet::CollisionResponse(const Vector2& norm, float d, CObject* pObj) override;
public:
    CEnemyBullet(eSprite t, const Vector2& p, float damage = 1); ///< Constructor.
        
};


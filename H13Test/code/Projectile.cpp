#include "Projectile.h"
#include "ProjectileScriptComponent.h"
#include "ProjectileRenderComponent.h"

#include "QuadTree.h"
Projectile::Projectile()
	: GameObject("Projectile")
{
	mRenderComponent = new ProjectileRenderComponent(*this);
	mScriptComponent = new ProjectileScriptComponent(*this);
	mColliderComponent = new ColliderComponent(*this);
	//mApplication->quad->InsertObject(mApplication->quad, mColliderComponent);
	mApplication->addProjectile(this);
}

Projectile::~Projectile()
{
	mApplication->removeProjectile(this);
}
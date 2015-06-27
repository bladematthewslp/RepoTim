#include "Projectile.h"
#include "ProjectileScriptComponent.h"
#include "ProjectileRenderComponent.h"

Projectile::Projectile()
	: GameObject("Projectile")
{
	mRenderComponent = new ProjectileRenderComponent(*this);
	mScriptComponent = new ProjectileScriptComponent(*this);
}


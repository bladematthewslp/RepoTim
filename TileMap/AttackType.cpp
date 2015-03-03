#include "AttackType.h"
#include <iostream>

std::map<Attacks::Name, AttackType*>		Attacks::registeredAttacks;
std::string Attacks::NINJA_SLASH_GROUND		= "NINJA_SLASH_GROUND",
			Attacks::NINJA_SLICE			= "NINJA_SLICE", 
			Attacks::PLAYER_SLASH			= "PLAYER_SLASH",
			Attacks::PLAYER_SLASH1			= "PLAYER_SLASH1",
			Attacks::PLAYER_SLASH2			= "PLAYER_SLASH2",
			Attacks::PLAYER_SLASH3			= "PLAYER_SLASH3",
			Attacks::PLAYER_IMPACT			= "PLAYER_IMPACT",
			Attacks::PLAYER_CHOPPERSTYLE	= "PLAYER_CHOPPERSTYLE",
			Attacks::PLAYER_SWEEP			= "PLAYER_SWEEP",
			Attacks::PLAYER_REPEL			= "PLAYER_REPEL",
			Attacks::PLAYER_STINGER			= "PLAYER_STINGER",
			Attacks::PLAYER_QUICKSTINGER	= "PLAYER_QUICKSTINGER",
			Attacks::PLAYER_UPRISING		= "PLAYER_UPRISING",
			Attacks::PLAYER_QUICKUPRISING	= "PLAYER_QUICKUPRISING",
			Attacks::RYOBE_SWORDATTACK		= "RYOBE_SWORDATTACK",
			Attacks::RYOBE_DAGGERTHROW		= "RYOBE_DAGGERTHROW",
			Attacks::RYOBE_EMBRACER			= "RYOBE_EMBRACER",
			Attacks::RYOBE_FELLCRESCENT		= "RYOBE_FELLCRESCENT",
			Attacks::RYOBE_TELEPORT			= "RYOBE_TELEPORT"
			;

void Attacks::registerAttacks()
{
	registeredAttacks[NINJA_SLASH_GROUND]	= std::unique_ptr<AttackType>(new AttackType(DamageType::Weak,	false,	NINJA_SLASH_GROUND)).release();
	registeredAttacks[PLAYER_SLASH]			= std::unique_ptr<AttackType>(new AttackType(DamageType::Weak,	false,	PLAYER_SLASH)).release();
	registeredAttacks[PLAYER_SLASH1]		= std::unique_ptr<AttackType>(new AttackType(DamageType::Weak,	false,	PLAYER_SLASH1)).release();
	registeredAttacks[PLAYER_SLASH2]		= std::unique_ptr<AttackType>(new AttackType(DamageType::Medium,false,	PLAYER_SLASH2)).release();
	registeredAttacks[PLAYER_SLASH3]		= std::unique_ptr<AttackType>(new AttackType(DamageType::Strong,false,	PLAYER_SLASH3)).release();
	registeredAttacks[PLAYER_IMPACT]		= std::unique_ptr<AttackType>(new AttackType(DamageType::Strong,true,	PLAYER_IMPACT)).release();
	registeredAttacks[PLAYER_SWEEP]			= std::unique_ptr<AttackType>(new AttackType(DamageType::Medium,false,	PLAYER_SWEEP, true)).release();
	registeredAttacks[PLAYER_REPEL]			= std::unique_ptr<AttackType>(new AttackType(DamageType::Medium,false,	PLAYER_REPEL, true)).release();
	registeredAttacks[PLAYER_CHOPPERSTYLE]	= std::unique_ptr<AttackType>(new AttackType(DamageType::Medium,true,	PLAYER_CHOPPERSTYLE)).release();
	registeredAttacks[PLAYER_STINGER]		= std::unique_ptr<AttackType>(new AttackType(DamageType::Weak,	false,	PLAYER_STINGER)).release();
	registeredAttacks[PLAYER_QUICKSTINGER]	= std::unique_ptr<AttackType>(new AttackType(DamageType::Weak,	false,	PLAYER_QUICKSTINGER)).release();
	registeredAttacks[PLAYER_UPRISING]		= std::unique_ptr<AttackType>(new AttackType(DamageType::Medium,false,	PLAYER_UPRISING)).release();
	registeredAttacks[PLAYER_QUICKUPRISING]	= std::unique_ptr<AttackType>(new AttackType(DamageType::Medium,false,	PLAYER_QUICKUPRISING)).release();
	registeredAttacks[RYOBE_SWORDATTACK]	= std::unique_ptr<AttackType>(new AttackType(DamageType::Medium,false,	RYOBE_SWORDATTACK)).release();
	registeredAttacks[RYOBE_DAGGERTHROW]	= std::unique_ptr<AttackType>(new AttackType(DamageType::Medium,false,	RYOBE_DAGGERTHROW)).release();
	registeredAttacks[RYOBE_EMBRACER]		= std::unique_ptr<AttackType>(new AttackType(DamageType::Strong,false,	RYOBE_EMBRACER)).release();
	registeredAttacks[RYOBE_FELLCRESCENT]	= std::unique_ptr<AttackType>(new AttackType(DamageType::Super,false,	RYOBE_FELLCRESCENT)).release();
	registeredAttacks[RYOBE_TELEPORT]		= std::unique_ptr<AttackType>(new AttackType(DamageType::NoDamage,false,RYOBE_TELEPORT)).release();
	
	

	//std::cout << "REGISTERING ATTACKS" << std::endl; 
}

AttackType& Attacks::getAttack(Attacks::Name name)
{
	return *registeredAttacks[name];
}

AttackType::AttackType(DamageType damageType, bool canLaunch, std::string name, bool isAirAttack)
	: mDamageType(damageType)
	, mCanLaunch(canLaunch)
	, mName(name)
	, mIsAirAttack(isAirAttack)
{
	//mFunction = [&] { std::cout << other.mName << std::endl; };

}

void AttackType::run()
{
	mFunction();

}
#pragma once

#include <string>
#include <functional>
#include <map>
#include "GameObject.h"



enum DamageType
{
	Weak,
	Medium,
	Strong,
	Super,
	Unblockable

};

struct AttackType
{
	std::string		mName;
	bool			mCanLaunch;
	bool			mIsAirAttack;
	DamageType		mDamageType;
	AttackType(DamageType damageType, bool canLaunch, std::string name = "Attack",bool isAirAttack = false);
	std::function<void()> mFunction;

	void			run();

};

struct Attacks
{
	typedef std::string Name;
	
	static std::string	NINJA_SLASH_GROUND	,
						NINJA_SLICE			,
						PLAYER_SLASH		,
						PLAYER_SLASH1		,
						PLAYER_SLASH2		,
						PLAYER_SLASH3		,
						PLAYER_IMPACT		,
						PLAYER_CHOPPERSTYLE ,
						PLAYER_SWEEP		,
						PLAYER_REPEL		,
						PLAYER_STINGER		,
						PLAYER_QUICKSTINGER ,
						PLAYER_UPRISING		,
						PLAYER_QUICKUPRISING,
						RYOBE_SWORDATTACK	,
						RYOBE_DAGGERTHROW	
						;
	static std::map<Attacks::Name, AttackType*>		registeredAttacks;		
	
	
	static void				registerAttacks();

	static AttackType&			getAttack(Attacks::Name name);

};




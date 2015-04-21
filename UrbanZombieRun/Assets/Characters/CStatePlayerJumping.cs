using UnityEngine;
using System.Collections;
using Identifiers;

class CStatePlayerJumping : CState
{
	PlayerLogic logic;
	float verticalSpeed = 5;
	float gravity = 10.0f;

	public CStatePlayerJumping(GameObject character)
		: base(character, "CStatePlayerJumping")
	{

	}
	
	public override void entry()
	{
		logic = mCharacter.GetComponent<PlayerLogic> ();
		logic.setAnimState(AnimStates.jump);
		logic.playSound(Sounds.jump);

		logic.setVelocity(Vector3.zero);
	}
	
	public override CState		handleInput()
	{
		return this;
	}
	public override CState		update()
	{
		// subtract gravity acceleration from vertical speed
		verticalSpeed -= gravity * Time.deltaTime;

		// update vertical velocity 
		Vector3 velocity = logic.getVelocity ();
		velocity.y = verticalSpeed;
		logic.setVelocity (velocity);
		logic.move ();

		// if the player begins descending...
		if(velocity.y < 0)
		{
			// change to falling state
			CState newState = new CStatePlayerFalling(mCharacter);
			newState.entry();
			return newState;
		}
		
		return this;
		
	}
	public override void			exit()
	{

	}
	
}

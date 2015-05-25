using UnityEngine;
using System.Collections;
using Identifiers;

class CStatePlayerFalling : CState
{
	PlayerLogic logic;
	float gravity = 10.0f;
	
	float verticalSpeed = 0;
	
	public CStatePlayerFalling(GameObject character)
		: base(character, "CStatePlayerFalling")
	{
		
	}
	
	public override void entry()
	{

		logic = mCharacter.GetComponent<PlayerLogic> ();
		logic.setAnimState(AnimStates.falling);
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
		
		if( logic.checkIfGrounded() )
		{
			CState newState = new CStatePlayerRunning(mCharacter);
			newState.entry();
			return newState;
		}
		return this;
		
	}
	public override void			exit()
	{
	}
	
}

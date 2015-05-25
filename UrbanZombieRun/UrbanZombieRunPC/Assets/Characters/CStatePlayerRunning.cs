using UnityEngine;
using System.Collections;
using Identifiers;

class CStatePlayerRunning : CState
{
	PlayerLogic logic;
	float horizontalSpeed = 6;
	float direction = 0;

	Vector2 touchDeltaPosition = new Vector2(0,0);

	public CStatePlayerRunning(GameObject character)
		: base(character, "CStatePlayerRunning")
	{

	}

	public override void entry()
	{
		logic = mCharacter.GetComponent<PlayerLogic> ();

		logic.setVelocity( new Vector3(0, -0.75f * Time.deltaTime, 0));
		logic.setAnimState(AnimStates.run);
	}

	public override CState		handleInput()
	{
		direction = 0;
		// Handle Horizontal direction
		if (Input.GetButton ("Horizontal"))
			direction = Input.GetAxisRaw ("Horizontal");

		/*
		if(Input.GetMouseButtonDown(0) )
		{
			// Construct a ray from the current touch coordinates
			Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);//Input.GetTouch(0).position);
			RaycastHit hit;
			
			// Create a particle if hit
			if (Physics.Raycast(ray, out hit) && hit.collider.name == "MoveRight")
				Debug.Log("!!!!");

		}

		if(Input.touchCount == 1 && Input.GetTouch(0).phase == TouchPhase.Moved)
		{
			touchDeltaPosition = Input.GetTouch(0).deltaPosition;

			if(touchDeltaPosition.y >= 10)
			{
				CState newState = new CStatePlayerJumping(mCharacter);
				newState.entry();
				return newState;
			}

			if(touchDeltaPosition.x > 0)
				direction = 1;
			else if(touchDeltaPosition.x < 0)
				direction = -1;



		}
		*/
		// Handle jump button presses
		if(Input.GetButtonDown("Jump"))
		{
			CState newState = new CStatePlayerJumping(mCharacter);
			newState.entry();
			return newState;
		}



		// check if player ran off something solid
		if( !logic.checkIfGrounded() )
		{
			// if so, change to falling state
			CState newState = new CStatePlayerFalling(mCharacter);
			newState.entry();
			return newState;
		}

		return this;
	}
	public override CState		update()
	{

		// update horizontal velocity 
		Vector3 velocity = logic.getVelocity ();
		velocity.x = direction * horizontalSpeed;
		logic.setVelocity (velocity);

		logic.move ();
		return this;
	}
	public override void			exit()
	{
	}

	public void moveRight()
	{
		// update horizontal velocity 
		Vector3 velocity = logic.getVelocity ();
		velocity.x = 1  * horizontalSpeed;
		logic.setVelocity (velocity);
		
		logic.move ();

	}

}

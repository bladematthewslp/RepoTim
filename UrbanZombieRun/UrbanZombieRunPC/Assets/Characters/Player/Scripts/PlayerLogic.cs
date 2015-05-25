using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using Identifiers;

namespace Identifiers
{
	public enum AnimStates
	{
		falling,
		jump,
		jumpIdle,
		jumpLand,
		run
	};

	public enum Sounds
	{
		jump,
		coin,
	}

	public enum PlayerStates
	{
		running,
		jumping,
		falling
	}
}

public class PlayerLogic : MonoBehaviour 
{
	public bool			dead = false;
	public CState 		mState;
	public PlayerStates mPlayerState;
	public string		mStateName;

	public bool 		mIsGrounded = false;
	public Vector3 		mVelocity = new Vector3(0,0,0);
	public int			numCoinsCollected = 0;

	// Holds text component for coin counter HUD element
	public Text			textComponent;

	// The last collision flags returned from controller.Move
	public CollisionFlags collisionFlags;

	// Character controller setup
	public CharacterController controller;

	// Animation setup
	public Animation animComponent;
	public AnimationClip runAnimation;
	public AnimationClip jumpAnimation;
	public AnimationClip jumpIdleAnimation;
	public AnimationClip jumpLandAnimation;

	public RoomScript roomScript;
	// current animation state
	public AnimStates animState;
	AudioSource audioSource;
	public AudioClip jumpSound;
	public AudioClip coinSound;

	public float verticalSpeed = 5.0f;
	public float gravity = 10.0f;

	// Use this for initialization
	void Start () 
	{
		// get audio source
		audioSource = GetComponent<AudioSource>();
		// setup character controller
		controller = GetComponent<CharacterController> ();
		
		// setup animation component
		animComponent = GetComponent<Animation> ();

		// start off in the running state
		mState = new CStatePlayerRunning (gameObject);
		mState.entry ();

		mPlayerState = PlayerStates.running;

		//setVelocity( new Vector3(0, -0.75f * Time.deltaTime, 0));
		setVelocity( new Vector3(0, 0, 0));


	}
	
	// Update is called once per frame
	void Update () 
	{
		if(roomScript.isGameStarted() == false)
			return;

		if(dead)
			return;


		/*
		if(mPlayerState == PlayerStates.running)
		{
			// update vertical velocity 
			//Vector3 velocity = getVelocity ();
			//velocity.y = -0.75f * Time.deltaTime;
			//setVelocity (velocity);
			move ();
			if( !checkIfGrounded() )
			{
				Debug.Log("falling");
				setAnimState(AnimStates.falling);
				verticalSpeed = 0;
				mPlayerState = PlayerStates.falling;
				
			}
		}
		else if(mPlayerState == PlayerStates.jumping || mPlayerState == PlayerStates.falling)
		{
			// subtract gravity acceleration from vertical speed
			verticalSpeed -= gravity * Time.deltaTime;

			// update vertical velocity 
			Vector3 velocity = getVelocity ();
			velocity.y = verticalSpeed;
			setVelocity (velocity);
			move ();

			if( checkIfGrounded() )
			{
				Debug.Log("GROUNDED");
				setAnimState(AnimStates.run);
				verticalSpeed = 5;
				mPlayerState = PlayerStates.running;

				//velocity.y = -0.75f * Time.deltaTime;
				//setVelocity(velocity);
				//setVelocity( new Vector3(0, -0.75f * Time.deltaTime, 0));
			}
		}

		*/


		// First, handle the input
		CState newState = mState.handleInput ();

		if(newState != mState)					// if a button pressed changes the current state...
		{
			enterNewState(newState);			// ...set that new state as the current state
		}

		newState = mState.update ();			// run update on the current state
		{	
			if(newState != mState)				// if a condition occured to change state...
			{
				enterNewState(newState);		// ...set current state to the new state returned
			}
		}


		// just for debugging in the editor
		mStateName = mState.getName ();
	}

	// set animation state and sequences
	public void setAnimState(AnimStates newAnimState)
	{
		switch(newAnimState)
		{
			case AnimStates.run:
				animComponent[runAnimation.name].speed = 1.65f;
				animComponent.CrossFade(runAnimation.name);
				break;

			case AnimStates.jump:
				animComponent.Play(jumpAnimation.name);
				animComponent.CrossFadeQueued(jumpIdleAnimation.name);
				break;
			case AnimStates.falling:
				animComponent.CrossFade(jumpIdleAnimation.name);
				break;
			
		}


		animState = newAnimState;

	}

	public void playSound(Sounds sound)
	{

		switch(sound)
		{
			case Sounds.jump:
				audioSource.PlayOneShot(jumpSound);
				break;
			case Sounds.coin:
				audioSource.Play();
				break;

		}
	}

	void OnTriggerEnter(Collider other)
	{
		if (other.gameObject.tag == "coin")
		{
			GameObject.Destroy (other.gameObject);
			numCoinsCollected++;
			playSound(Sounds.coin);
			// Update coin count in HUD
			string textGUI = "x " + numCoinsCollected.ToString();
			textComponent.text = textGUI;
		}

		// Restart level if player hits killzone
		if(other.gameObject.name == "KillZone")
		{
			roomScript.stopRoom();
			animComponent.Stop();
			dead = true;
		}
	}

	void enterNewState(CState newState)
	{
		mState.exit ();
		mState = null;
		mState = newState;
	}

	public void move ()
	{
		collisionFlags = controller.Move (mVelocity * Time.deltaTime);
	}

	public bool checkIfGrounded () 
	{
		mIsGrounded =  (collisionFlags & CollisionFlags.CollidedBelow) != 0;
		return mIsGrounded;
		
	}

	public bool isGrounded()
	{
		return mIsGrounded;
	}


	public void setVelocity( Vector3 vel)
	{
		mVelocity = vel;
	}

	public Vector3 getVelocity()
	{
		return mVelocity;
	}

	public void moveRightBegin()
	{
		if(mPlayerState != PlayerStates.running)
			return;
		// update horizontal velocity 
		Vector3 velocity = getVelocity ();
		velocity.x = 6;
		setVelocity (velocity);
		
		//logic.move ();
	}

	public void moveRightEnd()
	{
		if(mPlayerState != PlayerStates.running)
			return;
		// update horizontal velocity 
		Vector3 velocity = getVelocity ();
		velocity.x = 0;
		setVelocity (velocity);
	}

	public void moveLeftBegin()
	{
		if(mPlayerState != PlayerStates.running)
			return;
		// update horizontal velocity 
		Vector3 velocity = getVelocity ();
		velocity.x = -6;
		setVelocity (velocity);
		
		//logic.move ();
	}
	
	public void moveLeftEnd()
	{
		if(mPlayerState != PlayerStates.running)
			return;
		// update horizontal velocity 
		Vector3 velocity = getVelocity ();
		velocity.x = 0;
		setVelocity (velocity);
	}

	public void jump()
	{
		if(mPlayerState == PlayerStates.running && roomScript.isGameStarted())
		{

			setAnimState(AnimStates.jump);
			playSound(Sounds.jump);
			
			setVelocity(Vector3.zero);

			mPlayerState = PlayerStates.jumping;

		}

	}

}

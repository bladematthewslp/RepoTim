using UnityEngine;
using System.Collections;

public class CState
{
	private string mStateName = "CharacterState";
	protected GameObject mCharacter;

	public CState 		(GameObject character, string stateName )
	{
		mStateName = stateName;
		mCharacter = character;
	}

	public virtual void		entry () { }
	public virtual CState		handleInput () { return this; }
	public virtual CState		update () { return this; }
	public virtual void		exit () {}

	public virtual void moveRight() {}

	public string		getName()
	{
		return mStateName;
	}

	~CState()
	{

	}

}

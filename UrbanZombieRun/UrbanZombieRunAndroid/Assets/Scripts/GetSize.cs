using UnityEngine;
using System.Collections;

public class GetSize : MonoBehaviour 
{

	// Use this for initialization
	void Start () 
	{
		double s = GetComponent<Collider>().bounds.size.z;
		Debug.Log( s);
		double d = GetComponent<Renderer>().bounds.size.z;
		Debug.Log(d);
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}

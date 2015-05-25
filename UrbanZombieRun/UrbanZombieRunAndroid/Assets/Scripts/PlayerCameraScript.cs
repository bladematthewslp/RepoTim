using UnityEngine;
using System.Collections;

public class PlayerCameraScript : MonoBehaviour 
{
	public float distance 	= 10;
	public Camera camera;
	public Vector3 cameraOffset;
	public GameObject objectToLookAt;
	public Vector3 offset = new Vector3(0,-2, 5);
	// Use this for initialization
	void Start () 
	{

		cameraOffset.z = distance;
		camera.transform.position = objectToLookAt.transform.position + cameraOffset;
		camera.transform.LookAt (objectToLookAt.transform.position + offset );
	}
	
	// Update is called once per frame
	void LateUpdate () 
	{
		camera.transform.position = objectToLookAt.transform.position + cameraOffset;
		camera.transform.LookAt (transform.position + offset);
	}
}

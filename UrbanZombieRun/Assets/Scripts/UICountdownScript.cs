using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UICountdownScript : MonoBehaviour 
{
	public int numIterations = 0;
	public float countdown = 0;
	public RawImage rawImageComponent;
	public Texture[] numberTextures = new Texture[2];


	// Use this for initialization
	void Start () 
	{

		rawImageComponent = GetComponent<RawImage>();
		GetComponent<RawImage>().enabled = true;
	}
	
	// Update is called once per frame
	void Update () 
	{


		countdown += Time.deltaTime;
		if(countdown >= 1)
		{
			if(numIterations == numberTextures.Length)
			{
				GameObject.Destroy(this.gameObject);
				return;
			}
			rawImageComponent.texture = numberTextures[numIterations];
			numIterations++;
			countdown = 0;
		}
	}
}

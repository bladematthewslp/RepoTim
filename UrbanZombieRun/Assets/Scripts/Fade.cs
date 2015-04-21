using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Fade : MonoBehaviour 
{
	public bool fadeComplete = false;
	public Color color;
	public void FadeMe()
	{
		StartCoroutine(DoFade(2.0f) );
	}

	void Start()
	{
	}

	void Update()
	{




	}

	IEnumerator DoFade(float waitTime)
	{
		Image image = GetComponent<Image>();
		yield return new WaitForSeconds(waitTime);
		while(image.color.a < 254)
		{
			color = image.color;
			color.a += Time.deltaTime /3;
			image.color = color;
			if(color.a > 1)
				Application.LoadLevel(Application.loadedLevel);

			yield return null;
		}

		yield return null;

	}





}


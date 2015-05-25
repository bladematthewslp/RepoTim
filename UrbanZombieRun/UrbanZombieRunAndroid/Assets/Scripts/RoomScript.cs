using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class RoomScript : MonoBehaviour 
{
	public GameObject[] sections = new GameObject[4];

	bool 				moveRoom = true;
	float 				assetSpawnTimer = 0;						// timer to spawn assets in world
	public float		timeToSpawnAssets = 2.0f;
	public Vector3 		roomSpeed = new Vector3(0, 0, -3f);			// how fast the room moves
	Vector3 			newDisplacement = new Vector3(0,0,86.7f);	// default location for repositioned world items
	float				itemSpawnPositionZ = 40.0f;
		
	public Text			distanceTextComponent;						// distance HUD element
	public float 		distanceTraveled = 0;						// total distance traveled

	double worldBoundsZ = -28.9496536254883;									// position that marks to destroy or relocate objects
	double newZPosition = 86.8489608764649;
	bool gameStarted = false;

	public GameObject gameLogo;
	public GameObject startTextUI;
	public GameObject playButton;

	public RawImage countdownNumberComponent;
	public Fade fade;
	public int numRoomSpeedIncreases = 0;
	public int maxNumRoomSpeedIncreases = 5;
	public float roomSpeedCounter = 0;
	public float timeToIncreaseSpeed = 15;
	// Use this for initialization
	void Start () 
	{

	}

	void FixedUpdate()
	{


		for(int i = 0; i < sections.Length; ++i)
		{
			sections[i].transform.position +=  roomSpeed * Time.smoothDeltaTime;
			/*
			if(sections[i].transform.position.z < worldBoundsZ)
			{
				int previousSection = (i == 0 ? sections.Length - 1 : i- 1);
				//otherwise, move the game object to the other side of the world to repeat the room
				Vector3 newLocation = sections[i].transform.position;
				newLocation.z = (float)newZPosition;//newDisplacement.z;
				sections[i].transform.position = newLocation;
				
			}
			*/
		}


		if(sections[0].transform.position.z < worldBoundsZ)
		{
			for(int i = 0; i < sections.Length; ++i)
			{
				Vector3 newLocation = sections[i].transform.position;
				newLocation.z += -(float)worldBoundsZ;//newDisplacement.z;
				sections[i].transform.position = newLocation;
				
			}
		}
	}

	public void BeginGame()
	{
		gameStarted = true;
		GameObject.Destroy(gameLogo);
		GameObject.Destroy(startTextUI);
		GameObject.Destroy(playButton);
		GenerateRoomAssets();
		countdownNumberComponent.gameObject.SetActive(true);

	}

	// Update is called once per frame
	void Update () 
	{
		if(Input.GetKeyDown(KeyCode.Escape))
			Application.Quit();
		if(moveRoom == false)
			return;

		if( ( Input.GetKeyDown(KeyCode.Return)  )  && gameStarted == false)
		{
			gameStarted = true;
			GameObject.Destroy(gameLogo);
			GameObject.Destroy(startTextUI);
			GenerateRoomAssets();
			countdownNumberComponent.gameObject.SetActive(true);
		}





	

		foreach(Transform child in transform)
		{

			// move all world items down Z axis towards player

			child.transform.position +=  roomSpeed * Time.deltaTime;
			if(child.tag == "coin")
			{
				// special rotation for coin 
				child.transform.rotation *= Quaternion.AngleAxis(2, Vector3.forward);
			}

			// if the item is less than the out of bounds marker
			if(child.position.z < worldBoundsZ)
			{
				// destroy if item is coin or barrel
				if(child.tag == "coin" || child.name == "barrels")
					GameObject.Destroy(child.gameObject);
				else
				{
					//otherwise, move the game object to the other side of the world to repeat the room
					//Vector3 newLocation = child.transform.position;
					//newLocation.z = newDisplacement.z;
					//child.transform.position = newLocation;
				}
			}
		}


		if(gameStarted == false)
			return;

		assetSpawnTimer += Time.deltaTime;
		if (assetSpawnTimer > timeToSpawnAssets) 
		{
			GenerateRoomAssets();
			assetSpawnTimer = 0;
		}

		// update distance tracker
		distanceTraveled += -roomSpeed.z * Time.deltaTime;
		distanceTextComponent.text = "Distance: " + distanceTraveled.ToString("F2") + "m";


		// increase room speed
		roomSpeedCounter += Time.deltaTime;
		if(roomSpeedCounter > timeToIncreaseSpeed && numRoomSpeedIncreases < maxNumRoomSpeedIncreases)
		{
			numRoomSpeedIncreases++;
			roomSpeed.z -= 1.5f;
			roomSpeedCounter = 0;
			timeToSpawnAssets -= .2f;
		}

	}

	void GenerateRoomAssets()
	{
		// generates room objects on a 3x6 grid in a double for-loop
		float startPosX;
		int startPosZ = 0;

		for (int i = 0; i < 6; ++i) 
		{
			startPosX = -1.7f;
			for(int j = 0; j < 3; ++j)
			{
				int randomValue = (int)(Random.value * 6);

				switch(randomValue)
				{
				case 0:
					// create Coin
					GameObject newCoin = Instantiate (Resources.Load("Coin")) as GameObject;
					newCoin.transform.position = new Vector3(startPosX, .8f, itemSpawnPositionZ + startPosZ);
					newCoin.transform.SetParent (transform);
					break;
				case 1:
					// create Obstacle
					GameObject obstacle = Instantiate (Resources.Load("Barrels")) as GameObject;//GameObject.CreatePrimitive (PrimitiveType.Cube);
					obstacle.name = "barrels";
					obstacle.transform.position = new Vector3 (startPosX, 2.28f, itemSpawnPositionZ + startPosZ);
					obstacle.transform.SetParent (transform);
					break;
				case 2:
					createJanitor();
					break;

				}
				startPosX += 1.7f;
			}
			startPosZ += 2;
		}
		if( itemSpawnPositionZ < 90)
			itemSpawnPositionZ += 20.0f;

	}


	void createJanitor()
	{
		// YES, A JANITOR IN THE SEWER. TO BE CONTINUED...
	}

	public bool isGameStarted()
	{
		return gameStarted;
	}

	public void stopRoom()
	{
		roomSpeed.z = 0;
		moveRoom = false;
		fade.FadeMe();
	}


}

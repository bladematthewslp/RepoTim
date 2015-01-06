var mainShip;
var shipVelocity;
var shipArray = [];

var borderWidth= 0.0;
var borderHeight = 0.0;
var enemyShipSpeed = 1.9;

var startPosition;
var targetPosition;
var targetDirection = new THREE.Vector3();

var targetPositions = [];
var allShipsInPosition = false;
var currentMovingShip = 0;

var numShips;

var bossShipGeometry;
var bossShipMaterial;
var bossShipMesh;

var pawnShipGeometry;
var pawnShipMaterial;
var pawnShipMesh;

var pawnShipArray = [];
var diamondPoints = [];

var testBox0, testBox1, testBox2, testBox3;

function initializeGame()
{
	mainShip = shipArray[0];
	mainShip = bossShipMesh;
	borderWidth= canvas.width/2*0.65;
	borderHeight = canvas.height/2 * 0.55;
	
	startPosition = shipArray[0].position;
	targetPosition = testBox.position;
	
	
	initializeShips();
	
	numShips = shipArray.length;
}


	
function updateGame()
{
	runDiamondFormation();
}




function initializeShips()
{
	var numShips = shipArray.length;
	var xFlip = 1;
	targetPositions[0] = new THREE.Vector3();
	targetPositions[0].copy(testBox.position);
	for(var i = 1; i < numShips; i++)
	{
		targetPositions[i] = new THREE.Vector3();
		targetPositions[i].copy(testBox.position);
		targetPositions[i].setX((testBox.position.x + 125) * xFlip);
		
		if(i > 0)
			targetPositions[i].setY(targetPositions[i].y + 50);
		xFlip = xFlip * -1.25;
	}
	
	//targetDirection.subVectors(targetPositions[currentMovingShip], shipArray[currentMovingShip].position);
	//targetDirection.normalize();
}

function shipFormation()
{
		var distance = shipArray[currentMovingShip].position.distanceTo(targetPositions[currentMovingShip]);
		if(distance > 2)
		{
			shipArray[currentMovingShip].translateOnAxis(targetDirection, 3);
			
		}
		else
		{
			currentMovingShip++;
			if(currentMovingShip == numShips)
			{
				allShipsInPosition = true;
				for(var i =  1; i < numShips; i++)
				{
					shipArray[0].add(shipArray[i]);
				}
			}
			else
			{
					targetDirection.subVectors(targetPositions[currentMovingShip], shipArray[currentMovingShip].position);
					targetDirection.normalize();	
			}
		}
}



function moveShips()
{	
	if(allShipsInPosition == false)
	{
		shipFormation();
	}
	else
	{
		var numShips = shipArray.length;
		var speedModifier = -2 ;

		var currentPosition = mainShip.position;
			
		// Set triangle's X and Y positions
		mainShip.translateX(enemyShipSpeed);

		
		// Check if triangle is past the border
		if(mainShip.position.x > borderWidth  - 50 || mainShip.position.x < -borderWidth + 50 )	
		{
				enemyShipSpeed *= -1;
				mainShip.translateX(enemyShipSpeed);
		}
	
	}

}

















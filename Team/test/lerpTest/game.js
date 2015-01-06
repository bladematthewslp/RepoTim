var mainShip;
var shipVelocity;
var shipArray = [];

var borderWidth= 0.0;
var borderHeight = 0.0;
var enemyShipSpeed = 2;

var startPosition;
var targetPosition;
var targetDirection = new THREE.Vector3();

var targetPositions = [];
var allShipsInPosition = false;
var movingShip = 0;

var numShips;

function initializeGame()
{
	mainShip = shipArray[0];
	borderWidth= canvas.width/2*0.65;
	borderHeight = canvas.height/2 * 0.55;
	
	startPosition = shipArray[0].position;
	targetPosition = testBox.position;
	
	
	initializeShips();
	
	numShips = shipArray.length;	
}

function updateGame()
{
	moveShips();
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
	
	targetDirection.subVectors(targetPositions[movingShip], shipArray[movingShip].position);
	targetDirection.normalize();
}

function shipFormation()
{
		var distance = shipArray[movingShip].position.distanceTo(targetPositions[movingShip]);
		if(distance > 1)
		{
			shipArray[movingShip].translateOnAxis(targetDirection, 0.05 * 30);
			//shipArray[movingShip].position.copy( lerp(0.01, shipArray[movingShip].position, targetPositions[movingShip] ) );
		}
		else
		{
			movingShip++;
			if(movingShip == numShips)
			{
				allShipsInPosition = true;
				for(var i =  1; i < numShips; i++)
				{
					shipArray[0].add(shipArray[i]);
				}
			}
			else
			{
					targetDirection.subVectors(targetPositions[movingShip], shipArray[movingShip].position);
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
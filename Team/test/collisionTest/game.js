var mainShip;
var shipVelocity;
var shipArray = [];

var borderWidth= 0.0;
var borderHeight = 0.0;
var enemyShipSpeed = 1;


function initializeGame()
{
	mainShip = movingBox;
	//mainShip = boxMesh;
	borderWidth= canvas.width/2*0.65;
	borderHeight = canvas.height/2 * 0.55;

	boxMesh.xMin = -15;
	boxMesh.xMax = 15;
	boxMesh.yMin = -15;
	boxMesh.yMax = 15;
}


function updateGame()
{
	//moveShip();
}

function moveShip(vel)
{
	var speedModifier = -2 ;

	var currentPosition = movingBox.position;
		
	// Set triangle's X and Y positions
	mainShip.translateX(vel.x);
	mainShip.translateY(vel.y);
	
	checkCollision();
	/*
	
	// Check if triangle is past the border
	if(mainShip.position.x > borderWidth  - 50 || mainShip.position.x < -borderWidth + 50 )	
	{
			enemyShipSpeed *= -1;
			mainShip.translateX(enemyShipSpeed);
	}
		*/
}

function checkCollision()
{
	
	var yDistance = Math.abs(movingBox.position.y - boxMesh.position.y);
	var xDistance = Math.abs(movingBox.position.x - boxMesh.position.x);
	
	if(yDistance < 30 && xDistance < 30)
	{
		boxMesh.material = collisionMaterial;
		//return;
	}
	else
	{
		if(!boxMesh.material == triangleMaterial);
			boxMesh.material = triangleMaterial
	}	//console.log("COLLISSION!!!");
		
	//console.log(yDistance);
	/*
	if(movingBox.maxY < boxMesh.minY)
		return false;
	if(movingBox.
		*/

}
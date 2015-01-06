var dotResult;
var hit;
function shieldShips()
{
	enemyWave.call(this);
	
	var shieldR = new THREE.Vector3(30, 0, 1);
	var shieldR2 = new THREE.Vector3(60, -30, 1);
	
	
	var shieldC = new THREE.Vector3(0, -30, 1);
	var shieldL = new THREE.Vector3(-30, 0, 1);
	var shieldL2 = new THREE.Vector3(-60, 0, 1);
	var respectiveProjectilePosition = new THREE.Vector3();
	
	var basePositionsPawn = [
							new THREE.Vector3(-100, 225, 1),
							new THREE.Vector3( 100, 225, 1),
							new THREE.Vector3( -30, 150, 1),
							new THREE.Vector3(  30, 150, 1),
						];
	var basePositionsCenturion = [
									new THREE.Vector3( -30, 225, 1),
									new THREE.Vector3(  30, 225, 1),
								 ];
								 
	var moving = false;
	var laserAttack = false;
	var laserOn = false;
	this.timer = 0;
	var shipTwoXSpeed = -1;
	var shipThreeXSpeed = 1;
	
	var hit = false;
	var maxSpawnTime = 30;
	var spawnTimer = maxSpawnTime;
	
	this.init = function()
	{
		for(var i = 0; i < 4; i++)
		{
			if(i > 1)
				this.shipArray[i] = new enemyShip( { shipRank: pawn, shield: true, damageAmount: 1});
			else
				this.shipArray[i] = new enemyShip( { shipRank: pawn, damageAmount: 1});
			this.numShips++;
			scene.add(this.shipArray[i].mesh);
			this.shipArray[i].mesh.position.copy(basePositionsPawn[i]);
						
		}
		
		for(var i = 4; i < 6; i++)
		{
			this.shipArray[i] = new enemyShip( { shipRank: centurion, laser: true, damageAmount: 1  });
			this.numShips++;
			scene.add(this.shipArray[i].mesh);
			this.shipArray[i].mesh.position.copy(basePositionsCenturion[i-4]);
		}
		
		this.shipArray[0].pushPattern( { dest: new THREE.Vector3(-200, 125, 1),speed: 1} );
		this.shipArray[0].pushPattern( { dest: new THREE.Vector3(-200,  75, 1),speed: 1} );
		this.shipArray[0].pushPattern( { dest: new THREE.Vector3(-200,  25, 1),speed: 1} );
		this.shipArray[0].pushPattern( { dest: new THREE.Vector3(-100, -25, 1),speed: 1.33} );
		this.shipArray[0].pushPattern( { dest: new THREE.Vector3(-100, 225, 1),speed: 1} );
		
		this.shipArray[1].pushPattern( { dest: new THREE.Vector3( 200, 125, 1),speed: 1});
		this.shipArray[1].pushPattern( { dest: new THREE.Vector3( 200,  75, 1),speed: 1});
		this.shipArray[1].pushPattern( { dest: new THREE.Vector3( 200,  25, 1),speed: 1});
		this.shipArray[1].pushPattern( { dest: new THREE.Vector3( 100, -25, 1),speed: 1.33});
		this.shipArray[1].pushPattern( { dest: new THREE.Vector3( 100, 225, 1),speed: 1});
		
		this.shipArray[2].pushPattern( { dest: new THREE.Vector3( -30, 125, 1),speed: 0.17});
		this.shipArray[2].pushPattern( { dest: new THREE.Vector3( -30,  75, 1),speed: 1});
		this.shipArray[2].pushPattern( { dest: new THREE.Vector3(-100,  25, 1),speed: 1.68});
		this.shipArray[2].pushPattern( { dest: new THREE.Vector3( -30, -25, 1),speed: 1});
		this.shipArray[2].pushPattern( { dest: new THREE.Vector3( -30, 150, 1),speed: 0.75});
		
		this.shipArray[3].pushPattern( { dest: new THREE.Vector3(  30, 125, 1),speed: 0.17});
		this.shipArray[3].pushPattern( { dest: new THREE.Vector3(  30,  75, 1),speed: 1});
		this.shipArray[3].pushPattern( { dest: new THREE.Vector3( 100,  25, 1),speed: 1.68});
		this.shipArray[3].pushPattern( { dest: new THREE.Vector3(  30, -25, 1),speed: 1});
		this.shipArray[3].pushPattern( { dest: new THREE.Vector3(  30, 150, 1),speed: 0.75});
		
		
		this.waveReady = true;
		
	};
	
	var patternIndex = 0;
	this.run = function()
	{
		
		if(keyPressedEnter == true)
		{
			laserAttack = true;
			//moving = true;
			for(var ship of this.shipArray)
			{
				if(ship.shield != null)
					ship.shield.deactivate();
					
				//ship.movementActive = true;
			}
			//moving = true;
			keyPressedEnter = false;
			/*this.shipArray[0].movementActive = true;
			this.shipArray[1].movementActive = true;
			this.shipArray[2].movementActive = true;
			this.shipArray[3].movementActive = true;*/
		}
		var count = 0;
		if(moving == true)
		{
			for(var ship of this.shipArray)
			{
				if(ship.updateMovement() == false)
				{
					ship.movementActive = false;
					count++;
				}
			}
			if(count == 4)
			{
				for(var ship of this.shipArray)
				{
					if(ship.shield != null)
						ship.shield.activate();
				}
				//moving = false;
			}
			/*
			if( this.shipArray[0].updateMovement() == false)
				this.shipArray[0].movementActive = false;
				
			if( this.shipArray[1].updateMovement() == false)
				this.shipArray[1].movementActive = false;	
				
			if( this.shipArray[2].updateMovement() == false)
				this.shipArray[2].movementActive = false;
			
			if( this.shipArray[3].updateMovement() == false)
				this.shipArray[3].movementActive = false;
			
			
			if(this.shipArray[0].movementActive == false && 
				this.shipArray[1].movementActive == false && 
					this.shipArray[2].movementActive == false &&
						this.shipArray[3].movementActive == false)
			{
				moving = false;
			}
			*/
			//this.shipArray[2].mesh.translateX(-2);
		}
		if(laserAttack == true)
		{
			this.timer ++;
			if(this.timer < 200)
			{
				var xFlip = 1;
				for(var ship of this.shipArray)
				{
					if(ship.shield != null)
					{
						shipX = ship.mesh.position.x;
							
						ship.mesh.translateX( -1 * xFlip);
						xFlip *= -1;
					}
				}
				//this.shipArray[2].mesh.translateX(shipTwoXSpeed);
				//this.shipArray[3].mesh.translateX(shipThreeXSpeed);
			}
			else if(this.timer > 200 && this.timer < 550)
			{
				
				this.shipArray[4].laserBeam.run(this);
			}
			
			if(this.timer > 600)
			{
				var xFlip = -1;
				for(var ship of this.shipArray)
				{
					if(ship.shield != null)
					{
						shipX = ship.mesh.position.x;
							
						ship.mesh.translateX( -1 * xFlip);
						xFlip *= -1;
					}
				}
				//this.shipArray[2].mesh.translateX(-shipTwoXSpeed);
				//this.shipArray[3].mesh.translateX(-shipThreeXSpeed);

			}
			
			if(this.timer >= 800)
			{
				this.timer = 0;
				laserAttack = false;
				for(var ship of this.shipArray)
				{
					if(ship.shield != null)
						ship.shield.activate();
						
					ship.movementActive = true;
				}
			}
			

			
		}
		
		
		if(hit == true)
		{
			spawnTimer -= 0.1;
			if(spawnTimer <= 0)
			{
				spawnTimer = maxSpawnTime;
				hit = false;
			}
		}
		
	};
	
	
	this.checkLaser = function()
	{
		for(var ship of this.shipArray)
		{
			if(ship.laserBeam != null)
			{
				var beamWidth = ship.laserBeam.getBeamWidth();
				var distanceFromBeam = (Math.abs(playerMesh.position.x) - 25) - (ship.mesh.position.x + beamWidth);
				
				if(ship.laserBeam.canHurt() == true && this.timer < 550 && distanceFromBeam < 0 && spawnTimer == maxSpawnTime)
				{
					hit = true;
					console.log("distanceFromBeam");
					return true;
					
				}
			}
		}
	}
	
	
	
	
	this.exit = function()
	{

	};
	
	
}

function item(properties)
{
	this.health = 0;
	this.damage = 1;
	this.shipType = null;
	this.shield = false;
	
	if(properties.health)
		this.health = properties.health;

}





shieldShips.prototype = new enemyWave();
shieldShips.prototype.constructor = shieldShips;
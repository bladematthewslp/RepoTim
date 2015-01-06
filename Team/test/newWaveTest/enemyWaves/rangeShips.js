function rangeShips()
{
	enemyWave.call(this);
	
	var laserOn = false;
	this.timer = 0;
	this.lastTime;
	this.attacking = false;
	
	this.laserBeam = new beam();
	
	
	var num = 1;
	var dir = 1;
	
	this.beamWidth = 0;
	
	var hit = false;
	var maxSpawnTime = 30;
	var spawnTimer = maxSpawnTime;
	
	this.init = function()
	{
		this.shipArray[0] = new enemyShip( { shipRank: centurion });
		scene.add(this.shipArray[0].mesh);
		this.shipArray[0].mesh.position.set(0, 200, 200);
		
		this.numShips = this.shipArray.length;
		var rectLength = 120, rectWidth = 40;
		
		
		this.shipArray[0].mesh.add( this.laserBeam.mesh );
		this.laserBeam.mesh.position.setY(-25);
		
		lastTime = Date.now();
	};
	
	this.run = function()
	{
		
		this.timer ++;
		if(keyPressedEnter == true && laserOn == false)
		{
			//this.shipArray[0].mesh.rotateOnAxis( new THREE.Vector3(0, 0, 1), 45 * (Math.PI/180) );
			laserOn = true;
			keyPressedEnter = false;
		}
		
		if(laserOn == true)
		{
			if( this.laserBeam.run(this) == false )
			{
				this.timer == 0;
				laserOn = false;
				this.attacking = false;

			}
		}
		this.laserBeam.mesh.geometry.verticesNeedUpdate = true;
		
		var beamWidth = this.laserBeam.getBeamWidth();
		var distanceFromBeam = (Math.abs(playerMesh.position.x) - 25) - (this.shipArray[0].mesh.position.x + beamWidth);
		if(this.attacking == true && distanceFromBeam < 0)
		{
			//console.log( distanceFromBeam );	
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
		var beamWidth = this.laserBeam.getBeamWidth();
		var distanceFromBeam = (Math.abs(playerMesh.position.x) - 25) - (this.shipArray[0].mesh.position.x + beamWidth);
		if(this.attacking == true && distanceFromBeam < 0 && spawnTimer == maxSpawnTime)
		{
			hit = true;
			
			return true;
			
		}
	}
	
	this.exit = function()
	{
	
	};
	
	
}





rangeShips.prototype = new enemyWave();
rangeShips.prototype.constructor = rangeShips;
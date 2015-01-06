
function cavalry(numShipsCavalry, numShipsCohort)
{
	enemyWave.call(this);
	this.numShipsCavalry = numShipsCavalry;
	this.numShipsCohort = numShipsCohort;
	
	this.numShips = numShipsCavalry + numShipsCohort;
	
	
	
	
	this.init = function()
	{
	
		// Initializing positions of calvary ships
		var xFlip = 1;
		var xInitPos = -175;
		var yInitPos = 200;
		
		var shipGeometryCavalry = [-30.0, 60.0, 0,
									30.0, 60.0, 0,
									0.00, 0.00, 0];
									
		var shipMaterialCavalry = new THREE.MeshBasicMaterial( { color: "blue", side : THREE.DoubleSide } );
		var shipGeometryCohort = [-15.0, 40.0, 0,
									15.0, 40.0, 0,
									0.00, 0.00, 0];
		var shipMaterialCohort  = new THREE.MeshBasicMaterial( { color: "red", side : THREE.DoubleSide } );
									
		
		for(var i = 0; i < this.numShipsCavalry; i++)
		{
			this.shipArray[i] = _Ship.prototype.makeShip(shipGeometryCavalry, shipMaterialCavalry);
			scene.add(this.shipArray[i]);
			if( i > 0 && i % 2 == 0)
				yInitPos -= 75;
			this.shipArray[i].position.set(xFlip * xInitPos,yInitPos,0);
			xFlip *= -1;
			
		}
		
		// Initializing positions of cohort ships
		xInitPos = 53;
		yInitPos = 200;
	
		var counter = 0;
		
		for(var i = this.numShipsCavalry, xFlip = -1; i < this.numShips; i++ )
		{
			this.shipArray[i] = _Ship.prototype.makeShip(shipGeometryCohort, shipMaterialCohort);
			scene.add(this.shipArray[i]);
			
			// set the x-position of the first ship to 0
			if(counter == 0)
			{
				this.shipArray[i].position.set( 0, yInitPos, 0);
			}
			else if(counter % 5 == 0)
			{
				// move the first ship on the next row to x-position = 0 and set y-init position
				yInitPos -= 50;
				xFlip = -1;
				this.shipArray[i].position.set( 0, yInitPos, 0);
			}
			else
			{
				// for ships to the left of the center ship
				if(xFlip < 0)
				{
					this.shipArray[i].position.set( xInitPos * xFlip, yInitPos, 0);
					xFlip *= -1;	// xflip to the other side of the center ship
				}
				else // for ships to the right of the center shp
				{
					this.shipArray[i].position.set( xInitPos * xFlip, yInitPos, 0);
					xFlip = xFlip * -1 - 1; // xflip to the other side of the center ship and decrease by 1
				}
			}
		
			counter++;
		}
		
		// Make the mainShip the first cohort ship
		this.mainShip = this.shipArray[this.numShipsCavalry];
	}
	
	this.run = function()
	{
	
		for(var i = 0; i < this.numShips; i++)
		{
			this.shipArray[i].translateX(enemyShipSpeed * 0.5);
			if(this.mainShip.position.x > 50   || this.mainShip.position.x < -50)
			{
				enemyShipSpeed *= -1;
				this.shipArray[i].translateX(enemyShipSpeed * 0.5);
			}
			
		}
	
	}
	
	this.cleanup = function()
	{
		for(var i = 0; i < this.numShips; i++)
		{
			scene.remove(this.shipArray[i]);
			this.shipArray[i] = null;
		}
	
	}


}

cavalry.prototype = new enemyWave;
cavalry.prototype.constructor = cavalry;
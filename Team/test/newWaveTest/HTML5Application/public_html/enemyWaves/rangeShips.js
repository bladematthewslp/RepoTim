function rangeShips()
{
	enemyWave.call(this);
	
	var laserOn = false;
	this.timer = 0;//Date.now();
	this.lastTime;
	var attacking = false;
	this.beamShape;
	this.beamGeometry;
	this.beamMaterial;
	this.beam;
	
	
	
	var num = 1;
	var dir = 1;
	
	this.init = function()
	{
		this.setupBeam();
		this.shipArray[0] = new enemyShip(centurion);
		scene.add(this.shipArray[0].mesh);
		this.shipArray[0].mesh.position.set(200, 200, 200);
		
		this.numShips = this.shipArray.length;
		var rectLength = 120, rectWidth = 40;

		this.shipArray[0].mesh.add( this.beam );
		this.beam.position.setY(-25);
		lastTime = Date.now()
	};
	
	this.run = function()
	{
		//this.timer = Date.now() / 1000;
		/*if(Date.now() - lastTime >= 1000) 
		{
			lastTime = Date.now();
			console.log(this.timer);
		}*/
	
		this.timer += 1;
		switch(this.timer)
		{
			case 125:
				this.beam.material.opacity = 0;
				break;
			case 135:
				this.beam.material.opacity = 0.8;
				break;
			case 145:
				this.beam.material.opacity = 0;
				break;
			case 155:
				this.beam.material.opacity = 0.8;
				break;
			case 160:
				this.beam.material.opacity = 0;
				break;
			case 165:
				this.beam.material.opacity = 0.8;
				break;
			case 450:
				this.beam.material.opacity = 0.0;
				break;
		}
		if(this.timer >= 60 && this.timer <= 125 && attacking != true)
		{
			this.beam.material.opacity = 0.8;
			this.beam.geometry.vertices[1].y -= 9;
			this.beam.geometry.vertices[2].y -= 9;
			//console.log(this.beam.material.opacity);
		}
		if(this.timer > 200 && this.timer < 300 || this.timer >= 350)
		{
			attacking = true;

			this.beam.geometry.vertices[0].x += num;
			this.beam.geometry.vertices[1].x += num;
			this.beam.geometry.vertices[2].x -= num;
			this.beam.geometry.vertices[3].x -= num;
			//console.log(this.beam.geometry.vertices[2].x);
			if(this.timer == 350)
			{
				num *= -1;
			}
			if(this.timer == 450)
			{
				num *= -1;
				this.timer = -100;
				attacking = false;
				this.resetBeam();
			}
		}
		
		
		this.beam.geometry.verticesNeedUpdate = true;
		
	};
	
	this.exit = function()
	{
	
	};
	this.resetBeam = function()
	{
		this.beam.geometry.vertices[0].x = 5;
		
		this.beam.geometry.vertices[1].x = 5;
		this.beam.geometry.vertices[1].y = -11;
		
		this.beam.geometry.vertices[2].x = -5;
		this.beam.geometry.vertices[2].y = -11;
		
		this.beam.geometry.vertices[3].x = -5;
		//this.beam.material.opacity = 0.8;
	}
	this.setupBeam = function()
	{
		this.beamShape = new THREE.Shape();
		this.beamShape.moveTo( 0,0 );
		this.beamShape.lineTo( 0, 0 );
		this.beamShape.lineTo( -5,  -10 );
		this.beamShape.lineTo( -5,  -11 );
		this.beamShape.lineTo(  5,  -11 );
		this.beamShape.lineTo(  5,  -10 );
		this.beamShape.lineTo(  0,  0 );
		
		this.beamGeometry = new THREE.ShapeGeometry( this.beamShape ); 
		this.beamMaterial = new THREE.MeshBasicMaterial( { color: 0x1d7ada, transparent: true, opacity: 0.8, alphaTest: 0.0 } );
		
		this.beam = new THREE.Mesh( this.beamGeometry, this.beamMaterial ) ;		
		
		this.beam.geometry.dynamic = true;
	}
}


rangeShips.prototype = new enemyWave();
rangeShips.prototype.constructor = rangeShips;
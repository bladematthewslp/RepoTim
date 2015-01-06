function blackHole()
{
	enemyWave.call(this);

	this.timer = 0;
	this.rotTimer = 0;

	var attacking = false;
	
	var path = new THREE.Vector3();					// the path between the ship and the blackHole
	var distance;									// the distance between the ship and the blackHole
	
	var hole = new THREE.Mesh( new THREE.PlaneGeometry(10,10), new THREE.MeshBasicMaterial({ color: "red"} ));
	
	var num = 1;
	var dir = 1;
	
	var blackHoleMesh = new THREE.Mesh( new THREE.CircleGeometry(10,32), new THREE.MeshBasicMaterial({ color: "black"} ));
	
	this.init = function()
	{
		scene.add(blackHoleMesh);
		blackHoleMesh.position.set(220, -275, -1);
		
		this.addBlackHoleLines();
		
		
		
		
		for(var i = 0; i < 15; i++)
		{
			this.shipArray[i] = new enemyShip( {shipRank: pawn });
			scene.add(this.shipArray[i].mesh);
			
		}
		
		
		this.shipArray[0].mesh.position.set(-150, -225, 1);
		this.shipArray[1].mesh.position.set(-150, 225, 1);
		this.shipArray[2].mesh.position.set(-75 , 225, 1);
		this.shipArray[3].mesh.position.set(0 , 225, 1);
		this.shipArray[4].mesh.position.set(75 , 225, 1);
		this.shipArray[5].mesh.position.set(150 , 225, 1);
		this.shipArray[6].mesh.position.set(-150 , 175, 1);
		this.shipArray[7].mesh.position.set(-75 , 175, 1);
		this.shipArray[8].mesh.position.set(0 , 175, 1);
		this.shipArray[9].mesh.position.set(75 , 175, 1);
		this.shipArray[10].mesh.position.set(150 , 175, 1);
		this.shipArray[11].mesh.position.set(-75, 100, 1);
		this.shipArray[12].mesh.position.set(0, 100, 1);
		this.shipArray[13].mesh.position.set(75, 100, 1);
		this.shipArray[14].mesh.position.set(150, 100, 1);
		
		this.numShips = this.shipArray.length;
		
	};
	
	this.run = function()
	{
		
		if(keyPressedEnter == true && attacking == false)
		{
			attacking = true;
			keyPressedEnter = false;
			
		}
		
		if(attacking == true)
		{
			this.rotTimer += 0.001;
			this.timer += 0.08;
			blackHoleMesh.rotateOnAxis( new THREE.Vector3(0,0,1), this.rotTimer );
			
			for(var j = 0; j < this.shipArray.length; j++)
			{
				path.subVectors(blackHoleMesh.position, this.shipArray[j].mesh.position);
				path.normalize();
				distance = blackHoleMesh.position.distanceTo(this.shipArray[j].mesh.position);
				
				var size = this.shipArray[j].mesh.geometry.vertices.length;
			
				this.shipArray[j].mesh.translateOnAxis(path, this.timer/2);
				for(var i = 0; i < size; i++)
				{
					if(this.shipArray[j].mesh.geometry.vertices[i].x < 0)
						this.shipArray[j].mesh.geometry.vertices[i].x += 1/distance *30;
					
					if(this.shipArray[j].mesh.geometry.vertices[i].x > 0)
						this.shipArray[j].mesh.geometry.vertices[i].x -= 1/distance *30;
					
					if(this.shipArray[j].mesh.geometry.vertices[i].y < 0)
						this.shipArray[j].mesh.geometry.vertices[i].y += 1/distance *30;
						
					if(this.shipArray[j].mesh.geometry.vertices[i].y > 0)
						this.shipArray[j].mesh.geometry.vertices[i].y -= 1/distance *30;
							
						
					this.shipArray[j].mesh.geometry.verticesNeedUpdate = true;
					
					
				}
				
				// also decrease size of healthBar belonging to ship
				var numChildren = this.shipArray[j].mesh.children.length;
				if( numChildren > 0)
				{
					var childVerticesSize = this.shipArray[j].mesh.children[0].geometry.vertices.length;
					var child = this.shipArray[j].mesh.children[0].geometry;
					
					child.dynamic = true;
					
					for(var i = 0; i < childVerticesSize; i++)
					{
						if(child.vertices[i].x < 0)
							child.vertices[i].x += 1/distance *30;
						
						if(child.vertices[i].x > 0)
							child.vertices[i].x -= 1/distance *30;
						
						if(child.vertices[i].y < 0)
							child.vertices[i].y += 1/distance *30;
							
						if(child.vertices[i].y > 0)
							child.vertices[i].y -= 1/distance *30;
								
						child.verticesNeedUpdate = true;
					}
				
				}
					
			}
			
			
			// remove ships that collided with black hole
			for(var j = 0; j < this.shipArray.length; j++)
			{
				if(this.shipArray[j].mesh.position.distanceTo(blackHoleMesh.position) < 4)
				{
					scene.remove(this.shipArray[j].healthBar);
					scene.remove(this.shipArray[j].mesh);
					this.shipArray.splice(j,1);
					this.numShips--;
				}	
			}
		}
		
		
		
	
		
		
		
		
		
	};
	
	this.addBlackHoleLines = function()
	{
		SUBDIVISIONS = 20;
		geometry = new THREE.Geometry();
		curve = new THREE.QuadraticBezierCurve3();
		curve.v0 = new THREE.Vector3(0, 0, 0);
		curve.v1 = new THREE.Vector3(-25, 25, 0);
		curve.v2 = new THREE.Vector3(-7.5, 50, 0);
		for (j = 0; j < SUBDIVISIONS; j++) 
		{
			geometry.vertices.push( curve.getPoint(j / SUBDIVISIONS) )
		}
		material = new THREE.LineBasicMaterial( { color: 0xffffff, linewidth: 2 } );
		line = new THREE.Line(geometry, material);

		blackHoleMesh.add(line);
		
		geometry = new THREE.Geometry();
		curve.v0 = new THREE.Vector3(0, 0, 0);
		curve.v1 = new THREE.Vector3(25, 25, 0);
		curve.v2 = new THREE.Vector3(50, 7.5, 0);
		for (j = 0; j < SUBDIVISIONS; j++) 
		{
			geometry.vertices.push( curve.getPoint(j / SUBDIVISIONS) )
		}
		line2 = new THREE.Line(geometry, material);
		blackHoleMesh.add(line2);
		
		geometry = new THREE.Geometry();
		curve.v0 = new THREE.Vector3(0, 0, 0);
		curve.v1 = new THREE.Vector3(25, -25, 0);
		curve.v2 = new THREE.Vector3(-7.5, -50, 0);
		for (j = 0; j < SUBDIVISIONS; j++) 
		{
			geometry.vertices.push( curve.getPoint(j / SUBDIVISIONS) )
		}
		line3 = new THREE.Line(geometry, material);
		blackHoleMesh.add(line3);
		
		geometry = new THREE.Geometry();
		curve.v0 = new THREE.Vector3(0, 0, 0);
		curve.v1 = new THREE.Vector3(-25, -25, 0);
		curve.v2 = new THREE.Vector3(-50, -7.5, 0);
		for (j = 0; j < SUBDIVISIONS; j++) 
		{
			geometry.vertices.push( curve.getPoint(j / SUBDIVISIONS) )
		}
		line4 = new THREE.Line(geometry, material);
		blackHoleMesh.add(line4);
	}
	
	this.exit = function()
	{
		scene.remove(this.blackHoleMesh);
	};
	
	
}




blackHole.prototype = new enemyWave();
blackHole.prototype.constructor = blackHole;
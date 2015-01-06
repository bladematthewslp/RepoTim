// Level.js

var level = function(numShips, timer)
{
	this.numShips 	= numShips;
	this.timer 		= timer;
	
	this.sendEnemyWaveOne = function() { console.log("Enemy Wave One"); };
	this.sendEnemyWaveTwo = function() { console.log("Enemy Wave Two"); };
	
	this.enemyWaves = [  this.sendEnemyWaveOne,	this.sendEnemyWaveTwo ];
	this.sendLevelData = function(){  };
}





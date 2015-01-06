var shipType =
{
	pawn : 1,
	boss: 1 << 1,
	superboss: 1 << 2,

}

var sType = function() 
{
	t = 9;
	var u = 9;//u = 9;
}

function ship()
{
	this.plane = 1;
	this.ship = 4 >> 1;
	this.space= 0;// << 2

	this.type = shipType.boss;// shipType.pawn;//new shipType();
	
	console.log( this.type);
}
ship();
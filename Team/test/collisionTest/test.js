function Person()
{
	var name = "bob";



}

var me;
function startTest()
{
	me = new Person();
	me.name = "tim";

	console.log(me.name);

}

startTest();
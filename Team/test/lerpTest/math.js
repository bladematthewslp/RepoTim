// Custom math library for all our mathematical needs!

function lerp(alpha, source, dest)
{
	var sourceVector = new THREE.Vector3();
	sourceVector.copy(source);
	sourceVector.multiplyScalar(1.0 - (alpha + 0.001));
	
	var destVector = new THREE.Vector3();
	destVector.copy(dest);
	destVector.multiplyScalar(alpha);
	
	var returnVector = new THREE.Vector3();
	returnVector.addVectors(sourceVector, destVector);
	
	return returnVector;

}
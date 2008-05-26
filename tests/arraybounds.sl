surface arraybounds()
{
	uniform float testArray[3] = {1, 1, 1};

	testArray[0] = 0.5;
	testArray[1] = 0.4;
	testArray[2] = 0.9;

	float c = testArray[-1];
	c = testArray[3];
	testArray[-1] = 0;
	testArray[3] = 0;
	testArray[-100] = 0;
	c = testArray[1000];

	Ci = (testArray[0], testArray[1], testArray[2]);
	Oi = Os;
}

surface derivtest()
{
	float x = 0.5*(v + u) + 0.2 * float noise(20*u, 20*v);
	float dxdx = Deriv(x,x);

	Ci = dxdx*(x, x, 1);
}

surface
curvetube (
	float Ka = 1;
	float Kd = .5;
	float Ks = .5;
	float roughness = .1;
	color specularcolor = 1;
	uniform float constantwidth = .3;
) {

	float x = 2.0 * u - 1.0;
	float y = sqrt(1.0 - x*x);

	vector Nn = normalize(N);
	float radius = constantwidth / 2.0;
	float bumpamt = radius * y / length(vtransform("object", Nn));
	N = calculatenormal(P + bumpamt*Nn);

	normal Nf = faceforward(normalize(N),I);
	Oi = Os;
	Ci = Os * (Cs * (Ka*ambient() + Kd*diffuse(Nf)) +
		specularcolor * Ks*specular(Nf,-normalize(I), roughness));
}

color sideeffect(output color c)
{
	c = (0.5,0,0);
	return color (0,0,1);
}

surface condexpr_sideeffect()
{
	Ci = (0,0.5,0);
	color c = s + 0.2*(0.5-float noise(s*10,t*10)) < 0.5
		? sideeffect(Ci) : (0,0,1);
	Ci += c;

	string shadowmap = "";
	float shad = shadowmap == "" ? 1 : (1 - shadow(shadowmap, P));
}

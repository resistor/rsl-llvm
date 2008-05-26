surface linear_ramp_with_spot(
		color dcds = (1,0,0);
		color dcdy = (0,0,1)
		)
{
	Oi = Os;
	float r = sqrt((s-0.5)*(s-0.5) + (t-0.5)*(t-0.5));
	Ci = Os*mix(dcds*s + dcdy*t, 1, 1 - step(0.1001, r));
}

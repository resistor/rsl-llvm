imager break_continue()
{
	float i = 0;
	uniform float numSteps = 24;
	uniform float format[3];
	option("Format", format);
	float x = xcomp(P)/format[0];
	float y = ycomp(P)/format[1];
	if(mod(x*4,1) > 0.98)
	{
		Ci = 0;
	}
	else
	{
		if(x < 0.5)
		{
			float intens = 0;
			for(i = 0; i <= numSteps; i+=1)
			{
				if(i/numSteps > y)
				{
					if(x < 0.25)
					{
						break;
					}
					else
					{
						float j = 0;
						while(1)
							break 2;
					}
				}
				intens += 1/numSteps;
			}
			Ci = intens*(0.5,1,0.5);
		}
		else
		{
			float intens = 0;
			for(i = 0; i <= numSteps; i+=1)
			{
				if(i/numSteps > 1-y)
				{
					if(x < 0.75)
						continue;
					else
					{
						while(1)
							if(1)
								while(1)
									continue 3;
					}
				}
				intens += 1/numSteps;
			}
			Ci = intens*(0.5,0.5,1);
		}
	}
}

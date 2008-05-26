surface divmatrix(string shadName="";)
{
    uniform matrix CurrentToShadowCamSpace = 1;
    uniform matrix CurrentToShadowProjSpace = 1;

    if (shadName != "")
    	textureinfo(shadName, "viewingmatrix", CurrentToShadowCamSpace);

    uniform matrix InvCurrentToShadowCamSpace = 1/CurrentToShadowCamSpace;

Oi = 1.0;
Ci = noise(s,t);
}

surface
face_plastic (float Ka = 1;
         float Kd = .5;
         float Ks = .5;
         float roughness = .1;
	 color specularcolor = 1;
	 uniform color facecol = 1;)
{
    normal Nf = faceforward (normalize(N),I);
    Oi = Os;
    Ci = Os * ( facecol * (Ka*ambient() + Kd*diffuse(Nf)) +
		specularcolor * Ks*specular(Nf,-normalize(I),roughness));
}

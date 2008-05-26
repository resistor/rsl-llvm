imager imageralphabug() {
  float resolution[3];
  option("Format", resolution);
  float width = resolution[0];
  float height = resolution[1];
  float s = xcomp(P) / width;
  float t = ycomp(P) / height;
  float overlayalpha = 0.5 * min(step(0.5,s), step(0.5,t));
  color overlaycolor = noise(s*10, t*10);
  
  Ci = Ci*(1-overlayalpha) + overlaycolor*overlayalpha;
  Oi = 1-(1-Oi)*(1-overlayalpha);
}

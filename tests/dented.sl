displacement
dented ( float Km = 1; float power = 3; float frequency = 1; float maxoctaves = 6; )
{
  float size;
  float magnitude = 0;
  float i;
  point PP;

  PP = transform ("shader", P);
  size = frequency;
  for (i = 0;  i < maxoctaves;  i += 1) {
      magnitude += abs (.5 - noise (PP*size)) / size;
      size *= 2;
    }
  P = P - (Km * pow (magnitude, power)) * normalize (N);
  N = calculatenormal (P);
}

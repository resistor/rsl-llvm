surface
show_xyz (float xmin = -1,
ymin = -1,
zmin = -1,
xmax = 1,
ymax = 1,
zmax = 1)
{
uniform point scale, zero;
point objP, cubeP;

if (xmax == xmin || ymax == ymin || zmax == zmin) {
} else {
scale = point (1 / (xmax - xmin), 1 / (ymax - ymin),
1 / (zmax - zmin));
zero = point (xmin, ymin, zmin);

objP = transform ("shader", P);
cubeP = (objP - zero) * scale;
Ci = color (xcomp (cubeP), ycomp(cubeP), zcomp(cubeP) );
}
}
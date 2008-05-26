surface facevertex(
 float Ka = 1;
 float Kd = 0.75;
 float Ks = 0.4;
 float roughness = 0.1;
 color specularcolor = 1;
 float density = 0.005;
 float frequency = 10;
 varying float s_facevarying = 0;
 varying float t_facevarying = 0;
 varying float s_facevertex = 0;
 varying float t_facevertex = 0;
) {

 vector IN = normalize(I);
 normal Nf = faceforward(normalize(N), I);


 float s_varying = s_facevarying;
 float t_varying = t_facevarying;
 float s_vertex = s_facevertex;
 float t_vertex = t_facevertex;


 float swidth_varying = max(abs(Du(s_varying) * du) + abs(Dv(s_varying) * dv), 1.0E-7) * frequency;
 float twidth_varying = max(abs(Du(t_varying) * du) + abs(Dv(t_varying) * dv), 1.0E-7) * frequency;
 float swidth_vertex = max(abs(Du(s_vertex) * du) + abs(Dv(s_vertex) * dv), 1.0E-7) * frequency;
 float twidth_vertex = max(abs(Du(t_vertex) * du) + abs(Dv(t_vertex) * dv), 1.0E-7) * frequency;


 float ss_varying = mod(frequency * s_varying, 1);
 float tt_varying = mod(frequency * t_varying, 1);
 float ss_vertex = mod(frequency * s_vertex, 1);
 float tt_vertex = mod(frequency * t_vertex, 1);


 float GWF = density * 0.5;
 float w_varying = smoothstep(GWF, GWF+swidth_varying, ss_varying) -
                   smoothstep(1-GWF-swidth_varying, 1-GWF, ss_varying);
 float h_varying = smoothstep(GWF, GWF+twidth_varying, tt_varying) -
                   smoothstep(1-GWF-twidth_varying, 1-GWF, tt_varying);
 float d_varying = 1 - w_varying * h_varying;
 float w_vertex = smoothstep(GWF, GWF+swidth_vertex, ss_vertex) -
                  smoothstep(1-GWF-swidth_vertex, 1-GWF, ss_vertex);
 float h_vertex = smoothstep(GWF, GWF+twidth_vertex, tt_vertex) -
                  smoothstep(1-GWF-twidth_vertex, 1-GWF, tt_vertex);
 float d_vertex = 1 - w_vertex * h_vertex;


 Oi = Os;

 color varyingcolor = color(0,1,0);
 color vertexcolor = color(1,0,0);
 color topcolor = mix(vertexcolor, varyingcolor, d_varying);
 color surfacecolor = mix(Cs, topcolor, (d_varying+d_vertex));

 Ci = Oi * surfacecolor;



}

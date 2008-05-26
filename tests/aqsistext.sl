float cubic(float Pc[]; float x; float y) {
  return Pc[0]*x*x*x + Pc[1]*x*x*y + Pc[2]*x*y*y + Pc[3]*y*y*y
  + Pc[4]*x*x + Pc[5]*x*y + Pc[6]*y*y + Pc[7]*x + Pc[8]*y + Pc[9];
}


float cubicgradx(float Pc[]; float x; float y) {
  return 3*Pc[0]*x*x + 2*Pc[1]*x*y + Pc[2]*y*y + 2*Pc[4]*x + Pc[5]*y + Pc[7];
}


float cubicgrady(float Pc[]; float x; float y) {
  return Pc[1]*x*x + 2*Pc[2]*x*y + 3*Pc[3]*y*y + Pc[5]*x + 2*Pc[6]*y + Pc[8];
}

float aqsistext_mask(float s; float t) {



float Qc1[10] = {
   -2.515455999999997e+000,
   -1.468212479999998e+002,
   -2.856536927999995e+003,
   -1.852548213599996e+004,
   -3.138538013868060e+006,
    4.184088320992688e+006,
   -9.080414450785264e+006,
   -1.916338893062538e+008,
   -3.555433156037660e+008,
    3.913333377932780e+010
};

float Qc2[10] = {
    3.176522999999993e+000,
   -1.303022699999999e+002,
    1.781684100000000e+003,
   -8.120601000000011e+003,
   -8.709029702512207e+005,
    8.446794868238396e+005,
   -1.940215343163121e+006,
   -3.388764263479087e+007,
   -4.866920986486877e+007,
    4.913481392003620e+009
};

float Sc1a[10] = {
   -1.560895999999972e+000,
   -1.076614559999988e+002,
   -2.475285371999988e+003,
   -1.897007496300003e+004,
   -4.203757925723708e+005,
   -1.008869191772405e+005,
   -7.395343386686108e+005,
    1.021959972815947e+007,
    4.231012854331020e+007,
    1.619176102444687e+009
};

float Sc1b[10] = {
    1.281290399999982e+001,
    2.375315279999981e+002,
    1.467823031999996e+003,
    3.023464536000010e+003,
    1.205445041712036e+004,
   -6.328299537503940e+004,
   -7.180880134607939e+004,
    3.392372672377217e+005,
   -1.514004847128142e+006,
    2.064460489533454e+006
};

float Sc2a[10] = {
   -3.732479999999983e-001,
   -5.782233599999982e+001,
   -2.985881183999995e+003,
   -5.139586223200000e+004,
   -2.631670560009098e+000,
    3.699543764663996e+005,
    7.819825232895721e+006,
   -1.079471991752684e+007,
   -3.985480538763968e+008,
    6.793959228746701e+009
};

float Sc2b[10] = {
    2.352637000000104e+000,
   -5.720622600000166e+001,
    4.636715160000063e+002,
   -1.252726551999998e+003,
   -1.846763602109960e+003,
   -6.592559436540401e+003,
    1.285963272360889e+005,
   -3.864184150032301e+005,
   -7.438671069995483e+006,
    1.621462796641338e+008
};

float Sc3a[10] = {
    5.053029696000000e+003,
   -4.118395881599998e+004,
    1.118878881119999e+005,
   -1.013250455279999e+005,
   -3.572216779433399e+005,
   -9.000108087994801e+005,
    5.756484950751777e+006,
    1.383060896290501e+007,
    2.711575485516367e+008,
    1.126225316211760e+009
};

float Sc3b[10] = {
    3.842405830000005e+002,
   -2.440218393000003e+003,
    5.165744301000007e+003,
   -3.645153819000006e+003,
    1.739903439690002e+004,
   -3.924885612033014e+004,
    4.897977973740215e+003,
    1.641019444597991e+006,
    1.507638564822112e+007,
   -1.138439458260446e+008
};

float Sc4a[10] = {
   -6.612913132999999e+003,
    4.398978869400002e+004,
   -9.754155596400009e+004,
    7.209517952800010e+004,
   -3.900824717933405e+005,
    1.178804479406984e+005,
    1.696167582980258e+006,
   -4.879382691530628e+007,
   -5.122662213495559e+008,
    3.782558913476014e+009
};

float Sc4b[10] = {
   -2.509911278999998e+003,
    1.145250908099999e+004,
   -1.741893765299999e+004,
    8.831234762999993e+003,
    1.364069703129298e+005,
   -9.938912235713974e+004,
   -1.704812004398699e+005,
   -8.481654673763756e+006,
   -6.854711509977910e+007,
   -3.141699222699289e+008
};

float Sc5a[10] = {
   -1.108956700000006e+001,
    1.405341540000006e+002,
   -5.936465160000021e+002,
    8.358968880000023e+002,
    2.227940722530032e+003,
   -3.338964917802015e+004,
    9.913940441721011e+004,
   -2.470532821691856e+005,
    6.859080825118593e+006,
    1.916457264647791e+008
};

float Sc5b[10] = {
   -1.000000000000011e+000,
    8.271000000000059e+001,
   -2.280314700000008e+003,
    2.095609209300000e+004,
   -1.640258734248001e+004,
    4.888192197095951e+004,
    2.539159491029130e+006,
    5.028775045349196e+006,
    1.189107392873075e+008,
    1.992721536814904e+009
};

float Sc6a[10] = {
    1.194389981000002e+003,
    5.504775690000010e+003,
    8.456912700000017e+003,
    4.330747000000009e+003,
    5.079518640874504e+005,
    2.042561801719503e+006,
    1.952816523506253e+006,
    7.791598981763187e+007,
   -6.508484938309293e+007,
   -7.029013111518749e+009
};

float Sc6b[10] = {
    8.615124999999830e+000,
    1.894907249999976e+002,
    1.389290534999992e+003,
    3.395290527000006e+003,
   -2.161032396471031e+004,
    2.697558897572927e+004,
    8.647800264089205e+003,
   -9.382476414227656e+005,
   -3.404335509997699e+006,
    3.871235795097654e+007
};

float x_global, y_global;
float x, y;
float mask1, mask2, mask3, mask4, pattern;

x_global = s * 708 + 66;
y_global = t * 708 + 230;

if((x_global<66) || (x_global>774) || (y_global<230) || (y_global>367))
  pattern = 0.5;
  else {
    y = y_global - 304;
    float Ax = x_global - 173.38;
 float A2 = -90.95*Ax - 69.82*y + 4468.2875;
    if(A2 > -1000) {
      x = Ax;
   float A1 = 90.95*x - 69.82*y + 4467.8315;
      mask1 = min(step(-45.6,y), 1-step(45.35,y));
      mask2 = min(step(-22.5, y), 1-step(-11.47,y));
      if(x<0) {
        mask3 = min(mask1, min(1-step(A1, 0), step(A1, 2364.7)));
     mask4 = min(mask2, step(-43, x));
     pattern = max(mask3, mask4);
      }
      else {
        mask3 = min(mask1, min(1-step(A2,0), step(A2,2364.7)));
     mask4 = min(mask2, 1-step(43, x));
     pattern = max(mask3, mask4);
      }
    }

    else if(x_global<429) {
      x = x_global - 336.8;
      if(x<0) {
        if(y<0) {
       mask1 = min(step(cubic(Qc2,-x,-y),0), 1-step(cubic(Qc1,-x,-y),0));
     }
     else {
       mask1 = min(step(cubic(Qc2,-x,y),0), 1-step(cubic(Qc1,-x,y),0));
     }
      }
      else {
        if(y<0) {
       mask1 = min(step(cubic(Qc2,x,-y),0), 1-step(cubic(Qc1,x,-y),0));
     }
     else {
       mask1 = min(step(cubic(Qc2,x,y),0), 1-step(cubic(Qc1,x,y),0));
     }
      }
   float Q1 = 19.6*x + 35.02*y + 1433.914;
      mask2 = min(min(step(-61.9,y), 1-step(-42.3,y)), min(1-step(Q1,0), step(Q1,588)));
      pattern = max(mask1, mask2);
    }

    else if(x_global<574) {
      x = x_global - 497.34;
      if(x<0) {
        if(y<-20.72) {
       mask1 = min(1-step(cubic(Sc5a,x,y),0), step(cubic(Sc5b,x,y),0));
       pattern = min(mask1, step(-60.34, x));
     }
     else if(y<21.78) {
       pattern = min(1-step(cubic(Sc3a,x,y),0), step(cubic(Sc3b,x,y),0));
     }
     else {
       pattern = min(1-step(cubic(Sc1a,x,y),0), 1-step(cubic(Sc1b,x,y),0));
     }
      }
      else {
        if(y<-20.72) {
       pattern = min(step(cubic(Sc6a,x,y),0), step(cubic(Sc6b,x,y),0));
     }
     else if(y<21.78) {
       pattern = min(1-step(cubic(Sc4a,x,y),0), step(cubic(Sc4b,x,y),0));
     }
     else {
       mask1 = min(1-step(cubic(Sc2a,x,y),0), step(cubic(Sc2b,x,y),0));
       pattern = min(mask1, 1-step(57.13, x));
     }
      }
    }

    else if(x_global<617) {
      pattern = min(min(step(583.46, x_global), 1-step(608.34, x_global)), min(step(258.83, y_global), 1-step(349.13, y_global)));
    }

    else {
      x = x_global - 688.52;

      if(x<0) {
        if(y<-20.72) {
       mask1 = min(1-step(cubic(Sc5a,x,y),0), step(cubic(Sc5b,x,y),0));
       pattern = min(mask1, step(-60.34, x));
     }
     else if(y<21.78) {
       pattern = min(1-step(cubic(Sc3a,x,y),0), step(cubic(Sc3b,x,y),0));
     }
     else {
       pattern = min(1-step(cubic(Sc1a,x,y),0), 1-step(cubic(Sc1b,x,y),0));
     }
      }
      else {
        if(y<-20.72) {
       pattern = min(step(cubic(Sc6a,x,y),0), step(cubic(Sc6b,x,y),0));
     }
     else if(y<21.78) {
       pattern = min(1-step(cubic(Sc4a,x,y),0), step(cubic(Sc4b,x,y),0));
     }
     else {
       mask1 = min(1-step(cubic(Sc2a,x,y),0), step(cubic(Sc2b,x,y),0));
       pattern = min(mask1, 1-step(57.13, x));
     }
      }
    }
  }
  return pattern;
}


surface aqsistext() {
  Ci = Cs * aqsistext_mask(s,t);
  Oi = Os;
}
xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 69;
 56.68064;32.52299;-10.43046;,
 53.21381;39.06496;0.65864;,
 43.23035;5.60905;-33.31225;,
 27.71184;-4.69161;-33.55836;,
 35.05215;38.73975;15.15524;,
 -45.17109;-16.05511;11.93451;,
 25.80120;37.45976;21.13347;,
 1.97135;34.16154;36.53305;,
 -1.17462;31.79782;36.13560;,
 -1.76596;31.35275;36.06038;,
 -23.90553;12.17078;30.05387;,
 -29.97552;6.91154;28.40706;,
 -47.98678;-8.69412;23.52019;,
 -48.96222;-16.12135;14.96065;,
 -50.63456;-13.23090;19.97700;,
 -48.78328;-10.05919;22.45460;,
 53.19290;44.07466;0.59194;,
 56.49111;37.85145;-9.95735;,
 34.62641;43.74323;15.41193;,
 28.02696;42.82872;19.67662;,
 40.80542;6.46418;-36.64154;,
 1.53319;39.16245;36.79755;,
 -2.05553;36.46616;36.34400;,
 -22.68722;18.58923;30.74640;,
 25.88217;-3.44041;-36.87845;,
 -30.43116;11.88005;28.64534;,
 -53.40838;-8.02872;22.41135;,
 -55.45245;-16.12113;13.88999;,
 -54.42455;-9.76985;21.05180;,
 -56.78644;-13.81511;17.89111;,
 -47.98678;-8.69412;23.52019;,
 -53.40838;-8.02872;22.41135;,
 -48.78328;-10.05919;22.45460;,
 -50.63456;-13.23090;19.97700;,
 -56.78644;-13.81511;17.89111;,
 -54.42455;-9.76985;21.05180;,
 -46.95568;-16.72465;14.18830;,
 -55.45245;-16.12113;13.88999;,
 -56.78644;-13.81511;17.89111;,
 25.88217;-3.44041;-36.87845;,
 -1.76596;31.35275;36.06038;,
 -2.05553;36.46616;36.34400;,
 -23.90553;12.17078;30.05387;,
 -22.68722;18.58923;30.74640;,
 -30.43116;11.88005;28.64534;,
 -29.97552;6.91154;28.40706;,
 1.97135;34.16154;36.53305;,
 1.53319;39.16245;36.79755;,
 -1.17462;31.79782;36.13560;,
 52.12474;41.99542;4.11903;,
 34.62641;43.74323;15.41193;,
 52.16867;37.02992;4.10868;,
 35.05215;38.73975;15.15524;,
 25.80120;37.45976;21.13347;,
 28.02696;42.82872;19.67662;,
 40.80542;6.46418;-36.64154;,
 56.68064;32.52299;-10.43046;,
 56.49111;37.85145;-9.95735;,
 53.21381;39.06496;0.65864;,
 53.19290;44.07466;0.59194;,
 52.12474;41.99542;4.11903;,
 52.16867;37.02992;4.10868;,
 -45.17109;-16.05511;11.93451;,
 -48.96222;-16.12135;14.96065;,
 -46.95568;-16.72465;14.18830;,
 52.16867;37.02992;4.10868;,
 52.12474;41.99542;4.11903;,
 43.23035;5.60905;-33.31225;,
 40.80542;6.46418;-36.64154;;
 
 60;
 3;0,1,2;,
 3;2,1,3;,
 3;1,4,3;,
 3;3,4,5;,
 3;4,6,5;,
 3;6,7,5;,
 3;7,8,5;,
 3;8,9,5;,
 3;9,10,5;,
 3;10,11,5;,
 3;11,12,5;,
 3;5,12,13;,
 3;13,12,14;,
 3;12,15,14;,
 3;16,17,18;,
 3;18,17,19;,
 3;17,20,19;,
 3;19,20,21;,
 3;21,20,22;,
 3;22,20,23;,
 3;20,24,23;,
 3;23,24,25;,
 3;25,24,26;,
 3;24,27,26;,
 3;26,27,28;,
 3;27,29,28;,
 3;30,31,32;,
 3;32,31,33;,
 3;33,31,34;,
 3;31,35,34;,
 3;36,13,37;,
 3;13,14,37;,
 3;14,38,37;,
 3;3,5,39;,
 3;39,5,37;,
 3;5,36,37;,
 3;40,41,42;,
 3;41,43,42;,
 3;43,44,42;,
 3;42,44,45;,
 3;45,44,30;,
 3;44,31,30;,
 3;46,47,48;,
 3;47,41,48;,
 3;41,40,48;,
 3;49,50,51;,
 3;51,50,52;,
 3;52,50,53;,
 3;50,54,53;,
 3;54,47,53;,
 3;47,46,53;,
 4;2,3,39,55;,
 3;56,57,58;,
 3;57,59,58;,
 3;59,60,58;,
 3;60,61,58;,
 3;62,63,64;,
 3;65,4,1;,
 3;16,18,66;,
 4;57,56,67,68;;
 
 MeshMaterialList {
  1;
  60;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\stone.jpg";
   }
  }
 }
 MeshNormals {
  56;
  0.195814;-0.819932;0.537929;,
  0.454413;-0.697815;0.553681;,
  0.718687;0.004913;0.695316;,
  0.385355;-0.408380;0.827483;,
  0.549820;-0.247049;0.797912;,
  -0.454390;0.697830;-0.553681;,
  -0.454376;0.697833;-0.553690;,
  -0.454443;0.697770;-0.553713;,
  -0.454358;0.697848;-0.553685;,
  -0.073533;-0.993754;0.083936;,
  -0.035609;-0.738363;0.673463;,
  0.308057;-0.541682;0.782101;,
  0.150193;-0.355161;0.922660;,
  0.904394;-0.269396;-0.330903;,
  0.135959;-0.519657;0.843488;,
  0.828328;-0.329331;0.453227;,
  -0.454595;0.697765;-0.553595;,
  0.454350;-0.697793;0.553761;,
  0.806553;0.205717;0.554214;,
  0.454343;-0.697792;0.553768;,
  0.454374;-0.697819;0.553708;,
  0.790331;-0.386708;0.475221;,
  -0.454649;0.697769;-0.553546;,
  -0.454389;0.697831;-0.553681;,
  -0.454319;0.697873;-0.553686;,
  -0.454567;0.697784;-0.553594;,
  -0.454386;0.697833;-0.553681;,
  -0.454383;0.697832;-0.553684;,
  -0.454462;0.697752;-0.553721;,
  0.454417;-0.697826;0.553664;,
  0.527808;-0.450013;0.720352;,
  -0.454433;0.697779;-0.553710;,
  -0.454484;0.697722;-0.553740;,
  -0.230793;-0.408233;0.883221;,
  -0.232043;-0.510929;0.827712;,
  -0.161230;-0.718375;0.676714;,
  0.883873;-0.178166;-0.432464;,
  -0.075799;-0.982400;0.170719;,
  0.220741;-0.866312;-0.448082;,
  -0.055723;-0.944092;-0.324938;,
  0.126873;-0.903093;-0.410277;,
  -0.207691;-0.065895;0.975973;,
  -0.144757;-0.062943;0.987463;,
  -0.207712;-0.065876;0.975969;,
  -0.207717;-0.065876;0.975968;,
  -0.207722;-0.065871;0.975968;,
  -0.207733;-0.065856;0.975966;,
  0.243835;-0.029904;0.969356;,
  0.546602;0.153285;0.823243;,
  0.542453;0.003074;0.840081;,
  0.714192;-0.345234;-0.608887;,
  0.999370;0.035080;0.005479;,
  0.865346;0.270797;0.421717;,
  0.427616;0.716316;0.551395;,
  -0.427669;-0.715930;-0.551854;,
  0.815410;0.079935;-0.573338;;
  60;
  3;21,15,20;,
  3;20,15,1;,
  3;15,30,1;,
  3;1,30,29;,
  3;30,4,29;,
  3;4,3,29;,
  3;3,12,29;,
  3;12,11,29;,
  3;11,19,29;,
  3;19,17,29;,
  3;17,14,29;,
  3;29,14,0;,
  3;0,14,10;,
  3;13,13,13;,
  3;31,28,32;,
  3;32,28,7;,
  3;28,27,7;,
  3;7,27,8;,
  3;8,27,6;,
  3;6,27,26;,
  3;27,23,26;,
  3;26,23,5;,
  3;5,23,16;,
  3;23,25,16;,
  3;16,25,22;,
  3;25,24,22;,
  3;14,33,34;,
  3;34,33,10;,
  3;10,33,35;,
  3;36,36,36;,
  3;9,0,37;,
  3;0,10,37;,
  3;10,35,37;,
  3;38,39,40;,
  3;40,39,37;,
  3;39,9,37;,
  3;41,42,43;,
  3;42,44,43;,
  3;44,45,43;,
  3;43,45,46;,
  3;46,45,14;,
  3;45,33,14;,
  3;3,47,12;,
  3;47,42,12;,
  3;42,11,12;,
  3;18,48,2;,
  3;2,48,30;,
  3;30,48,4;,
  3;48,49,4;,
  3;49,47,4;,
  3;47,3,4;,
  4;50,38,40,50;,
  3;21,51,15;,
  3;51,52,15;,
  3;52,18,15;,
  3;18,2,15;,
  3;53,53,53;,
  3;54,54,54;,
  3;52,48,18;,
  4;51,55,50,50;;
 }
 MeshTextureCoords {
  69;
  0.250050;0.599740;,
  0.253900;0.587320;,
  0.264980;0.625360;,
  0.282210;0.625630;,
  0.274060;0.571090;,
  0.363120;0.574700;,
  0.284330;0.564400;,
  0.310780;0.547160;,
  0.314280;0.547600;,
  0.314930;0.547690;,
  0.339510;0.554410;,
  0.346250;0.556260;,
  0.366240;0.561730;,
  0.367320;0.571310;,
  0.369180;0.565690;,
  0.367130;0.562920;,
  0.253710;0.686290;,
  0.250050;0.674480;,
  0.274320;0.702880;,
  0.281650;0.707660;,
  0.267460;0.644610;,
  0.311060;0.726830;,
  0.315040;0.726320;,
  0.337950;0.720050;,
  0.284030;0.644340;,
  0.346540;0.717700;,
  0.372050;0.710720;,
  0.374320;0.701180;,
  0.373180;0.709200;,
  0.375800;0.705660;,
  0.400640;0.570640;,
  0.394630;0.571390;,
  0.399760;0.569110;,
  0.397700;0.565560;,
  0.390880;0.564910;,
  0.393500;0.569440;,
  0.365100;0.572180;,
  0.374530;0.572510;,
  0.376010;0.568030;,
  0.284240;0.629350;,
  0.451950;0.615480;,
  0.451630;0.621200;,
  0.427380;0.594000;,
  0.428730;0.601190;,
  0.420130;0.593680;,
  0.420640;0.588110;,
  0.456100;0.618620;,
  0.455620;0.624220;,
  0.452610;0.615970;,
  0.511780;0.627390;,
  0.492350;0.629350;,
  0.511820;0.621830;,
  0.492820;0.623750;,
  0.482550;0.622310;,
  0.485020;0.628320;,
  0.267680;0.629080;,
  0.884040;0.261420;,
  0.883510;0.267390;,
  0.871730;0.268750;,
  0.871800;0.274360;,
  0.867880;0.272030;,
  0.867900;0.266470;,
  0.092890;0.604520;,
  0.097100;0.607900;,
  0.094870;0.607040;,
  0.255060;0.583460;,
  0.254900;0.690240;,
  0.909440;0.231290;,
  0.913130;0.232250;;
 }
}

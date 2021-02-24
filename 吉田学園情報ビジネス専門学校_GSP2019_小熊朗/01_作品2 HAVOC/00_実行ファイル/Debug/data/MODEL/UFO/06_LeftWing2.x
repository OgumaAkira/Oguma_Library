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
 42;
 -147.81130;-5.96330;242.18039;,
 -111.61710;-8.94040;151.10200;,
 -92.02060;-30.86650;160.93630;,
 -134.13750;-21.26110;249.04250;,
 -65.11680;-22.84660;174.11870;,
 -115.36701;-15.66600;258.23980;,
 -57.80880;7.09870;177.46680;,
 -110.26750;5.22760;260.57499;,
 -77.40600;29.02480;167.63179;,
 -123.94059;20.52540;253.71360;,
 -104.30980;21.00490;154.44870;,
 -142.71251;14.93030;244.51630;,
 -111.61710;-8.94040;151.10200;,
 -147.81130;-5.96330;242.18039;,
 -70.47600;-11.78030;51.87700;,
 -45.42230;-39.81180;64.45040;,
 -11.02710;-29.55890;81.30360;,
 -1.68420;8.72550;85.58270;,
 -26.73790;36.75700;73.00930;,
 -61.13380;26.50340;56.15610;,
 -70.47600;-11.78030;51.87700;,
 -38.19480;-8.86760;8.49520;,
 -19.49220;-29.79340;17.88150;,
 6.18590;-22.13960;30.46330;,
 13.16000;6.44070;33.65810;,
 -5.54330;27.36720;24.27110;,
 -31.22070;19.71340;11.69000;,
 -38.19480;-8.86760;8.49520;,
 -134.13750;-21.26110;249.04250;,
 -210.94291;0.65380;412.30279;,
 -147.81130;-5.96330;242.18039;,
 -115.36701;-15.66600;258.23980;,
 -110.26750;5.22760;260.57499;,
 -123.94059;20.52540;253.71360;,
 -142.71251;14.93030;244.51630;,
 -38.19480;-8.86760;8.49520;,
 -1.09760;-1.96420;-0.00420;,
 -19.49220;-29.79340;17.88150;,
 6.18590;-22.13960;30.46330;,
 13.16000;6.44070;33.65810;,
 -5.54330;27.36720;24.27110;,
 -31.22070;19.71340;11.69000;;
 
 30;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;1,14,15,2;,
 4;2,15,16,4;,
 4;4,16,17,6;,
 4;6,17,18,8;,
 4;8,18,19,10;,
 4;10,19,20,12;,
 4;14,21,22,15;,
 4;15,22,23,16;,
 4;16,23,24,17;,
 4;17,24,25,18;,
 4;18,25,26,19;,
 4;19,26,27,20;,
 3;28,29,30;,
 3;31,29,28;,
 3;32,29,31;,
 3;33,29,32;,
 3;34,29,33;,
 3;30,29,34;,
 3;35,36,37;,
 3;37,36,38;,
 3;38,36,39;,
 3;39,36,40;,
 3;40,36,41;,
 3;41,36,35;;
 
 MeshMaterialList {
  7;
  30;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\gsp012\\Desktop\\UFO_Triangle_v1_L2.123c33ed20b0-6dc4-4836-9410-f5bf4abee507\\13885_UFO_Triangle_diffuse - Copy.jpg";
   }
  }
  Material {
   0.204000;0.225600;0.501600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.238400;0.599200;0.156800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.533600;0.210400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.060000;0.207200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.138400;0.197600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  32;
  -0.670982;-0.704056;-0.232569;,
  0.185956;-0.960921;0.205065;,
  0.814384;-0.256925;0.520355;,
  0.587574;0.704055;0.398828;,
  -0.268181;0.962609;-0.038249;,
  -0.664342;-0.705054;-0.248093;,
  0.193721;-0.962450;0.190161;,
  0.823203;-0.257468;0.506011;,
  0.596005;0.705062;0.384273;,
  -0.261082;0.963832;-0.053521;,
  -0.610623;-0.706355;-0.358053;,
  0.251257;-0.965063;0.074318;,
  0.883057;-0.259224;0.391169;,
  0.652143;0.706347;0.275288;,
  -0.210486;0.964840;-0.157413;,
  -0.498504;-0.224203;-0.837393;,
  0.034924;-0.824987;-0.564072;,
  0.769900;-0.607563;-0.195244;,
  0.971228;0.216124;-0.100030;,
  0.433376;0.819280;-0.375453;,
  -0.301321;0.596431;-0.743959;,
  -0.674924;-0.703351;-0.223103;,
  0.500959;-0.523973;-0.688834;,
  -0.898515;0.258893;-0.354465;,
  -0.892124;0.259072;-0.370130;,
  -0.841730;0.258386;-0.474055;,
  0.181210;-0.959858;0.214094;,
  0.808912;-0.256556;0.529000;,
  0.582369;0.703344;0.407619;,
  -0.272460;0.961731;-0.028965;,
  -0.902274;0.258747;-0.344894;,
  0.263312;0.498227;-0.826097;;
  30;
  4;0,5,5,0;,
  4;1,6,6,1;,
  4;2,7,7,2;,
  4;3,8,8,3;,
  4;4,9,9,4;,
  4;23,24,24,23;,
  4;5,10,10,5;,
  4;6,11,11,6;,
  4;7,12,12,7;,
  4;8,13,13,8;,
  4;9,14,14,9;,
  4;24,25,25,24;,
  4;10,15,16,10;,
  4;11,16,17,11;,
  4;12,17,18,12;,
  4;13,18,19,13;,
  4;14,19,20,14;,
  4;25,20,15,25;,
  3;0,21,0;,
  3;1,26,1;,
  3;2,27,2;,
  3;3,28,3;,
  3;4,29,4;,
  3;23,30,23;,
  3;15,22,16;,
  3;16,22,17;,
  3;17,22,18;,
  3;18,31,19;,
  3;19,31,20;,
  3;20,31,15;;
 }
 MeshTextureCoords {
  42;
  0.375000;0.687500;,
  0.375000;0.562190;,
  0.416670;0.562190;,
  0.416670;0.687500;,
  0.458330;0.562190;,
  0.458330;0.687500;,
  0.500000;0.562190;,
  0.500000;0.687500;,
  0.541670;0.562190;,
  0.541670;0.687500;,
  0.583330;0.562190;,
  0.583330;0.687500;,
  0.625000;0.562190;,
  0.625000;0.687500;,
  0.375000;0.436870;,
  0.416670;0.436870;,
  0.458330;0.436870;,
  0.500000;0.436870;,
  0.541670;0.436870;,
  0.583330;0.436870;,
  0.625000;0.436870;,
  0.375000;0.311560;,
  0.416670;0.311560;,
  0.458330;0.311560;,
  0.500000;0.311560;,
  0.541670;0.311560;,
  0.583330;0.311560;,
  0.625000;0.311560;,
  0.421880;0.979070;,
  0.500000;0.850000;,
  0.578120;0.979070;,
  0.343750;0.843750;,
  0.421880;0.708430;,
  0.578120;0.708430;,
  0.656250;0.843750;,
  0.578120;0.020930;,
  0.500000;0.162500;,
  0.421880;0.020930;,
  0.343750;0.156250;,
  0.421880;0.291570;,
  0.578120;0.291570;,
  0.656250;0.156250;;
 }
}

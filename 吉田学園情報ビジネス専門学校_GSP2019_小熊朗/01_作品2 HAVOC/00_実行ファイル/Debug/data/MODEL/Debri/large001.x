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
 63;
 348.39240;17.42420;2.38120;,
 269.58081;17.42420;-180.55350;,
 261.91260;17.42420;205.70551;,
 92.49910;17.42420;-218.00220;,
 155.07950;17.42420;147.61530;,
 -58.64490;17.42420;31.39990;,
 -144.78470;17.42420;-153.17661;,
 -233.46840;17.42420;-63.65740;,
 -244.18500;17.42420;-126.02210;,
 -274.36890;17.42420;-97.70490;,
 -255.42610;17.42420;-120.46090;,
 348.43079;-2.47550;2.67200;,
 333.53970;-2.47550;37.68830;,
 269.43991;-2.47550;-180.67480;,
 256.91110;-2.47550;217.84950;,
 93.27800;-2.47550;-217.92610;,
 158.53380;-2.47550;164.35800;,
 89.32270;-2.47550;126.72460;,
 -175.98151;-2.47550;-144.36929;,
 -38.26950;-2.47550;57.34530;,
 -271.64569;-2.47550;-69.55300;,
 -286.55829;-2.47550;-114.16220;,
 -302.38751;-2.47550;-95.14330;,
 -302.38751;9.40370;-95.14330;,
 -299.14001;16.98520;-99.04430;,
 -302.38751;-2.47550;-95.14330;,
 -286.55829;-2.47550;-114.16220;,
 -286.54251;-1.47840;-114.18020;,
 269.58081;17.42420;-180.55350;,
 269.43991;-2.47550;-180.67480;,
 93.27800;-2.47550;-217.92610;,
 92.49910;17.42420;-218.00220;,
 348.39240;17.42420;2.38120;,
 348.43079;-2.47550;2.67200;,
 269.43991;-2.47550;-180.67480;,
 269.58081;17.42420;-180.55350;,
 261.91260;17.42420;205.70551;,
 155.07950;17.42420;147.61530;,
 256.91110;-2.47550;217.84950;,
 158.53380;-2.47550;164.35800;,
 89.32270;-2.47550;126.72460;,
 -58.64490;17.42420;31.39990;,
 -38.26950;-2.47550;57.34530;,
 -271.64569;-2.47550;-69.55300;,
 -233.46840;17.42420;-63.65740;,
 -274.36890;33.22150;-97.70490;,
 -302.38751;9.40370;-95.14330;,
 -271.21939;40.57560;-101.48460;,
 -299.14001;16.98520;-99.04430;,
 261.91260;17.42420;205.70551;,
 333.53970;-2.47550;37.68830;,
 256.91110;-2.47550;217.84950;,
 -175.98151;-2.47550;-144.36929;,
 -244.18500;17.42420;-126.02210;,
 -144.78470;17.42420;-153.17661;,
 -271.21939;40.57560;-101.48460;,
 -255.42610;17.42420;-120.46090;,
 -233.46840;17.42420;-63.65740;,
 -274.36890;17.42420;-97.70490;,
 -274.36890;33.22150;-97.70490;,
 -274.36890;17.42420;-97.70490;,
 -255.42610;17.42420;-120.46090;,
 -302.38751;-2.47550;-95.14330;;
 
 49;
 3;0,1,2;,
 3;1,3,2;,
 3;2,3,4;,
 3;4,3,5;,
 3;3,6,5;,
 3;5,6,7;,
 3;6,8,7;,
 3;7,8,9;,
 3;8,10,9;,
 3;11,12,13;,
 3;12,14,13;,
 3;13,14,15;,
 3;14,16,15;,
 3;16,17,15;,
 3;15,17,18;,
 3;17,19,18;,
 3;19,20,18;,
 3;18,20,21;,
 3;20,22,21;,
 3;23,24,25;,
 3;25,24,26;,
 3;24,27,26;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 3;36,37,38;,
 3;38,37,39;,
 3;39,37,40;,
 3;37,41,40;,
 3;40,41,42;,
 3;42,41,43;,
 3;41,44,43;,
 3;44,45,43;,
 3;43,45,46;,
 3;47,48,45;,
 3;48,46,45;,
 3;32,49,33;,
 3;33,49,50;,
 3;49,51,50;,
 3;26,27,52;,
 3;27,53,52;,
 3;53,54,52;,
 3;52,54,30;,
 3;54,31,30;,
 3;55,56,24;,
 3;24,56,27;,
 3;56,53,27;,
 3;57,58,59;,
 4;47,45,60,61;,
 3;46,62,43;;
 
 MeshMaterialList {
  1;
  49;
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
  36;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.180508;0.925870;0.331937;,
  -0.768544;0.000000;-0.639797;,
  -0.109548;0.973350;0.201468;,
  -0.258579;0.840828;0.475548;,
  -0.399275;0.548558;0.734618;,
  -0.297793;0.781908;0.547666;,
  -0.441737;0.160613;-0.882650;,
  -0.649450;0.165309;-0.742218;,
  -0.399380;0.548734;0.734430;,
  -0.768580;0.000015;-0.639754;,
  -0.625712;-0.004383;-0.780042;,
  0.633603;0.000213;-0.773658;,
  -0.109439;-0.007994;-0.993961;,
  -0.029131;-0.004926;-0.999564;,
  0.999996;0.001873;-0.002326;,
  0.990292;0.004156;0.138937;,
  -0.399381;0.548635;0.734503;,
  -0.399377;0.548646;0.734497;,
  -0.399379;0.548666;0.734481;,
  -0.399370;0.548689;0.734468;,
  -0.460928;0.452167;0.763603;,
  -0.499954;0.381471;0.777513;,
  -0.399381;0.548736;0.734427;,
  0.920201;0.007733;0.391369;,
  0.920204;0.007852;0.391361;,
  0.920194;0.007572;0.391389;,
  -0.263501;-0.013666;-0.964563;,
  -0.318849;0.125983;-0.939395;,
  -0.263506;-0.013873;-0.964558;,
  -0.407074;0.396687;-0.822758;,
  -0.407063;0.396694;-0.822760;,
  0.639782;0.000000;-0.768556;,
  0.768521;-0.000122;0.639825;,
  -0.639773;0.000000;0.768564;;
  49;
  3;0,0,4;,
  3;0,0,4;,
  3;4,0,7;,
  3;7,0,5;,
  3;0,0,5;,
  3;5,0,2;,
  3;0,0,2;,
  3;2,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;3,9,11;,
  3;11,9,12;,
  3;9,8,12;,
  4;13,13,14,15;,
  4;16,17,13,13;,
  3;4,7,18;,
  3;18,7,19;,
  3;19,7,20;,
  3;7,5,20;,
  3;20,5,21;,
  3;21,5,22;,
  3;5,2,22;,
  3;2,10,22;,
  3;22,10,23;,
  3;6,24,10;,
  3;24,23,10;,
  3;16,25,17;,
  3;17,25,26;,
  3;25,27,26;,
  3;12,8,28;,
  3;8,29,28;,
  3;29,30,28;,
  3;28,30,14;,
  3;30,15,14;,
  3;31,32,9;,
  3;9,32,8;,
  3;32,29,8;,
  3;33,33,33;,
  4;34,34,34,34;,
  3;23,35,22;;
 }
 MeshTextureCoords {
  63;
  0.112100;0.686300;,
  0.127670;0.649830;,
  0.129190;0.726830;,
  0.162670;0.642360;,
  0.150310;0.715250;,
  0.192550;0.692080;,
  0.209570;0.655290;,
  0.227100;0.673130;,
  0.229220;0.660700;,
  0.235190;0.666340;,
  0.231440;0.661810;,
  0.112100;0.784710;,
  0.115040;0.777730;,
  0.127710;0.821260;,
  0.130190;0.741820;,
  0.162530;0.828690;,
  0.149630;0.752480;,
  0.163310;0.759980;,
  0.215750;0.814020;,
  0.188530;0.773810;,
  0.234660;0.799110;,
  0.237600;0.808000;,
  0.240730;0.804210;,
  0.120480;0.035120;,
  0.119840;0.036640;,
  0.120480;0.032760;,
  0.117350;0.032760;,
  0.117350;0.032960;,
  0.007430;0.036720;,
  0.007460;0.032760;,
  0.042280;0.032760;,
  0.042430;0.036720;,
  0.356820;0.388140;,
  0.356770;0.384180;,
  0.393010;0.384180;,
  0.392980;0.388140;,
  0.955630;0.021620;,
  0.934510;0.021620;,
  0.954640;0.017650;,
  0.935200;0.017650;,
  0.921520;0.017650;,
  0.892270;0.021620;,
  0.896300;0.017650;,
  0.850170;0.017650;,
  0.857720;0.021620;,
  0.849630;0.024770;,
  0.844090;0.020020;,
  0.850260;0.026230;,
  0.844740;0.021530;,
  0.316640;0.388140;,
  0.349850;0.384180;,
  0.314240;0.384180;,
  0.095500;0.032760;,
  0.108980;0.036720;,
  0.089330;0.036720;,
  0.114320;0.041340;,
  0.111200;0.036720;,
  0.384920;0.403140;,
  0.393010;0.403140;,
  0.393010;0.406290;,
  0.849630;0.021620;,
  0.853380;0.021620;,
  0.844090;0.017650;;
 }
}

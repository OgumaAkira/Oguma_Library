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
 154;
 -0.00000;24.37836;-1.51601;,
 3.71322;23.39085;-7.29389;,
 -0.00000;23.39085;-8.38419;,
 -0.00000;24.37836;-1.51601;,
 6.24751;23.39085;-4.36916;,
 -0.00000;24.37836;-1.51601;,
 6.79827;23.39085;-0.53857;,
 -0.00000;24.37836;-1.51601;,
 5.19062;23.39085;2.98168;,
 -0.00000;24.37836;-1.51601;,
 1.93499;23.39085;5.07395;,
 -0.00000;24.37836;-1.51601;,
 -1.93499;23.39085;5.07395;,
 -0.00000;24.37836;-1.51601;,
 -5.19062;23.39085;2.98168;,
 -0.00000;24.37836;-1.51601;,
 -6.79827;23.39085;-0.53857;,
 -0.00000;24.37836;-1.51601;,
 -6.24751;23.39085;-4.36916;,
 -0.00000;24.37836;-1.51601;,
 -3.71322;23.39085;-7.29389;,
 -0.00000;24.37836;-1.51601;,
 -0.00000;23.39085;-8.38419;,
 7.12561;20.50838;-12.60368;,
 -0.00000;20.50838;-14.69594;,
 11.98888;20.50838;-6.99115;,
 13.04578;20.50838;0.35969;,
 9.96073;20.50838;7.11501;,
 3.71321;20.50838;11.13004;,
 -3.71322;20.50838;11.13004;,
 -9.96073;20.50838;7.11500;,
 -13.04578;20.50838;0.35968;,
 -11.98888;20.50838;-6.99116;,
 -7.12561;20.50838;-12.60368;,
 -0.00000;20.50838;-14.69594;,
 9.96073;15.96442;-17.01521;,
 -0.00000;15.96442;-19.93995;,
 16.75900;15.96442;-9.16959;,
 18.23640;15.96442;1.10599;,
 13.92388;15.96442;10.54909;,
 5.19062;15.96442;16.16162;,
 -5.19062;15.96442;16.16162;,
 -13.92389;15.96442;10.54908;,
 -18.23641;15.96442;1.10598;,
 -16.75900;15.96442;-9.16959;,
 -9.96073;15.96442;-17.01521;,
 -0.00000;15.96442;-19.93995;,
 11.98888;10.12713;-20.17110;,
 -0.00000;10.12713;-23.69135;,
 20.17139;10.12713;-10.72798;,
 21.94963;10.12713;1.63987;,
 16.75900;10.12713;13.00574;,
 6.24751;10.12713;19.76107;,
 -6.24752;10.12713;19.76106;,
 -16.75900;10.12713;13.00573;,
 -21.94963;10.12713;1.63986;,
 -20.17139;10.12713;-10.72798;,
 -11.98888;10.12713;-20.17110;,
 -0.00000;10.12713;-23.69135;,
 13.04578;3.46940;-21.81565;,
 -0.00000;3.46940;-25.64624;,
 21.94963;3.46940;-11.54007;,
 23.88462;3.46940;1.91808;,
 18.23640;3.46940;14.28592;,
 6.79826;3.46940;21.63677;,
 -6.79827;3.46940;21.63677;,
 -18.23642;3.46940;14.28592;,
 -23.88462;3.46940;1.91807;,
 -21.94963;3.46940;-11.54007;,
 -13.04578;3.46940;-21.81565;,
 -0.00000;3.46940;-25.64624;,
 13.04578;-3.46940;-21.81565;,
 -0.00000;-3.46940;-25.64624;,
 21.94963;-3.46940;-11.54007;,
 23.88462;-3.46940;1.91808;,
 18.23640;-3.46940;14.28592;,
 6.79826;-3.46940;21.63677;,
 -6.79827;-3.46940;21.63677;,
 -18.23642;-3.46940;14.28592;,
 -23.88462;-3.46940;1.91807;,
 -21.94963;-3.46940;-11.54007;,
 -13.04578;-3.46940;-21.81565;,
 -0.00000;-3.46940;-25.64624;,
 11.98888;-10.12714;-20.17110;,
 -0.00000;-10.12714;-23.69135;,
 20.17139;-10.12714;-10.72798;,
 21.94963;-10.12714;1.63987;,
 16.75900;-10.12714;13.00574;,
 6.24751;-10.12714;19.76106;,
 -6.24752;-10.12714;19.76106;,
 -16.75900;-10.12714;13.00573;,
 -21.94963;-10.12714;1.63985;,
 -20.17139;-10.12714;-10.72798;,
 -11.98888;-10.12714;-20.17110;,
 -0.00000;-10.12714;-23.69135;,
 9.96073;-15.96443;-17.01521;,
 -0.00000;-15.96443;-19.93994;,
 16.75900;-15.96443;-9.16959;,
 18.23640;-15.96443;1.10599;,
 13.92388;-15.96443;10.54909;,
 5.19062;-15.96443;16.16162;,
 -5.19062;-15.96443;16.16161;,
 -13.92388;-15.96443;10.54908;,
 -18.23641;-15.96443;1.10598;,
 -16.75900;-15.96443;-9.16959;,
 -9.96073;-15.96443;-17.01521;,
 -0.00000;-15.96443;-19.93994;,
 7.12561;-20.50838;-12.60367;,
 -0.00000;-20.50838;-14.69594;,
 11.98888;-20.50838;-6.99115;,
 13.04578;-20.50838;0.35969;,
 9.96073;-20.50838;7.11501;,
 3.71321;-20.50838;11.13004;,
 -3.71322;-20.50838;11.13004;,
 -9.96073;-20.50838;7.11500;,
 -13.04578;-20.50838;0.35968;,
 -11.98888;-20.50838;-6.99116;,
 -7.12561;-20.50838;-12.60367;,
 -0.00000;-20.50838;-14.69594;,
 3.71322;-23.39085;-7.29389;,
 -0.00000;-23.39085;-8.38419;,
 6.24751;-23.39085;-4.36916;,
 6.79827;-23.39085;-0.53857;,
 5.19062;-23.39085;2.98169;,
 1.93499;-23.39085;5.07395;,
 -1.93499;-23.39085;5.07395;,
 -5.19062;-23.39085;2.98168;,
 -6.79827;-23.39085;-0.53857;,
 -6.24751;-23.39085;-4.36916;,
 -3.71322;-23.39085;-7.29389;,
 -0.00000;-23.39085;-8.38419;,
 -0.00000;-23.39085;-8.38419;,
 3.71322;-23.39085;-7.29389;,
 -0.00000;-24.37836;-1.51601;,
 6.24751;-23.39085;-4.36916;,
 -0.00000;-24.37836;-1.51601;,
 6.79827;-23.39085;-0.53857;,
 -0.00000;-24.37836;-1.51601;,
 5.19062;-23.39085;2.98169;,
 -0.00000;-24.37836;-1.51601;,
 1.93499;-23.39085;5.07395;,
 -0.00000;-24.37836;-1.51601;,
 -1.93499;-23.39085;5.07395;,
 -0.00000;-24.37836;-1.51601;,
 -5.19062;-23.39085;2.98168;,
 -0.00000;-24.37836;-1.51601;,
 -6.79827;-23.39085;-0.53857;,
 -0.00000;-24.37836;-1.51601;,
 -6.24751;-23.39085;-4.36916;,
 -0.00000;-24.37836;-1.51601;,
 -3.71322;-23.39085;-7.29389;,
 -0.00000;-24.37836;-1.51601;,
 -0.00000;-23.39085;-8.38419;,
 -0.00000;-24.37836;-1.51601;;
 
 121;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 4;2,1,23,24;,
 4;1,4,25,23;,
 4;4,6,26,25;,
 4;6,8,27,26;,
 4;8,10,28,27;,
 4;10,12,29,28;,
 4;12,14,30,29;,
 4;14,16,31,30;,
 4;16,18,32,31;,
 4;18,20,33,32;,
 4;20,22,34,33;,
 4;24,23,35,36;,
 4;23,25,37,35;,
 4;25,26,38,37;,
 4;26,27,39,38;,
 4;27,28,40,39;,
 4;28,29,41,40;,
 4;29,30,42,41;,
 4;30,31,43,42;,
 4;31,32,44,43;,
 4;32,33,45,44;,
 4;33,34,46,45;,
 4;36,35,47,48;,
 4;35,37,49,47;,
 4;37,38,50,49;,
 4;38,39,51,50;,
 4;39,40,52,51;,
 4;40,41,53,52;,
 4;41,42,54,53;,
 4;42,43,55,54;,
 4;43,44,56,55;,
 4;44,45,57,56;,
 4;45,46,58,57;,
 4;48,47,59,60;,
 4;47,49,61,59;,
 4;49,50,62,61;,
 4;50,51,63,62;,
 4;51,52,64,63;,
 4;52,53,65,64;,
 4;53,54,66,65;,
 4;54,55,67,66;,
 4;55,56,68,67;,
 4;56,57,69,68;,
 4;57,58,70,69;,
 4;60,59,71,72;,
 4;59,61,73,71;,
 4;61,62,74,73;,
 4;62,63,75,74;,
 4;63,64,76,75;,
 4;64,65,77,76;,
 4;65,66,78,77;,
 4;66,67,79,78;,
 4;67,68,80,79;,
 4;68,69,81,80;,
 4;69,70,82,81;,
 4;72,71,83,84;,
 4;71,73,85,83;,
 4;73,74,86,85;,
 4;74,75,87,86;,
 4;75,76,88,87;,
 4;76,77,89,88;,
 4;77,78,90,89;,
 4;78,79,91,90;,
 4;79,80,92,91;,
 4;80,81,93,92;,
 4;81,82,94,93;,
 4;84,83,95,96;,
 4;83,85,97,95;,
 4;85,86,98,97;,
 4;86,87,99,98;,
 4;87,88,100,99;,
 4;88,89,101,100;,
 4;89,90,102,101;,
 4;90,91,103,102;,
 4;91,92,104,103;,
 4;92,93,105,104;,
 4;93,94,106,105;,
 4;96,95,107,108;,
 4;95,97,109,107;,
 4;97,98,110,109;,
 4;98,99,111,110;,
 4;99,100,112,111;,
 4;100,101,113,112;,
 4;101,102,114,113;,
 4;102,103,115,114;,
 4;103,104,116,115;,
 4;104,105,117,116;,
 4;105,106,118,117;,
 4;108,107,119,120;,
 4;107,109,121,119;,
 4;109,110,122,121;,
 4;110,111,123,122;,
 4;111,112,124,123;,
 4;112,113,125,124;,
 4;113,114,126,125;,
 4;114,115,127,126;,
 4;115,116,128,127;,
 4;116,117,129,128;,
 4;117,118,130,129;,
 3;131,132,133;,
 3;132,134,135;,
 3;134,136,137;,
 3;136,138,139;,
 3;138,140,141;,
 3;140,142,143;,
 3;142,144,145;,
 3;144,146,147;,
 3;146,148,149;,
 3;148,150,151;,
 3;150,152,153;;
 
 MeshMaterialList {
  1;
  121;
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
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.400000;0.400000;;
   TextureFilename {
    "data\\TEXTURE\\magic001.png";
   }
  }
 }
 MeshNormals {
  112;
  -0.000000;1.000000;0.000000;,
  0.000000;0.959625;-0.281284;,
  0.152074;0.959625;-0.236631;,
  0.255865;0.959625;-0.116850;,
  0.278421;0.959625;0.040031;,
  0.212580;0.959625;0.184202;,
  0.079247;0.959625;0.269890;,
  -0.079247;0.959625;0.269890;,
  -0.212580;0.959625;0.184202;,
  -0.278421;0.959625;0.040031;,
  -0.255865;0.959625;-0.116850;,
  -0.152074;0.959625;-0.236631;,
  0.000000;0.841672;-0.539989;,
  0.291940;0.841672;-0.454268;,
  0.491191;0.841672;-0.224320;,
  0.534493;0.841672;0.076848;,
  0.408097;0.841672;0.353618;,
  0.152132;0.841672;0.518116;,
  -0.152133;0.841672;0.518116;,
  -0.408097;0.841672;0.353617;,
  -0.534493;0.841672;0.076848;,
  -0.491191;0.841672;-0.224320;,
  -0.291940;0.841672;-0.454268;,
  0.000000;0.655483;-0.755209;,
  0.408297;0.655484;-0.635323;,
  0.686963;0.655483;-0.313725;,
  0.747523;0.655483;0.107478;,
  0.570749;0.655483;0.494557;,
  0.212767;0.655483;0.724618;,
  -0.212768;0.655483;0.724618;,
  -0.570750;0.655483;0.494557;,
  -0.747523;0.655483;0.107477;,
  -0.686963;0.655483;-0.313726;,
  -0.408297;0.655483;-0.635323;,
  0.000000;0.415976;-0.909376;,
  0.491646;0.415976;-0.765015;,
  0.827197;0.415976;-0.377768;,
  0.900119;0.415977;0.129418;,
  0.687260;0.415976;0.595514;,
  0.256201;0.415976;0.872539;,
  -0.256201;0.415976;0.872539;,
  -0.687260;0.415976;0.595514;,
  -0.900119;0.415976;0.129417;,
  -0.827197;0.415976;-0.377768;,
  -0.491645;0.415976;-0.765015;,
  0.000000;0.142540;-0.989789;,
  0.535120;0.142540;-0.832664;,
  0.900344;0.142540;-0.411173;,
  0.979714;0.142540;0.140862;,
  0.748032;0.142540;0.648174;,
  0.278856;0.142540;0.949696;,
  -0.278856;0.142540;0.949696;,
  -0.748033;0.142540;0.648174;,
  -0.979714;0.142540;0.140861;,
  -0.900344;0.142540;-0.411174;,
  -0.535120;0.142540;-0.832664;,
  0.000000;-0.142540;-0.989789;,
  0.535120;-0.142540;-0.832664;,
  0.900344;-0.142540;-0.411174;,
  0.979714;-0.142540;0.140862;,
  0.748032;-0.142540;0.648174;,
  0.278856;-0.142540;0.949696;,
  -0.278856;-0.142540;0.949696;,
  -0.748033;-0.142540;0.648174;,
  -0.979714;-0.142540;0.140861;,
  -0.900344;-0.142540;-0.411174;,
  -0.535120;-0.142540;-0.832664;,
  0.000000;-0.415976;-0.909375;,
  0.491645;-0.415976;-0.765015;,
  0.827197;-0.415976;-0.377768;,
  0.900119;-0.415977;0.129418;,
  0.687260;-0.415976;0.595515;,
  0.256201;-0.415976;0.872539;,
  -0.256201;-0.415977;0.872539;,
  -0.687260;-0.415977;0.595514;,
  -0.900119;-0.415977;0.129417;,
  -0.827197;-0.415976;-0.377769;,
  -0.491645;-0.415976;-0.765016;,
  0.000000;-0.655484;-0.755209;,
  0.408297;-0.655484;-0.635323;,
  0.686963;-0.655484;-0.313725;,
  0.747522;-0.655484;0.107478;,
  0.570749;-0.655483;0.494557;,
  0.212767;-0.655483;0.724618;,
  -0.212767;-0.655483;0.724618;,
  -0.570749;-0.655483;0.494557;,
  -0.747522;-0.655484;0.107477;,
  -0.686962;-0.655484;-0.313726;,
  -0.408297;-0.655484;-0.635323;,
  0.000000;-0.841672;-0.539989;,
  0.291940;-0.841672;-0.454268;,
  0.491191;-0.841672;-0.224320;,
  0.534492;-0.841672;0.076848;,
  0.408096;-0.841672;0.353618;,
  0.152132;-0.841672;0.518116;,
  -0.152133;-0.841672;0.518115;,
  -0.408096;-0.841672;0.353617;,
  -0.534492;-0.841672;0.076848;,
  -0.491191;-0.841672;-0.224320;,
  -0.291940;-0.841672;-0.454268;,
  0.000000;-0.959625;-0.281284;,
  0.152074;-0.959625;-0.236631;,
  0.255865;-0.959625;-0.116850;,
  0.278421;-0.959625;0.040031;,
  0.212580;-0.959625;0.184202;,
  0.079247;-0.959625;0.269890;,
  -0.079247;-0.959625;0.269890;,
  -0.212580;-0.959625;0.184202;,
  -0.278421;-0.959625;0.040031;,
  -0.255865;-0.959625;-0.116850;,
  -0.152074;-0.959625;-0.236631;,
  -0.000000;-1.000000;0.000000;;
  121;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,1,11;,
  4;1,2,13,12;,
  4;2,3,14,13;,
  4;3,4,15,14;,
  4;4,5,16,15;,
  4;5,6,17,16;,
  4;6,7,18,17;,
  4;7,8,19,18;,
  4;8,9,20,19;,
  4;9,10,21,20;,
  4;10,11,22,21;,
  4;11,1,12,22;,
  4;12,13,24,23;,
  4;13,14,25,24;,
  4;14,15,26,25;,
  4;15,16,27,26;,
  4;16,17,28,27;,
  4;17,18,29,28;,
  4;18,19,30,29;,
  4;19,20,31,30;,
  4;20,21,32,31;,
  4;21,22,33,32;,
  4;22,12,23,33;,
  4;23,24,35,34;,
  4;24,25,36,35;,
  4;25,26,37,36;,
  4;26,27,38,37;,
  4;27,28,39,38;,
  4;28,29,40,39;,
  4;29,30,41,40;,
  4;30,31,42,41;,
  4;31,32,43,42;,
  4;32,33,44,43;,
  4;33,23,34,44;,
  4;34,35,46,45;,
  4;35,36,47,46;,
  4;36,37,48,47;,
  4;37,38,49,48;,
  4;38,39,50,49;,
  4;39,40,51,50;,
  4;40,41,52,51;,
  4;41,42,53,52;,
  4;42,43,54,53;,
  4;43,44,55,54;,
  4;44,34,45,55;,
  4;45,46,57,56;,
  4;46,47,58,57;,
  4;47,48,59,58;,
  4;48,49,60,59;,
  4;49,50,61,60;,
  4;50,51,62,61;,
  4;51,52,63,62;,
  4;52,53,64,63;,
  4;53,54,65,64;,
  4;54,55,66,65;,
  4;55,45,56,66;,
  4;56,57,68,67;,
  4;57,58,69,68;,
  4;58,59,70,69;,
  4;59,60,71,70;,
  4;60,61,72,71;,
  4;61,62,73,72;,
  4;62,63,74,73;,
  4;63,64,75,74;,
  4;64,65,76,75;,
  4;65,66,77,76;,
  4;66,56,67,77;,
  4;67,68,79,78;,
  4;68,69,80,79;,
  4;69,70,81,80;,
  4;70,71,82,81;,
  4;71,72,83,82;,
  4;72,73,84,83;,
  4;73,74,85,84;,
  4;74,75,86,85;,
  4;75,76,87,86;,
  4;76,77,88,87;,
  4;77,67,78,88;,
  4;78,79,90,89;,
  4;79,80,91,90;,
  4;80,81,92,91;,
  4;81,82,93,92;,
  4;82,83,94,93;,
  4;83,84,95,94;,
  4;84,85,96,95;,
  4;85,86,97,96;,
  4;86,87,98,97;,
  4;87,88,99,98;,
  4;88,78,89,99;,
  4;89,90,101,100;,
  4;90,91,102,101;,
  4;91,92,103,102;,
  4;92,93,104,103;,
  4;93,94,105,104;,
  4;94,95,106,105;,
  4;95,96,107,106;,
  4;96,97,108,107;,
  4;97,98,109,108;,
  4;98,99,110,109;,
  4;99,89,100,110;,
  3;100,101,111;,
  3;101,102,111;,
  3;102,103,111;,
  3;103,104,111;,
  3;104,105,111;,
  3;105,106,111;,
  3;106,107,111;,
  3;107,108,111;,
  3;108,109,111;,
  3;109,110,111;,
  3;110,100,111;;
 }
 MeshTextureCoords {
  154;
  0.045455;0.000000;,
  0.090909;0.090909;,
  0.000000;0.090909;,
  0.136364;0.000000;,
  0.181818;0.090909;,
  0.227273;0.000000;,
  0.272727;0.090909;,
  0.318182;0.000000;,
  0.363636;0.090909;,
  0.409091;0.000000;,
  0.454545;0.090909;,
  0.500000;0.000000;,
  0.545455;0.090909;,
  0.590909;0.000000;,
  0.636364;0.090909;,
  0.681818;0.000000;,
  0.727273;0.090909;,
  0.772727;0.000000;,
  0.818182;0.090909;,
  0.863636;0.000000;,
  0.909091;0.090909;,
  0.954546;0.000000;,
  1.000000;0.090909;,
  0.090909;0.181818;,
  0.000000;0.181818;,
  0.181818;0.181818;,
  0.272727;0.181818;,
  0.363636;0.181818;,
  0.454545;0.181818;,
  0.545455;0.181818;,
  0.636364;0.181818;,
  0.727273;0.181818;,
  0.818182;0.181818;,
  0.909091;0.181818;,
  1.000000;0.181818;,
  0.090909;0.272727;,
  0.000000;0.272727;,
  0.181818;0.272727;,
  0.272727;0.272727;,
  0.363636;0.272727;,
  0.454545;0.272727;,
  0.545455;0.272727;,
  0.636364;0.272727;,
  0.727273;0.272727;,
  0.818182;0.272727;,
  0.909091;0.272727;,
  1.000000;0.272727;,
  0.090909;0.363636;,
  0.000000;0.363636;,
  0.181818;0.363636;,
  0.272727;0.363636;,
  0.363636;0.363636;,
  0.454545;0.363636;,
  0.545455;0.363636;,
  0.636364;0.363636;,
  0.727273;0.363636;,
  0.818182;0.363636;,
  0.909091;0.363636;,
  1.000000;0.363636;,
  0.090909;0.454545;,
  0.000000;0.454545;,
  0.181818;0.454545;,
  0.272727;0.454545;,
  0.363636;0.454545;,
  0.454545;0.454545;,
  0.545455;0.454545;,
  0.636364;0.454545;,
  0.727273;0.454545;,
  0.818182;0.454545;,
  0.909091;0.454545;,
  1.000000;0.454545;,
  0.090909;0.545455;,
  0.000000;0.545455;,
  0.181818;0.545455;,
  0.272727;0.545455;,
  0.363636;0.545455;,
  0.454545;0.545455;,
  0.545455;0.545455;,
  0.636364;0.545455;,
  0.727273;0.545455;,
  0.818182;0.545455;,
  0.909091;0.545455;,
  1.000000;0.545455;,
  0.090909;0.636364;,
  0.000000;0.636364;,
  0.181818;0.636364;,
  0.272727;0.636364;,
  0.363636;0.636364;,
  0.454545;0.636364;,
  0.545455;0.636364;,
  0.636364;0.636364;,
  0.727273;0.636364;,
  0.818182;0.636364;,
  0.909091;0.636364;,
  1.000000;0.636364;,
  0.090909;0.727273;,
  0.000000;0.727273;,
  0.181818;0.727273;,
  0.272727;0.727273;,
  0.363636;0.727273;,
  0.454545;0.727273;,
  0.545455;0.727273;,
  0.636364;0.727273;,
  0.727273;0.727273;,
  0.818182;0.727273;,
  0.909091;0.727273;,
  1.000000;0.727273;,
  0.090909;0.818182;,
  0.000000;0.818182;,
  0.181818;0.818182;,
  0.272727;0.818182;,
  0.363636;0.818182;,
  0.454545;0.818182;,
  0.545455;0.818182;,
  0.636364;0.818182;,
  0.727273;0.818182;,
  0.818182;0.818182;,
  0.909091;0.818182;,
  1.000000;0.818182;,
  0.090909;0.909091;,
  0.000000;0.909091;,
  0.181818;0.909091;,
  0.272727;0.909091;,
  0.363636;0.909091;,
  0.454545;0.909091;,
  0.545455;0.909091;,
  0.636364;0.909091;,
  0.727273;0.909091;,
  0.818182;0.909091;,
  0.909091;0.909091;,
  1.000000;0.909091;,
  0.000000;0.909091;,
  0.090909;0.909091;,
  0.045455;1.000000;,
  0.181818;0.909091;,
  0.136364;1.000000;,
  0.272727;0.909091;,
  0.227273;1.000000;,
  0.363636;0.909091;,
  0.318182;1.000000;,
  0.454545;0.909091;,
  0.409091;1.000000;,
  0.545455;0.909091;,
  0.500000;1.000000;,
  0.636364;0.909091;,
  0.590909;1.000000;,
  0.727273;0.909091;,
  0.681818;1.000000;,
  0.818182;0.909091;,
  0.772727;1.000000;,
  0.909091;0.909091;,
  0.863636;1.000000;,
  1.000000;0.909091;,
  0.954546;1.000000;;
 }
}

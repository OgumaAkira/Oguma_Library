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
 168;
 4.00000;8.00000;6.50000;,
 -14.67560;46.17080;17.97260;,
 -13.30160;37.92560;20.18420;,
 5.31880;0.08420;8.67740;,
 -35.69060;84.84620;30.64580;,
 -34.30340;76.50320;32.84960;,
 -35.40500;67.10360;30.47360;,
 -14.49200;28.83320;17.86160;,
 4.02460;-8.29000;6.48740;,
 -18.30680;24.97880;11.04200;,
 0.10720;-11.48080;-0.06700;,
 -39.09020;62.96000;23.57660;,
 -42.87140;64.49900;16.73600;,
 -22.18340;26.75420;4.26020;,
 -3.81800;-9.34660;-6.61660;,
 -23.55680;35.13800;2.04860;,
 -5.13620;-1.32760;-8.79220;,
 -44.25860;73.01600;14.53280;,
 -43.15700;82.22240;16.90820;,
 -22.36700;44.07080;4.37060;,
 -3.84080;6.98000;-6.60100;,
 -18.55220;48.08240;11.19020;,
 0.07540;10.26380;-0.04780;,
 -39.47120;86.58260;23.80580;,
 -35.69060;84.84620;30.64580;,
 -14.67560;46.17080;17.97260;,
 4.00000;8.00000;6.50000;,
 -155.18961;51.13280;84.69980;,
 -169.85780;30.43340;94.22780;,
 -171.51080;35.99420;92.49260;,
 -156.49280;57.42140;82.52300;,
 -180.01880;16.05740;101.26820;,
 -181.23380;20.92040;99.57500;,
 -180.10220;26.10620;101.33360;,
 -170.62820;41.85440;94.70240;,
 -155.00661;64.11440;84.59180;,
 -147.06500;65.31560;97.58540;,
 -150.94040;67.00580;91.03100;,
 -167.04739;44.32640;100.74920;,
 -163.43300;42.84020;106.77560;,
 -176.69240;28.34180;106.57220;,
 -173.51300;27.00740;111.94880;,
 -147.29420;52.32020;97.72640;,
 -162.58099;31.42040;106.27220;,
 -165.94341;29.10140;100.08320;,
 -151.18880;49.68800;91.18100;,
 -173.34979;16.95620;111.86540;,
 -176.52380;14.88140;106.47020;,
 -161.86580;37.30940;108.57200;,
 -145.94000;59.01260;99.87260;,
 -172.39400;22.14800;113.71580;,
 -239.22620;-54.97900;141.76880;,
 -238.51460;-56.27560;140.40379;,
 -246.65359;-65.78320;146.41580;,
 -248.85921;-67.17340;148.62440;,
 -238.01660;-58.71520;141.04640;,
 -248.16020;-69.36460;148.20740;,
 -252.38541;-73.20400;152.22020;,
 -236.71280;-54.63700;145.31059;,
 -237.61819;-53.47600;143.32820;,
 -246.03081;-63.86500;148.39461;,
 -247.38319;-66.96880;150.68120;,
 -235.95441;-58.63240;142.32500;,
 -244.91299;-67.39000;147.72020;,
 -235.49420;-58.41700;144.56779;,
 -246.68300;-69.18100;150.25400;,
 -235.05920;-55.83280;145.24940;,
 -244.29080;-65.47300;149.69901;,
 -203.78059;-8.35540;117.39620;,
 -204.30020;-12.52000;115.86740;,
 -215.95461;-26.58700;123.93560;,
 -215.78841;-22.95940;125.41700;,
 -203.00600;-16.39180;116.92700;,
 -214.53920;-29.95900;124.66520;,
 -223.21280;-41.21560;130.61900;,
 -224.74220;-38.32000;130.19659;,
 -224.93420;-35.24560;131.65340;,
 -198.49040;-7.49200;125.25620;,
 -201.21440;-6.51460;121.37420;,
 -213.65421;-21.35560;128.87959;,
 -211.14680;-22.18900;132.11720;,
 -223.28360;-33.81220;134.68820;,
 -221.01860;-34.61380;137.35220;,
 -200.16980;-17.30140;120.74420;,
 -211.98680;-30.79960;127.87400;,
 -197.70200;-15.56020;124.78280;,
 -209.91859;-29.22760;131.37440;,
 -219.34579;-40.53280;136.33940;,
 -220.96100;-41.94220;133.28720;,
 -197.23759;-11.38120;126.34340;,
 -209.78120;-25.57480;132.87560;,
 -219.53180;-37.51360;137.79620;,
 -192.09380;4.05440;107.34500;,
 -191.56520;8.73440;109.16180;,
 -190.61000;-0.35200;108.57500;,
 -188.75360;10.84040;113.85260;,
 -185.75301;9.63560;118.43000;,
 -187.41620;-1.39540;113.04680;,
 -184.72639;0.53060;117.82100;,
 -184.29320;5.20760;119.68580;,
 -231.26601;-48.03400;135.05840;,
 -231.52040;-45.52840;136.31900;,
 -229.90759;-50.43220;135.35300;,
 -230.22079;-44.30200;138.87080;,
 -228.30800;-44.92960;141.05240;,
 -228.06560;-50.86900;137.57060;,
 -226.68860;-49.87660;140.06900;,
 -226.95441;-47.33320;141.34340;,
 -82.72280;103.97960;59.00960;,
 -81.50000;113.21360;61.31240;,
 -92.34380;108.31340;67.85240;,
 -93.57080;99.12140;65.55200;,
 -82.90940;121.48760;59.12240;,
 -93.79460;116.65700;65.68700;,
 -114.62960;106.26680;78.25220;,
 -113.12060;98.10500;80.38160;,
 -114.34580;89.08280;78.08060;,
 -90.62000;102.07400;45.53240;,
 -86.64020;100.65200;52.25240;,
 -97.54940;95.35220;58.83140;,
 -101.60180;97.21580;52.15520;,
 -118.39940;85.34360;71.40560;,
 -122.54780;87.12860;64.78700;,
 -90.80660;119.57120;45.64460;,
 -92.02940;110.66540;43.34240;,
 -103.05260;105.76520;49.98980;,
 -101.82560;114.74060;52.29020;,
 -124.05680;95.48780;62.65700;,
 -122.83160;104.29760;64.95800;,
 -82.90940;121.48760;59.12240;,
 -86.88920;127.32320;52.40240;,
 -97.84760;120.65720;59.01080;,
 -93.79460;116.65700;65.68700;,
 -118.77800;108.24560;71.63360;,
 -114.62960;106.26680;78.25220;,
 -132.09560;73.56140;91.82540;,
 -133.60880;65.32340;89.69780;,
 -133.40781;81.30200;89.57660;,
 -137.79201;62.02340;83.10080;,
 -141.84860;63.66320;76.42700;,
 -151.18880;49.68800;91.18100;,
 -155.18961;51.13280;84.69980;,
 -143.06480;71.27720;74.12000;,
 -141.61700;79.53140;76.28660;,
 -156.49280;57.42140;82.52300;,
 -155.00661;64.11440;84.59180;,
 -137.47580;83.18240;82.90940;,
 -133.40781;81.30200;89.57660;,
 -150.94040;67.00580;91.03100;,
 -147.06500;65.31560;97.58540;,
 -53.01020;99.97940;44.13080;,
 -54.15440;90.64700;41.78060;,
 -54.37880;108.32720;41.91680;,
 -72.99560;116.65700;53.14340;,
 -71.62280;108.31340;55.35560;,
 -72.84200;99.12140;53.05100;,
 -57.88700;86.66360;34.91240;,
 -61.69520;88.35320;28.08800;,
 -76.70420;95.35220;46.26020;,
 -80.61740;97.21580;39.50000;,
 -63.06380;96.89300;25.87400;,
 -61.91960;106.00880;28.22360;,
 -81.98960;105.76520;37.28780;,
 -80.77040;114.74060;39.59240;,
 -58.18640;110.21480;35.09240;,
 -54.37880;108.32720;41.91680;,
 -76.90880;120.65720;46.38320;,
 -72.99560;116.65700;53.14340;;
 
 148;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;2,5,6,7;,
 4;3,2,7,8;,
 4;8,7,9,10;,
 4;7,6,11,9;,
 4;9,11,12,13;,
 4;10,9,13,14;,
 4;14,13,15,16;,
 4;13,12,17,15;,
 4;15,17,18,19;,
 4;16,15,19,20;,
 4;20,19,21,22;,
 4;19,18,23,21;,
 4;21,23,24,25;,
 4;22,21,25,26;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;29,32,33,34;,
 4;30,29,34,35;,
 4;36,37,38,39;,
 4;37,35,34,38;,
 4;38,34,33,40;,
 4;39,38,40,41;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;44,47,31,28;,
 4;45,44,28,27;,
 4;36,39,48,49;,
 4;39,41,50,48;,
 4;48,50,46,43;,
 4;49,48,43,42;,
 4;51,52,53,54;,
 4;55,56,53,52;,
 4;57,54,53,56;,
 4;58,59,60,61;,
 4;51,54,60,59;,
 4;57,61,60,54;,
 4;55,62,63,56;,
 4;64,65,63,62;,
 4;57,56,63,65;,
 4;64,66,67,65;,
 4;58,61,67,66;,
 4;57,65,67,61;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;70,73,74,75;,
 4;71,70,75,76;,
 4;77,78,79,80;,
 4;78,68,71,79;,
 4;79,71,76,81;,
 4;80,79,81,82;,
 4;72,83,84,73;,
 4;83,85,86,84;,
 4;84,86,87,88;,
 4;73,84,88,74;,
 4;85,89,90,86;,
 4;89,77,80,90;,
 4;90,80,82,91;,
 4;86,90,91,87;,
 4;33,32,92,93;,
 4;32,31,94,92;,
 4;92,94,72,69;,
 4;93,92,69,68;,
 4;41,40,95,96;,
 4;40,33,93,95;,
 4;95,93,68,78;,
 4;96,95,78,77;,
 4;31,47,97,94;,
 4;47,46,98,97;,
 4;97,98,85,83;,
 4;94,97,83,72;,
 4;46,50,99,98;,
 4;50,41,96,99;,
 4;99,96,77,89;,
 4;98,99,89,85;,
 4;76,75,100,101;,
 4;75,74,102,100;,
 4;100,102,55,52;,
 4;101,100,52,51;,
 4;82,81,103,104;,
 4;81,76,101,103;,
 4;103,101,51,59;,
 4;104,103,59,58;,
 4;74,88,105,102;,
 4;88,87,106,105;,
 4;105,106,64,62;,
 4;102,105,62,55;,
 4;87,91,107,106;,
 4;91,82,104,107;,
 4;107,104,58,66;,
 4;106,107,66,64;,
 4;108,109,110,111;,
 4;109,112,113,110;,
 4;110,113,114,115;,
 4;111,110,115,116;,
 4;117,118,119,120;,
 4;118,108,111,119;,
 4;119,111,116,121;,
 4;120,119,121,122;,
 4;123,124,125,126;,
 4;124,117,120,125;,
 4;125,120,122,127;,
 4;126,125,127,128;,
 4;129,130,131,132;,
 4;130,123,126,131;,
 4;131,126,128,133;,
 4;132,131,133,134;,
 4;116,115,135,136;,
 4;115,114,137,135;,
 4;135,137,36,49;,
 4;136,135,49,42;,
 4;122,121,138,139;,
 4;121,116,136,138;,
 4;138,136,42,140;,
 4;139,138,140,141;,
 4;128,127,142,143;,
 4;127,122,139,142;,
 4;142,139,141,144;,
 4;143,142,144,145;,
 4;134,133,146,147;,
 4;133,128,143,146;,
 4;146,143,145,148;,
 4;147,146,148,149;,
 4;6,5,150,151;,
 4;5,4,152,150;,
 4;150,152,153,154;,
 4;151,150,154,155;,
 4;12,11,156,157;,
 4;11,6,151,156;,
 4;156,151,155,158;,
 4;157,156,158,159;,
 4;18,17,160,161;,
 4;17,12,157,160;,
 4;160,157,159,162;,
 4;161,160,162,163;,
 4;24,23,164,165;,
 4;23,18,161,164;,
 4;164,161,163,166;,
 4;165,164,166,167;,
 4;167,166,130,129;,
 4;166,163,123,130;,
 4;163,162,124,123;,
 4;162,159,117,124;,
 4;159,158,118,117;,
 4;158,155,108,118;,
 4;155,154,109,108;,
 4;154,153,112,109;;
 
 MeshMaterialList {
  2;
  148;
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
   0.778400;0.800000;0.125600;1.000000;;
   74.000000;
   0.500000;0.500000;0.500000;;
   0.009730;0.010000;0.001570;;
  }
  Material {
   0.213600;0.153600;0.112800;1.000000;;
   7.000000;
   0.850000;0.850000;0.850000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  173;
  0.904604;0.417760;0.084667;,
  -0.242401;0.552985;0.797151;,
  -0.296016;-0.411988;0.861766;,
  0.788818;-0.555563;0.262899;,
  -0.898922;-0.427032;-0.097898;,
  0.183232;-0.586963;-0.788607;,
  0.305116;0.406537;-0.861180;,
  -0.819372;0.529463;-0.219771;,
  -0.667826;-0.072054;-0.740822;,
  0.737783;-0.574685;0.354138;,
  -0.820231;0.498323;-0.280884;,
  0.040255;-0.584768;-0.810201;,
  -0.139819;0.497158;0.856320;,
  0.791114;-0.546249;0.275227;,
  0.149337;-0.562765;-0.813016;,
  -0.826382;0.518420;-0.219850;,
  -0.217692;0.528068;0.820825;,
  0.829401;-0.518347;0.208349;,
  0.236120;-0.537230;-0.809711;,
  -0.863441;0.487660;-0.129065;,
  -0.326947;0.499727;0.802109;,
  -0.848152;0.467919;-0.248376;,
  -0.186139;0.474136;0.860551;,
  0.797884;-0.520355;0.304323;,
  0.122860;-0.531668;-0.837994;,
  0.615520;0.612962;0.495391;,
  0.166039;-0.617599;0.768767;,
  -0.588977;-0.688507;-0.423160;,
  -0.204562;0.547663;-0.811307;,
  -0.044210;0.594511;0.802871;,
  0.714620;-0.572077;0.402549;,
  0.043221;-0.628222;-0.776832;,
  -0.732323;0.542767;-0.411226;,
  0.853479;0.491851;0.172211;,
  -0.187909;-0.466133;0.864529;,
  -0.853205;-0.493230;-0.169606;,
  0.187026;0.463823;-0.865961;,
  -0.573177;-0.030041;-0.818881;,
  -0.498805;-0.198649;-0.843642;,
  -0.861293;0.443313;-0.248290;,
  -0.626964;0.686223;0.368801;,
  -0.173294;0.440244;0.880996;,
  0.554169;-0.768140;-0.320715;,
  0.687987;-0.712107;0.139921;,
  0.457178;-0.030291;0.888859;,
  -0.556239;-0.014052;-0.830904;,
  0.124023;-0.552910;-0.823959;,
  -0.564155;-0.022499;-0.825363;,
  -0.822203;0.512440;-0.247764;,
  -0.648619;0.670322;0.360501;,
  -0.666844;0.637782;0.385428;,
  -0.182117;0.520904;0.833962;,
  0.624312;-0.700220;-0.346304;,
  0.786713;-0.540167;0.298834;,
  0.638084;-0.682181;-0.357040;,
  0.468359;-0.006670;0.883513;,
  0.467544;-0.022136;0.883693;,
  0.208956;-0.539771;-0.815466;,
  -0.848283;0.501103;-0.171209;,
  -0.276071;0.512580;0.813048;,
  0.820817;-0.523189;0.229199;,
  0.083896;-0.559477;-0.824589;,
  -0.841089;0.469581;-0.268445;,
  -0.166227;0.472744;0.865379;,
  0.771020;-0.544811;0.329711;,
  0.520694;0.013319;0.853640;,
  0.150989;0.613142;0.775409;,
  0.507179;0.010481;0.861777;,
  0.599360;-0.616519;0.510560;,
  -0.276347;-0.918710;0.282144;,
  0.526618;-0.821894;-0.217172;,
  0.209697;-0.907801;-0.363214;,
  -0.518753;-0.005943;-0.854904;,
  -0.514366;-0.007930;-0.857534;,
  -0.620081;0.545884;-0.563481;,
  0.312889;0.906059;-0.284881;,
  -0.558295;0.793423;0.242458;,
  -0.199709;0.550364;0.810689;,
  0.777083;-0.552759;0.300998;,
  0.151776;-0.591684;-0.791754;,
  -0.808467;0.521166;-0.273437;,
  0.715676;0.601855;0.354372;,
  0.034221;-0.566708;0.823208;,
  -0.709446;-0.622221;-0.330948;,
  -0.041600;0.544879;-0.837482;,
  0.896656;0.431024;0.101126;,
  0.527722;0.010052;0.849357;,
  -0.277737;-0.419619;0.864166;,
  0.838843;0.268417;0.473597;,
  -0.645706;-0.609835;0.459527;,
  -0.893035;-0.436824;-0.108045;,
  -0.718408;-0.507540;0.475702;,
  -0.521711;-0.005073;-0.853107;,
  0.281967;0.416225;-0.864437;,
  -0.824205;-0.268624;-0.498525;,
  0.646670;0.608445;-0.460014;,
  0.723185;0.498671;-0.477840;,
  0.237363;-0.547329;-0.802552;,
  -0.141927;-0.339891;-0.929694;,
  -0.857185;0.495461;-0.140543;,
  -0.402674;-0.132892;-0.905645;,
  -0.661229;0.669967;0.337520;,
  -0.702922;0.600290;0.381514;,
  -0.320644;0.510914;0.797593;,
  0.824641;-0.524587;0.211603;,
  0.677067;-0.636337;-0.369669;,
  0.624574;-0.715354;-0.313329;,
  0.012602;0.320569;0.947142;,
  0.343641;0.129599;0.930116;,
  0.825759;0.270549;0.494900;,
  -0.707281;-0.522781;0.475872;,
  -0.816085;-0.268832;-0.511601;,
  0.710339;0.517141;-0.477476;,
  -0.137984;-0.342878;-0.929191;,
  -0.700262;0.608308;0.373624;,
  0.671815;-0.648825;-0.357338;,
  0.023819;0.330361;0.943554;,
  -0.607954;-0.045613;-0.792661;,
  -0.638887;0.662407;0.391202;,
  0.526195;-0.792143;-0.309240;,
  0.419639;-0.044587;0.906595;,
  -0.556120;-0.016082;-0.830947;,
  -0.636385;0.681463;0.361417;,
  0.620931;-0.702594;-0.347571;,
  0.471545;-0.011458;0.881768;,
  -0.675346;0.107274;-0.729658;,
  -0.679393;0.632344;0.372246;,
  0.664189;-0.651299;-0.366964;,
  0.588537;-0.124357;0.798849;,
  -0.571282;-0.027807;-0.820283;,
  -0.659030;0.649287;0.379613;,
  0.602412;-0.723651;-0.336793;,
  0.461008;-0.028792;0.886929;,
  0.511406;0.013537;0.859232;,
  0.373156;-0.921866;-0.104487;,
  -0.514574;-0.006289;-0.857423;,
  -0.292078;0.902296;0.317101;,
  0.493669;0.007411;0.869618;,
  0.609133;-0.737830;-0.290800;,
  -0.523912;-0.010241;-0.851711;,
  -0.658330;0.679826;0.323169;,
  0.523540;0.012265;0.851913;,
  -0.437851;-0.820312;0.367933;,
  -0.520323;-0.006219;-0.853947;,
  0.454575;0.809584;-0.371395;,
  0.421985;0.601823;0.678039;,
  0.286624;0.848163;0.445495;,
  -0.427189;0.533635;-0.729892;,
  -0.516389;-0.005522;-0.856337;,
  -0.121031;-0.978056;-0.169580;,
  0.041496;-0.993924;0.101949;,
  0.385816;-0.641506;0.663035;,
  0.516492;0.013760;0.856182;,
  0.089033;-0.258223;0.961974;,
  0.070684;-0.259023;0.963281;,
  -0.076007;0.260688;-0.962426;,
  -0.051783;0.259937;-0.964236;,
  -0.814943;0.320486;-0.482863;,
  -0.825048;0.314511;-0.469446;,
  -0.796556;0.323922;-0.510464;,
  0.752496;-0.327137;0.571604;,
  0.751198;-0.325414;0.574289;,
  0.756751;-0.324667;0.567379;,
  -0.666618;0.617899;0.416919;,
  0.430101;-0.794908;-0.427942;,
  0.479830;-0.834301;-0.271488;,
  0.350058;-0.069594;0.934139;,
  -0.137658;-0.333661;-0.932588;,
  0.036594;0.317884;0.947423;,
  -0.499034;-0.290397;-0.816477;,
  -0.392400;-0.288935;-0.873235;,
  -0.324169;0.756344;-0.568206;,
  -0.593254;0.714648;-0.370577;;
  148;
  4;0,85,109,88;,
  4;85,33,86,109;,
  4;153,86,34,87;,
  4;154,153,87,2;,
  4;2,87,110,91;,
  4;87,34,89,110;,
  4;110,89,35,90;,
  4;91,110,90,4;,
  4;4,90,111,94;,
  4;90,35,92,111;,
  4;155,92,36,93;,
  4;156,155,93,6;,
  4;6,93,112,96;,
  4;93,36,95,112;,
  4;112,95,33,85;,
  4;96,112,85,0;,
  4;5,97,113,100;,
  4;97,18,98,113;,
  4;157,158,19,99;,
  4;159,157,99,7;,
  4;1,101,114,103;,
  4;101,7,99,114;,
  4;114,99,19,102;,
  4;103,114,102,20;,
  4;3,104,115,106;,
  4;104,17,105,115;,
  4;115,105,18,97;,
  4;106,115,97,5;,
  4;1,103,116,108;,
  4;103,20,107,116;,
  4;160,161,17,104;,
  4;162,160,104,3;,
  4;10,37,117,39;,
  4;11,38,117,37;,
  4;8,39,117,38;,
  4;12,40,118,41;,
  4;10,39,118,40;,
  4;163,41,118,39;,
  4;11,42,119,164;,
  4;9,43,119,42;,
  4;165,164,119,43;,
  4;9,44,120,43;,
  4;12,41,120,44;,
  4;166,166,120,41;,
  4;15,45,121,48;,
  4;45,14,46,121;,
  4;121,46,24,47;,
  4;48,121,47,21;,
  4;16,49,122,51;,
  4;49,15,48,122;,
  4;122,48,21,50;,
  4;51,122,50,22;,
  4;14,52,123,46;,
  4;52,13,53,123;,
  4;123,53,23,54;,
  4;46,123,54,24;,
  4;13,55,124,53;,
  4;55,16,51,124;,
  4;124,51,22,56;,
  4;53,124,56,23;,
  4;19,158,125,58;,
  4;98,18,57,167;,
  4;125,57,14,45;,
  4;58,125,45,15;,
  4;20,102,126,59;,
  4;102,19,58,126;,
  4;126,58,15,49;,
  4;59,126,49,16;,
  4;18,105,127,57;,
  4;105,17,60,127;,
  4;127,60,13,52;,
  4;57,127,52,14;,
  4;17,161,128,60;,
  4;107,20,59,168;,
  4;128,59,16,55;,
  4;60,128,55,13;,
  4;21,47,129,62;,
  4;47,24,61,129;,
  4;129,61,11,37;,
  4;62,129,37,10;,
  4;22,50,130,63;,
  4;50,21,62,130;,
  4;130,62,10,40;,
  4;63,130,40,12;,
  4;24,54,131,61;,
  4;54,23,64,131;,
  4;131,64,9,42;,
  4;61,131,42,11;,
  4;23,56,132,64;,
  4;56,22,63,132;,
  4;132,63,12,44;,
  4;64,132,44,9;,
  4;151,152,133,68;,
  4;152,145,66,133;,
  4;133,66,29,67;,
  4;68,133,67,30;,
  4;149,150,134,71;,
  4;150,151,68,134;,
  4;134,68,30,70;,
  4;71,134,70,31;,
  4;147,148,135,74;,
  4;148,169,170,135;,
  4;135,170,31,73;,
  4;74,135,73,32;,
  4;145,146,136,66;,
  4;171,147,74,172;,
  4;136,74,32,76;,
  4;66,136,76,29;,
  4;30,67,137,78;,
  4;67,29,77,137;,
  4;137,77,1,108;,
  4;78,137,108,3;,
  4;31,70,138,79;,
  4;70,30,78,138;,
  4;138,78,3,106;,
  4;79,138,106,5;,
  4;32,73,139,80;,
  4;73,31,79,139;,
  4;139,79,5,100;,
  4;80,139,100,7;,
  4;29,76,140,77;,
  4;76,32,80,140;,
  4;140,80,7,101;,
  4;77,140,101,1;,
  4;34,86,141,82;,
  4;86,33,81,141;,
  4;141,81,25,65;,
  4;82,141,65,26;,
  4;35,89,142,83;,
  4;89,34,82,142;,
  4;142,82,26,69;,
  4;83,142,69,27;,
  4;36,92,143,84;,
  4;92,35,83,143;,
  4;143,83,27,72;,
  4;84,143,72,28;,
  4;33,95,144,81;,
  4;95,36,84,144;,
  4;144,84,28,75;,
  4;81,144,75,25;,
  4;25,75,146,145;,
  4;75,28,147,171;,
  4;28,72,148,147;,
  4;72,27,169,148;,
  4;27,69,150,149;,
  4;69,26,151,150;,
  4;26,65,152,151;,
  4;65,25,145,152;;
 }
 MeshTextureCoords {
  168;
  0.375000;0.000000;,
  0.410120;0.000000;,
  0.409930;0.125000;,
  0.380890;0.125020;,
  0.445240;0.000000;,
  0.443050;0.125000;,
  0.442670;0.250000;,
  0.409690;0.250000;,
  0.375000;0.250000;,
  0.409340;0.375000;,
  0.375000;0.375000;,
  0.442120;0.375000;,
  0.441720;0.500000;,
  0.409090;0.500000;,
  0.375000;0.500000;,
  0.409140;0.625000;,
  0.375000;0.625000;,
  0.441790;0.625000;,
  0.442170;0.750000;,
  0.409380;0.750000;,
  0.375000;0.750000;,
  0.409730;0.875000;,
  0.375000;0.875000;,
  0.442720;0.875000;,
  0.445240;1.000000;,
  0.410120;1.000000;,
  0.375000;1.000000;,
  0.875000;0.250000;,
  0.834400;0.209480;,
  0.862480;0.125100;,
  0.875000;0.125000;,
  0.825020;0.200160;,
  0.849960;0.125160;,
  0.824860;0.050160;,
  0.834300;0.040730;,
  0.875000;0.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.749940;0.012560;,
  0.665590;0.040670;,
  0.749880;0.025080;,
  0.674900;0.050040;,
  0.625000;0.250000;,
  0.665490;0.209540;,
  0.749940;0.237650;,
  0.750000;0.250000;,
  0.674740;0.200280;,
  0.749880;0.225240;,
  0.637400;0.125100;,
  0.621090;0.125030;,
  0.649800;0.125160;,
  0.775740;0.099090;,
  0.785360;0.124920;,
  0.774010;0.124940;,
  0.764990;0.109890;,
  0.775660;0.150760;,
  0.764940;0.140000;,
  0.749880;0.124960;,
  0.723750;0.098840;,
  0.749740;0.089300;,
  0.749810;0.100740;,
  0.734690;0.109750;,
  0.749740;0.160540;,
  0.749820;0.149130;,
  0.723830;0.151000;,
  0.734740;0.140140;,
  0.714120;0.124920;,
  0.725620;0.124940;,
  0.806530;0.068350;,
  0.825480;0.125020;,
  0.814790;0.124980;,
  0.798530;0.076320;,
  0.806560;0.181700;,
  0.798510;0.173650;,
  0.791080;0.166220;,
  0.804900;0.124960;,
  0.791120;0.083710;,
  0.692950;0.068090;,
  0.749740;0.049280;,
  0.749700;0.059900;,
  0.700880;0.076020;,
  0.749690;0.069750;,
  0.708260;0.083400;,
  0.749740;0.200760;,
  0.749700;0.190070;,
  0.692920;0.181960;,
  0.700900;0.173950;,
  0.708300;0.166520;,
  0.749690;0.180170;,
  0.674000;0.125020;,
  0.684620;0.124980;,
  0.694480;0.124960;,
  0.837410;0.125100;,
  0.815460;0.059500;,
  0.815560;0.190710;,
  0.749810;0.037500;,
  0.684150;0.059300;,
  0.749800;0.212710;,
  0.684050;0.190910;,
  0.662200;0.125110;,
  0.795370;0.124930;,
  0.783990;0.090830;,
  0.783920;0.159040;,
  0.749700;0.079260;,
  0.715420;0.090530;,
  0.749700;0.170600;,
  0.715480;0.159340;,
  0.704030;0.124930;,
  0.517290;0.250000;,
  0.517480;0.125000;,
  0.534580;0.125000;,
  0.534400;0.250000;,
  0.516770;0.000000;,
  0.534820;0.000000;,
  0.569310;0.000000;,
  0.567350;0.125000;,
  0.567160;0.250000;,
  0.517020;0.500000;,
  0.517100;0.375000;,
  0.534310;0.375000;,
  0.534340;0.500000;,
  0.567190;0.375000;,
  0.567370;0.500000;,
  0.517310;0.750000;,
  0.517120;0.625000;,
  0.534510;0.625000;,
  0.534690;0.750000;,
  0.567630;0.625000;,
  0.567820;0.750000;,
  0.516770;1.000000;,
  0.517500;0.875000;,
  0.534780;0.875000;,
  0.534820;1.000000;,
  0.567790;0.875000;,
  0.569310;1.000000;,
  0.596960;0.125000;,
  0.596850;0.250000;,
  0.597150;0.000000;,
  0.596890;0.375000;,
  0.597030;0.500000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.597200;0.625000;,
  0.597320;0.750000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.597270;0.875000;,
  0.597150;1.000000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.472550;0.125000;,
  0.472230;0.250000;,
  0.472790;0.000000;,
  0.500330;0.000000;,
  0.501900;0.125000;,
  0.501710;0.250000;,
  0.471760;0.375000;,
  0.471410;0.500000;,
  0.501440;0.375000;,
  0.501250;0.500000;,
  0.471440;0.625000;,
  0.471760;0.750000;,
  0.501290;0.625000;,
  0.501490;0.750000;,
  0.472230;0.875000;,
  0.472790;1.000000;,
  0.501760;0.875000;,
  0.500330;1.000000;;
 }
}

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
 81;
 -0.41012;39.87686;57.94478;,
 69.46116;39.84520;58.16714;,
 64.04585;11.62992;40.73619;,
 -5.63414;12.65811;41.12951;,
 98.39005;39.83299;62.50214;,
 92.51297;9.21189;43.58490;,
 69.43035;39.84735;68.41045;,
 63.09149;6.82052;48.00689;,
 -0.45378;39.87992;72.43093;,
 -6.98409;5.85645;51.41191;,
 -70.32506;39.91156;72.20867;,
 -76.66412;6.88467;51.80526;,
 -99.25399;39.92380;67.87366;,
 -105.13120;9.30271;48.95648;,
 -70.29419;39.90939;61.96544;,
 -75.70944;11.69410;44.53450;,
 -0.41012;39.87686;57.94478;,
 -5.63414;12.65811;41.12951;,
 61.90872;-0.06458;-1.66994;,
 -7.69591;1.37655;0.22112;,
 90.19353;-3.47986;-2.43708;,
 60.58983;-6.86837;-1.63084;,
 -9.56112;-8.24549;0.27639;,
 -79.16555;-6.80416;2.16743;,
 -107.45044;-3.38900;2.93453;,
 -77.84661;-0.00039;2.12836;,
 -7.69591;1.37655;0.22112;,
 64.30166;11.61206;-44.21026;,
 -5.38728;12.64090;-40.81682;,
 92.79074;9.19251;-48.60464;,
 63.39102;6.79956;-51.42575;,
 -6.67553;5.83498;-51.02113;,
 -76.36454;6.86373;-47.62751;,
 -104.85352;9.28332;-43.23315;,
 -75.45358;11.67630;-40.41211;,
 -5.38728;12.64090;-40.81682;,
 69.82308;39.81997;-61.96533;,
 -0.06099;39.85251;-57.94486;,
 98.78288;39.80559;-67.87362;,
 69.85395;39.81783;-72.20858;,
 -0.01736;39.84946;-72.43098;,
 -69.90147;39.88204;-68.41043;,
 -98.86109;39.89640;-62.50194;,
 -69.93225;39.88419;-58.16711;,
 -0.06099;39.85251;-57.94486;,
 75.23835;68.03531;-44.53442;,
 5.16303;67.07125;-41.12944;,
 104.66005;70.42669;-48.95646;,
 76.19289;72.84476;-51.80510;,
 6.51302;73.87290;-51.41187;,
 -63.56251;72.90891;-48.00682;,
 -92.98411;70.51747;-43.58484;,
 -64.51694;68.09945;-40.73618;,
 5.16303;67.07125;-41.12944;,
 77.37553;79.72976;-2.12828;,
 7.22482;78.35281;-0.22105;,
 106.97935;83.11840;-2.93447;,
 78.69444;86.53356;-2.16738;,
 9.09002;87.97488;-0.27632;,
 -61.06093;86.59780;1.63088;,
 -90.66461;83.20925;2.43715;,
 -62.37981;79.79402;1.66998;,
 7.22482;78.35281;-0.22105;,
 74.98249;68.05307;40.41210;,
 4.91615;67.08851;40.81683;,
 104.38242;70.44606;43.23315;,
 75.89338;72.86564;47.62759;,
 6.20438;73.89440;51.02093;,
 -63.86208;72.92985;51.42580;,
 -93.26181;70.53685;48.60471;,
 -64.77285;68.11727;44.21033;,
 4.91615;67.08851;40.81683;,
 69.46116;39.84520;58.16714;,
 -0.41012;39.87686;57.94478;,
 98.39005;39.83299;62.50214;,
 69.43035;39.84735;68.41045;,
 -0.45378;39.87992;72.43093;,
 -70.32506;39.91156;72.20867;,
 -99.25399;39.92380;67.87366;,
 -70.29419;39.90939;61.96544;,
 -0.41012;39.87686;57.94478;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;46,45,54,55;,
 4;45,47,56,54;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;55,54,63,64;,
 4;54,56,65,63;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;64,63,72,73;,
 4;63,65,74,72;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;;
 
 MeshMaterialList {
  1;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.304314;0.304314;0.304314;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  100;
  -0.022735;0.528595;-0.848569;,
  0.065739;0.515278;-0.854498;,
  0.128265;0.503302;-0.854538;,
  0.108316;-0.537449;0.836311;,
  0.022735;-0.528595;0.848570;,
  -0.065739;-0.515276;0.854499;,
  -0.128266;-0.503300;0.854539;,
  -0.108316;0.537448;-0.836312;,
  -0.015801;0.801308;-0.598043;,
  0.067919;0.794332;-0.603675;,
  0.127304;0.786011;-0.604963;,
  0.096291;-0.803211;0.587860;,
  0.015801;-0.801308;0.598043;,
  -0.067919;-0.794331;0.603676;,
  -0.127304;-0.786011;0.604964;,
  -0.096290;0.803211;-0.587861;,
  0.000526;1.000000;-0.000229;,
  0.070348;0.997523;-0.000170;,
  0.119870;0.992790;-0.000129;,
  0.066796;-0.997767;0.000294;,
  -0.000526;-1.000000;0.000229;,
  -0.070348;-0.997523;0.000170;,
  -0.119868;-0.992790;0.000129;,
  -0.066796;0.997767;-0.000293;,
  0.016671;0.801676;0.597527;,
  0.100240;0.792719;0.601289;,
  0.159246;0.783023;0.601262;,
  0.064647;-0.805512;-0.589042;,
  -0.016671;-0.801675;-0.597527;,
  -0.100241;-0.792718;-0.601290;,
  -0.159247;-0.783022;-0.601262;,
  -0.064646;0.805512;0.589043;,
  0.023344;0.529275;0.848129;,
  0.111457;0.513660;0.850724;,
  0.173344;0.500107;0.848437;,
  0.063319;-0.540474;-0.838975;,
  -0.023344;-0.529273;-0.848130;,
  -0.111460;-0.513658;-0.850725;,
  -0.173347;-0.500103;-0.848438;,
  -0.063317;0.540473;0.838975;,
  0.015800;-0.801309;0.598043;,
  0.096291;-0.803211;0.587860;,
  0.152072;-0.801486;0.578355;,
  0.067918;0.794332;-0.603676;,
  -0.015800;0.801308;-0.598043;,
  -0.096292;0.803211;-0.587860;,
  -0.152073;0.801486;-0.578354;,
  -0.067918;-0.794332;0.603675;,
  -0.000526;-1.000000;0.000229;,
  0.066796;-0.997767;0.000293;,
  0.113732;-0.993511;0.000339;,
  0.070348;0.997523;-0.000170;,
  0.000526;1.000000;-0.000229;,
  -0.066796;0.997767;-0.000294;,
  -0.113731;0.993511;-0.000340;,
  -0.070348;-0.997522;0.000170;,
  -0.016671;-0.801676;-0.597527;,
  0.064647;-0.805512;-0.589042;,
  0.121245;-0.805074;-0.580651;,
  0.100240;0.792718;0.601290;,
  0.016671;0.801675;0.597527;,
  -0.064646;0.805512;0.589042;,
  -0.121245;0.805074;0.580651;,
  -0.100241;-0.792718;-0.601290;,
  0.167831;-0.541237;0.823951;,
  0.152071;-0.801487;0.578354;,
  -0.167829;0.541235;-0.823953;,
  -0.152070;0.801486;-0.578355;,
  0.113730;-0.993512;0.000340;,
  -0.113731;0.993512;-0.000340;,
  0.121244;-0.805074;-0.580651;,
  -0.121244;0.805073;0.580652;,
  0.123944;-0.545851;-0.828664;,
  -0.123942;0.545849;0.828666;,
  0.022735;-0.528597;0.848569;,
  0.108316;-0.537448;0.836312;,
  0.167831;-0.541234;0.823953;,
  0.128264;0.503301;-0.854539;,
  0.065738;0.515277;-0.854499;,
  0.127303;0.786011;-0.604964;,
  -0.022735;0.528596;-0.848569;,
  -0.108318;0.537450;-0.836310;,
  -0.167834;0.541236;-0.823951;,
  -0.128262;-0.503302;0.854539;,
  -0.065737;-0.515279;0.854498;,
  -0.127302;-0.786011;0.604964;,
  0.119868;0.992790;-0.000129;,
  -0.119869;-0.992790;0.000129;,
  0.159246;0.783023;0.601262;,
  -0.159246;-0.783023;-0.601262;,
  0.063318;-0.540474;-0.838974;,
  -0.023344;-0.529274;-0.848130;,
  0.123944;-0.545852;-0.828664;,
  0.111457;0.513659;0.850724;,
  0.173345;0.500106;0.848437;,
  0.023344;0.529274;0.848130;,
  -0.063318;0.540474;0.838975;,
  -0.123945;0.545851;0.828664;,
  -0.111458;-0.513660;-0.850724;,
  -0.173343;-0.500107;-0.848437;;
  64;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;64,3,11,65;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;66,7,15,67;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;65,11,19,68;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;67,15,23,69;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;68,19,27,70;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;69,23,31,71;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;70,27,35,72;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;71,31,39,73;,
  4;31,24,32,39;,
  4;74,75,41,40;,
  4;75,76,42,41;,
  4;77,78,43,79;,
  4;78,80,44,43;,
  4;80,81,45,44;,
  4;81,82,46,45;,
  4;83,84,47,85;,
  4;84,74,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;79,43,51,86;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;85,47,55,87;,
  4;47,40,48,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;86,51,59,88;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;87,55,63,89;,
  4;55,48,56,63;,
  4;56,57,90,91;,
  4;57,58,92,90;,
  4;88,59,93,94;,
  4;59,60,95,93;,
  4;60,61,96,95;,
  4;61,62,97,96;,
  4;89,63,98,99;,
  4;63,56,91,98;;
 }
 MeshTextureCoords {
  81;
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;;
 }
}

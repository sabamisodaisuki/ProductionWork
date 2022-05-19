//============================================================
//
// 3D制作　メッシュ理[Meshield.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _MESHIELD_H_
#define _MESHIELD_H_

#include "main.h"
//メッシュの構造体の定義
typedef struct
{
	D3DXVECTOR3 g_posMeshfield;				//位置					
	D3DXVECTOR3 g_moveMeshfield;			//移動量
	
}MESHFIELD;

//============================================================
// プロトタイプ宣言
//============================================================
void lnitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
MESHFIELD*GetMeshfield(void);
#endif

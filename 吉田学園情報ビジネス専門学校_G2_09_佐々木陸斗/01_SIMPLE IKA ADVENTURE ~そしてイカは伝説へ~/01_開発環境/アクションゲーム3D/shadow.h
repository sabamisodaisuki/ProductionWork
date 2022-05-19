//============================================================
//
// 3D����@�e�̏���[shadow.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//============================================================
// �e�̍\���̂̒�`
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//���_					
	D3DXVECTOR3 rot;				//�����_
	D3DXMATRIX mtxWorld;			//
	bool bUse;						//
}Shadow;

//============================================================
// �v���g�^�C�v�錾
//============================================================
void lnitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
#endif

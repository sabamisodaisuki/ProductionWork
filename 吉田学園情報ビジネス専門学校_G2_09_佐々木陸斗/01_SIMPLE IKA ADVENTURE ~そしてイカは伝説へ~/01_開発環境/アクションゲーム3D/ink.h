//============================================================
//
// 3D����@�C���N�̏���[Ink.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _INK_H_
#define _INK_H_

#include "main.h"

//============================================================
// �C���N�̍\���̂̒�`
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//���_					
	D3DXVECTOR3 rot;				//�����_
	D3DXMATRIX mtxWorld;			//
	bool bUse;						//
}Ink;

//============================================================
// �v���g�^�C�v�錾
//============================================================
void lnitInk(void);
void UninitInk(void);
void UpdateInk(void);
void DrawInk(void);
int SetInk(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionInk(int nIdxInk, D3DXVECTOR3 pos);
#endif


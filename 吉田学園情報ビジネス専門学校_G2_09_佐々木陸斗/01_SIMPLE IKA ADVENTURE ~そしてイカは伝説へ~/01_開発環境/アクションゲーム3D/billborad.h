//============================================================
//
// 3D����@billborad�̏���[billborad.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _BILLBORAD_H_
#define _BILLBORAD_

#include "main.h"

//============================================================
// �\���̂̒�`
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//���_					
	D3DXVECTOR3 rot;				//�����_
	D3DXMATRIX mtxWorld;			//
	float fWidth;					//��
	float fHeight;					//����
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Billborad;

//============================================================
// �v���g�^�C�v�錾
//============================================================
void lnitBillborad(void);
void UninitBillborad(void);
void UpdateBillborad(void);
void DrawBillborad(void);
void SetBillborad(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

#endif

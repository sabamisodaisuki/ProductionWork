//============================================================
//
// 3D����@�G�t�F�N�g�̏���[effect.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
//============================================================
//�}�N����`
//============================================================
#define MAX_EFFECT			(4096)		//�G�t�F�N�g�̍ő吔
//============================================================
// �G�t�F�N�g�̍\���̂̒�`
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//���_					
	D3DXVECTOR3 rot;				//�����_
	D3DXCOLOR col;					//�F
	D3DXVECTOR3 size;				//�T�C�Y
	D3DXVECTOR3 move;				//�ړ�
	D3DXMATRIX mtxWorld;			//
	float fWidth;					//��
	float fHeight;					//����
	int nLife;						//����
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Effect;

//============================================================
// �v���g�^�C�v�錾
//============================================================
void lnitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int life);
void ZZEffect(void);
#endif
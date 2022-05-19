
//============================================================
//
// 3D����@�ǂ̏���[wall.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//============================================================
// �e�̍\���̂̒�`
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//���_					
	D3DXVECTOR3 rot;				//�����_
	D3DXVECTOR3 col;				//�F
	D3DXMATRIX mtxWorld;			//
	float fWidth;					//��
	float fHeight;					//����
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Wall;

//============================================================
// �v���g�^�C�v�錾
//============================================================
void lnitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth,float fHeight, float fcol);
void ZZWall(void);
Wall*GetWall(void);
#endif
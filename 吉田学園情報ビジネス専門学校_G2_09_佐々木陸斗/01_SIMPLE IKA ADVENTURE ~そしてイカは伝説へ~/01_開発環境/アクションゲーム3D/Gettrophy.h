//============================================================
//
// 3D����@�Q�b�g�g���t�B�[�̏���[billborad.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _GETTROPHY_H_
#define _GETTROPHY_H_
#define MAX_GETTROPHY				(3)		//�ǂݍ��ރT�C�Y
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 move;								//�ړ���
	float fWidth;									//��
	float fHeight;									//����
	bool bUse;										//�g�p���Ă��邩�ǂ���
}GETTrophy;


//�v���g�^�C�v�錾
void lnitGetTrophy(void);
void UninitGetTrophy(void);
void UpdateGetTrophy(void);
void DrawGetTrophy(void);
void SetGetTrophy(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight);
void AddGetTrophy(int nValue);
int GetgetTrophy(void);
#endif 


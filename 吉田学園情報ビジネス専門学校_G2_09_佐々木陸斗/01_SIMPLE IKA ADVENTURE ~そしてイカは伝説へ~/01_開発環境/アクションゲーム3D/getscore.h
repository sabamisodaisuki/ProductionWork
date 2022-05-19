//============================================================
//
// 3D����@�Q�b�g�X�R�A�̏���[billborad.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _GETSCORE_H_
#define _GETSCORE_H_
#define MAX_GETScore				(3)		//�ǂݍ��ރT�C�Y
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 move;								//�ړ���
	float fWidth;									//��
	float fHeight;									//����
	bool bUse;										//�g�p���Ă��邩�ǂ���
}GETScore;


//�v���g�^�C�v�錾
void lnitGetScore(void);
void UninitGetScore(void);
void UpdateGetScore(void);
void DrawGetScore(void);
void SetGetScore(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight);
void AddGetScore(int nValue);
int GetgetScore(void);
#endif 

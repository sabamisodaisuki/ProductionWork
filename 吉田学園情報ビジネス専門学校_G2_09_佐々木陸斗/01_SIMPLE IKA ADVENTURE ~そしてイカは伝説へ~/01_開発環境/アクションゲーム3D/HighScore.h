//============================================================
//
// 3D����@�n�C�X�R�A�̏���[billborad.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_
#define MAX_HigeScore				(5)		//�ǂݍ��ރT�C�Y



#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 move;				//�ړ���
	float fWidth;					//��
	float fHeight;					//����
	bool bUse;						//�g�p���Ă��邩�ǂ���
}HigeScore;


//�v���g�^�C�v�錾
void lnitHigeScore(void);
void UninitHigeScore(void);
void UpdateHigeScore(void);
void DrawHigeScore(void);
void SetHigeScore(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight);
void AddHigeScore(int nValue);
void LoadHigeScore(void);
void SaveHigeScore(void);
int GetHigeScore(void);
#endif 
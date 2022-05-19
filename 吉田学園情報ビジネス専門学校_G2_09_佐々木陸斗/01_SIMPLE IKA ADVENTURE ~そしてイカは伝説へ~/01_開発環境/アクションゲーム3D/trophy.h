//============================================================
//
// 3D����@�g���t�B�[�̏���[trophy.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _TROPHY_H_
#define _TROPHY_H_

#include "main.h"

//�}�N����`
#define MAX_TROPHY			(128)		//�G�̍ő吔
#define NUM_TROPHY			(10)		//�G�̎��
#define TROPHY_SIZE			(300.0f)	//�G�̃T�C�Y

//�G�̏��
typedef enum
{
	TROPHYSTA_NORMAL = 0,
	TROPHYSTA_DAMAGE,
	TROPHYSTA_MAX
}TROPHYSTATE;


//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 move;								//�ړ���
	int nType;										//���
	TROPHYSTATE state;								//���
	int nCounterState;								//��ԊǗ��J�E���^�[
	int nLife;										//�̗�
	int nScore;										//���̃X�R�A
	bool bUse;										//�g�p���Ă��邩�ǂ���
}TROPHY;


//�v���g�^�C�v�錾
void lnitTrophy(void);
void UninitTrophy(void);
void UpdateTrophy(void);
void DrawTrophy(void);
void SetTrophy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
void HitTrophy(int nCntTROPHY, int nDamage);

TROPHY*GetTrophy(void);




#endif 


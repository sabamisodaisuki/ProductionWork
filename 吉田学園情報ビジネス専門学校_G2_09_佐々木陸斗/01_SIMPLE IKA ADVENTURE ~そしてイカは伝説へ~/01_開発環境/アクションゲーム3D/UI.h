//============================================================
//
// 3D����@UI�̏���[Ui.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _Ui_H_
#define _Ui_H_

#include "main.h"

//�}�N����`
#define MAX_Ui			(128)		//�G�̍ő吔
#define NUM_Ui			(10)		//�G�̎��
#define Ui_SIZE			(300.0f)	//�G�̃T�C�Y

//�G�̏��
typedef enum
{
	UiSTA_NORMAL = 0,
	UiSTA_DAMAGE,
	UiSTA_MAX
}UiSTATE;


//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 move;								//�ړ���
	int nType;										//���
	UiSTATE state;									//���
	float fWidth;									//��
	float fHeight;									//��
	int nCounterState;								//��ԊǗ��J�E���^�[
	int nLife;										//�̗�
	int nScore;										//���̃X�R�A
	bool bUse;										//�g�p���Ă��邩�ǂ���
}Ui;


//�v���g�^�C�v�錾
void lnitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
void SetUi(D3DXVECTOR3 pos, float fWidth, float fHeight);


#endif 



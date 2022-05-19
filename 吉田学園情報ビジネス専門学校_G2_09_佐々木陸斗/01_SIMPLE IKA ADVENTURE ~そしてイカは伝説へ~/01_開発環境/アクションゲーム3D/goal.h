//===================================
//
// 3D����@�S�[���̏���[goal.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"
//===================================
//���f���̍\���̂̒�`
//===================================
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu					
	D3DXVECTOR3 move;				//�ړ���
	D3DXVECTOR3 scale;				//
	D3DXVECTOR3 rot;					//
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posOld;				//�O��̈ʒu
									//D3DXVECTOR3 VtxMinGoal;				//�ŏ��l
									//D3DXVECTOR3 VtxMaxGoal;				//�ő�l
	D3DXVECTOR3 size;
	int nNumVtx;							//���_��
	DWORD sizeFVF;							//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;							//���_�o�b�t�@�̃|�C���^
	int nCounterState;						//��ԊǗ��J�E���^�[
	int nLife;								//�̗�
	int nCounterAnim;						//�J�E���^�[
	int nPatternAnim;						//�p�^�[���ԍ�
	int nDirectionMove;						//����
	float fWidth;							//��
	float fHeight;							//����
	bool bDisp;								//�\�����邩���Ȃ���
	bool bIsJumping;						//�W�����v��
	bool bUse;
	int nType;								//�^�C�v
}Goal;
//===================================
// �v���g�^�C�v�錾
//===================================
void lnitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
bool CollisionGoal(D3DXVECTOR3*pPos,//���݂̈ʒu
	D3DXVECTOR3*pPosOld,			//�O��̍���
	D3DXVECTOR3*pMove,				//�ړ���
	D3DXVECTOR3*pSize);				//�T�C�Y
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
void GoalSet(void);


#endif


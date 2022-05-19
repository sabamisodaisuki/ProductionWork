//===================================
//
// 3D����@��[Miti.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _MITI_H_
#define _MITI_H_

#include "main.h"
//===================================
//���f���̍\���̂̒�`
//===================================
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu					
	D3DXVECTOR3 move;						//�ړ���
	D3DXVECTOR3 scale;						//
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posOld;						//�O��̈ʒu
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
}MITI;
//===================================
// �v���g�^�C�v�錾
//===================================
void lnitMiti(void);
void UninitMiti(void);
void UpdateMiti(void);
void DrawMiti(void);
void SetMiti(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
void MitiSet(void);


#endif


//===================================
//
// 3D����@�v���C���[[player.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
//===================================
//���f���̍\���̂̒�`
//===================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu					
	D3DXVECTOR3 move;				//�ړ���
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rot;				//�p�x
	D3DXVECTOR3 posOld;				//�O��̈ʒu
	D3DXVECTOR3 VtxMin;				//�ŏ��l
	D3DXVECTOR3 VtxMax;				//�ő�l
	D3DXVECTOR3 size;				//�T�C�Y
	int nCounterState;				//��ԊǗ��J�E���^�[
	int nLife;						//�̗�
	int nCounterAnim;				//�J�E���^�[
	int nPatternAnim;				//�p�^�[���ԍ�
	int nDirectionMove;				//����
	float fWidth;					//��
	float fHeight;					//����
	bool bDisp;						//�\�����邩���Ȃ���
	bool bIsJumping;				//�W�����v
	bool blsLanding;
	bool bUse;

}Player;
//===================================
// �v���g�^�C�v�錾
//===================================
void lnitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DeathPlayer(D3DXVECTOR3 pos);
Player*GetPlayer(void);
#endif


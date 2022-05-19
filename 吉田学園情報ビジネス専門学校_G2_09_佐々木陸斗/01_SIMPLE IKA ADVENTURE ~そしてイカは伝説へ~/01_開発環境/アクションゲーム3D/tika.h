//===================================
//
// 3D����	�n���z�u[Tika.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _Tika_H_
#define _Tika_H_

#include "main.h"
//===================================
//Tika�̍\���̂̒�`
//===================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu					
	D3DXVECTOR3 move;				//�ړ���
	D3DXVECTOR3 scale;				//
	D3DXVECTOR3 rot;				//
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posOld;				//�O��̈ʒu
	D3DXVECTOR3 size;
	int nNumVtx;					//���_��
	DWORD sizeFVF;					//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;					//���_�o�b�t�@�̃|�C���^
	int nCounterState;				//��ԊǗ��J�E���^�[
	int nLife;						//�̗�
	int nCounterAnim;				//�J�E���^�[
	int nPatternAnim;				//�p�^�[���ԍ�
	int nDirectionMove;				//����
	float fWidth;					//��
	float fHeight;					//����
	bool bDisp;						//�\�����邩���Ȃ���
	bool bIsJumping;				//�W�����v��
	bool bUse;
	int nType;						//�^�C�v
}Tika;
//===================================
// �v���g�^�C�v�錾
//===================================
void lnitTika(void);
void UninitTika(void);
void UpdateTika(void);
void DrawTika(void);							
void SetTika(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);//�u���b�N�̐ݒ菈��
void TikaSet(void);
bool CollisionTika(D3DXVECTOR3*pPos,//���݂̈ʒu
	D3DXVECTOR3*pPosOld,			//�O��̍���
	D3DXVECTOR3*pMove,				//�ړ���
	D3DXVECTOR3*pSize);				//�T�C�Y
Tika*GetTika(void);

#endif



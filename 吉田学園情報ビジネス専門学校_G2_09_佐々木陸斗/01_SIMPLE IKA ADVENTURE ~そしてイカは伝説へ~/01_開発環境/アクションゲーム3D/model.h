//===================================
//
// 3D����@���f��[model.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _MODEL_H_
#define _MODEL_H_

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
	D3DXVECTOR3 size;						//�T�C�Y
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
	bool bUse;								//�g�p���邩�ǂ���
	int nType;								//�^�C�v
}Model;
//===================================
// �v���g�^�C�v�錾
//===================================
void lnitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
bool CollisionModel(D3DXVECTOR3*pPos,//���݂̈ʒu
	D3DXVECTOR3*pPosOld,			//�O��̍���
	D3DXVECTOR3*pMove,				//�ړ���
	D3DXVECTOR3*pSize);				//�T�C�Y
									//�u���b�N�̐ݒ菈��
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);
void ModelSet(void);
float GetYMaxModel(void);
Model*GetModel(void);

#endif

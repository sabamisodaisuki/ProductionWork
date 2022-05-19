//============================================================
//
// 3D����@�J��������[camera.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//============================================================
// �J�����̍\���̂̒�`
//============================================================
typedef struct
{
	D3DXVECTOR3 posV;				//���_					
	D3DXVECTOR3 posR;				//�����_
	D3DXVECTOR3 vecU;				//�������x�N�g��
	D3DXVECTOR3 posVDest;			//�ړI�̎��_		
	D3DXVECTOR3 posRDest;			//�ړI�̒����_
	D3DXVECTOR3 rot;				//����
	D3DXVECTOR3 move;				//�ړ���
	D3DXMATRIX mtxProjection;		//�v���W�F�N�V����
	D3DXMATRIX mtxviex;				//�r���[�}�g���b�N�X
	float fDistance;				//���_���璍���_�܂ł̋���B
	float fDistance1;				//���_���璍���_�܂ł̋���A


}Camera;

//============================================================
// �v���g�^�C�v�錾
//============================================================
Camera*GetCamera(void);
void lnitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

#endif

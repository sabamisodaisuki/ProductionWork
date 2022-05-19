//============================================================
//
// 3D����@���b�V����[Meshield.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _MESHIELD_H_
#define _MESHIELD_H_

#include "main.h"
//���b�V���̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 g_posMeshfield;				//�ʒu					
	D3DXVECTOR3 g_moveMeshfield;			//�ړ���
	
}MESHFIELD;

//============================================================
// �v���g�^�C�v�錾
//============================================================
void lnitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
MESHFIELD*GetMeshfield(void);
#endif

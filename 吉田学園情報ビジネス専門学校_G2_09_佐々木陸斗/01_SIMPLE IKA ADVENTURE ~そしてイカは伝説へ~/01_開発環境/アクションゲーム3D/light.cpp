//============================================================
//
// 3D����@���C�g����[light.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "light.h"
#include "main.h"

//============================================================
// �O���[�o���ϐ�
//============================================================
D3DLIGHT9 g_light [10];	//���C�g���

//============================================================
// ���C�g�̏���������
//============================================================
void lnitLight(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�x�N�g��
	D3DXVECTOR3 verDir[10];

	//���C�g�N���A
	ZeroMemory(&g_light[0],sizeof(D3DLIGHT9));
	ZeroMemory(&g_light[1], sizeof(D3DLIGHT9));

	//���C�g�̎��
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g������ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	//���C�g�̕�����ݒ�
	verDir[0] = D3DXVECTOR3(0.2f, -1.0f, -0.4f);
	verDir[1] = D3DXVECTOR3(-0.2f,-1.0f,  0.4f);

	//���K������
	D3DXVec3Normalize(&verDir[0], &verDir[0]);
	g_light[0].Direction = verDir[0];

	//���K������
	D3DXVec3Normalize(&verDir[1], &verDir[1]);
	g_light[1].Direction = verDir[1];

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light[0]);

	//���C�g��ݒ肷��
	pDevice->SetLight(1, &g_light[1]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	//���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);
}

//============================================================
// ���C�g�̏I������
//============================================================
void UninitLight(void)
{

}

//============================================================
// ���C�g�̃A�b�v�f�[�g����
//============================================================
void UpdateLight(void)
{

}
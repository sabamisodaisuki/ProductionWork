//============================================================
//
// 3D����@�J�����̏���[camera.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "camera.h "
#include "main.h"
#include "input.h"
#include "player.h"

//============================================================
//�O���[�o���ϐ�
//============================================================
Camera g_camera;

//============================================================
// �J�����̏�����
//============================================================
void lnitCamera(void)
{
	//�v���C���[�̏����擾
	Player*pPlayer = GetPlayer();

	//���_�E�����_�E��������ݒ�
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -245.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x)*(g_camera.posR.x - g_camera.posV.x)+(g_camera.posR.z-g_camera.posV.z)*(g_camera.posR.z-g_camera.posV.z));
	g_camera.fDistance1 = 20.0f;

}

//============================================================
// �J�����̏I������
//============================================================
void UninitCamera(void)
{

}

//============================================================
// �J�����̃A�b�v�f�[�g����
//============================================================
void UpdateCamera(void)
{
	//�v���C���[�̏����擾
	Player*pPlayer = GetPlayer();

	//�J�����̐��K��

	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}
	else if (g_camera.rot.y< -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
	}

//============================================================
// �J�����̒Ǐ]
//============================================================
	g_camera.posRDest.x = pPlayer->pos.x;// -sinf(pPlayer->rot.y) * g_camera.fDistance1;
	g_camera.posRDest.y = pPlayer->pos.y;
	g_camera.posRDest.z = pPlayer->pos.z;// -cosf(pPlayer->rot.y) * g_camera.fDistance1;

	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x)*0.1f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z)*0.1f;

	g_camera.posVDest.x = g_camera.posRDest.x; //+cosf(pPlayer->rot.y)*g_camera.fDistance;
	g_camera.posVDest.y = g_camera.posRDest.y + 250.0f;
	g_camera.posVDest.z = g_camera.posRDest.z - 350.0f;// +sinf(pPlayer->rot.y)*g_camera.fDistance;

	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
}

//============================================================
// �J�����̃Z�b�g����
//============================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxviex);

	//�r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&g_camera.mtxviex,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxviex);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̐���
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}
//============================================================
// �J�������
//============================================================
Camera*GetCamera(void)
{
	return&g_camera;
}
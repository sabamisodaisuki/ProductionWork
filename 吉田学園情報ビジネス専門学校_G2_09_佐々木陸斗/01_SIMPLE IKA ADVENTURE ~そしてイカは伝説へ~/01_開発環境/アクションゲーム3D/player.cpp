//===========================================================
//
// 3D����@���f������[Player.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "Player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include"meshfield.h"
#include"wall.h"
#include"effect.h"
#include"MODEL.h"
#include"sound.h"
#include"goal.h"
#include"enemy.h"
#include"bird.h"
#include"trophy.h"
#include"tika.h"
#include"Score.h"
#include"Gettrophy.h"
#include"getscore.h"
//============================================================
//�}�N����`
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);//�����W��
#define PLAYER_G	(1.0f)//�d��
#define SPEED		(4.5f)//����	

//============================================================
//�O���[�o���ϐ�
//============================================================
LPD3DXMESH g_MeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
D3DXVECTOR3 g_rotDestPlayer;
D3DXMATRIX g_mtxWorldPlayer;
DWORD g_nNumMatPlayer = 0;
Player g_Player;
int g_nIdxShadow;
int CntGet;

//�v���C���[�̎擾
Player*GetPlayer(void)
{
	return &g_Player;
}

//============================================================
//�@�v���C���[�̏���������
//============================================================
void lnitPlayer(void)
{
	Model*pModel;
	pModel = GetModel();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/ikao2.x",//�g�����f���FMODEL.x,ika.x,Suraimu.x
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_nNumMatPlayer,
		&g_MeshPlayer);

	g_Player.pos = D3DXVECTOR3(30.0f, 420.0f, -590.0f);//�ʒu�̏�����...�G���A1(30.0f, 420.0f, -590.0f)2,2000.0f, 260.0f, -590.0f,�G���A3(3050.0f, 200.0f, -590.0f)
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
	g_rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�p�x�̏�����
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��l��������
	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot);
	g_Player.VtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//�ŏ��l
	g_Player.VtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//�ő�l
	
	int nNumVtx;									//���_��
	DWORD sizeFVF;									//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;									//���_�o�b�t�@�̃|�C���^

	//���_���̎擾
	nNumVtx = g_MeshPlayer->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_MeshPlayer->GetFVF());

	//���_�o�b�t�@�����b�N
	g_MeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���_���W���r���ă��f���̍ő�l���擾
		if (Vtx.x > g_Player.VtxMax.x)
		{
			g_Player.VtxMax.x = Vtx.x;
		}

		if (Vtx.y > g_Player.VtxMax.y)
		{
			g_Player.VtxMax.y = Vtx.y;
		}

		if (Vtx.z > g_Player.VtxMax.z)
		{
			g_Player.VtxMax.z = Vtx.z;
		}

		//���_���W���r���ă��f���̍ŏ��l���擾

		if (Vtx.x < g_Player.VtxMin.x)
		{
			g_Player.VtxMin.x = Vtx.x;
		}

		if (Vtx.y < g_Player.VtxMin.y)
		{
			g_Player.VtxMin.y = Vtx.y;
		}

		if (Vtx.z < g_Player.VtxMin.z)
		{
			g_Player.VtxMin.z = Vtx.z;
		}
		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�ccc
		pVtxBuff += sizeFVF;
	}
	
	//���_�o�b�t�@�̃A�����b�N
	g_MeshPlayer->UnlockVertexBuffer();
	//	�v���C���[�T�C�Y
	g_Player.size.x = (g_Player.VtxMax.x - g_Player.VtxMin.x) / 2.0f;
	g_Player.size.y = (g_Player.VtxMax.y - g_Player.VtxMin.y) / 2.0f;
	g_Player.size.z = (g_Player.VtxMax.z - g_Player.VtxMin.z) / 2.0f;
}
//============================================================
//�@�I������
//============================================================
void UninitPlayer(void)
{
	//�T�E���h�̒�~
	StopSound();
	//���b�V���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//============================================================
// �v���C���[�̃A�b�v�f�[�g����
//============================================================
void UpdatePlayer(void)
{
	Camera*pCamera = GetCamera();
	MESHFIELD*pMeshfield=GetMeshfield();	//���b�V���̓����蔻��p
	//Wall*pWall = GetWall();				//�ǂ̓����蔻��p
	Model*pModel;
	pModel = GetModel();
	
	//���f���������ʒu��
	if (GetKeyboardPress(DIK_F1))
	{//F1�L�[��������

		g_Player.pos = D3DXVECTOR3(30.0f, 420.0f, -590.0f);
	}

	//���f�����Q�X�e�[�W�̈ʒu��
	if (GetKeyboardPress(DIK_P))
	{//F1�L�[��������

		g_Player.pos = D3DXVECTOR3(2000.0f, 260.0f, -590.0f);
	}

	//�v���C���[���R�X�e�[�W�̈ʒu��
	if (GetKeyboardPress(DIK_M))
	{//F1�L�[��������

		g_Player.pos = D3DXVECTOR3(4400.0f, 300.0f, -590.0f);
	}

	//���f���̉E�ړ�
	else if (GetKeyboardPress(DIK_D))
	{//�E����
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f)*SPEED;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f)*SPEED;
		g_rotDestPlayer.y = pCamera->rot.y + D3DX_PI *-0.0f;
	}
	
	//���f���̍��ړ�
	else if (GetKeyboardPress(DIK_A))
	{//������
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f)*SPEED;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f)*SPEED;
		g_rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 1.0f;
	}
	
	//���f������
	 if (GetKeyboardPress(DIK_W))
	{//�W�����v
		 if (g_Player.bIsJumping == false)
		 {
			 //�T�E���h�̍Đ�
			 PlaySound(SOUND_LABEL_SE_jump);
			g_Player.bIsJumping = true;
			g_Player.move.y = 12.5f;
			SetEffect(g_Player.pos,g_Player.rot, D3DXVECTOR3(20.0f, 20.0f, 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40);
		 }
	}
	 //���f������
	 if (GetKeyboardPress(DIK_RETURN))
	 {//�W�����v
		 if (g_Player.bIsJumping == false)
		 {
			 //�T�E���h�̍Đ�
			 PlaySound(SOUND_LABEL_SE_jump);
			 g_Player.bIsJumping = true;
			 g_Player.move.y = 12.5f;
			 SetEffect(g_Player.pos, g_Player.rot, D3DXVECTOR3(20.0f, 20.0f, 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40);
		 }
	 }
	 //����Ҍ���
	 if (GetKeyboardTrigger(DIK_I))
	 {//�B���g���t�B�[
		 //�T�E���h�̍Đ�
		 PlaySound(SOUND_LABEL_SE_fanfare);
		 SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 2);
		 AddScore(50);
		 AddGetTrophy(1);
	 }
	float fDest = g_rotDestPlayer.y -g_Player.rot.y;

	if (fDest> D3DX_PI)
	{
		fDest -= D3DX_PI * 2;
	}
	else if (fDest < -D3DX_PI)
	{
		fDest += D3DX_PI * 2;
	}

	g_Player.rot.y += fDest*ANGLE_DAMPING_COEFFICIENT;

	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2;
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}

	//�O��̈ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	//�ړ��l
	g_Player.pos.x += g_Player.move.x / 2;
	g_Player.pos.y += g_Player.move.y / 2;
	g_Player.pos.z += g_Player.move.z / 2;
	g_Player.move.x = (-g_Player.move.x)*0.1f / 2;
	g_Player.move.y -= PLAYER_G / 2;
	g_Player.move.z = (-g_Player.move.z)*0.1f / 2;
	
	 if (g_Player.pos.y <pMeshfield->g_posMeshfield.y)
	{//���b�V���̉��ɓ�������
		g_Player.pos.y = pMeshfield->g_posMeshfield.y;
		g_Player.bIsJumping = false;
		DeathPlayer(D3DXVECTOR3(30.0f, 420.0f, -590.0f));
		AddGetTrophy(1);
		if (CntGet <1)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_fanfare);
			SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 4);
			CntGet++;
			AddGetScore(13);
		}
	}
	
	 //���f���Ƃ̓����蔻��
	 bool blsLanding = CollisionModel
		(&g_Player.pos,			//pPos
		 &g_Player.posOld,		//pPosOld
		 &g_Player.move,		//pMove
		 &g_Player.size);		//psize
	 if (blsLanding == true)
	 {
		 SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_Player.pos.x,g_Player.pos.y, g_Player.pos.z));
	 }
	 else
	 {
		 SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 1.0f, g_Player.pos.z));
	 }
	//���f���Ƃ̓����蔻��
	  CollisionGoal
	 (&g_Player.pos,		//pPos
		 &g_Player.posOld,	//pPosOld
		 &g_Player.move,	//pMove
		 &g_Player.size);	//psize

	//���Ƃ̓����蔻��
	  CollisionEnemy
	  (&g_Player.pos,		//pPos
		  &g_Player.posOld,	//pPosOld
		  &g_Player.move,	//pMove
		  &g_Player.size);	//psize

	  //���Ƃ̓����蔻��
	  CollisionBird
	  (&g_Player.pos,		//pPos
		  &g_Player.posOld,	//pPosOld
		  &g_Player.move,	//pMove
		  &g_Player.size);	//psize

	//�n���Ƃ̓����蔻��
	  CollisionTika
	  (&g_Player.pos,		//pPos
		  &g_Player.posOld,	//pPosOld
		  &g_Player.move,	//pMove
		  &g_Player.size);	//psize

	//�u���b�N�̏�ŃW�����v
	 if (blsLanding == true)
	 {
		 g_Player.bIsJumping = false;
	 }
}

//============================================================
// �v���C���[�̕`�揈��
//============================================================
void DrawPlayer(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p
	D3DMATERIAL9 matDef;//�}�e���A���̕ۑ�
	D3DXMATERIAL *pMat;//�}�e���A���̕ۊ�

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);
	//�}�g���b�N�X�̐ݒ�

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//���݂̃}�e���A��
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���g�擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		g_MeshPlayer->DrawSubset(nCntMat);
	}
	//�ۑ������}�e���A��
	pDevice->SetMaterial(&matDef);
}

void DeathPlayer(D3DXVECTOR3 pos)
{
	g_Player.pos = pos;
	int Death;

}
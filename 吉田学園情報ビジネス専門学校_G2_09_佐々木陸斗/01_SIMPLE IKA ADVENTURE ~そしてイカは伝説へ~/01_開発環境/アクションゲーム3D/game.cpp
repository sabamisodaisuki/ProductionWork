//============================================================
//
// 3D����@�Q�[���̏���[game.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"title.h"
#include"game.h"
#include"sound.h"
#include"Score.h"
#include"Time.h"
#include"HighScore.h"
#include "light.h"
#include "meshfield.h"
#include "shadow.h"
#include "billborad.h"
#include "model.h"
#include "wall.h"
#include "effect.h"
#include "camera.h"
#include "fade.h"
#include"goal.h"
#include"miti.h"
#include"enemy.h"
#include"trophy.h"
#include"bird.h"
#include"tika.h"
#include"Gettrophy.h"
#include"UI.h"
//============================================================
//�Q�[����ʏ�����
//============================================================
void lnitGAME(void)
{
	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGMGameBGM);

	//�J�����̏�����
	lnitCamera();

	//���C�g�̏�����
	lnitLight();


	//�|���S���̏�����
	//lnitPolygon();

	//���b�V���̏�����
	lnitMeshfield();

	//�e�̏�����
	lnitShadow();

	//�v���C���[�̏�����
	lnitPlayer();

	//���f��
	lnitModel();

	//�S�[���̏�����
	lnitGoal();

	//���̏�����
	lnitEnemy();

	//���̏�����
	lnitBird();

	////���̏�����
	lnitMiti();

	//�n���̏�����
	lnitTika();

	//�r���{�[�h
	lnitBillborad();

	//�Ǐ�����
	lnitWall();

	//�G�t�F�N�g������
	lnitEffect();

	//�^�C���̏�����
	lnitTime();
	
	//�X�R�A�̏���������
	lnitScore();

	//�n�C�X�R�A�̏�����
	lnitHigeScore();

	//�g���t�B�[�l���̏�����
	lnitGetTrophy();

	//UI�̏�����
	lnitUi();

	//�g���t�B�[�̏���������
	lnitTrophy();
}



//============================================================
//�Q�[���̏I������
//============================================================
void UninitGAME(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�J�����I��
	UninitCamera();

	//�|���S���̏I��
	//UninitPolygon();

	//���C�g�̏I��
	UninitLight();

	//���b�V���̏I��
	UninitMeshfield();

	//�e�̏I��
	UninitShadow();
	
	//�v���C���[�̏I��
	UninitPlayer();

	//���f���̏I��
	UninitModel();

	//���̏I��
	UninitEnemy();

	//�S�[���̏I������
	UninitGoal();

	//���̏I��
	UninitBird();

	//���̏I��
	UninitMiti();

	//�n���̏I��
	UninitTika();

	//�r���{�[�h�̏�����
	UninitBillborad();

	//�G�t�F�N�g�̏�����
	UninitEffect();

	//�ǏI��
	UninitWall();

	//�X�R�A�̏I������
	UninitScore();

	//�^�C���̏I������
	UninitTime();

	//�n�C�X�R�A�̏I��
	UninitHigeScore();

	//�g���t�B�[�̏I������
	UninitTrophy();

	//UI�̏I������
	UninitUi();

	//�g���t�B�[�̊l������
	UninitGetTrophy();
}

//============================================================
//�Q�[���̕`�揈��
//============================================================
void DrawGAME(void)
{
	//�J�����̃Z�b�g
	SetCamera();

	//�|���S���̕`��
	//DrawPolygon();

	//���b�V���̕`��
	//DrawMeshfield();

	//�v���C���[�̕`��
	DrawPlayer();

	//���f���̕`��
	DrawModel();

	//���̕`��
	DrawEnemy();

	//���̕`��
	DrawBird();

	//�S�[���̕`�揈��
	DrawGoal();

	//���̕`��
	DrawMiti();

	//�e�̕`��
	DrawShadow();

	//�n���̕`��
	DrawTika();

	//�G�t�F�N�g�̕`��
	DrawEffect();

	//�r���{�[�h�̕`�揈��
	DrawBillborad();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�^�C���̕`�揈��
	DrawTime();

	//�n�C�X�R�A�̕`�揈��
	DrawHigeScore();

	//�g���t�B�[�̕`�揈��
	DrawTrophy();

	//Ui�̕`�揈��
	DrawUi();

	//�g���t�B�[�l���̕`�揈��
	DrawGetTrophy();
}

//============================================================
//�Q�[����ʂ̍X�V����
//============================================================
void UpdateGAME(void)
{
	//�t�F�[�h�̍X�V����
	UpdateFade();

	//�J�����X�V
	UpdateCamera();

	//���C�g�̍X�V
	UpdateLight();

	//�e�̍X�V
	UpdateShadow();

	//�v���C���[�̍X�V
	UpdatePlayer();

	//���f���̍X�V
	UpdateModel();

	//���̍X�V
	UpdateEnemy();

	//���̍X�V
	UpdateBird();

	//�S�[���̍X�V
	UpdateGoal();

	//���̍X�V����
	UpdateMiti();

	//�n���̍X�V����
	UpdateTika();

	//�r���{�[�h�̍X�V
	UpdateBillborad();

	//�G�t�F�N�g�̍X�V
	UpdateEffect();

	//�ǂ̍X�V
	UpdateWall();

	//�X�R�A�̍X�V����
	UpdateScore();

	//�^�C���̍X�V
	UpdateTime();

	//�n�C�X�R�A�̍X�V����
	UpdateHigeScore();

	//�g���t�B�[�̍X�V����
	UpdateTrophy();

	//UI�̍X�V����
	UpdateUi();

	//�g���t�B�[�l���̍X�V����
	UpdateGetTrophy();
}
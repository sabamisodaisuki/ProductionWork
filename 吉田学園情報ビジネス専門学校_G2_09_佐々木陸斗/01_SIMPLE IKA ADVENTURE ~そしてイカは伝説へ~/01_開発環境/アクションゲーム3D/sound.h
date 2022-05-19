//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Sasaki Rikuto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGMTITLE2,		//�^�C�g��BGM
	SOUND_LABEL_BGMTITLE,		//�^�C�g��BGM
	SOUND_LABEL_BGMMAOU,		//�^�C�g��BGM2
	SOUND_LABEL_BGMGame,		//�Q�[��BGM
	SOUND_LABEL_BGMGameBGM,		//�Q�[��BGM
	SOUND_LABEL_SE_ketei,		//���艹
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_bakuha,	// ������
	SOUND_LABEL_SE_aruki,	// ����
	SOUND_LABEL_SE_jump,	// ����
	SOUND_LABEL_SE_fanfare,
	SOUND_LABEL_MAX,
	SOUND_LABEL_si
} SOUND_LABEL;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

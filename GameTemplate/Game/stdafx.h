#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
#include "tkSoundSource.h"					//�T�E���h

//�Q�[���S�̂ŕp�ɂɎg���̂�stdafx.h��h���C���N���[�h����
#include "SkinModelRender.h"				//���f��
#include "SpriteRender.h"					//�摜
#include "FontRender.h"						//����
#include "Light.h"							//���C�g
#include "../../ExEngine/effect/Effect.h"	//�G�t�F�N�g

//�F�Ƃ��͂����ɖ��O��Ԃł܂Ƃ߂Ă����B
//NewGO�̍ۂ̖��O����
namespace
{
	/// <summary>
	/// �D��x
	/// </summary>
	const int PRIORITY_0 = 0;
	const int PRIORITY_1 = 1;
	const int PRIORITY_2 = 2;

	/// <summary>
	/// �F
	/// </summary>
	const Vector3 WHITE = { 1.0f, 1.0f ,1.0f };	//���F
	const Vector3 RED = { 1.0f, 0.0f ,0.0f };	//�ԐF
	const Vector3 BLUE = { 0.0f, 0.0f ,1.0f };	//�F
	const Vector3 YELLOW = { 0.0f, 0.0f ,1.0f };//���F
	const Vector3 GREEN = { 1.0f, 1.0f ,0.0f };	//�ΐF
	const Vector3 GRAY = { 0.7f,0.7f,0.7f };	//�D�F
	/// <summary>
	/// ���O
	/// </summary>
	const char* TITLESCENE_NAME = "titlescene";
	const char* STAGESELECT_NAME = "stageselectscene";
	const char* GAMESCENE_NAME = "gamescene";
	const char* LIGHT_NAME = "light";
	const char* PLAYER_NAME = "player";
	const char* ENEMY_NAME = "enemy";
	/// <summary>
	/// �X�e�[�W�ԍ�
	/// </summary>
	const int STAGE1 = 1;
	const int STAGE2 = 2;
	const int STAGE3 = 3;

	const float GRAVITY = 0.3f;		//�d��
}
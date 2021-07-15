#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
#include "tkSoundSource.h"					//�T�E���h


//�Q�[���S�̂ŕp�ɂɎg���̂�stdafx.h��h���C���N���[�h����
#include "Noncopyable.h"					// �R�s�[�֎~�|���V�[��񋟂��邽�߂̃N���X�B
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
	const int PRIORITY_3 = 3;
	const int PRIORITY_4 = 4;
	const int PRIORITY_5 = 5;
	const int PRIORITY_6 = 6;
	const int PRIORITY_10 = 10;

	/// <summary>
	/// �F
	/// </summary>
	const Vector3 WHITE = { 1.0f, 1.0f ,1.0f };	//���F
	const Vector3 RED = { 1.0f, 0.0f ,0.0f };	//�ԐF
	const Vector3 BLUE = { 0.0f, 0.0f ,1.0f };	//�F
	const Vector3 YELLOW = { 1.0f, 1.0f ,0.0f };//���F
	const Vector3 GREEN = { 0.0f, 1.0f ,0.0f };	//�ΐF
	const Vector3 GRAY = { 0.8f,0.8f,0.8f };	//�D�F
	const Vector3 BLACK = { 0.0f,0.0f,0.0f };	//���F
	/// <summary>
	/// ���O
	/// </summary>
	const char* const LIGHT_NAME = { "light" };
	const char* const TITLESCENE_NAME = { "titlescene" };
	const char* const STAGESELECT_NAME = { "stageselectscene" };
	const char* const GAMESCENE_NAME = { "gamescene" };
	const char* const STAGE_NAME = { "stage" };
	const char* const PLAYER_NAME = { "player" };
	const char* const ENEMY_NAME = { "enemy" };

	/// <summary>
	/// �X�e�[�W�ԍ�
	/// </summary>
	const int STAGE1 = 1;
	const int STAGE2 = 2;
	const int STAGE3 = 3;
	const int STAGE4 = 4;

	const float GRAVITY = 0.3f;		//�d��
	const int PLAYER_MAX_NUM = 4;
	const int ENEMY_MAX_NUM = 6;
}
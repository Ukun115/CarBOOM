#include "stdafx.h"
#include "system/system.h"
#include "TitleScene.h"
#include "StopWatch.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	//�t�B�W�N�X���[���h�̃C���X�^���X���쐬����B
	PhysicsWorld::CreateInstance();
	//�G�t�F�N�g�G���W���̃C���X�^���X���쐬����B
	EffectEngine::CreateInstance();
	//�T�E���h�G���W���̃C���X�^���X���쐬����B
	SoundEngine::CreateInstance();
	SoundEngine::GetInstance()->Init();

	//�T�E���h�Ǌ��N���X
	nsCARBOOM::SoundPlayBack* m_soundPlayBack = nullptr;
	m_soundPlayBack = NewGO<nsCARBOOM::SoundPlayBack>(nsStdafx::PRIORITY_0, nsStdafx::SOUNDPLAYBACK_NAME);

	//�X�g�b�v�E�H�b�`�𐶐�����
	StopWatch stopWatch;

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//�^�C�g���V�[���I�u�W�F�N�g����
	nsCARBOOM::TitleScene* m_titleScene = NewGO<nsCARBOOM::TitleScene>(nsStdafx::PRIORITY_0, nullptr);

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�X�g�b�v�E�H�b�`�̌v���J�n
		stopWatch.Start();

		//�����_�����O�J�n�B
		g_engine->BeginFrame();

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�B
		GameObjectManager::GetInstance()->ExecuteUpdate();
		//�������[���h�̍X�V�B
		PhysicsWorld::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		//�G�t�F�N�g�G���W���̍X�V�B
		EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

		//�o�^����Ă���Q�[���I�u�W�F�N�g�̕`��֐����Ăяo���B
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//�G�t�F�N�g�̃h���[�B
		EffectEngine::GetInstance()->Draw();

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();

		//�X�s�����b�N���s���B
		int restTime = 0;
		do {
			stopWatch.Stop();
			restTime = 16 - (int)stopWatch.GetElapsedMillisecond();
		} while (restTime > 0);

		//�X�g�b�v�E�H�b�`�̌v���I��
		stopWatch.Stop();
		//�f���^�^�C�����X�g�b�v�E�H�b�`�̌v�����Ԃ���A�v�Z����
		GameTime().PushFrameDeltaTime((float)stopWatch.GetElapsed());
	}

	/*GameObjectManager::DeleteInstance();
	PhysicsWorld::DeleteInstance();
	EffectEngine::DeleteInstance();*/

	return 0;
}
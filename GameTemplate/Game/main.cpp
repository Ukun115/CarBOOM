#include "stdafx.h"
#include "system/system.h"
#include "TitleScene.h"


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

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	Light* m_light = nullptr;
	//���C�g�I�u�W�F�N�g����
	m_light = NewGO<Light>(PRIORITY_0, LIGHT_NAME);
	//�f�B���N�V�������C�g���Z�b�g
	m_light->SetDirectionLightData();
	//�������C�g���Z�b�g
	m_light->SetHemiSphereLightData();

	//�^�C�g���V�[���I�u�W�F�N�g����
	TitleScene* m_titleScene = NewGO<TitleScene>(PRIORITY_0, TITLESCENE_NAME);


	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
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
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}
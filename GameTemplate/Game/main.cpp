#include "stdafx.h"
#include "system/system.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"
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
	PhysicsWorld::CreateInstance();

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//�f�B���N�V�������C�g�����[�h
	DirectionLight* m_directionlight = NewGO<DirectionLight>(0, "directionlight");
	m_directionlight->SetDirectionLightData();

	//�|�C���g���C�g�����[�h
	PointLight* m_pointlight = NewGO<PointLight>(0, "pointlight");
	m_pointlight->SetPointLightData();

	//�X�|�b�g���C�g�����[�h
	SpotLight* m_spotlight = NewGO<SpotLight>(0, "spotlight");
	m_spotlight->SetSpotLightData();

	//�^�C�g���V�[���N���X����J�n
	TitleScene* titleScene = NewGO<TitleScene>(0);

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);


		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}
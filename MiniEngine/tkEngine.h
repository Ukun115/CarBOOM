#pragma once

#include "HID/GamePad.h"
#include "../GameTemplate/Game/GameTime.h"

class TkmFile;
class Shader;
class GraphicsEngine;

class TkEngine {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~TkEngine();
	/// <summary>
	/// �t���[���̊J�n���ɌĂ΂�鏈���B
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// �t���[���̏I�����ɌĂ΂�鏈���B
	/// </summary>
	void EndFrame();
	/// <summary>
	/// �Q�[���G���W���̏������B
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);

	const int GetRate()const {
		return m_rate;
	}

	TkmFile* GetTkmFileFromBank(const char* filePath)
	{
		return m_tkmFileBank.Get(filePath);
	}

	void RegistTkmFileToBank(const char* filePath, TkmFile* tkmFile)
	{
		m_tkmFileBank.Regist(filePath, tkmFile);
	}

	Shader* GetShaderFromBank(const char* filePath, const char* entryPointFuncName)
	{
		std::string programName = filePath;
		programName += entryPointFuncName;
		return m_shaderBank.Get(programName.c_str());
	}

	void RegistShaderToBank(const char* filePath, const char* entryPointFuncName, Shader* shader)
	{
		std::string programName = filePath;
		programName += entryPointFuncName;
		m_shaderBank.Regist(programName.c_str(), shader);
	}

private:
	TResourceBank<TkmFile> m_tkmFileBank;
	TResourceBank<Shader> m_shaderBank;

	GraphicsEngine* m_graphicsEngine = nullptr;		//�O���t�B�b�N�G���W���B
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//�Q�[���p�b�h�B
	GameTime m_gameTime;							//�Q�[���^�C���B
	int m_rate = 0;
};

extern TkEngine* g_engine;	//TK�G���W���B
extern GameTime* g_gameTime;

//�f�o�b�O�@�\���ȈՓI�ɃA�N�Z�X���邽�߂̖��O���
namespace dbg {

#if BUILD_LEVEL != BUILD_LEVEL_MASTER
	/*!
	* @brief	�R���W�����̃f�o�b�O�\����L���ɂ���B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	static inline void SetDrawPhysicsCollisionEnable()
	{
		PhysicsWorld().SetDebugDrawMode(1);
	}
	/*!
	* @brief	�R���W�����̃f�o�b�O�\����L���ɂ���B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	static inline void SetDrawPhysicsCollisionDisable()
	{
		PhysicsWorld().SetDebugDrawMode(0);
	}
	/*!
	* @brief	�x�N�g���̃f�o�b�O�o�́B
	*/
	static inline void DrawVector(Vector3 vector, Vector3 origin, const char* name = "no name")
	{
		prefab::CVectorRender::SRenderData renderData = { name, vector, origin };
		Engine().GetVectorRender()->AddVector(renderData);
	}
	/*!
	* @brief	�x�N�g���̃f�o�b�O�`���L���ɂ���B
	*/
	static inline void SetDrawVectorEnable()
	{
		Engine().GetVectorRender()->SetRenderFlag(true);
	}
	/*!
	* @brief	�x�N�g���̃f�o�b�O�`��𖳌��ɂ���B
	*/
	static inline void SetDrawVectorDisable()
	{
		Engine().GetVectorRender()->SetRenderFlag(false);
	}
	static inline void SetDrawVectorNameList(const std::vector<std::string>& list)
	{
		Engine().GetVectorRender()->SetRenderVectorNameList(list);
	}
#else

	static inline void SetDrawPhysicsCollisionEnable()
	{
	}

	static inline void SetDrawPhysicsCollisionDisable()
	{
	}

	static inline void DrawVector(Vector3 vector, Vector3 origin, const char* name = "no name")
	{
	}

	static inline void SetDrawVectorEnable()
	{
	}

	static inline void SetDrawVectorDisable()
	{
	}
	static inline void SetDrawVectorNameList(const std::vector<std::string>& list)
	{
	}
#endif

}

#pragma once
#include "stdafx.h"

class GameTime
{
public:
	static GameTime& GetInstance()
	{
		static GameTime t;
		return t;
	}
	/*!
	 *@brief	1�t���[���̌o�ߎ��Ԃ��擾(�P�ʁE�b)�B
	 */
	const float GetFrameDeltaTime() const
	{
		//�Œ�FPS�ɂ���B�ς͗v�����B
		//return 1.0f / 30.0f;
		return m_frameDeltaTime;
	}
	void PushFrameDeltaTime(float deltaTime)
	{
		m_frameDeltaTimeQue.push_back(deltaTime);
		if (m_frameDeltaTimeQue.size() > 30.0f) {
			float totalTime = 0.0f;
			for (auto time : m_frameDeltaTimeQue) {
				totalTime += time;
			}
			//���ϒl���Ƃ�B
			m_frameDeltaTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
			m_frameDeltaTimeQue.pop_front();
		}
	}
	/// <summary>
	/// �v���J�n
	/// </summary>
	/// <remark>
	/// �{�֐��̓G���W�����ł̂ݎg�p���܂��B
	/// ���[�U�[�͎g�p���Ȃ��ł��������B
	/// </remark>
	//void BeginMeasurement()
	//{
	//	//�v���J�n�B
	//	m_sw.Start();
	//}
	static GameTime& GameTimeFunc() {

		return GameTime::GetInstance();
	}

	private:
	std::list<float> m_frameDeltaTimeQue;
	float		m_frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB
};


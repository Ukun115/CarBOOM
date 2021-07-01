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
	 *@brief	1フレームの経過時間を取得(単位・秒)。
	 */
	const float GetFrameDeltaTime() const
	{
		//固定FPSにする。可変は要検討。
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
			//平均値をとる。
			m_frameDeltaTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
			m_frameDeltaTimeQue.pop_front();
		}
	}
	/// <summary>
	/// 計測開始
	/// </summary>
	/// <remark>
	/// 本関数はエンジン内でのみ使用します。
	/// ユーザーは使用しないでください。
	/// </remark>
	//void BeginMeasurement()
	//{
	//	//計測開始。
	//	m_sw.Start();
	//}
	static GameTime& GameTimeFunc() {

		return GameTime::GetInstance();
	}

	private:
	std::list<float> m_frameDeltaTimeQue;
	float		m_frameDeltaTime = 1.0f / 60.0f;		//1フレームの経過時間。
};


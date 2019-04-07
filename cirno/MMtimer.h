
#pragma once
#include <windows.h>

class MMTimer
{
private:
	static LARGE_INTEGER m_clk;			// ����ʱ����Ϣ
	static LONGLONG m_oldclk;			// ���濪ʼʱ�Ӻͽ���ʱ��
	static int m_freq;					// ʱ��Ƶ��(ʱ��ʱ�任����)��ʱ���

public:
	static void Sleep(int ms);
};

LARGE_INTEGER MMTimer::m_clk;
LONGLONG MMTimer::m_oldclk;
int MMTimer::m_freq = 0;

// ��ʱ
void MMTimer::Sleep(int ms)
{
	if (m_oldclk == 0)
	{
		QueryPerformanceFrequency(&m_clk);
		m_freq = (int)m_clk.QuadPart / 1000;	// ��ü�������ʱ��Ƶ��

		// ��ʼ��ʱ
		QueryPerformanceCounter(&m_clk);
		m_oldclk = m_clk.QuadPart;				// ��ÿ�ʼʱ��
	}

	unsigned int c = ms * m_freq;

	m_oldclk += c;

	QueryPerformanceCounter(&m_clk);

	if (m_clk.QuadPart > m_oldclk)
		m_oldclk = m_clk.QuadPart;
	else
		do
		{
			::Sleep(1);
			QueryPerformanceCounter(&m_clk);	// �����ֹʱ��
		} while (m_clk.QuadPart < m_oldclk);
}
#ifndef _OKA_SCREENMANAGER_H_
#define _OKA_SCREENMANAGER_H_

namespace oka
{
	class ScreenManager
	{
	private:
		static ScreenManager* m_instance;
		int m_width;
		int m_height;

		ScreenManager() :
			m_width(900), m_height(900)
		{};

	public:
		static ScreenManager* GetInstance();
		void SetWidth(const int _width) { m_width = _width; };
		void SetHeight(const int _height) { m_height = _height; };
		int GetWidth()const { return m_width; };
		int GetHeight()const { return m_height; };
		void SetViewport(const int _x, const int _y, const int _width, const int _height)const;
	};
}

#endif
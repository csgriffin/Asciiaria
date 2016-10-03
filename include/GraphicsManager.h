#pragma once

#include <SFML/Graphics.hpp>

#include "Manager.h"
#include "Color.h"
#include "Vector.h"
#include "Frame.h"

namespace df {

	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	float charHeight();
	float charWidth();
	Vector spacesToPixels(Vector spaces);
	Vector pixelsToSpaces(Vector pixels);

	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};

	class GraphicsManager :
		public Manager
	{

	private:
		GraphicsManager();
		GraphicsManager(GraphicsManager const&);
		void operator=(GraphicsManager const&);
		sf::Font font;
		sf::RenderWindow *p_window;
		int window_horizontal_pixels;
		int window_vertical_pixels;
		int window_horizontal_chars;
		int window_vertical_chars;
		sf::Color GraphicsManager::gimmeDatColor(df::Color color) const;

	public:
		int drawString(Vector pos, std::string str, Justification just, Color color) const;
		static GraphicsManager &getInstance();
		int startUp();
		void shutDown();
		int drawCh(Vector world_pos, char ch, Color color) const;
		int getHorizontal() const;
		int getVertical() const;
		int getHorizontalPixels() const;
		int getVerticalPixels() const;
		int swapBuffers();
		sf::RenderWindow *getWindow() const;
		int drawFrame(Vector world_pos, Frame frame, bool centered, Color color) const;
		
	};
}


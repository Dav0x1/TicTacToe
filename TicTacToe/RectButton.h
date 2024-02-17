#pragma once
#include <SFML/Graphics.hpp>
namespace btn {
	class RectButton
	{
	private:
		enum states { IDLE = 0, HOVER, ACTIVE, PRESSED };
		enum styles { COLOR, TEXTURE, TEXT };

		sf::RectangleShape btn;
		sf::Color clr;
		
		short state;
		short style;

		bool isPressedOut;
	public:
		//Constructors and destructors
		RectButton(unsigned short X, unsigned short Y,unsigned short Width, unsigned short Height,sf::Color Color);
		RectButton(unsigned short X, unsigned short Y,unsigned short Width, unsigned short Height,sf::Texture & Texture);
		~RectButton();
		//Functions
		void render(sf::RenderTarget &Target);
		bool update(sf::RenderWindow &Window);
	};
}

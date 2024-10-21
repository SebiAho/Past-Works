#pragma once
#include <string>
#include "../System/System.h"
#include "../System/ComponentManager.h"
#include "../3rd_party/SFML/SFML/Graphics.hpp"
#include "../Components/TransformComponent.h"
#include "../Misc/CompCast.h"

#include "Renderer.h"
#include "GraphicAssetManager.h"

namespace seb
{

	class GraphicsSystem :public System//System class that handless graphics
	{
	public:
		GraphicsSystem();
		~GraphicsSystem();

		void Intitialize(ObjectManager &_objects);
		void Update();
		void handleMessage(MessageHandler &_messages);

		/*Set window settings, if window is already open will close and reopen it*/
		void SetWindowSettings(unsigned int _width, unsigned int _height, std::string _name, sf::Color _clearColor = sf::Color::Black, _Uint32t _style = sf::Style::Default);

		/*Initialize GraphicsComponent, sets On variable to true*/
		void InitGraphicComp(GraphicsComponent* _comp, std::string _texture, sf::IntRect _area = sf::IntRect(), sf::Color _color = sf::Color::White);
		/*Initialize GraphicsComponent of object, sets On variable to true*/
		void InitGraphicComp(Object* _ob, std::string _texture, sf::IntRect _area = sf::IntRect(), sf::Color _color = sf::Color::White);

		Renderer& getRenderer(){ return renderer; };
		GraphicAssetManager& getAssets(){ return assets; };

	private:
		sf::RenderWindow window;
		Renderer renderer;
		ObjectManager *objects;
		ComponentHandler *graphic_comps;//Pointer to graphic component handler
		GraphicAssetManager assets;

		//Window settings
		sf::Color clear_color;//Window clear color
		sf::Vector2i window_size;
		std::string name;//Window name
		_Uint32t style;//Window style
		
		//Component casts
		CompCast<GraphicsComponent> gCast;//Cast Component to GraphicsComponent
		CompCast<TransformComponent> tCast;//Cast Component to TransformComponent

		void setTransform(Object *_object);

		int loop_number;
	};
}

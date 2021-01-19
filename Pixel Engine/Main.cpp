#include"Pixel.h"
#include"Application.h"

int main()
{

	PX::PixelSettings settings;
	settings.window_width = 600;
	settings.window_height = 400;
	settings.window_title = "Pixel Engine";
	settings.renderspace_width = 600;
	settings.renderspace_height = 400;

	settings.window_settings.majorVersion = 4;
	settings.window_settings.minorVersion = 0;
	settings.window_settings.attributeFlags = PX::WindowSettings::Core;
	settings.window_settings.sRgbCapable = true;
	settings.window_settings.stencilBits = 24;
	settings.window_settings.depthBits = 8;
	
	PX::PX_Game* game = new Game();

	PX::Pixel::SetupGame(game);
	PX::Pixel::Init(settings);
	PX::Pixel::Start();


	// One Atlas could accomodate various types and sizes of fonts.

	// DID NOT TAKE A FONT. IT IS CRASHING
	//Text *text = new Text("Text", 20, Math::Vector3(0,100,0), Math::Vector2(100,100), Math::Vector4(1,1,1,1));

}
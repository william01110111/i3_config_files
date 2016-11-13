
///you must put the following lines into linker options to use sfml window
/*

-lsfml-graphics
-lsfml-window
-lsfml-system

*/

#include <SFML/Graphics.hpp>

#include <string>
using std::string;

#include <memory>
using std::shared_ptr;

#include <thread>

sf::RenderWindow window;

enum Mode
{
	NO_MODE=0,
	VOL,
}
mode=NO_MODE;

string windowName="WidapPopupWindow";

void createWindow();

void showVolLevel(double level);

void sleepFor(double time);

int main(int argc, char** argv)
{
	showVolLevel(0.3);
	sleepFor(1.2);
}

void createWindow()
{
	if (window.isOpen())
		window.close();
	
	int screenX=sf::VideoMode::getDesktopMode().width;
	int screenY=sf::VideoMode::getDesktopMode().height;
	
	int dimX=screenX*0.15;
	int dimY=dimX;
	
	window.create(sf::VideoMode(dimX, dimY), windowName);
	
	window.setPosition(sf::Vector2i((screenX-dimX)/2, screenY-dimY*1.3));
}

void showVolLevel(double level)
{
	if (mode!=VOL)
	{
		createWindow();
	}
}

void sleepFor(double time)
{
	std::chrono::milliseconds timespan(int(time*1000));

	std::this_thread::sleep_for(timespan);
}


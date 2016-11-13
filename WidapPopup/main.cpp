
///vslid commands to this program
//WidapPopupRun volume 0.3
//WidapPopupRun volume -0.3 #for muted
//WidapPopupRun volume auto

///you must put the following lines into linker options to use sfml window
/*

-lsfml-graphics
-lsfml-window
-lsfml-system

*/

#include <SFML/Graphics.hpp>

#include <string>
using std::string;
using std::stod;
using std::stoi;

#include <math.h>

#include <memory>
using std::shared_ptr;

#include <iostream>
using std::cout;
using std::endl;

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

double getCurrentVolLevel();

void sleepFor(double time);

int main(int argc, char** argv)
{
	if (argc<2)
	{
		cout << "no command" << endl;
		return 1;
	}
	else
	{
		string command=argv[1];
		
		if (command=="volume")
		{
			if (argc<3)
			{
				cout << "no level" << endl;
				return 1;
			}
			else
			{
				string levelStr=argv[2];
				double level=0;
				
				if (levelStr=="auto")
				{
					level=getCurrentVolLevel();
				}
				else
				{
					level=stod(levelStr);
				}
				
				showVolLevel(level);
				sleepFor(1.2);
			}

		}
		else
		{
			cout << "invalid command" << endl;
		}
	}
}

void createWindow()
{
	if (window.isOpen())
		window.close();
	
	int screenX=sf::VideoMode::getDesktopMode().width;
	int screenY=sf::VideoMode::getDesktopMode().height;
	
	int dimX=screenX*0.15;
	int dimY=dimX;
	
	window.create(sf::VideoMode(dimX, dimY), windowName, sf::Style::None);
	
	window.setPosition(sf::Vector2i((screenX-dimX)/2, screenY-dimY*1.3));
	
	window.setActive(false);
}

void showVolLevel(double level)
{
	bool muted=(level<=0);
	level=fabs(level);
	
	if (mode!=VOL)
	{
		createWindow();
	}
	
	const sf::Color backgroundC(16, 16, 16, 255);
	const sf::Color speakerC(136, 136, 136, 255);
	const sf::Color sliderBkndC(speakerC);
	const sf::Color sliderC=(muted?sliderBkndC:sf::Color(37, 141, 249, 255));
	
	double w=window.getSize().x;
	double h=window.getSize().y;
	
	sf::RectangleShape speakerS1;
	speakerS1.setPosition(sf::Vector2f(0.2*w, 0.3*h));
	speakerS1.setSize(sf::Vector2f(0.2*w, 0.2*h));
	speakerS1.setFillColor(speakerC);
	
	sf::ConvexShape speakerS2(4);
	speakerS2.setPoint(0, sf::Vector2f(0.4*w, 0.3*h));
	speakerS2.setPoint(1, sf::Vector2f(0.6*w, 0.1*h));
	speakerS2.setPoint(2, sf::Vector2f(0.6*w, 0.7*h));
	speakerS2.setPoint(3, sf::Vector2f(0.4*w, 0.5*h));
	speakerS2.setFillColor(speakerC);
	
	sf::RectangleShape sliderS1;
	sliderS1.setPosition(sf::Vector2f(0.1*w, 0.85*h));
	sliderS1.setSize(sf::Vector2f(0.8*w*level, 0.1*h));
	sliderS1.setFillColor(sliderC);
	
	window.clear(backgroundC);
	window.draw(speakerS1);
	window.draw(speakerS2);
	window.draw(sliderS1);
	
	window.display();
}

double getCurrentVolLevel()
{
	return 0.5;
}

void sleepFor(double time)
{
	std::chrono::milliseconds timespan(int(time*1000));

	std::this_thread::sleep_for(timespan);
}



///valid commands to this program

//WidapPopupRun volume
//WidapPopupRun brightness [0-100]
//WidapPopupRun kb-brightness [0-100]

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

const double PI=3.14159265358979323846;

string windowName="WidapPopupWindow";

void createWindow();

void showVolLevel(double level);
void showBrightLevel(double level);
void showKbBrightLevel(double level);
void showError();

double getCurrentVolLevel();

string getOutputFromCmd(string cmd);

bool substringMatches(const string& in, int pos, const string& subStr);
int searchInString(const string& in, int startPos, const string& pattern);

void sleepFor(double time);

int main(int argc, char** argv)
{
	string command;
	if (argc>=2)
	{
		command=argv[1];
	}
	
	if (command=="volume")
	{
		double level;
		
		level=getCurrentVolLevel();
		
		showVolLevel(level);
		sleepFor(0.8);
	}
	else if (command=="brightness")
	{
		if (argc>=3)
		{
			showBrightLevel(stoi(argv[2])/100.0);
			sleepFor(0.8);
		}
		else
		{
			cout << "no brightness level given" << endl;
		}
	}
	else if (command=="kb-brightness")
	{
		if (argc>=3)
		{
			showKbBrightLevel(stoi(argv[2])/100.0);
			sleepFor(0.8);
		}
		else
		{
			cout << "no brightness level given" << endl;
		}
	}
	else
	{
		cout << "invalid command" << endl;
		cout << "\tWidapPopupRun volume" << endl;
		cout << "\tWidapPopupRun brightness [0-100]" << endl;
		cout << "\tWidapPopupRun kb-brightness [0-100]" << endl;
		showError();
		sleepFor(0.8);
	}
}

void createWindow()
{
	if (window.isOpen())
		window.close();
	
	int screenX=sf::VideoMode::getDesktopMode().width;
	//int screenY=sf::VideoMode::getDesktopMode().height;
	
	int dimX=screenX*0.14;
	int dimY=dimX;
	
	window.create(sf::VideoMode(dimX, dimY), windowName, sf::Style::None);
	
	//window.setPosition(sf::Vector2i((screenX-dimX)/2, screenY-dimY*1.3));
	
	//window.setSize(sf::Vector2u(dimX, dimY));
	
	//window.setView(sf::View(sf::FloatRect(0, 0, dimX, dimY)));
}

void showError()
{
	if (!window.isOpen())
	{
		createWindow();
	}
	
	window.clear(sf::Color(255, 0, 0));
	
	window.display();
}

void showVolLevel(double level)
{
	bool muted=(level<=0);
	level=fabs(level);
	
	if (!window.isOpen())
	{
		createWindow();
	}
	
	const sf::Color backgroundC(16, 16, 16);
	const sf::Color speakerC(136, 136, 136);
	const sf::Color sliderBkndC(38, 38, 38);
	const sf::Color sliderC=(muted?speakerC:sf::Color(37, 141, 249));
	const sf::Color muteXC(237, 60, 42);
	const sf::Color soundWaveC=sliderC;
	
	double w=window.getSize().x;
	double h=window.getSize().y;
	
	window.clear(backgroundC);
	
	sf::RectangleShape speakerS1;
	speakerS1.setPosition(sf::Vector2f(0.2*w, 0.3*h));
	speakerS1.setSize(sf::Vector2f(0.1*w, 0.2*h));
	speakerS1.setFillColor(speakerC);
	window.draw(speakerS1);
	
	sf::ConvexShape speakerS2(4);
	speakerS2.setPoint(0, sf::Vector2f(0.3*w, 0.3*h));
	speakerS2.setPoint(1, sf::Vector2f(0.5*w, 0.1*h));
	speakerS2.setPoint(2, sf::Vector2f(0.5*w, 0.7*h));
	speakerS2.setPoint(3, sf::Vector2f(0.3*w, 0.5*h));
	speakerS2.setFillColor(speakerC);
	window.draw(speakerS2);
	
	sf::RectangleShape sliderBkndS1;
	sliderBkndS1.setPosition(sf::Vector2f(0.1*w, 0.85*h));
	sliderBkndS1.setSize(sf::Vector2f(0.8*w, 0.05*h));
	sliderBkndS1.setFillColor(sliderBkndC);
	window.draw(sliderBkndS1);
	
	sf::RectangleShape sliderS1;
	sliderS1.setPosition(sf::Vector2f(0.1*w, 0.85*h));
	sliderS1.setSize(sf::Vector2f(0.8*w*level, 0.05*h));
	sliderS1.setFillColor(sliderC);
	window.draw(sliderS1);
	
	if (muted)
	{
		sf::CircleShape muteXS2;
		muteXS2.setRadius(0.15*h);
		muteXS2.setOrigin(sf::Vector2f(muteXS2.getRadius(), muteXS2.getRadius()));
		muteXS2.setPosition(sf::Vector2f(0.55*w, 0.4*h));
		muteXS2.setFillColor(sf::Color(0, 0, 0, 0));
		muteXS2.setOutlineThickness(0.05*h);
		muteXS2.setOutlineColor(muteXC);
		window.draw(muteXS2);
		
		sf::RectangleShape muteXS1;
		muteXS1.setSize(sf::Vector2f(0.3*w, 0.05*h));
		muteXS1.setOrigin(sf::Vector2f(muteXS1.getSize().x/2.0, muteXS1.getSize().y/2.0));
		muteXS1.setRotation(45);
		muteXS1.setPosition(sf::Vector2f(0.55*w, 0.4*h));
		muteXS1.setFillColor(muteXC);
		window.draw(muteXS1);
	}
	else
	{
		const int res=16;
		const double rad=0.1*w;
		const double ang=100;
		
		for (int i=0; i<res; i++)
		{
			for (int j=1; j<level*3.5+0.5; j++)
			{
				sf::RectangleShape soundWaveS;
				const int dir=(i+0.5)*ang/res+360-ang/2;
				const int dst=rad*j;
				soundWaveS.setSize(sf::Vector2f((PI*j*rad*2*ang/360)/res+0.01*h, 0.02*h));
				soundWaveS.setOrigin(sf::Vector2f(soundWaveS.getSize().x/2.0, soundWaveS.getSize().y/2.0));
				soundWaveS.setRotation(dir+90);
				soundWaveS.setPosition(sf::Vector2f(cos(dir*PI/180)*dst+w*0.5, sin(dir*PI/180)*dst+h*0.4));
				soundWaveS.setFillColor(soundWaveC);
				window.draw(soundWaveS);
			}
		}
	}
	
	window.display();
}

void showBrightLevel(double level)
{
	level=fabs(level);
	
	if (!window.isOpen())
	{
		createWindow();
	}
	
	const sf::Color backgroundC(16, 16, 16);
	//const sf::Color sunRayC(255*(0.5+level*0.5), 255*(0.5+level*0.5), 255*(0.5+level*0.5));
	const sf::Color sunRayC(221, 221, 221);
	const sf::Color sliderBkndC(38, 38, 38);
	const sf::Color sliderC=(sf::Color(37, 141, 249));
	const sf::Color muteXC(237, 60, 42);
	const sf::Color sunBodyC=sunRayC;
	
	double w=window.getSize().x;
	double h=window.getSize().y;
	
	window.clear(backgroundC);
	
	sf::CircleShape sunBodyS;
	sunBodyS.setRadius(0.15*h);
	sunBodyS.setOrigin(sf::Vector2f(sunBodyS.getRadius(), sunBodyS.getRadius()));
	sunBodyS.setPosition(sf::Vector2f(0.5*w, 0.45*h));
	sunBodyS.setFillColor(sunBodyC);
	window.draw(sunBodyS);
	
	for (int i=0; i<6; i++)
	{
		sf::RectangleShape rayS;
		const int dir=i/6.0*360;
		const int dst=level*w*0.2+w*0.01;
		rayS.setSize(sf::Vector2f(dst, 0.04*h));
		rayS.setOrigin(sf::Vector2f(0, rayS.getSize().y/2.0));
		rayS.setRotation(dir);
		rayS.setPosition(sf::Vector2f(cos(dir*PI/180)*w*0.2+w*0.5, sin(dir*PI/180)*h*0.2+h*0.45));
		rayS.setFillColor(sunRayC);
		window.draw(rayS);
	}
	
	sf::RectangleShape sliderBkndS1;
	sliderBkndS1.setPosition(sf::Vector2f(0.1*w, 0.85*h));
	sliderBkndS1.setSize(sf::Vector2f(0.8*w, 0.05*h));
	sliderBkndS1.setFillColor(sliderBkndC);
	window.draw(sliderBkndS1);
	
	sf::RectangleShape sliderS1;
	sliderS1.setPosition(sf::Vector2f(0.1*w, 0.85*h));
	sliderS1.setSize(sf::Vector2f(0.8*w*level, 0.05*h));
	sliderS1.setFillColor(sliderC);
	window.draw(sliderS1);
	
	window.display();
}

void showKbBrightLevel(double level)
{
	level=fabs(level);
	
	if (!window.isOpen())
	{
		createWindow();
	}
	
	const sf::Color backgroundC(16, 16, 16);
	//const sf::Color sunRayC(255*(0.5+level*0.5), 255*(0.5+level*0.5), 255*(0.5+level*0.5));
	const sf::Color sunRayC(level*128+127, level*128+127, level*128+127);
	const sf::Color sliderBkndC(38, 38, 38);
	const sf::Color sliderC=(sf::Color(37, 141, 249));
	//const sf::Color muteXC(237, 60, 42);
	const sf::Color keyC=sunRayC;
	
	double w=window.getSize().x;
	double h=window.getSize().y;
	
	window.clear(backgroundC);
	
	/*
	sf::CircleShape sunBodyS;
	sunBodyS.setRadius(0.15*h);
	sunBodyS.setOrigin(sf::Vector2f(sunBodyS.getRadius(), sunBodyS.getRadius()));
	sunBodyS.setPosition(sf::Vector2f(0.5*w, 0.45*h));
	sunBodyS.setFillColor(sunBodyC);
	window.draw(sunBodyS);
	*/
	
	sf::ConvexShape keyS(4);
	keyS.setPoint(0, sf::Vector2f(0.15*w, 0.7*h));
	keyS.setPoint(1, sf::Vector2f(0.85*w, 0.7*h));
	keyS.setPoint(2, sf::Vector2f(0.7*w, 0.5*h));
	keyS.setPoint(3, sf::Vector2f(0.3*w, 0.5*h));
	keyS.setFillColor(sliderBkndC);
	keyS.setOutlineColor(keyC);
	keyS.setOutlineThickness(h*0.02);
	window.draw(keyS);
	
	/*
	sf::RectangleShape blockerS;
	blockerS.setPosition(sf::Vector2f(0.2*w, 0.455*h));
	blockerS.setSize(sf::Vector2f(0.6*w, 0.04*h));
	blockerS.setFillColor(backgroundC);
	window.draw(blockerS);
	*/
	
	sf::ConvexShape GlyphS(5);
	GlyphS.setPoint(0, sf::Vector2f(0.4*w, 0.67*h));
	GlyphS.setPoint(1, sf::Vector2f(0.5*w, 0.55*h));
	GlyphS.setPoint(2, sf::Vector2f(0.6*w, 0.67*h));
	GlyphS.setPoint(3, sf::Vector2f(0.55*w, 0.61*h));
	GlyphS.setPoint(4, sf::Vector2f(0.45*w, 0.61*h));
	GlyphS.setFillColor(sf::Color::Transparent);
	GlyphS.setOutlineColor(keyC);
	GlyphS.setOutlineThickness(h*0.02);
	window.draw(GlyphS);
	
	for (int i=0; i<4; i++)
	{
		sf::RectangleShape rayS;
		const int dir=i/12.0*360-90-45;
		const int dst=level*w*0.2;
		rayS.setSize(sf::Vector2f(dst, 0.04*h));
		rayS.setOrigin(sf::Vector2f(0, rayS.getSize().y/2.0));
		rayS.setRotation(dir);
		rayS.setPosition(sf::Vector2f(cos(dir*PI/180)*w*0.4+w*0.5, sin(dir*PI/180)*h*0.4+h*0.7));
		rayS.setFillColor(sunRayC);
		window.draw(rayS);
	}
	
	sf::RectangleShape sliderBkndS1;
	sliderBkndS1.setPosition(sf::Vector2f(0.1*w, 0.85*h));
	sliderBkndS1.setSize(sf::Vector2f(0.8*w, 0.05*h));
	sliderBkndS1.setFillColor(sliderBkndC);
	window.draw(sliderBkndS1);
	
	sf::RectangleShape sliderS1;
	sliderS1.setPosition(sf::Vector2f(0.1*w, 0.85*h));
	sliderS1.setSize(sf::Vector2f(0.8*w*level, 0.05*h));
	sliderS1.setFillColor(sliderC);
	window.draw(sliderS1);
	
	window.display();
}

double getCurrentVolLevel()
{
	/*
	string amixerOut=getOutputFromCmd("amixer sget Master");
	
	int end1=searchInString(amixerOut, 0, "%]");
	
	if (end1<0)
		return 0;
	
	int start1=end1-1;
	
	while (start1>=0 && amixerOut[start1]!='[')
	{
		start1--;
	}
	
	start1++;
	
	int percent=stoi(amixerOut.substr(start1, end1-start1));
	
	int start2=end1;
	
	while (start2<int(amixerOut.size()) && amixerOut[start2]!='[')
	{
		start2++;
	}
	
	start2++;
	
	int end2=start2;
	
	while (end2<int(amixerOut.size()) && amixerOut[end2]!=']')
	{
		end2++;
	}
	
	cout << endl << start2 << ", " << end2 << endl;
	
	string onOff=amixerOut.substr(start2, end2-start2);
	
	bool muted=(onOff=="off");
	*/
	
	bool muted=(getOutputFromCmd("pamixer --get-mute")=="true\n");
	int percent=stoi(getOutputFromCmd("pamixer --get-volume"));
	
	return (muted?-1:1)*percent/100.0;
}

string getOutputFromCmd(string cmd)
{
	const int bufferSize=4096;
    char buffer[bufferSize];
    std::string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed in getOutputFromCmd");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, bufferSize, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

bool substringMatches(const string& in, int pos, const string& subStr)
{
	//check if the substring extends past the string size
	if (in.size()<pos+subStr.size())
		return false;
	
	for (unsigned i=0; i<subStr.size(); ++i)
	{
		if (in[i+pos]!=subStr[i])
			return false;
	}
	
	return true;
}

int searchInString(const string& in, int startPos, const string& pattern)
{
	for (unsigned i=startPos; i<in.size(); i++)
	{
		if (substringMatches(in, i, pattern))
			return i;
	}
	
	return -1;
}

void sleepFor(double time)
{
	std::chrono::milliseconds timespan(int(time*1000));

	std::this_thread::sleep_for(timespan);
}


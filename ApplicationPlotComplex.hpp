#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include"ortogonals.hpp"
#include"ortogonalper.hpp"
#include<functional>
#include<cmath>

using namespace sf;
using namespace std;

string getWithLines( const string & text );

typedef Vector2< long double > Vector2l;

Vector2l toVector( const lcomplex & z );
Vector2l toVector( const lortogonal & z );

class ApplicationPlotComplex{
public:
	
	ApplicationPlotComplex();
	
	void initVars();
	void zoom( float scale , RenderWindow & window );
	void resized( RenderWindow & window );
	void events();
	void update();
	void render();
	void run();
	void loadShaderFromFile( const string & file_name );
	void loadShaderFromMemory( const string & text );
	
	const string & getTextShader() const;

protected:
	
	string createShaderText( const string & text );
	
	string textShader;
	RenderWindow window;
	Vector2l windowPosition;
	Vector2l windowSize;
	RectangleShape rectangle;
	Shader shader;
	Font font;
	Text * text;
	Text * text2;
	Text * text3;
	Text * text4;
	long double left;
	long double bottom;
	long double width;
	long double height;
	bool updateShader;
	int index;
	float velAngle;
	long double ration;
	lcomplex z;
	unsigned int n;
	
	Clock clock;
	Clock deltaClock;
	long double time;
	long double deltaTime;
	long double vel;
	int ortogonal;
	bool module;
	bool colored;
	bool fullscreen;
	bool isTextData;
	bool isTextIterations;
	float ortoAngle;
	float ortoAngle2;
	Vector2u prevWindowSize;

};
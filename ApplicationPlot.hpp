#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include"ortogonals.hpp"
#include"ortogonalper.hpp"
#include<functional>
#include<cmath>

using namespace sf;
using namespace std;

typedef Vector2< long double > Vector2l;

class ApplicationPlot{
public:
	
	struct RealFunction{
		
		bool right;
		function< long double( long double ) > func;
		bool is_print_text;
		Color color;

	};

	struct ComplexFunction{
		
		function< lcomplex( lcomplex ) > func;
		bool is_print_text;
		Color color;
		long double angle;

	};

	struct VectorFunction{
		
		function< Vector2l( long double ) > func;
		bool is_print_text;
		Color color;

	};

	ApplicationPlot();

	void initVars();
	void events();
	void update();
	void render();
	void run();

	void add_func( function< long double( long double ) > f , const Color & color = Color::White  , bool right = true , bool is_print = true );
	void add_bi_func( function< long double( long double ) > f  , const Color & color = Color::White  , bool is_print = true );
	void add_complex_func( function< lcomplex( lcomplex ) > , long double angle = 0.l , const Color & color = Color::White  , bool is_print = true );
	void add_complex_func( function< lcomplex( lcomplex ) > , const Color & color = Color::White  , bool is_print = true );
	void add_complex_func( function< lcomplex( long double ) > , const Color & color = Color::White , bool right = true , bool is_print = true );
	void add_bi_complex_func( function< lcomplex( lcomplex ) > , long double angle = 0.l , const Color & color = Color::White  , bool is_print = true );
	void add_bi_complex_func( function< lcomplex( lcomplex ) > , const Color & color = Color::White  , bool is_print = true );
	void add_bi_complex_func( function< lcomplex( long double ) > , const Color & color = Color::White , bool is_print = true );
	void add_vector_func( function< Vector2l( long double ) > , const Color & color = Color::White , bool is_print = true );
	
	void set_time( long double time );
	void set_velocity_time( long double vel );
	void set_acceleration_time( long double acc );
	void set_updates_for_second( unsigned int N );

protected:
	
	void zoom( float scale , RenderWindow & window );
	void resized( RenderWindow & window );
	void draw_func( const function< long double( long double ) > & f , const Color & color , bool is_right , bool is_print );
	void draw_complex_func( const function< lcomplex( lcomplex ) > & f , long double angle , const Color & color , bool is_print );
	void draw_vector_func( const function< Vector2l( long double ) > & f , const Color & color , bool is_print );

	vector< RealFunction > real_functions;
	vector< ComplexFunction > complex_functions;
	vector< VectorFunction > vector_functions;
	RenderWindow window;
	Window miniwindow;
	Clock clock;
	Clock deltaClock;
	Vector2l windowPosition;
	Vector2l windowSize;
	Font font;
	Text * text;
	Text * text2;
	Text * text3;
	lcomplex z;
	unsigned int n;
	unsigned int updatesForSecond;
	long double velTime;
	long double accTime;
	float velAngle;
	long double left_;
	long double bottom;
	long double width;
	long double height;
	long double timer;
	bool updateGraphics;
	int index;
	long double deltaTime;
	long double vel;
	long double ration;
	bool ortogonal;
	bool module;
	bool colored;
	bool fullscreen;
	bool isTextData;
	bool isTextIterations;
	float ortoAngle;
	Vector2u prevWindowSize;
	vector< Vector2l > math_points;
	vector< CircleShape > points;
	vector< Text > numbers;
	VertexArray lines;
	VertexArray coords;
	Vector2l staticSize;
	int countNumbers;
	
};
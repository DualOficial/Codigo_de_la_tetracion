#include"ApplicationPlotComplex.hpp"
#include<fstream>
#include<sstream>

typedef Vector2< long double > Vector2l;

Vector2l toVector( const lcomplex & z ){
	
	return Vector2l( z.real() , z.imag() );
	
}

Vector2l toVector( const lortogonal & z ){
	
	return Vector2l( z.real() , z.imag() );
	
}

string getWithLines( const string & text ){
	
	istringstream ss( text );

	string result;
	string line;
	unsigned int n = 0;

	while( getline( ss , line ) ){
		
		result += to_string( n ) + " : " + line + "\n";
		n++;

	}
	
	return result;
}

string replaceText( const string & text , const string & wanted , const string & replace ){
	
	string result;
	int n = 0;

	for( int i = 0; i < text.size(); i++ ){
		
		if( wanted[ n ] == text[ i ] ){
			
			n++;

		}
		else{
			
			n = 0;

		}

		result.push_back( text[ i ] );

		if( n == wanted.size() ){
			
			result = result.substr( 0 , result.size() - wanted.size() );
			result += replace;
			n = 0;

		}

	}

	return result;
}

string ApplicationPlotComplex::createShaderText( const string & text ){
	
	string default_text;
	ifstream file( "ortogonal_shader.frag" );
	ostringstream ss;

	ss<<file.rdbuf();
	default_text = ss.str();

	file.close();
	
	textShader = replaceText( text , "#ADD ORTOGONAL SHADER" , default_text );

	return textShader;
}

ApplicationPlotComplex::ApplicationPlotComplex(){
	
	initVars();

	window.create( VideoMode( Vector2u( 700 , 700 ) ) , "ApplicationPlotComplex - Permutation Calculator" );

	ration = ( long double )( window.getSize().x ) / ( long double )( window.getSize().y );
	left = -1.l * ration;
	bottom = -1.l;
	width = 2.l * ration;
	height = 2.l;
	windowSize = Vector2l( window.getSize() );
	textShader = string();

	rectangle.setSize( Vector2f( windowSize ) );
	
	font.openFromFile( "tuffy.ttf" );

	text = new Text( font );
	text2 = new Text( font );
	text3 = new Text( font );
	text4 = new Text( font );

	text->setString( "z:\nr-range:\ni-range:" );
	text->setFillColor( Color::White );
	text->setCharacterSize( 30 );
	text->setOutlineThickness( 5 );
	text->setOutlineColor( Color::Black );
	text->setPosition( Vector2f( 100.f , 450.f - text->getGlobalBounds().size.x / 2.f ) );
	text2->setString( "iteration:" );
	text2->setCharacterSize( 30 );
	text2->setPosition( Vector2f( 100.f , VideoMode::getDesktopMode().size.y - 100.f - text->getGlobalBounds().size.x / 2.f ) );
	text2->setOutlineThickness( 3 );
	text2->setFillColor( Color::Black );
	text2->setOutlineColor( Color::White );
	text3->setString( "iteration:" );
	text3->setCharacterSize( 30 );
	text3->setPosition( Vector2f( 100.f , VideoMode::getDesktopMode().size.y - 50.f - text->getGlobalBounds().size.x / 2.f ) );
	text3->setOutlineThickness( 3 );
	text3->setFillColor( Color::Black );
	text3->setOutlineColor( Color::White );
	
	text4->setString( "" );
	text4->setCharacterSize( 30 );
	text4->setOutlineThickness( 3 );
	text4->setFillColor( Color::White );
	text4->setOutlineColor( Color::Black );
	
	clock.restart();
	deltaClock.restart();

}

void ApplicationPlotComplex::loadShaderFromFile( const string & file_name ){
	
	string text;
	ifstream file( file_name );
	ostringstream ss;

	ss<<file.rdbuf();
	text = ss.str();

	file.close();

	loadShaderFromMemory( text );
}

void ApplicationPlotComplex::loadShaderFromMemory( const string & text ){
	
	shader.loadFromMemory( createShaderText( text ) , Shader::Type::Fragment );

}

const string & ApplicationPlotComplex::getTextShader() const{
	
	return textShader;

}

void ApplicationPlotComplex::initVars(){
	
	updateShader = true;
	index = 0;
	velAngle = 1.l;
	z = 0.l;
	n = 0;
	time = 0.l;
	deltaTime = 0.l;
	vel = 1.l;
	ortogonal = 0;
	module = false;
	colored = true;
	fullscreen = false;
	isTextData = true;
	isTextIterations = true;
	ortoAngle = 0.l;
	ortoAngle2 = 0.l;
	prevWindowSize = Vector2u();

}

void ApplicationPlotComplex::zoom( float scale , RenderWindow & window ){
	
	Vector2f postion( Mouse::getPosition( window ) );
	
	long double u = postion.x / windowSize.x * width + left;
	long double v = ( windowSize.y - postion.y ) / windowSize.y * height + bottom;
	
	long double factor = 1.l / scale;
	long double b = factor;
	long double a = u * ( 1.l - b );
	long double d = factor;
	long double c = v * ( 1.l - d );
	
	left = a + left * b;
	bottom = c + bottom * d;
	width *= factor;
	height *= factor;
	
	updateShader = true;
	
}

void ApplicationPlotComplex::resized( RenderWindow & window ){
	
	Vector2l newWindowPosition( window.getPosition() );
	Vector2l newWindowSize( window.getSize().x , window.getSize().y );
	long double differenceX = windowPosition.x - newWindowPosition.x;
	long double differenceY = newWindowPosition.y + newWindowSize.y - ( windowPosition.y + windowSize.y );
	
	left -= differenceX / windowSize.x * width;
	bottom -= differenceY / windowSize.y * height;
	width *= newWindowSize.x / windowSize.x;
	height *= newWindowSize.y / windowSize.y;
	
	updateShader = true;
	
}

void ApplicationPlotComplex::events(){
	
	time = clock.getElapsedTime().asSeconds();
	deltaTime = deltaClock.restart().asSeconds();
	
	while( const optional event = window.pollEvent() ){
		
		if( event->is< Event::Closed >() ){
			
			window.close();

		}
		
		if( const auto info = event->getIf< Event::MouseWheelScrolled >() ){
			
			if( window.hasFocus() ){
				
				zoom( 1.l + info->delta * 0.1l , window );

			}

		}

		if( const auto key = event->getIf< Event::KeyPressed >() ){
			
			switch( key->scancode ){
				
				case Keyboard::Scancode::R:{
					
					ortoAngle = 0.l;
					updateShader = true;

					break;
				}

				case Keyboard::Scancode::G:{
					
					ortoAngle2 = 0.l;
					updateShader = true;

					break;
				}
				
				case Keyboard::Scancode::H:{
					
					if( ortogonal == 2 ){
						
						ortogonal = 0;
						
					}
					else{
						
						ortogonal++;
						
					}
					
					updateShader = true;

					break;
				}
				
				case Keyboard::Scancode::B:{
					
					index--;
					updateShader = true;
					
					break;
				}
				
				case Keyboard::Scancode::N:{
					
					index++;
					updateShader = true;
					
					break;
				}
				
				case Keyboard::Scancode::I:{
					
					module = !module;
					updateShader = true;
					
					break;
				}
				
				case Keyboard::Scancode::K:{
					
					colored = !colored;
					updateShader = true;
					
					break;
				}
				
				case Keyboard::Scancode::T:{
					
					ration = ( long double )( window.getSize().x ) / ( long double )( window.getSize().y );
					
					left = -1.l * ration;
					bottom = -1.l;
					width = 2.l * ration;
					height = 2.l;
					
					updateShader = true;
					
					break;
				}
				
				case Keyboard::Scancode::Escape:{
					
					window.close();
					
					break;
				}
				
				case Keyboard::Scancode::O:{
					
					fullscreen = !fullscreen;
					
					if( fullscreen ){
						
						prevWindowSize = window.getSize();
						window.close();
						window.create( VideoMode::getDesktopMode() , "Fractal de Collatz-Uribe" , State::Fullscreen );
						rectangle.setSize( Vector2f( window.getSize() ) );
						
					}
					else{
						
						window.close();
						window.create( VideoMode( Vector2u( prevWindowSize.x , prevWindowSize.y ) ) , "Fractal de Collatz-Uribe" );
						
					}
					
					break;
				}
				
				case Keyboard::Scancode::P:{
					
					isTextData = !isTextData;
					
					break;
				}
				
				case Keyboard::Scancode::L:{
					
					isTextIterations = !isTextIterations;
					
					break;
				}
				
			}

		}

	}
	
}

void ApplicationPlotComplex::update(){
	
	Vector2l newWindowSize = Vector2l( window.getSize() );
	
	if( windowSize != newWindowSize ){
		
		resized( window );
		
	}
	
	windowSize = newWindowSize;
	windowPosition = Vector2l( window.getPosition() );
	
	if( window.hasFocus() ){
		
		Vector2l position( Mouse::getPosition( window ) );
		long double u = position.x / windowSize.x * width + left;
		long double v = ( windowSize.y - position.y ) / windowSize.y * height + bottom;
		
		window.setTitle( "ApplicationPlotComplex : " + to_string( u ) + " + " + to_string( v ) + "i"
		+                " , r-range: " + to_string( left ) + " to " + to_string( left + width )
		+                " , i-range: " + to_string( bottom ) + "i to " + to_string( bottom + height ) + "i"
		+                " , orto-angle: " + to_string( ortoAngle )
		+                " , index: " + to_string( index ) );
		
		if( fullscreen ){
			
			text->setString( "z: " + to_string( u ) + " + " + to_string( v ) + "i\n"
			+               "r-range: " + to_string( left ) + " to " + to_string( left + width ) + "\n"
			+               "i-range: " + to_string( bottom ) + "i to " + to_string( bottom + height ) + "i");
			text2->setString( "orto-angle: " + to_string( ortoAngle ) );
			text3->setString( "index: " + to_string( index ) );
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Z ) ){
			
			ortoAngle -= deltaTime * velAngle * constants::pi< long double >();
			
			updateShader = true;
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::X ) ){
			
			ortoAngle += deltaTime * velAngle * constants::pi< long double >();
			
			updateShader = true;
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::C ) ){
			
			ortoAngle2 -= deltaTime * velAngle * constants::pi< long double >();
			
			updateShader = true;
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::V ) ){
			
			ortoAngle2 += deltaTime * velAngle * constants::pi< long double >();
			
			updateShader = true;
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::D ) ){
			
			zoom( 1.l + 1.01l * deltaTime , window );
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::A ) ){
			
			zoom( 1.l - 1.01l * deltaTime , window );
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Right ) || Keyboard::isKeyPressed( Keyboard::Scancode::E ) ){
			
			left += width * deltaTime * vel;
			updateShader = true;
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Left ) || Keyboard::isKeyPressed( Keyboard::Scancode::Q ) ){
			
			left -= width * deltaTime * vel;
			updateShader = true;
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Down ) || Keyboard::isKeyPressed( Keyboard::Scancode::S ) ){
			
			bottom -= height * deltaTime * vel;
			updateShader = true;
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Up ) || Keyboard::isKeyPressed( Keyboard::Scancode::W ) ){
			
			bottom += height * deltaTime * vel;
			updateShader = true;
			
		}
		
	}
	
	if( updateShader ){
		
		shader.setUniform( "left" , float( left ) );
		shader.setUniform( "bottom" , float( bottom ) );
		shader.setUniform( "width" , float( width ) );
		shader.setUniform( "height" , float( height ) );
		shader.setUniform( "resolution" , Vector2f( windowSize ) );
		shader.setUniform( "index" , ortoAngle );
		shader.setUniform( "index2" , ortoAngle2 );
		shader.setUniform( "colored" , colored );
		shader.setUniform( "mod" , module );
		shader.setUniform( "ortogonal" , ortogonal );
		shader.setUniform( "value" , index );
		
	}
	
}

void ApplicationPlotComplex::render(){
	
	window.clear();
	window.draw( rectangle , & shader );
	
	if( fullscreen ){
		
		if( isTextData ){
			
			window.draw( * text );
			window.draw( * text2 );
			
		}
		
		if( isTextIterations ){
			
			window.draw( * text3 );
			
		}
		
	}
	
	window.display();
	
}


void ApplicationPlotComplex::run(){
	
	while( window.isOpen() ){
		
		events();
		update();
		render();
		
	}

}

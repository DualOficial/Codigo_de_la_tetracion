#include"ApplicationPlot.hpp"

ApplicationPlot::ApplicationPlot() : lines( PrimitiveType::Lines , 4 ) , coords( PrimitiveType::Lines ){
	
	initVars();
	
	window.create( VideoMode( Vector2u( 700 , 700 ) ) , "ApplicationPlot" );
	
	staticSize = Vector2l( window.getSize() );

	velAngle = 1.l;
	ration = ( long double )( window.getSize().x ) / ( long double )( window.getSize().y );

	left_ = -8.l * ration;
	bottom = -8.l;
	width = 16.l * ration;
	height = 16.l;
	windowSize = Vector2l( window.getSize() );
	
	text = new Text( font , "" , 32 );
	text2 = new Text( font , "" , 32 );
	text3 = new Text( font , "" , 32 );

	font.openFromFile( "tuffy.ttf" );
	text->setString( "z:\nr-range:\ni-range:" );
	text->setFillColor( Color::White );
	text->setCharacterSize( 30 );
	text->setOutlineThickness( 5 );
	text->setOutlineColor( Color::Black );
	text->setPosition( Vector2f( 100.f , 450.f - text->getGlobalBounds().size.x / 2.f ) );
	text2->setString( "iteration:" );
	text2->setFillColor( Color::White );
	text2->setCharacterSize( 30 );
	text2->setPosition( Vector2f( 100.f , VideoMode::getDesktopMode().size.y - 100.f - text->getGlobalBounds().size.x / 2.f ) );
	text2->setOutlineThickness( 3 );
	text2->setFillColor( Color::Black );
	text2->setOutlineColor( Color::White );
	text3->setString( "iteration:" );
	text3->setFillColor( Color::White );
	text3->setCharacterSize( 30 );
	text3->setPosition( Vector2f( 100.f , VideoMode::getDesktopMode().size.y - 50.f - text->getGlobalBounds().size.x / 2.f ) );
	text3->setOutlineThickness( 3 );
	text3->setFillColor( Color::Black );
	text3->setOutlineColor( Color::White );
	
	clock.restart();
	deltaClock.restart();

}

void ApplicationPlot::initVars(){
	
	timer = 0.l;
	index = 0;
	vel = 1.l;
	updateGraphics = true;
	ortogonal = false;
	module = false;
	colored = true;
	fullscreen = false;
	isTextData = true;
	isTextIterations = true;
	ortoAngle = 0.l;
	countNumbers = 0;
	velTime = 1.l;
	accTime = 0.l;
	updatesForSecond = 1000;
	z = 0.l;
	n = 0;

}

void ApplicationPlot::set_acceleration_time( long double acc ){
	
	accTime = acc;

}

void ApplicationPlot::events(){
	
	while( const std::optional event = window.pollEvent() ){
		
		if( event->is< sf::Event::Closed >() ){
			
			window.close();
			
		}
		
		if( const auto info = event->getIf< sf::Event::MouseWheelScrolled >() ){
			
			if( window.hasFocus() ){
				
				zoom( 1.l + info->delta * 0.1l , window );
				
			}
			
		}
		
		if( const auto key = event->getIf< sf::Event::KeyPressed >() ){
			
			if( key->scancode == Keyboard::Scancode::R ){
				
				ortoAngle = 0.l;
				updateGraphics = true;
				
			}
			
			if( key->scancode == Keyboard::Scancode::H ){
				
				ortogonal = !ortogonal;
				updateGraphics = true;
				
			}
			
			if( key->scancode == Keyboard::Scancode::C ){
				
				index--;
				updateGraphics = true;
				
			}
			
			if( key->scancode == Keyboard::Scancode::V ){
				
				index++;
				updateGraphics = true;
				
			}
			
			if( key->scancode == Keyboard::Scancode::I ){
				
				module = !module;
				updateGraphics = true;
				
			}
			
			if( key->scancode == Keyboard::Scancode::K ){
				
				colored = !colored;
				updateGraphics = true;
				
			}
			
			if( key->scancode == Keyboard::Scancode::T ){
				
				ration = ( long double )( window.getSize().x ) / ( long double )( window.getSize().y );
				
				left_ = -1.l * ration;
				bottom = -1.l;
				width = 2.l * ration;
				height = 2.l;
				
				updateGraphics = true;
				
			}
			
			if( key->scancode == Keyboard::Scancode::Escape ){
				
				window.close();
				
			}
			
			if( key->scancode == Keyboard::Scancode::O ){
				
				fullscreen = !fullscreen;
				
				if( fullscreen ){
					
					prevWindowSize = window.getSize();
					window.close();
					window.create( VideoMode::getDesktopMode() , "Fractal de Collatz-Uribe" , State::Fullscreen );
					staticSize = Vector2l( window.getSize() );
					
				}
				else{
					
					window.close();
					window.create( VideoMode( Vector2u( prevWindowSize.x , prevWindowSize.y ) ) , "Fractal de Collatz-Uribe" );
					staticSize = Vector2l( prevWindowSize );
					
				}
				
			}
			
			if( key->scancode == Keyboard::Scancode::P ){
				
				isTextData = !isTextData;
				
			}
			
			if( key->scancode == Keyboard::Scancode::L ){
				
				isTextIterations = !isTextIterations;
				
			}
			
		}
		
	}
	
}

void ApplicationPlot::update(){
	
	Vector2l newWindowSize = Vector2l( window.getSize() );
	
	if( windowSize != newWindowSize ){
		
		resized( window );
		
	}
	
	windowSize = newWindowSize;
	windowPosition = Vector2l( window.getPosition() );
	
	if( window.hasFocus() ){
		
		Vector2l position( Mouse::getPosition( window ) );
		long double u = position.x / windowSize.x * width + left_;
		long double v = ( windowSize.y - position.y ) / windowSize.y * height + bottom;
		
		window.setTitle( "ApplicationPlot : " + to_string( u ) + " + " + to_string( v ) + "i"
		+                " , r-range: " + to_string( left_ ) + " to " + to_string( left_ + width )
		+                " , i-range: " + to_string( bottom ) + "i to " + to_string( bottom + height ) + "i"
		+                " , time: " + to_string( timer )
		+                " , index: " + to_string( index ) );
		
		if( fullscreen ){
			
			text->setString( "z: " + to_string( u ) + " + " + to_string( v ) + "i\n"
			+               "r-range: " + to_string( left_ ) + " to " + to_string( left_ + width ) + "\n"
			+               "i-range: " + to_string( bottom ) + "i to " + to_string( bottom + height ) + "i");
			text2->setString( "time: " + to_string( timer ) );
			text3->setString( "index: " + to_string( index ) );
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::X ) ){
			
			ortoAngle += deltaTime * constants::pi< long double >() * velAngle;
			
			updateGraphics = true;
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Z ) ){
			
			ortoAngle -= deltaTime * constants::pi< long double >() * velAngle;
			
			updateGraphics = true;
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::D ) ){
			
			zoom( 1.l + 1.01l * deltaTime , window );
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::A ) ){
			
			zoom( 1.l - 1.01l * deltaTime , window );
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Right ) || Keyboard::isKeyPressed( Keyboard::Scancode::E ) ){
			
			left_ += width * deltaTime * vel;
			updateGraphics = true;
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Left ) || Keyboard::isKeyPressed( Keyboard::Scancode::Q ) ){
			
			left_ -= width * deltaTime * vel;
			updateGraphics = true;
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Down ) || Keyboard::isKeyPressed( Keyboard::Scancode::S ) ){
			
			bottom -= height * deltaTime * vel;
			updateGraphics = true;
			
		}
		
		if( Keyboard::isKeyPressed( Keyboard::Scancode::Up ) || Keyboard::isKeyPressed( Keyboard::Scancode::W ) ){
			
			bottom += height * deltaTime * vel;
			updateGraphics = true;
			
		}
		
	}
	
	if( updateGraphics ){
		
		lines[ 0 ].position = Vector2f( 0.l , staticSize.y + bottom / height * staticSize.y );
		lines[ 1 ].position = Vector2f( staticSize.x , staticSize.y + bottom / height * staticSize.y );
		lines[ 2 ].position = Vector2f( -left_ / width * staticSize.x , 0.l );
		lines[ 3 ].position = Vector2f( -left_ / width * staticSize.x , staticSize.y );
		
		for( int i = 0; i < points.size(); i++ ){
			
			Vector2l v = math_points[ i ];
			Vector2l position( ( v.x - left_ ) * staticSize.x / width  , staticSize.y - ( v.y - bottom ) * staticSize.y / height );
			
			points[ i ].setPosition( Vector2f( position.x , position.y ) );
			
		}
		
		countNumbers = ceil( width ) + ceil( height );
		numbers.clear();
		
		if( coords.getVertexCount() / 2 != countNumbers ){
			
			coords.clear();
			
		}
		
		if( width < 280.f && height < 280.f ){
			
			coords.resize( countNumbers * 2 );
			
			for( int i = 0; i < ceil( width ); i++ ){
				
				long double x = ceil( left_ ) + i;
				
				coords[ i * 2 ].position = Vector2f( ( x - left_ ) * staticSize.x / width , lines[ 0 ].position.y - 5.l );
				coords[ i * 2 + 1 ].position = Vector2f( ( x - left_ ) * staticSize.x / width , lines[ 0 ].position.y + 5.l );
				
			}
			
			for( int i = 0; i < ceil( height ); i++ ){
				
				long double y = ceil( bottom ) + i;
				
				coords[ i * 2 + ceil( width ) * 2 ].position = Vector2f( lines[ 2 ].position.x - 5.l , staticSize.y - ( y - bottom ) * staticSize.y / height );
				coords[ i * 2 + 1 + ceil( width ) * 2 ].position = Vector2f( lines[ 2 ].position.x + 5.l , staticSize.y - ( y - bottom ) * staticSize.y / height );
				
			}
			
			//numbers.resize( countNumbers );
			Vector2f scale( staticSize.x / 700.f * 10.f / 1.f / width , staticSize.y / 700.f * 10.f / 1.f / height );
			
			if( width < 21.f || height < 21.f ){
				
				scale = Vector2f( staticSize.x / 700.f * 0.4 , staticSize.y / 700.f * 0.7 );
				
			}
			/*
			for( int i = 0; i < ceil( width ); i++ ){
				
				numbers[ i ].setFont( font );
				numbers[ i ].setString( to_stringi( ceil( left_ ) + i ) );
				numbers[ i ].setScale( scale );
				
				if( ceil( left_ ) + i == 0 ){
					
					numbers[ i ].setPosition( lines[ 2 ].position.x , lines[ 0 ].position.y );
					
				}
				else{
					
					numbers[ i ].setPosition( coords[ i * 2 ].position.x - numbers[ i ].getGlobalBounds().width / 2.f , lines[ 0 ].position.y );
					
				}
				
			}
			
			for( int i = 0; i < ceil( height ); i++ ){
				
				if( ceil( bottom ) + i == 0 ){
					
					continue;
					
				}
				
				numbers[ ceil( width ) + i ].setFont( font );
				numbers[ ceil( width ) + i ].setString( to_stringi( ceil( bottom ) + i ) );
				numbers[ ceil( width ) + i ].setScale( scale );
				numbers[ ceil( width ) + i ].setPosition( lines[ 2 ].position.x , coords[ i * 2 + ceil( width ) * 2 ].position.y - numbers[ i ].getGlobalBounds().height / 2.f );
				
			}
			*/
		}
		
	}
	
	if( clock.getElapsedTime().asSeconds() > 1.l / ( long double )( updatesForSecond ) ){
		
		//add_func( []( long double x ){ return F( x ).real(); } );

		for( vector< RealFunction >::iterator i = real_functions.begin(); i != real_functions.end(); i++ ){
			
			draw_func( i->func , i->color , i->right , i->is_print_text );

		}
		
		for( vector< ComplexFunction >::iterator i = complex_functions.begin(); i != complex_functions.end(); i++ ){
			
			draw_complex_func( i->func , i->angle , i->color , i->is_print_text );

		}

		for( vector< VectorFunction >::iterator i = vector_functions.begin(); i != vector_functions.end(); i++ ){
			
			draw_vector_func( i->func , i->color , i->is_print_text );

		}
		
		clock.restart();
		timer += velTime / ( long double )( updatesForSecond );
		velTime += accTime / ( long double )( updatesForSecond );

	}
	
	updateGraphics = false;
	
}

void ApplicationPlot::render(){
	
	window.clear();
	
	if( fullscreen ){
		
		if( isTextData ){
			
			window.draw( * text );
			window.draw( * text2 );
			
		}
		
		if( isTextIterations ){
			
			window.draw( * text3 );
			
		}
		
	}
	
	window.draw( lines );
	window.draw( coords );
	
	for( CircleShape & point : points ){
		
		window.draw( point );
		
	}
	
	for( Text & number : numbers ){
		
		window.draw( number );
		
	}
	
	window.display();

}

void ApplicationPlot::run(){
	
	while( window.isOpen() ){
		
		deltaTime = deltaClock.restart().asSeconds();
		
		events();
		update();
		render();

	}

}

void ApplicationPlot::zoom( float scale , RenderWindow & window ){
	
	Vector2f postion( Mouse::getPosition( window ) );
	
	long double u = postion.x / windowSize.x * width + left_;
	long double v = ( windowSize.y - postion.y ) / windowSize.y * height + bottom;
	
	long double factor = 1.l / scale;
	long double b = factor;
	long double a = u * ( 1.l - b );
	long double d = factor;
	long double c = v * ( 1.l - d );
	
	left_ = a + left_ * b;
	bottom = c + bottom * d;
	width *= factor;
	height *= factor;
	
	updateGraphics = true;
	
}

void ApplicationPlot::resized( RenderWindow & window ){
	
	Vector2l newWindowPosition( window.getPosition() );
	Vector2l newWindowSize( window.getSize().x , window.getSize().y );
	long double differenceX = windowPosition.x - newWindowPosition.x;
	long double differenceY = newWindowPosition.y + newWindowSize.y - ( windowPosition.y + windowSize.y );
	
	left_ -= differenceX / windowSize.x * width;
	bottom -= differenceY / windowSize.y * height;
	width *= newWindowSize.x / windowSize.x;
	height *= newWindowSize.y / windowSize.y;
	
	updateGraphics = true;
	
}

void ApplicationPlot::draw_func( const function< long double( long double ) > & f , const Color & color , bool is_right , bool is_print ){
	
	long double a = is_right ? timer : -timer;
	Vector2l result( a ,f( a ) );
	Vector2f position( ( result.x - left_ ) * staticSize.x / width  , staticSize.y - ( result.y - bottom ) * staticSize.y / height );
	CircleShape point( 2.l );
	point.setFillColor( color );
	point.setPosition( Vector2f( position.x , position.y ) );
	
	if( is_print ){
		
		cout<<result.y<<" , "<<timer<<endl;

	}

	points.push_back( point );
	math_points.push_back( result );
	
}

void ApplicationPlot::draw_complex_func( const function< lcomplex( lcomplex ) > & f , long double angle , const Color & color , bool is_print ){
	
	lcomplex r = f( lcomplex( cos( angle ) * timer , sin( angle ) * timer ) );
	Vector2l result( r.real() , r.imag() );
	Vector2f position( ( result.x - left_ ) * staticSize.x / width  , staticSize.y - ( result.y - bottom ) * staticSize.y / height );
	CircleShape point( 2.l );
	point.setFillColor( color );
	point.setPosition( Vector2f( position.x , position.y ) );
	
	if( is_print ){
		
		cout<<r<<" , "<<timer<<endl;

	}

	points.push_back( point );
	math_points.push_back( result );

}

void ApplicationPlot::draw_vector_func( const function< Vector2l( long double ) > & f , const Color & color , bool is_print ){
	
	Vector2l result = f( timer );
	Vector2f position( ( result.x - left_ ) * staticSize.x / width  , staticSize.y - ( result.y - bottom ) * staticSize.y / height );
	CircleShape point( 2.l );
	point.setFillColor( color );
	point.setPosition( Vector2f( position.x , position.y ) );
	
	if( is_print ){
		
		cout<<result.x<<" , "<<result.y<<" : "<<timer<<endl;

	}

	points.push_back( point );
	math_points.push_back( result );

}

void ApplicationPlot::add_func( function< long double( long double ) > f , const Color & color , bool right , bool is_print ){
	
	RealFunction real_func;
	
	real_func.func = f;
	real_func.color = color;
	real_func.is_print_text = is_print;
	real_func.right = right;

	real_functions.push_back( real_func );

}

void ApplicationPlot::add_bi_func( function< long double( long double ) > f , const Color & color , bool is_print ){
	
	add_func( f , color , true , is_print );
	add_func( f , color , false , is_print );

}

void ApplicationPlot::add_complex_func( function< lcomplex( lcomplex ) > f , long double angle , const Color & color , bool is_print ){
	
	ComplexFunction complex_func;
	
	complex_func.func = f;
	complex_func.angle = angle;
	complex_func.color = color;
	complex_func.is_print_text = is_print;

	complex_functions.push_back( complex_func );
	
}

void ApplicationPlot::add_complex_func( function< lcomplex( lcomplex ) > f , const Color & color , bool is_print ){
	
	ComplexFunction complex_func;
	
	complex_func.func = f;
	complex_func.angle = 0.l;
	complex_func.color = color;
	complex_func.is_print_text = is_print;

	complex_functions.push_back( complex_func );
	
}

void ApplicationPlot::add_complex_func( function< lcomplex( long double ) > f , const Color & color , bool right , bool is_print ){
	
	ComplexFunction complex_func;
	
	complex_func.func = [ f ]( lcomplex value ){ return f( value.real() ); };
	complex_func.angle = 180.l;
	complex_func.color = color;
	complex_func.is_print_text = is_print;

	complex_functions.push_back( complex_func );
	
}

////////////

void ApplicationPlot::add_bi_complex_func( function< lcomplex( lcomplex ) > f , long double angle , const Color & color , bool is_print ){
	
	add_complex_func( f , angle , color , is_print );
	add_complex_func( f , angle + 180.l , color , is_print );
	
}

void ApplicationPlot::add_bi_complex_func( function< lcomplex( lcomplex ) > f , const Color & color , bool is_print ){
	
	add_complex_func( f , color , is_print );
	add_complex_func( f , 180.l , color , is_print );

}

void ApplicationPlot::add_bi_complex_func( function< lcomplex( long double ) > f , const Color & color , bool is_print ){
	
	add_complex_func( f , color , is_print );
	add_complex_func( f , color , true , is_print );
	
}

void ApplicationPlot::add_vector_func( function< Vector2l( long double ) > f , const Color & color , bool is_print ){
	
	VectorFunction vector_func;
	
	vector_func.func = [ f ]( lcomplex value ){ return f( value.real() ); };
	vector_func.color = color;
	vector_func.is_print_text = is_print;

	vector_functions.push_back( vector_func );

}

void ApplicationPlot::set_time( long double time ){
	
	timer = time;

}

void ApplicationPlot::set_velocity_time( long double vel ){
	
	velTime = vel;

}

void ApplicationPlot::set_updates_for_second( unsigned int N ){
	
	updatesForSecond = N;

}

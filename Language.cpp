#include"Language.hpp"
#include<algorithm>

string GetFileContents( const string & filename ){
	
	ifstream file( filename );
	stringstream ss;

	ss<<file.rdbuf();

	file.close();

	return ss.str();
}

namespace type_char{
	
	bool everything( const char & a ){
	
		return true;

	}

	bool is_empty( const char & a ){
	
		return a == ' ' || a == '\n';

	}

	bool is_name( const char & a ){
		
		return a == '_' || ( 48 <= a && a <= 57 ) || ( 65 <= a && a <= 90 ) || ( 97 <= a && a <= 122 );

	}

	bool is_number( const char & a ){
		
		return a == '+' || a == '-' || ( 48 <= a && a <= 57 ) || a == '.';

	}

}

Language::Language() : m_text() , m_index() , m_state() , m_word() , m_cache() , m_line() , m_errors() , m_captured_text() , m_type_errors() , m_write_nodes() , m_nodes() , m_text_state() , m_look_nodes() , m_looking_for() , m_init_text(){
	
	//nothing

}

Language::Language( const string & filename ) : m_text() , m_index() , m_state() , m_word() , m_cache() , m_line() , m_errors() , m_captured_text() , m_type_errors() , m_write_nodes() , m_nodes() , m_text_state() , m_look_nodes() , m_looking_for() , m_init_text(){
	
	loadFromFile( filename );

}

Language::~Language(){
	
	//nothing

}

void Language::node( unsigned int state , const char & a , unsigned int to_state , normal_func f , unsigned int error_key ){
	
	Node n;

	n.state = state;
	n.character = a;
	n.to_state = to_state;
	n.normal_function = f;
	n.error_key = error_key;

	m_nodes.push_back( n );

}

void Language::write_node( unsigned int state , const char & a , unsigned int to_state , normal_func f , unsigned int error_key , unsigned int error_extra ){
	
	WriteNode n;

	n.state = state;
	n.to_state = to_state;
	n.character = a;
	n.normal_function = f;
	n.error_key = error_key;
	n.error_extra = error_extra;

	m_write_nodes.push_back( n );

}

void Language::write_node( unsigned int state , const char & a , unsigned int to_state , unsigned int error_extra ){
	
	write_node( state , a , to_state , type_char::everything , -1 , error_extra );

}

void Language::look_node( unsigned int state , unsigned int to_state , normal_func f , normal_func f_extra , unsigned int error_key , unsigned int error_extra ){
	
	LookNode n;

	n.error_extra = error_extra;
	n.error_key = error_key;
	n.normal_function = f;
	n.read_function = f_extra;
	n.state = state;
	n.to_state = to_state;

	m_look_nodes.push_back( n );

}

bool Language::updateReadNodes(){
	
	for( vector< Node >::iterator i = m_nodes.begin(); i != m_nodes.end(); i++ ){
		
		if( i->state == m_state ){
			
			read( i->character , i->to_state , i->normal_function , i->error_key );

			return true;
		}

	}

	return false;
}

bool Language::updateWriteNodes(){
	
	for( vector< WriteNode >::iterator i = m_write_nodes.begin(); i != m_write_nodes.end(); i++ ){
		
		if( i->state == m_state ){
			
			m_captured_text = write( i->character , i->to_state , i->normal_function , i->error_key );

			return true;
		}

	}

	return false;
}

void Language::updateLookNodes(){
	
	for( vector< LookNode >::iterator i = m_look_nodes.begin(); i != m_look_nodes.end(); i++ ){
		
		if( i->state == m_state ){
			
			m_captured_text = ( look( i->to_state , i->normal_function , i->read_function , i->error_key ) == Final );

			return;
		}

	}

}

bool Language::capturedText() const{
	
	return m_captured_text;

}

bool Language::read( const char & a , unsigned int succes_state , normal_func f , unsigned int error_key ){
	
	bool result = read( a , succes_state );

	if( !result ){
		
		if( !f( character() ) ){
			
			addError( error_key );

		}

	}

	return result;
}

bool Language::write( const char & a , unsigned int to_state , normal_func f , unsigned int error_key ){
	
	bool result = write( a , to_state );

	if( !result ){
		
		if( !f( character() ) ){
			
			addError( error_key );

		}

	}

	return result;
}

Language::State Language::look( normal_func f , normal_func f_extra , unsigned int error_key ){
	
	if( m_looking_for ){
		
		if( f_extra( character() ) ){
			
			if( f_extra( afterCharacter() ) ) return Keep;
			
			m_word = m_text.substr( m_init_text , m_index - m_init_text + 1 );
			m_init_text = 0;
			m_looking_for = false;

			return Final;
		}

	}

	if( f_extra( character() ) ){
		
		if( charAreMissing() ){
			
			if( f_extra( afterCharacter() ) ){
				
				m_init_text = m_index;
				m_looking_for = true;

				return Init;
			}

			m_word = character();

			return Final;
		}

		m_word = character();

		return Final;
	}

	if( !f( character() ) ){
		
		addError( error_key );

		return Failed;
	}

	return Failed;
}

Language::State Language::look( unsigned int to_state , normal_func f , normal_func f_extra , unsigned int error_key ){
	
	State result = look( f , f_extra , error_key );

	if( result == Final ){
		
		m_text_state = m_state;
		m_state = to_state;

	}

	return result;
}

Language::State Language::read( const string & word ){
	
	if( m_word == word ){
		
		if( character() == word[ m_cache ] ){
			
			m_cache++;

			if( word.size() == m_cache ){
				
				m_word.clear();
				m_cache = 0;

				return Final;
			}

			return Keep;
		}

		m_word.clear();
		m_cache = 0;

		return Failed;
	}

	if( m_word.empty() ){
		
		if( character() == word[ m_cache ] ){
			
			m_word = word;
			m_cache++;

			if( word.size() == 1 ) return Final;

			return Init;
		}

	}
	
	return Failed;
}

Language::State Language::read( const string & word , unsigned int succes_state ){
	
	State result = read( word );

	if( result == Final ) m_state = succes_state;

	return result;
}

Language::State Language::read( const string & word , unsigned int succes_state , initializer_list< char > expected_list ){
	
	State result = read( word );

	if( result == Final ){
		
		if( !charAreMissing() ) return Failed;
		if( find( expected_list.begin() , expected_list.end() , afterCharacter() ) == expected_list.end() ) return Failed;

		m_state = succes_state;

	}

	return result;
}

Language::State Language::read( const string & word , unsigned int succes_state , unsigned int failed_state ){
	
	State result = read( word );

	if( result == Final ) m_state = succes_state;
	else if( result == Failed ) m_state = failed_state;

	return result;
}

bool Language::read( const char & a ){
	
	return character() == a;

}

bool Language::read( const char & a , unsigned int succes_state ){
	
	bool result = read( a );

	if( result ) m_state = succes_state;

	return result;
}

bool Language::read( const char & a , unsigned int succes_state , unsigned int failed_state ){
	
	bool result = read( a );

	if( result ) m_state = succes_state;
	else if( result ) m_state = failed_state;

	return result;
}

bool Language::write( const char & a ){
	
	if( character() == a ) return true;

	m_word.push_back( character() );

	return false;
}

bool Language::write( const char & a , unsigned int succes_state ){
	
	bool result = write( a );

	if( result ){
		
		m_text_state = m_state;
		m_state = succes_state;
		
	}

	return result;
}

void Language::errorCode( const string & text ){

	m_type_errors.push_back( text );

}

void Language::addError( unsigned int error_key ){
	
	Error error;

	error.key = error_key;
	error.line = m_line + 1;

	m_errors.push_back( error );

	close();

}

bool Language::printErrors(){
	
	finalError();

	if( m_errors.empty() ) return true;

	cerr<<"Error Count: "<<m_errors.size()<<endl;

	for( int i = 0; i < m_errors.size(); i++ ){
		
		cerr<<"Error "<<i + 1<<" , Line "<<m_errors[ i ].line<<" : "<<m_type_errors[ m_errors[ i ].key ]<<endl;
		
	}

	return false;
}

void Language::finalError(){
	
	for( vector< Node >::iterator i = m_nodes.begin(); i != m_nodes.end(); i++ ){
		
		if( i->state == m_state ){
			
			addError( i->error_key );

			return;
		}

	}

	for( vector< WriteNode >::iterator i = m_write_nodes.begin(); i != m_write_nodes.end(); i++ ){
		
		if( i->state == m_state ){
			
			addError( i->error_extra );

			return;
		}

	}

	for( vector< LookNode >::iterator i = m_look_nodes.begin(); i != m_look_nodes.end(); i++ ){
		
		if( i->state == m_state ){
			
			addError( i->error_extra );

			return;
		}

	}

}

void Language::clear(){
	
	m_word.clear();

}

void Language::close(){
	
	m_index = m_text.size();

}

void Language::setState( int new_state ){
	
	m_state = new_state;

}

void Language::loadFromMemory( const string & text ){
	
	m_text = text;
	m_index = 0;
	m_state = 0;
	m_word = string();
	m_cache = 0;
	m_line = 0;
	m_nodes.clear();
	m_write_nodes.clear();
	m_errors.clear();
	m_type_errors.clear();
	m_captured_text = false;
	m_text_state = 0;
	m_look_nodes.clear();
	m_looking_for = false;
	m_init_text = 0;

}

void Language::loadFromFile( const string & filename ){
	
	loadFromMemory( GetFileContents( filename ) );

}

bool Language::isOpen() const{
	
	return m_index < m_text.size();

}

char Language::afterCharacter() const{
	
	return m_text[ m_index + 1 ];

}

bool Language::charAreMissing() const{
	
	return m_index + 1 < m_text.size();
	
}

unsigned int Language::textState() const{
	
	return m_text_state;

}

unsigned int Language::getErrorCount() const{
	
	return m_errors.size();

}

void Language::updateNodes(){
	
	if( updateReadNodes() ) return;
	if( updateWriteNodes() ) return;

	updateLookNodes();
}

void Language::update(){
	
	if( isOpen() ){
		
		if( m_captured_text ){
			
			clear();
			m_captured_text = false;
			
		}

		m_index++;

		if( m_text[ m_index ] == '\n' ){
		
			m_line++;

		}
		
	}

}

char Language::character() const{
	
	return m_text[ m_index ];

}

unsigned int Language::getIndex() const{
	
	return m_index;

}

unsigned int Language::getLine() const{
	
	return m_line + 1;

}

const string & Language::savedText() const{
	
	return m_word;

}

const string & Language::getText() const{
	
	return m_text;

}

unsigned int Language::pollState() const{
	
	return m_state;

}
#pragma once

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<functional>

using namespace std;

string GetFileContents( const string & filename );

namespace type_char{
	
	bool everything( const char & a );
	bool is_empty( const char & a );
	bool is_name( const char & a );
	bool is_number( const char & a );

}

class Language{
public:
	
	typedef function< bool( const char & ) > normal_func;

	enum State{
		
		Failed,
		Init,
		Keep,
		Final

	};

	struct Node{
		
		unsigned int state;
		char character;
		unsigned int to_state;
		normal_func normal_function;
		unsigned int error_key;

	};

	struct WriteNode{
		
		unsigned int state;
		unsigned int to_state;
		char character;
		normal_func normal_function;
		unsigned int error_key;
		unsigned int error_extra;

	};
	
	struct LookNode{
		
		unsigned int state;
		unsigned int to_state;
		normal_func normal_function;
		normal_func read_function;
		unsigned int error_key;
		unsigned int error_extra;

	};

	struct Error{
		
		unsigned int key;
		unsigned int line;

	};

	Language();
	Language( const string & filename );
	~Language();
	
	void loadFromMemory( const string & text );
	void loadFromFile( const string & filename );
	void setState( int new_state );

	State read( const string & word );
	State read( const string & word , unsigned int succes_state );
	State read( const string & word , unsigned int succes_state , initializer_list< char > expected_list );
	State read( const string & word , unsigned int succes_state , unsigned int failed_state );
	bool read( const char & a );
	bool read( const char & a , unsigned int succes_state );
	bool read( const char & a , unsigned int succes_state , unsigned int failed_state );
	bool read( const char & a , unsigned int succes_state , normal_func f , unsigned int error_key );

	bool write( const char & a );
	bool write( const char & a , unsigned int succes_state );
	bool write( const char & a , unsigned int succes_state , normal_func f , unsigned int error_key );

	State look( normal_func f = type_char::everything , normal_func f_extra = type_char::everything , unsigned int error_key = -1 );
	State look( unsigned int to_state , normal_func f = type_char::everything , normal_func f_extra = type_char::everything , unsigned int error_key = -1 );

	void node( unsigned int state , const char & a , unsigned int to_state , normal_func f = type_char::everything , unsigned int error_key = -1 );
	void write_node( unsigned int state , const char & a , unsigned int to_state , normal_func f = type_char::everything , unsigned int error_key = -1 , unsigned int error_extra = -1 );
	void write_node( unsigned int state , const char & a , unsigned int to_state , unsigned int error_extra );
	void look_node( unsigned int state , unsigned int to_state , normal_func f = type_char::everything , normal_func f_extra = type_char::everything , unsigned int error_key = -1 , unsigned int error_extra = -1 );
	bool capturedText() const;

	//error functions

	void errorCode( const string & text );
	void addError( unsigned int error_key );
	bool printErrors();

	bool charAreMissing() const;
	unsigned int textState() const;
	unsigned int pollState() const;
	unsigned int getIndex() const;
	unsigned int getErrorCount() const;
	unsigned int getLine() const;
	const string & savedText() const;
	const string & getText() const;
	char character() const;
	char afterCharacter() const;
	bool isOpen() const;
	void update();
	void close();
	
	void updateNodes();

protected:
	
	bool updateReadNodes();
	bool updateWriteNodes();
	void updateLookNodes();
	void finalError();
	void clear();

	string m_text;
	unsigned int m_index;
	unsigned int m_state;
	string m_word;
	unsigned int m_cache;
	unsigned int m_line;
	vector< string > m_type_errors;
	vector< Error > m_errors;
	vector< Node > m_nodes;
	vector< WriteNode > m_write_nodes;
	vector< LookNode > m_look_nodes;
	bool m_captured_text;
	unsigned int m_text_state;
	bool m_looking_for;
	unsigned int m_init_text;

};
#include"ortogonals.hpp"
#include<algorithm>

template< typename T >
T branch( T angle ){
	
	T x = ceil( ( angle + constants::pi< T >() ) / constants::tau< T >() ) - T( 1 );
	
	return x;
}

template< typename T >
T collapse( T angle ){
	
	return angle - branch( angle ) * constants::tau< T >();
	
}

template< typename T >
T rebranch( T z1 , T z2 ){
	
	return collapse( z1 ) + branch( z2 ) * constants::tau< T >();
	
}

template< typename T >
int is_sing( T z ){
	
	if( z == T( 0 ) ) return -1;
	if( z == T( 1 ) ) return 0;
	if( z == exp( T( 1 ) ) ) return 1;
	if( z == exp( exp( T( 1 ) ) ) ) return 2;
	if( z == exp( exp( exp( T( 1 ) ) ) ) ) return 3;
	
	return 4;
}

template< typename T >
T value_tetration( int k ){
	
	if( k == -1 ) return T( 0 );
	if( k == 0 ) return T( 1 );
	if( k == 1 ) return exp( T( 1 ) );
	if( k == 2 ) return exp( exp( T( 1 ) ) );
	if( k == 3 ) return exp( exp( exp( T( 1 ) ) ) );
	if( k > 3 ) return std::numeric_limits< T >::infinity();
	
	return -1.l;
}

template< typename Complex >
bool ortogonal< Complex >::overpased_sing() const{
	
	return type == Tetration ? info.sing > 3 : false;
	
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::make_sing( int k ){
	
	ortogonal< Complex > w;
	
	w.info.sing = k;
	
	if( k >= 0 ){
		
		w.type = ortogonal< Complex >::Tetration;
		
	}
	else{
		
		w.type = ortogonal< Complex >::Sing;
		
	}
	
	return w;
}

template< typename Complex >
ortogonal< Complex >::operator Complex() const{
	
	if( type ){
		
		return type == Tetration ? value_tetration< Real >( info.sing ) : Complex( std::numeric_limits< RealType >::quiet_NaN() , std::numeric_limits< RealType >::quiet_NaN() );
		
	}
	
	return info.z;
}

template< typename Complex >
int ortogonal< Complex >::sing() const{
	
	if( !type ){
		
		cerr<<"class ortogonal -> Erorr sing: a normal ortogonal can't be a singularity"<<endl;
		
		return 0;
	}

	return info.sing;
}

template< number_ortogonal T >
T collapse( const T & w ){
	
	return T( w.z() );

}

template< typename T >
T e_tetration_positive( T z , unsigned int n ){
	
	while( n ){
		
		z = exp( z );
		n--;

	}

	return z;
}

template< typename T >
T e_tetration_negative( T z , unsigned int n ){
	
	while( n ){
		
		z = log( z );
		n--;

	}

	return z;
}

template< number_ortogonal T >
T e_tetration_positive( T w , unsigned int n ){
	
	if( w.getType() ){
		
		return T::make_sing( w.sing() + n );

	}

	while( n ){
		
		w = exp( w );
		n--;

	}

	return w;
}

template< number_ortogonal T >
T e_tetration_negative( T  w , unsigned int n ){
	
	if( w.getType() ){
		
		return T::make_sing( w.sing() - n );

	}

	while( n ){
		
		w = log( w );
		n--;

	}

	return w;
}

template< typename T >
T e_tetration_integer( T w , int n ){
	
	return n < 0 ? e_tetration_negative( w , -n ) : e_tetration_positive( w , n );

}

template< number_ortogonal T >
T e_tetration_integer( T w , int n ){
	
	return n < 0 ? e_tetration_negative( w , -n ) : e_tetration_positive( w , n );

}

template< number_ortogonal T >
T collapse( const T & w , int level ){
	
	if( w.getType() == T::Sing ){
		
		cerr<<"class ortogonal -> collapse : Invalid collapse in singularities"<<endl;

		return T::NaN;
	}
	
	if( level < 0 ){
		
		return ortogonal( e_tetration_positive( e_tetration_negative( w.z() , -level ) , -level ) );

	}

	T result( w.z() );
	
	for( int i = 0; i < level; i++ ){
		
		result.add_branch( i , w.branch( i ) );

	}

	return result;
}

template< number_ortogonal T >
T kproduct( int n , T z , T w ){
	
	if( n < 0 ){
		
		for( unsigned int i = 0; i < -n; i++ ){
		
			z = exp( z );
			w = exp( w );
		
		}
	
		T result = z + w;
	
		for( unsigned int i = 0; i < -n; i++ ){
		
			result = log( result );
		
		}

		return result;
	}

	if( n == 0 ) return z + w;

	for( unsigned int i = 0; i < n - 1; i++ ){
		
		z = log( z );
		w = log( w );
		
	}
	
	T result = z * w;
	
	for( unsigned int i = 0; i < n - 1; i++ ){
		
		result = exp( result );
		
	}
	
	return result;
}

template< number_ortogonal T >
T kinverse( int n , T w ){
	
	if( n < 0 ){
		
		for( unsigned int i = 0; i < -n; i++ ){
		
			w = exp( w );
		
		}
	
		T result = -w;
	
		for( unsigned int i = 0; i < -n; i++ ){
		
			result = log( result );
		
		}
	
		return result;
	}

	if( n == 0 ) return -w;
	if( n == 1 ) return inverse( w );

	for( unsigned int i = 0; i < n - 1; i++ ){
		
		w = log( w );
		
	}
	
	T result = inverse( w );
	
	for( unsigned int i = 0; i < n - 1; i++ ){
		
		result = exp( result );
		
	}
	
	return result;
}

template< number_ortogonal T >
T inverse( const T & w ){
	
	return exp( -log( w ) );
	
}

template< number_ortogonal T >
T operator+( real_type< T > x , const T & w ){
	
	return w + x;
	
}

template< number_ortogonal T >
T operator-( real_type< T > x , const T & w ){
	
	return -w + x;
	
}

template< number_ortogonal T >
T operator*( real_type< T > x , const T & w ){
	
	return w * x;
	
}

template< number_ortogonal T >
T operator/( real_type< T > x , const T & w ){
	
	return inverse( w ) * x;
	
}

template< number_ortogonal T >
T exp( const T & w ){
	
	using Real = real_type< T >;

	if( w.type ){
		
		if( w.type == T::Sing ) return T::make_sing( w.info.sing + 1 );
		
		T result = T::make_sing( w.info.sing + 1 );
		
		for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
			
			result.branchs.insert( make_pair( i->first + 1 , i->second ) );
			
		}
		
		return result;
	}
	
	Real angle = w.info.z.imag();
	int new_branch = branch( angle );
	
	T result( exp( w.info.z ) );
	
	if( ( ( Real )( new_branch ) * constants::tau< Real >() < angle && result.info.z.imag() < 0 )
	||  ( ( Real )( new_branch ) * constants::tau< Real >() >= angle && result.info.z.imag() > 0 ) ){
		
		result.info.z = T::ComplexType( result.info.z.real() , 0 );
		
	}
	
	if( new_branch != 0 ){
		
		result.branchs.insert( make_pair( 0 , new_branch ) );
		
	}
	
	for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
		
		result.branchs.insert( make_pair( i->first + 1 , i->second ) );
		
	}
	
	return result;
}

template< number_ortogonal T >
T log( const T & w ){
	
	if( w.type ){
		
		if( w.type == T::Sing ) return T::make_sing( w.info.sing - 1 );
		if( w.info.sing == 0 ) return T::make_sing( -1 );
		
		if( w.branch( 0 ) == 0 ){
			
			T result = T::make_sing( w.info.sing - 1 );
			
			for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
				
				if( i->first != 0 ){
					
					result.branchs.insert( make_pair( i->first - 1 , i->second ) );
					
				}
				
			}
			
			return result;
		}
		
		real_type< T > angle = arg( w );
		
		T result( log( abs( value_tetration< real_type< T > >( w.info.sing ) ) ) , angle );
		
		for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
			
			if( i->first != 0 ){
				
				result.branchs.insert( make_pair( i->first - 1 , i->second ) );
				
			}
			
		}
		
		return result;
	}
	
	T result( log( abs( w ) ) , arg( w ) );
	
	for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
		
		if( i->first != 0 ){
			
			result.branchs.insert( make_pair( i->first - 1 , i->second ) );
			
		}
		
	}
	
	return result;
}

template< number_ortogonal T >
T pow( const T & u , const T & v ){
	
	return exp( v * log( u ) );
	
}

template< number_ortogonal T >
T cos( const T & w ){
	
	return ( exp( w * T::I ) + exp( -w * T::I ) ) / real_type< T >( 2 );
	
}

template< number_ortogonal T >
T sin( const T & w ){
	
	return ( exp( w * T::I ) - exp( -w * T::I ) ) / T::ComplexType( 0 , 2 );
	
}

template< number_ortogonal T >
T tan( const T & w ){
	
	return sin( w ) / cos( w );
	
}

template< number_ortogonal T >
T sec( const T & w ){
	
	return inverse( cos( w ) );
	
}

template< number_ortogonal T >
T csc( const T & w ){
	
	return inverse( sin( w ) );
	
}

template< number_ortogonal T >
T cot( const T & w ){
	
	return cos( w ) / sin( w );
	
}

template< number_ortogonal T >
T cosh( const T & w ){
	
	return ( exp( w ) + exp( -w ) ) / real_type< T >( 2 );
	
}

template< number_ortogonal T >
T sinh( const T & w ){
	
	return ( exp( w ) - exp( -w ) ) / real_type< T >( 2 );
	
}

template< number_ortogonal T >
T tanh( const T & w ){
	
	return sinh( w ) / cosh( w );
	
}

template< number_ortogonal T >
T sech( const T & w ){
	
	return inverse( cosh( w ) );
	
}

template< number_ortogonal T >
T csch( const T & w ){
	
	return inverse( sinh( w ) );
	
}

template< number_ortogonal T >
T coth( const T & w ){
	
	return inverse( tanh( w ) );
	
}

template< number_ortogonal T >
T sqrt( const T & w ){
	
	return pow( w , T( 0.5 ) );
	
}

template< number_ortogonal T >
T cbrt( const T & w ){
	
	return pow( w , real_type< T >( 1 ) / real_type< T >( 3 ) );
	
}

template< number_ortogonal T >
T root( const T & u ,const T & v ){
	
	return pow( u , inverse( v ) );
	
}

template< number_ortogonal T >
real_type< T > arg( const T & w ){
	
	return arg( w.z() ) + w.branch( 0 ) * constants::tau< real_type< T > >();
	
}

template< number_ortogonal T >
real_type< T > abs( const T & w ){
	
	return abs( w.z() );
	
}

template< number_ortogonal T >
T wlambert( const T & w ){
	
	return wlambert( Complex( w ) , w.branch( 0 ) );
	
}

template< number_ortogonal T >
T wave( const T & w ){
	
	return exp( wlambert( log( w ) ) );
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal() : type( Sing ) , branchs(){
	
	info.sing = -1;
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal( const Complex & z ) : branchs(){
	
	int k = is_sing( z );
	
	if( k == 4 ){
		
		info.z = z;
		type = Normal;
		
	}
	else if( k == -1 ){
		
		info.sing = -1;
		type = Sing;
		
	}
	else{
		
		info.sing = k;
		type = Tetration;
		
	}
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal( RealType r ) : branchs(){
	
	int k = is_sing( r );
	
	if( k == 4 ){
		
		info.z = r;
		type = Normal;
		
	}
	else if( k == -1 ){
		
		info.sing = -1;
		type = Sing;
		
	}
	else{
		
		info.sing = k;
		type = Tetration;
		
	}
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal( RealType r , RealType i ) : ortogonal( Complex( r , i ) ){
	
	//nothing
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal( const ortogonal & other ) : info( other.info ) , type( other.type ) , branchs( other.branchs ){
	
	//nothing
	
}

template< typename Complex >
ortogonal< Complex >::~ortogonal(){
	
	//nothing
	
}

template< typename Complex >
const ortogonal< Complex > ortogonal< Complex >::I = ortogonal( RealType( 1 ) , RealType( 0 ) );

template< typename Complex >
const ortogonal< Complex > ortogonal< Complex >::NaN = ortogonal( std::numeric_limits< RealType >::quiet_NaN() , std::numeric_limits< RealType >::quiet_NaN() );

template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator=( const ortogonal & other ){
	
	type = other.type;
	info = other.info;
	branchs = other.branchs;

	return *this;
}

template< typename Complex >
void ortogonal< Complex >::add_branch( unsigned int index , int value ){
	
	if( value == 0 || type == Sing ) return;
	
	if( type == Tetration ){
		
		if( index <= info.sing ){
			
			branchs.insert( make_pair( index , branch( index ) + value ) );
			
			return;
		}
		
		cout<<"class ortogonal : Error in add_branch -> Index exceeded in the tetration type."<<endl;
		
		return;
	}
	
	branchs.insert( make_pair( index , branch( index ) + value ) );
	
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator-() const{
	
	if( type ){
		
		if( type == Sing ){
			
			return ( info.sing == -1 ) ? *this : ortogonal::NaN;
			
		}
		
		return make_orto( Complex( -value_tetration< RealType >( info.sing ) ) , 0 , -branch( 0 ) );
	}

	if( info.z.imag() == RealType( 0 ) ) return make_orto( Complex( -info.z.real() ) , -branch( 0 ) );
	
	return make_orto( -info.z , -branch( 0 ) );
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator+( const ortogonal & other ) const{
	
	if( !type && !other.type ){
		
		Complex r = info.z + other.info.z;
		
		if( info.z.imag() > 0 && arg( other.info.z ) < arg( info.z ) - constants::pi< RealType >() && r.imag() < 0 && r.real() < 0 ){
			
			return make_orto( r , branch( 0 ) + other.branch( 0 ) + 1 );
			
		}
		
		if( info.z.imag() < 0 && arg( other.info.z ) > arg( info.z ) + constants::pi< RealType >() && r.imag() > 0 && r.real() < 0 ){
			
			return make_orto( r , branch( 0 ) + other.branch( 0 ) - 1 );
			
		}
		
		return make_orto( r , branch( 0 ) + other.branch( 0 ) );
	}
	
	if( type == Sing ) return info.sing + 1 ? ( info.sing + 2 ? ortogonal::NaN : *this ) : other;
	if( other.type == Sing ) return other.info.sing + 1 ? ( other.info.sing + 2 ? ortogonal::NaN : other ) : *this;
	if( overpased_sing() && !other.overpased_sing() ) return *this;
	if( !overpased_sing() && other.overpased_sing() ) return other;
	if( overpased_sing() && other.overpased_sing() ) return info.sing > other.info.sing ? *this : other;
	
	Complex a = type ? value_tetration< RealType >( info.sing ) : info.z;
	Complex b = other.type ? value_tetration< RealType >( other.info.sing ) : other.info.z;
	
	return make_orto( a + b , branch( 0 ) + other.branch( 0 ) );
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator*( const ortogonal & other ) const{
	
	if( !type && !other.type ){
		
		RealType angle1 = arg( info.z ) + ( RealType )( branch( 0 ) ) * constants::tau< RealType >();
		RealType angle2 = arg( other.info.z ) + ( RealType )( other.branch( 0 ) ) * constants::tau< RealType >();
		int new_branch = ::branch< RealType >( angle1 + angle2 );
		
		Complex product = info.z * other.info.z;
		Complex orto_z( log( abs( info.z ) ) , angle1 );
		Complex orto_z2( log( abs( other.info.z ) ) , angle2 );
		Complex orto_r = log( product );
		
		if( orto_z.imag() > 0 && arg( orto_z2 ) < arg( orto_z ) - constants::pi< RealType >() && orto_r.imag() < 0 && orto_r.real() < 0 ){
			
			return make_orto( product , new_branch , branch( 1 ) + other.branch( 1 ) + 1 );
			
		}
		
		if( orto_z.imag() < 0 && arg( orto_z2 ) > arg( orto_z ) + constants::pi< RealType >() && orto_r.imag() > 0 && orto_r.real() < 0 ){
			
			return make_orto( product , new_branch , branch( 1 ) + other.branch( 1 ) - 1 );
			
		}
		
		return make_orto( product , new_branch );
	}
	
	if( type == Sing ) return info.sing == -1 ? *this : ortogonal::NaN;
	if( other.type == Sing ) return other.info.sing == -1 ? other : ortogonal::NaN;
	
	if( overpased_sing() && !other.overpased_sing() ) return *this;
	if( !overpased_sing() && other.overpased_sing() ) return other;
	if( overpased_sing() && other.overpased_sing() ) return info.sing > other.info.sing ? *this : other;
	
	if( type ) if( info.sing == 0 ) return other;
	if( other.type ) if( other.info.sing == 0 ) return *this;
	
	Complex a = type ? value_tetration< RealType >( info.sing ) : info.z;
	Complex b = other.type ? value_tetration< RealType >( other.info.sing ) : other.info.z;
	
	RealType angle1 = arg( a ) + ( RealType )( branch( 0 ) ) * constants::tau< RealType >();
	RealType angle2 = arg( b ) + ( RealType )( other.branch( 0 ) ) * constants::tau< RealType >();
	int new_branch = ::branch< RealType >( angle1 + angle2 );
	
	return make_orto( a * b , new_branch , branch( 1 ) + other.branch( 1 ) );
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator-( const ortogonal & other ) const{
	
	return *this + -other;
	
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator/( const ortogonal & other ) const{
	
	return *this * inverse( other );
	
}

template< typename Complex >
ortogonal< Complex > operator+( const Complex & z , const ortogonal< Complex > & other ){
	
	return other + z;
	
}

template< typename Complex >
ortogonal< Complex > operator-( const Complex & z , const ortogonal< Complex > & other ){
	
	return -other + z;
	
}

template< typename Complex >
ortogonal< Complex > operator*( const Complex & z , const ortogonal< Complex > & other ){
	
	return other * z;
	
}

template< typename Complex >
ortogonal< Complex > operator/( const Complex & z , const ortogonal< Complex > & other ){
	
	return inverse( other ) * z;
	
}

template< typename Complex >
int ortogonal< Complex >::branch( unsigned int index ) const{
	
	if( type == Sing ){
		
		return -1;
		
	}
	
	if( branchs.find( index ) != branchs.end() ){
		
		return branchs.at( index );
		
	}
	
	return 0;
}

template< typename Complex >
int ortogonal< Complex >::complexity() const{
	
	if( type == Sing ){
		
		return -1;
		
	}
	
	if( type == Tetration ){
		
		if( branchs.empty() ){
			
			return 0;
			
		}
		
		map< unsigned int , int >::const_iterator i = max_element( branchs.begin() , branchs.end() );
		
		return i->second + 1;
	}
	
	if( branchs.empty() ){
		
		return 0;
		
	}
	
	map< unsigned int , int >::const_iterator i = max_element( branchs.begin() , branchs.end() );
	
	return i->second + 1;
}

template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator+=( const ortogonal & other ){
	
	return *this = *this + other;
	
}

template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator-=( const ortogonal & other ){
	
	return *this = *this - other;
	
}
template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator*=( const ortogonal & other ){
	
	return *this = *this * other;
	
}

template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator/=( const ortogonal & other ){
	
	return *this = *this / other;
	
}

template< typename Complex >
bool ortogonal< Complex >::operator==( const ortogonal & other ) const{
	
	return ( type ? info.sing == other.info.sing : info.z == other.info.z ) && type == other.type && branchs == other.branchs;

}

template< typename Complex >
bool ortogonal< Complex >::operator!=( const ortogonal & other ) const{
	
	return !( *this == other );

}

template< typename Complex >
const ortogonal< Complex >::Type & ortogonal< Complex >::getType() const{
	
	return type;
	
}

template< typename Complex >
Complex ortogonal< Complex >::z() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in z part : Can't exists the z part of a singularity minor that -1"<<endl;
		
		return Complex( std::numeric_limits< RealType >::quiet_NaN() , std::numeric_limits< RealType >::quiet_NaN() );
	}
	
	return type == Tetration ? value_tetration< RealType >( info.sing ) : info.z;
}

template< typename Complex >
ortogonal< Complex >::RealType ortogonal< Complex >::real() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in real part : Can't exists the real part of a singularity minor that -1"<<endl;
		
		return std::numeric_limits< RealType >::quiet_NaN();
	}
	
	return type == Tetration ? value_tetration< RealType >( info.sing ) : info.z.real();
}

template< typename Complex >
ortogonal< Complex >::RealType ortogonal< Complex >::imag() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in imaginary part : Can't exists the imaginary part of a singularity minor that -1"<<endl;
		
		return std::numeric_limits< RealType >::quiet_NaN();
	}
	
	return type == Tetration ? 0 : info.z.imag();
}

template< number_ortogonal T >
std::ostream & operator<<( std::ostream & o , const T & w ){
	
	if( w.type == T::Sing ){
		
		if( w.info.sing == -1 ) return o<<T::ComplexType( 0 )<<endl;

		o<<"singularity("<<w.info.sing<<")";
		
		return o;
	}
	
	if( w.type == T::Tetration ){
		
		if( w.info.sing > 3 ){
			
			o<<"singularity("<<w.info.sing<<")";
			
		}
		else{
			
			o<<Complex( value_tetration< Real >( w.info.sing ) );
			
		}
		
		for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
			
			o<<" , o"<<i->first<<" : "<<i->second;
			
		}
		
		return o;
	}
	
	o<<w.info.z;
	
	for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
		
		o<<" , o"<<i->first<<" : "<<i->second;
		
	}
	
	return o;
}

template< typename T >
T zexpz( T z ){
	
	return z * exp( z );
	
}

template< typename T >
T zexpz_d( T z ){
	
	return exp( z ) + z * exp( z );
	
}

template< typename T >
T zexpz_dd( T z ){
	
	return exp( z ) * T( 2 ) + z * exp( z );
	
}

template< typename T >
T InitPoint(T z, int k){
	
	T I( 0 , 1 );
	T two_pi_k_I = T( k ) * T( 3.141592653589793238462643383279502884l * 2.l ) * I;
	T ip( log(z) + two_pi_k_I - log( log( z ) + two_pi_k_I ) );// initial point coming from the general asymptotic approximation
	T p( sqrt( T( 2 ) * ( exp( T( 1 ) ) * z + T( 1 ) ) ) );// used when we are close to the branch cut around zero and when k=0,-1
	
	//we are close to the branch cut, the initial point must be chosen carefully
	if( k == 0 && abs( z - exp( -T( 1 ) ) ) <= real_type< T >( 1 ) ){
		
		if( k == 0 ) ip = -T( 1 ) + p - T( 1 ) / T( 3 ) * ( p * p ) + T( 11 ) / T( 72 ) * ( p * p * p );
		if( k == 1 && z.imag() < T( 0 ).real() ) ip = -T( 1 ) - p - T( 1 ) / T( 3 ) * ( p * p ) - T( 11 ) / T( 72 ) * ( p * p * p );
		if( k == -1 && z.imag() > T( 0 ).real() ) ip = -T( 1 ) - p - T( 1 ) / T( 3 ) * ( p * p ) - T( 11 ) / T( 72 ) * ( p * p * p );
		
	}
	
	if( k == 0 && abs(z - T( 0.5 )) <= real_type< T >( 0.5 ) ){
		
		// (1,1) Pade approximant for W(0,a)
		ip = ( T( 0.35173371l ) * ( T( 0.1237166l ) + T( 7.061302897l ) * z ) ) / ( T( 2 ) + T( 0.827184l ) * ( T( 1 ) + T( 2 ) * z ) );
		
	}
	
	if( k == -1 && abs( z - T( 0.5 ) ) <= real_type< T >( 0.5 ) ){
		
		// (1,1) Pade approximant for W(-1,a)
		ip = -( ( ( T( 2.2591588985l ) +
		T( 4.22096l ) * I ) * ( ( -T( 14.073271l ) - T( 33.767687754l ) * I ) * z - ( T( 12.7127l ) -
		T( 19.071643l ) * I ) * ( T( 1 ) + T( 2 ) * z ) ) ) / ( T( 2 ) - ( T( 17.23103l ) - T( 10.629721l ) * I ) * ( T( 1 ) + T( 2 ) * z ) ) );
		
	}

	return ip;
}

//Creditos por W de Lambert a https://github.com/IstvanMezo/LambertW-function

template< typename T >
T wlambert( T z , int k ){
	
	//For some particular z and k W(z,k) has simple value:
	if( z == T( 0 ) ) return ( k == 0 ) ? 0.l : -std::numeric_limits< real_type< T > >::infinity();
	if( z == -exp( -T( 1 ) ) && ( k == 0 || k == -1 ) ) return -T( 1 );
	if( z == exp( T( 1 ) ) && k == 0 ) return T( 1 );
	
	//Halley method begins
	T w( InitPoint( z , k ) ) , wprev; // intermediate values in the Halley method
	const unsigned int maxiter = wlambert_complexity; // max number of iterations. This eliminates improbable infinite loops
	unsigned int iter = 0; // iteration counter
	
	do{
		
		wprev = w;
		w -= T( 2 ) * ( ( zexpz( w ) - z ) * zexpz_d( w ) ) / ( T( 2 ) * pow( zexpz_d( w ) , T( 2 ) ) - ( zexpz( w ) - z ) * zexpz_dd( w ) );
		iter++;
		
	} while( abs( w - wprev ) > std::numeric_limits< real_type< T > >::epsilon() && iter < maxiter );
	
	return w;
}
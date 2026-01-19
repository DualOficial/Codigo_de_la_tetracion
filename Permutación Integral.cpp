#include<iostream>
#include<windows.h>
#include<limits>
#include<cmath>
#include<complex>
#include<fstream>
#include<permutation.hpp>

using namespace std;

//1.44466786100976613374
//u=0.713686195819710924085
//u1=0.786050014142266872399

/*
unsigned int max_iterations = 1000;

complex< long double > per2( complex< long double > x , long double y ){
	
	complex< long double > simplified_x = x;
	long double extra_x = 0.l;
	
	do{
		
		simplified_x = sqwv( simplified_x );
		extra_x++;
		
	} while( abs( simplified_x ) > 2.l );
	
	long double extra_y = floor( y );
	long double simplified_y = y - extra_y;
	complex< long double > prev_result;
	complex< long double > result;
	complex< long double > term = simplified_x;
	long double n = 0.l;
	
	do{
		
		prev_result = result;
		result = perPositive( pow( term , pow( term , simplified_y ) ) , n );
		term = sqwv( term );
		n++;
		
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() && n < max_iterations );
	
	return perInteger( result , extra_x + extra_y );
}
*/

complex< long double > log( complex< long double > x , complex< long double > y ){
	
	return log( x ) / log( y );
	
}

complex< long double > tetration( complex< long double > x , int y ){
	
	if( y == -1 ){
		
		return 0.l;
		
	}
	
	return pow( x , tetration( x , y - 1 ) );
}

complex< long double > per_tetration( complex< long double > x , int k , unsigned int y ){
	
	if( y == 0 ){
		
		return x;
		
	}
	
	return tetration( per_tetration( x , k , y - 1 ) , k );
}

complex< long double > cbwv( complex< long double > x ){
	
	complex< long double > prev_result;
	complex< long double > result = 1.l;
	
	do{
		
		prev_result = result;
		result = exp( wlambert( wlambert( result * log( x ) ) ) );
		
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() );
	
	return result;
}

complex< long double > gradialPositive( complex< long double > x , unsigned int n ){
	
	if( !n ){
		
		return x;
		
	}
	
	complex< long double > temp = gradialPositive( x , n - 1 );
	
	return asc( temp , complex< long double >( n ) );
}

complex< long double > gradialNegative( complex< long double > x , unsigned int n ){
	
	if( !n ){
		
		return x;
		
	}
	
	complex< long double > temp = gradialNegative( x , n - 1 );
	
	return wave( temp , complex< long double >( 1.l - n ) );
}

complex< long double > gradialInteger( complex< long double > x , int y ){
	
	if( y < 0 ){
		
		return gradialNegative( x , -y );
		
	}
	
	return gradialPositive( x , y );
}

complex< long double > perPositive( complex< long double > x , unsigned int n ){
	
	if( !n ){
		
		return x;
		
	}
	
	complex< long double > temp = perPositive( x , n - 1 );
	
	return pow( temp , temp );
}

complex< long double > perNegative( complex< long double > x , unsigned int n ){
	
	if( !n ){
		
		return x;
		
	}
	
	complex< long double > temp = perNegative( x , n - 1 );
	
	return wave( temp );
}

complex< long double > perInteger( complex< long double > x , int y ){
	
	if( y < 0 ){
		
		return perNegative( x , -y );
		
	}
	
	return perPositive( x , y );
}

complex< long double > perPositive3( complex< long double > x , unsigned int n ){
	
	if( !n ){
		
		return x;
		
	}
	
	complex< long double > temp = perPositive3( x , n - 1 );
	
	return pow( temp , pow( temp , temp ) );
}

complex< long double > perNegative3( complex< long double > x , unsigned int n ){
	
	if( !n ){
		
		return x;
		
	}
	
	complex< long double > temp = perNegative3( x , n - 1 );
	
	return cbwv( temp );
}

complex< long double > perInteger3( complex< long double > x , int y ){
	
	if( y < 0 ){
		
		return perNegative3( x , -y );
		
	}
	
	return perPositive3( x , y );
}

complex< long double > per( complex< long double > x , complex< long double > y ){
	
	complex< long double > term = x;
	complex< long double > prev_result;
	complex< long double > result;
	long double n = 0.l;
	
	do{
		
		prev_result = result;
		result = perPositive( pow( term , pow( term , y ) ) , n );
		term = wave( term );
		n++;
		cout<<result<<" , "<<n<<endl;
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() );
	
	return result;
}

complex< long double > per3( complex< long double > x , complex< long double > y ){
	
	complex< long double > term = x;
	complex< long double > prev_result;
	complex< long double > result;
	long double n = 0.l;
	
	do{
		
		prev_result = result;
		result = perPositive3( pow( term , pow( term , y ) ) , n );
		term = cbwv( term );
		n++;
		cout<<result<<" , "<<n<<endl;
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() );
	
	return result;
}

complex< long double > gen( complex< long double > x , complex< long double > y ){
	
	complex< long double > term1 = x;
	complex< long double > term2 = y;
	complex< long double > prev_result;
	complex< long double > result;
	long double n = 0.l;
	
	do{
		
		prev_result = result;
		result = ( 1.l / log( term1 ) ) - ( 1.l / log( term2 ) );
		term1 = wave( term1 );
		term2 = wave( term2 );
		n++;
		cout<<result<<" , "<<n<<endl;
		
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() );
	
	return result;
}

complex< long double > gen3( complex< long double > x , complex< long double > y ){
	
	complex< long double > term1 = x;
	complex< long double > term2 = y;
	complex< long double > prev_result;
	complex< long double > result;
	long double n = 0.l;
	
	do{
		
		prev_result = result;
		result = ( 1.l / log( term1 ) ) - ( 1.l / log( term2 ) );
		term1 = cbwv( term1 );
		term2 = cbwv( term2 );
		n++;
		cout<<result<<" , "<<n<<endl;
		
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() );
	
	return result;
}

complex< long double > gen_norm( complex< long double > x , complex< long double > y ){
	
	complex< long double > term1 = x;
	complex< long double > term2 = y;
	complex< long double > prev_result;
	complex< long double > result;
	long double n = 0.l;
	
	do{
		
		prev_result = result;
		result = ( 1.l / log( term1 ) ) - ( 1.l / log( term2 ) );
		term1 = pow( term1 , term1 );
		term2 = pow( term2 , term2 );
		n++;
		//cout<<result<<" , "<<n<<endl;
		
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() );
	
	return result;
}

//1.29128599706266354043l
//0.783430510712134407141
//2.71911406130334180149

complex< long double > F( complex< long double > x ){
	
	complex< long double > log_x = log( x );
	complex< long double > term1 = x;
	complex< long double > term2 = 1.l;
	complex< long double > term3 = exp( 1.l );
	complex< long double > prev_result;
	complex< long double > result = 1.l;
	long double n = 0.l;
	
	do{
		
		prev_result = result;
		term1 = wave( term1 );
		term2 *= term1;
		term3 = wave( term3 );
		result *= ( 1.l + log_x / term2 ) / term3;
		n++;
		cout<<result<<" , "<<n<<endl;
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() );
	
	return result;
}

long double f( long double x , long double y ){
	
	return 1.l / ( x - 1.l ) - 1.l / ( y - 1.l );
	
}

/*long double eperNegative( unsigned int n ){
	
	if( n < 7896194 ){
		
		return atof( obtenerLinea( "e_waves.txt" , n ).c_str() );
		
	}
	
	long double x = n;
	
	return 1.l + 1.l / x + 1.l / ( 2.l * x * x ) + 1.l / ( x * pow( log( x ) , 5.l ) );
}*/

long double perPositivel( long double x , unsigned int n ){
	
	if( !n ){
		
		return x;
		
	}
	
	long double temp = perPositivel( x , n - 1 );
	
	return powl( temp , temp );
}

//aprox 1.22500054177327552995 , 100000
//aprox 1.21005832904873905317 , 200000
//aprox 1.20217204456013474064 , 300000
//aprox 1.19691416789635901715 , 400000
//aprox 1.19691416789635901715 , 500000

int main(){
	//1 + 1/n < e per -n < 1 + 2/n
	cout.precision( 21 );
	long double prev_result;
	long double result = 0.l;
	long double n = 14442.l;
	/*
	do{
		*/
		prev_result = result;
		result = log( perPositivel( asc( n , -1.l ) , n ) ) / log( asc( n , -1.l ) );
		/*
		for( int i = 0; i < n / 14443.l - 1.l; i++ ){
			
			result = perPositivel( result , 14443 );
			
		}
		*/
		result = result;
		
		/*if( int( n ) % 100 == 0 ){*/
			
			cout<<result<<" , "<<n<<endl;
			
		/*}
		
		n++;
		
	} while( abs( result - prev_result ) > numeric_limits< long double >::epsilon() );*/
	
	return 0;
}

#include"math.hpp"

namespace math{
	
	float sign( float x ){
		
		return x == 0.f ? std::numeric_limits< float >::quiet_NaN() : x < 0.f ? -1.f : 1.f;
		
	}
	
	double sign( double x ){
		
		return x == 0.0 ? std::numeric_limits< double >::quiet_NaN() : x < 0.0 ? -1.0 : 1.0;
		
	}
	
	long double sign( long double x ){
		
		return x == 0.l ? std::numeric_limits< long double >::quiet_NaN() : x < 0.l ? -1.l : 1.l;
		
	}
	
	float cos( float x ){
		
		return ::cosf( x );
		
	}
	
	double cos( double x ){
		
		return ::cos( x );
		
	}
	
	long double cos( long double x ){
		
		return ::cosl( x );
		
	}
	
	float sin( float x ){
		
		return ::sinf( x );
		
	}
	
	double sin( double x ){
		
		return ::sin( x );
		
	}
	
	long double sin( long double x ){
		
		return ::sinl( x );
		
	}
	
	float tan( float x ){
		
		return ::tanf( x );
		
	}
	
	double tan( double x ){
		
		return ::tan( x );
		
	}
	
	long double tan( long double x ){
		
		return ::tanl( x );
		
	}
	
	float sec( float x ){
		
		return 1.f / ::cosf( x );
		
	}
	
	double sec( double x ){
		
		return 1.0 / ::cos( x );
		
	}
	
	long double sec( long double x ){
		
		return 1.l / ::cosl( x );
		
	}
	
	float csc( float x ){
		
		return 1.f / ::sinf( x );
		
	}
	
	double csc( double x ){
		
		return 1.0 / ::sin( x );
		
	}
	
	long double csc( long double x ){
		
		return 1.l / ::sinl( x );
		
	}
	
	float cot( float x ){
		
		return 1.f / ::tanf( x );
		
	}
	
	double cot( double x ){
		
		return 1.0 / ::tan( x );
		
	}
	
	long double cot( long double x ){
		
		return 1.l / ::tanl( x );
		
	}
	
	float log( float x ){
		
		return ::logf( x );
		
	}
	
	double log( double x ){
		
		return ::log( x );
		
	}
	
	long double log( long double x ){
		
		return ::logl( x );
		
	}
	
	float exp( float x ){
		
		return ::expf( x );
		
	}
	
	double exp( double x ){
		
		return ::exp( x );
		
	}
	
	long double exp( long double x ){
		
		return ::expl( x );
		
	}
	
	float sqrt( float x ){
		
		return ::sqrtf( x );
		
	}
	
	double sqrt( double x ){
		
		return ::sqrt( x );
		
	}
	
	long double sqrt( long double x ){
		
		return ::sqrtl( x );
		
	}
	
	float cbrt( float x ){
		
		return ::cbrtf( x );
		
	}
	
	double cbrt( double x ){
		
		return ::cbrt( x );
		
	}
	
	long double cbrt( long double x ){
		
		return ::cbrtl( x );
		
	}
	
	float abs( float x ){
		
		return ::fabs( x );
		
	}
	
	double abs( double x ){
		
		return ::abs( x );
		
	}
	
	long double abs( long double x ){
		
		return ::labs( x );
		
	}
	
	float base_quiet_NaN( float x ){
		
		return std::numeric_limits< float >::quiet_NaN();
		
	}
	
	double base_quiet_NaN( double x ){
		
		return std::numeric_limits< double >::quiet_NaN();
		
	}
	
	long double base_quiet_NaN( long double x ){
		
		return std::numeric_limits< long double >::quiet_NaN();
		
	}
	
}

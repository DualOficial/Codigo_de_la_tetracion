//add functions

template< typename T >
void ApplicationPlot::add_func( T f , const Color & color , bool right , bool is_print ){
	
	RealFunction real_func;
	
	real_func.func = [ f ]( long double x ){ return f( x ); };
	real_func.color = color;
	real_func.is_print_text = is_print;
	real_func.right = right;

	real_functions.push_back( real_func );

}

template< typename T >
void ApplicationPlot::add_bi_func( T f , const Color & color , bool is_print ){
	
	add_func( f , color , true , is_print );
	add_func( f , color , false , is_print );

}

template< typename T >
void ApplicationPlot::add_complex_func( T f , long double angle , const Color & color , bool is_print ){
	
	ComplexFunction complex_func;
	
	complex_func.func = [ f ]( lcomplex x ){ return f( x ); };
	complex_func.angle = angle * constants::pi< long double >() / 180.l;
	complex_func.color = color;
	complex_func.is_print_text = is_print;

	complex_functions.push_back( complex_func );
	
}

template< typename T >
void ApplicationPlot::add_complex_func( T f , const Color & color , bool is_print ){
	
	ComplexFunction complex_func;
	
	complex_func.func = [ f ]( lcomplex x ){ return f( x ); };
	complex_func.angle = 0.l;
	complex_func.color = color;
	complex_func.is_print_text = is_print;

	complex_functions.push_back( complex_func );
	
}

template< typename T >
void ApplicationPlot::add_normal_func( T f , const Color & color , bool right , bool is_print ){
	
	ComplexFunction complex_func;
	
	if( right ){
		
		complex_func.func = [ f ]( lcomplex x ){ return f( x.real() ); };

	}
	else{
		
		complex_func.func = [ f ]( lcomplex x ){ return f( -x.real() ); };

	}

	complex_func.angle = 0.l;
	complex_func.color = color;
	complex_func.is_print_text = is_print;

	complex_functions.push_back( complex_func );

}

template< typename T >
void ApplicationPlot::add_bi_normal_func( T f , const Color & color , bool is_print ){
	
	add_normal_func( f , color , true , is_print );
	add_normal_func( f , color , false , is_print );

}

template< typename T >
void ApplicationPlot::add_bi_complex_func( T f , long double angle , const Color & color , bool is_print ){
	
	add_complex_func( f , angle , color , is_print );
	add_complex_func( f , angle + 180.l , color , is_print );
	
}

template< typename T >
void ApplicationPlot::add_bi_complex_func( T f , const Color & color , bool is_print ){
	
	add_complex_func( f , color , is_print );
	add_complex_func( f , 180.l , color , is_print );

}

template< typename T >
void ApplicationPlot::add_vector_func( T f , const Color & color , bool is_print ){
	
	VectorFunction vector_func;
	
	vector_func.func = [ f ]( lcomplex value ){ return f( value.real() ); };
	vector_func.color = color;
	vector_func.is_print_text = is_print;

	vector_functions.push_back( vector_func );

}

template< typename F >
void TestFunc( F && f , long double init , long double increment ){
	
	while( true ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

template< typename F >
void TestFuncFinite( F && f , long double init , long double increment , long double max ){
	
	while( abs( init ) < max ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}
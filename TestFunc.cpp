#include"TestFunc.hpp"
#include<iostream>

void TestFunc( function< lcomplex( long double ) > f , long double init , long double increment ){
	
	while( true ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

void TestFunc( function< long double( long double ) > f , long double init , long double increment ){
	
	while( true ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

void TestFunc( function< lcomplex( lcomplex ) > f , long double init , long double increment ){
	
	while( true ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

void TestFuncFinite(  function< long double( long double ) > f , long double init , long double increment , long double max ){
	
	while( abs( init ) < max ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

void TestFuncFinite( function< lcomplex( lcomplex ) > f , long double init , long double increment , long double max ){
	
	while( abs( init ) < max ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

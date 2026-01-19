#include"TestFunc.hpp"
#include<iostream>

void TestFunc( lcomplex ( * f )( long double ) , long double init , long double increment ){
	
	while( true ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

void TestFunc( long double ( * f )( long double ) , long double init , long double increment ){
	
	while( true ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

void TestFunc( lcomplex ( * f )( lcomplex ) , long double init , long double increment ){
	
	while( true ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

void TestFuncFinite(  long double ( * f )( long double ) , long double init , long double increment , long double max ){
	
	while( abs( init ) < max ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}

void TestFuncFinite(  lcomplex ( * f )( lcomplex ) , long double init , long double increment , long double max ){
	
	while( abs( init ) < max ){
		
		cout<<f( init )<<" , "<<init<<endl;
		
		init += increment;
	}

}
#pragma once

//CREDITOS A https://github.com/lukaszgryglicki/cpptet
//Esto implementa el metodo de kuznetsob, que no entiendo todavia, pero aqui lo tienen por comodidad ;)

#include"definitions.hpp"

namespace kuz{
	
	template< typename T >
	T slo( T z1 );

	template< typename T >
	T tet_gen( T z1 );

	template< typename T >
	T fima( T z );

	template< typename T >
	T tai3( T z );

	template< typename T >
	T maclo( T z );

	template< typename T >
	T FIMA( T z );

	template< typename T >
	T TAI3( T z );

	template< typename T >
	T MACLO( T z );

	template< typename T >
	T tet( T z );

	template< typename T >
	T tet( T final_exp , T height );

}

#include"kuznetsob.inl"

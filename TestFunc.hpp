#pragma once

#include"definitions.hpp"

void TestFunc( lcomplex ( * f )( long double ) , long double init , long double increment );
void TestFunc( long double ( * f )( long double ) , long double init , long double increment );
void TestFunc( lcomplex ( * f )( lcomplex ) , long double init , long double increment );
void TestFuncFinite(  long double ( * f )( long double ) , long double init , long double increment , long double max );
void TestFuncFinite(  lcomplex ( * f )( lcomplex ) , long double init , long double increment , long double max );

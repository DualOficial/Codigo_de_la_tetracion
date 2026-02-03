#pragma once

#include"definitions.hpp"

void TestFunc( function< lcomplex( long double ) > f , long double init , long double increment );
void TestFunc( function< long double( long double ) > f , long double init , long double increment );
void TestFunc( function< lcomplex( lcomplex ) > f , long double init , long double increment );
void TestFuncFinite(  function< long double( long double ) > f , long double init , long double increment , long double max );
void TestFuncFinite(  function< lcomplex( lcomplex ) > f , long double init , long double increment , long double max );

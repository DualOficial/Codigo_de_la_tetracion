#pragma once

#include"definitions.hpp"

template< typename F >
void TestFunc( F && f , long double init , long double increment );

template< typename F >
void TestFuncFinite(  F && f , long double init , long double increment , long double max );

#include"TestFunc.inl"

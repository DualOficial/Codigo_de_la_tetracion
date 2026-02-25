#pragma once

#include"definitions.hpp"
#include"successions.hpp"

template< typename F >
auto Near( F && f , unsigned int complexity = 1000 );

template< typename F , typename G >
auto PolyTransform( F && f , G && t , unsigned int complexity = 150 );

#include"near.inl"
#pragma once

#include"definitions.hpp"

template< typename T >
T zexpz( T z );

template< typename T >
T zexpz_d( T z );

template< typename T >
T zexpz_dd( T z );

template< typename T >
T InitPoint( T z, int k);

extern int wlambert_complexity; //con 30 iteraciones ya es suficiente precisión

template< no_number_dual T >
T wlambert( T z , int k = 0 );
//alhorithm

template< typename T >
Formula< T >::Formula() : monomials(){
	
	//nothing

}

template< typename T >
void Formula< T >::insert( unsigned int n , const T & constant ){
	
	auto i = monomials.find( n );

	if( i == monomials.end() ){
		
		monomials.insert( make_pair( n , constant ) );

		return;
	}

	i->second += constant;
}

template< typename T >
Formula< T > Simplify( const Formula< T > & formula ){
	
	Formula< T > result;
	bool flag = false;

	for( const auto & m : formula.monomials ){
		
		for( auto & k : result.monomials ){
			
			if( k.first == m.first ){
				
				k.second += m.second;
				flag = true;

				break;
			}

		}

		if( !flag ){
			
			result.monomials.insert( m );

		}

		flag = false;
	}

	return result;
}

template< typename T >
Formula< T > & Formula< T >::operator=( const Formula< T > & other ){
	
	monomials = other.monomials;

	return *this;
}

template< typename T >
Formula< T > operator+( Formula< T > first , const Formula< T > & second ){
	
	for( const auto & m : second.monomials ){
		
		first.insert( m.first , m.second );

	}

	return first;
}

template< typename T >
Formula< T > & operator+=( Formula< T > & first , const Formula< T > & second ){
	
	return first = first + second;

}

template< typename T >
Formula< T > operator*( const Formula< T > first , const Formula< T > & second ){
	
	Formula< T > result;

	for( const auto & m1 : first.monomials ){
		
		for( const auto & m2 : second.monomials ){
			
			result.insert( m1.first + m2.first , m1.second * m2.second );

		}

	}

	return result;
}

template< typename T >
Formula< T > & operator*=( Formula< T > & first , const Formula< T > & second ){
	
	return first = first * second;

}

template< typename T >
Formula< T > pow( const Formula< T > & f , unsigned int n ){
	
	Formula< T > result;

	result.monomials.insert( make_pair( 0 , T( 1 ) ) );

	while( n > 0 ){
		
		result *= f;

		n--;
	}

	return result;
}

template< typename T >
T Compute( const Formula< T > & formula , const T & accelo , const T & base , const T & alpha_value ){
	
	T result;

	for( const auto & m : formula.monomials ){
		
		result += pow( alpha_value * log( base ) , accelo * T( m.first ) ) * m.second;

	}

	return result;
}

template< typename T >
T Compute( const Formula< T > & formula , const T & accelo , const T & alpha_value ){
	
	T result;

	for( const auto & m : formula.monomials ){
		
		result += pow( alpha_value , accelo * T( m.first ) ) * m.second;

	}

	return result;
}

template< typename T >
Formula< T > Extension( Formula< T > formula , const T & base , const T & alpha_value ){
	
	T sum_constants;

	for( auto & m : formula.monomials ){
		
		m.second /= pow( alpha_value * log( base ) , T( m.first ) ) - T( 1 );

		sum_constants += m.second;
	}

	formula.insert( 0 , -sum_constants );

	return formula;
}

template< typename T >
Formula< T > Extension( Formula< T > formula , const T & alpha_value ){
	
	T sum_constants;

	for( auto & m : formula.monomials ){
		
		m.second /= pow( alpha_value , T( m.first ) ) - T( 1 );

		sum_constants += m.second;
	}

	formula.insert( 0 , -sum_constants );

	return formula;
}

template< typename T >
Formula< T > Resolve( const Sum & sum , const vector< Formula< T > > & prev_formulas , const T & base , const T & alpha_value ){
	
	if( prev_formulas.empty() ){
		
		Formula< T > result;

		result.monomials.insert( make_pair( 1 , T( 1 ) ) );

		return result;
	}

	if( prev_formulas.size() == 1 ){
		
		Formula< T > result;

		T constant = log( base ) / ( alpha_value * log( base ) - T( 1 ) );

		result.monomials.insert( make_pair( 1 , -constant ) );
		result.monomials.insert( make_pair( 2 , constant ) );

		return result;
	}

	Formula< T > result;

	for( const Product & product : sum.products ){
		
		Formula< T > f;

		f.monomials.insert( make_pair( 1 , T( product.constant ) ) );
		
		for( const auto & i : product.elements ){
			
			f *= pow( Extension( prev_formulas[ i.first ] , base , alpha_value ) , i.second );
			
		}

		result += f;
	}

	return result;
}

template< typename T >
Formula< T > Resolve( const Sum & sum , const vector< Formula< T > > & prev_formulas , const T & alpha_value ){
	
	if( prev_formulas.empty() ){
		
		Formula< T > result;

		result.monomials.insert( make_pair( 1 , T( 1 ) ) );

		return result;
	}

	Formula< T > result;

	for( const Product & product : sum.products ){
		
		Formula< T > f;

		f.monomials.insert( make_pair( 1 , T( product.constant ) ) );
		
		for( const auto & i : product.elements ){
			
			f *= pow( Extension( prev_formulas[ i.first ] , alpha_value ) , i.second );
			
		}

		result += f;
	}

	return result;
}

//functions

template< typename T >
T alpha_tet( const T & base ){
	
	if( base == exp( real_type< T >( 1 ) ) ){
		
		T z = 2;
		T prev_z;

		do{
			
			prev_z = z;
			z = log( z );

		} while( abs( z - prev_z ) > std::numeric_limits< real_type< T > >::epsilon() );
		
		return z;
	}

	if( abs( base ) < real_type< T >( 1 ) ){
		
		T z = 2;
		T prev_z;

		do{
			
			prev_z = z;
			z = pow( base , z );

		} while( abs( z - prev_z ) > std::numeric_limits< real_type< T > >::epsilon() );
		
		return z;
	}
	
	T z = ( base == T( 2 ) ? 3 : 2 );
	T prev_z;

	do{
		
		prev_z = z;
		z = log( base , z );

	} while( abs( z - prev_z ) > std::numeric_limits< real_type< T > >::epsilon() );
	
	return z;
}

template< typename T >
T alpha_tet( const T & base , const T & test_value ){
	
	if( base == exp( T( 1 ) ) ){
		
		T z = test_value;
		T prev_z;

		do{
			
			prev_z = z;
			z = log( z );

		} while( abs( z - prev_z ) > std::numeric_limits< real_type< T > >::epsilon() );
		
		return z;
	}

	if( abs( base ) < real_type< T >( 1 ) ){
		
		T z = 2;
		T prev_z;

		do{
			
			prev_z = z;
			z = pow( base , z );

		} while( abs( z - prev_z ) > std::numeric_limits< real_type< T > >::epsilon() );
		
		return z;
	}
	
	T z = test_value;
	T prev_z;

	do{
		
		prev_z = z;
		z = log( base , z );

	} while( abs( z - prev_z ) > std::numeric_limits< decltype( base.real() ) >::epsilon() );
	
	return z;
}

template< typename T >
T tet( const T & base , const T & final_exp , T height , const T & v ){
	
	if( tetration_recursive ){
		
		auto half = real_type< T >( 0.5 );

		if( real_value( height ) < real_value( v ) - half ){
			
			int a = ( int ) floor( real_value( height ) - ( real_value( v ) - half ) );

			height = height - T( a );

			return tetration_integer( base , tet( base , final_exp , height , v ) , a );
		}
		
		if( real_value( height ) > real_value( v ) + half ){
			
			int a = ( int ) floor( real_value( height ) - ( real_value( v ) - half ) );

			height = height - T( a );

			return tetration_integer( base , tet( base , final_exp , height , v ) , a );
		}

	}

	if( abs( base ) < real_type< T >( 1 ) ){
		
		if( tetration_recursive ){
			
			if( abs( final_exp - v ) > real_type< T >( 1 ) ){
				
				return log( base , tet( base , pow( base , final_exp ) , height , v ) );

			}
			
		}
		
		T a = v - T( 1 );
		T b = tetration_integer( base , final_exp , tetration_complexity ) - a;
		
		T log_base = log( base );
		T c = T( 1 ) / ( v * log_base );
		T d = pow( c , -height );
		T x = ( -d * log_base * ( d - T( 1 ) ) / ( c - T( 1 ) ) - c + T( 1 ) ) / T( 2 );

		return tetration_integer( base , pow( b , d * pow( b , x ) ) + a , -tetration_complexity );
	}
	
	if( tetration_recursive ){
		
		if( abs( final_exp - v ) > real_type< T >( 1 ) ){
			
			return pow( base , tet( base , log( base , final_exp ) , height , v ) );

		}
		
	}

	if( base == exp( exp( -T( 1 ) ) ) ) return natural_tet( final_exp , height );
	
	T a = v - T( 1 );
	T b = tetration_integer( base , final_exp , -tetration_complexity ) - a;
	
	T log_base = log( base );
	T c = v * log_base;
	T d = pow( c , height );
	T x = ( log_base * ( d - T( 1 ) ) / ( c - T( 1 ) ) - d + T( 1 ) ) / T( 2 );

	return tetration_integer( base , pow( b , d * pow( b , x ) ) + a , tetration_complexity );
}

template< typename T >
T tet( const T & base , const T & final_exp , const T & height ){
	
	return tet( base , final_exp , height , alpha_tet( T( 2 ) , final_exp ) );
	
}

template< typename T >
T tet_e( const T & final_exp , T height , const T & v ){
	
	if( tetration_recursive ){
		
		if( abs( final_exp - v ) > real_type< T >( 1 ) ){
			
			return exp( tet_e( log( final_exp ) , height , v ) );

		}

		auto half = real_type< T >( 0.5 );

		if( real_value( height ) < real_value( v ) - half ){
			
			int a = ( int ) floor( real_value( height ) - ( real_value( v ) - half ) );

			height = height - T( a );

			return e_tetration_integer( tet_e( final_exp , height , v ) , a );
		}
		
		if( real_value( height ) > real_value( v ) + half ){
			
			int a = ( int ) floor( real_value( height ) - ( real_value( v ) - half ) );

			height = height - T( a );

			return e_tetration_integer( tet_e( final_exp , height , v ) , a );
		}
		
	}

	T a = v - T( 1 );
	T b = e_tetration_integer( final_exp , -tetration_complexity ) - a;
	
	T c = v;
	T d = pow( c , height );
	T x = ( ( d - T( 1 ) ) / ( c - T( 1 ) ) - d + T( 1 ) ) / T( 2 );

	return e_tetration_integer( pow( b , d * pow( b , x ) ) + a , tetration_complexity );
}

template< typename T >
T tet_e( const T & final_exp , const T & height ){
	
	return tet_e( final_exp , height , alpha_tet( exp( T( 1 ) ) , final_exp ) );
	
}

template< typename T >
T tet_gen( const T & base , const T & final_exp , T result , const T & v ){
	
	if( abs( base ) < real_type< T >( 1 ) ){
		
		T a = tetration_integer( base , result , tetration_complexity ) - v;
		T b = tetration_integer( base , final_exp , tetration_complexity ) - v;

		return log( v * log( base ) , a / b );
	}

	if( base == exp( exp( -T( 1 ) ) ) ) return natural_gen( final_exp , result );

	T a = tetration_integer( base , result , -tetration_complexity ) - v;
	T b = tetration_integer( base , final_exp , -tetration_complexity ) - v;

	return log( v * log( base ) , a / b );
}

template< typename T >
T tet_gen( const T & base , const T & final_exp , T result ){
	
	return tet_gen( base , final_exp , result , alpha_tet( base , final_exp ) );

}

template< typename T >
T tet_gen_e( const T & final_exp , const T & result , const T & v ){
	
	T a = e_tetration_integer( result , -tetration_complexity ) - v;
	T b = e_tetration_integer( final_exp , -tetration_complexity ) - v;

	return log( v , a / b );
}

template< typename T >
T tet_gen_e( const T & final_exp , const T & result ){
	
	return tet_gen_e( final_exp , result , alpha_tet( exp( T( 1 ) ) ) , final_exp );

}

template< typename T >
T exphalf( T z , const T & alpha_value ){
	
	if( tetration_recursive ){
		
		if( abs( z - alpha_value ) > real_type< T >( 1 ) ){
			
			return exp( exphalf( log( z ) , alpha_value ) );

		}

	}

	static array< T , 27 > array = {
		
		T( complex50("0.3181315052047641353126542515876645172035176138714048","1.337235701430689408901162143193710612539502138460512") ),
		T( complex50("0.9199697049219804666911757744245158931410482535237969","0.7267824659204923854082068222411697217046000669303214") ),
		T( complex50("0.5444367456232741730929185975307049552351030330982572","0.1724482342350999088234068362168849809363841189336084") ),
		T( complex50("0.106843471264890473486350283313987538045207061648842","0.01561652155827337058224752889043212152935044566232995") ),
		T( complex50("0.07854540011851279382553022631119705847055083506699241","-0.0153719367584218146670885277041829163939047199664483") ),
		T( complex50("-0.2200800373124322989203643809392675290604041453002812","0.3462963293875575843422664833538908442712751927691642") ),
		T( complex50("-2.260877518676347551574262187863194448379234307425556","-2.14984109358418163257080589123723099208616200444634") ),
		T( complex50("12.93619654604917863910128794422093580411618005796299","-15.73739998426389404937352562922178004592996414521458") ),
		T( complex50("102.0806788959624167985822954838644622368405134093014","66.60699178177363017703030419078339910504476277730122") ),
		T( complex50("-332.3254830079439108652838753257195919134465963143308","622.3460361371498993078956970797815864547496721264637") ),
		T( complex50("-3596.497762300994532171737195139250573935943218156936","-1735.732011083951115573103066331340335964272219473825") ),
		T( complex50("10267.51097622702274205975997761836242666483027085977","-18976.00067295173643159991057539999061253810711280539") ),
		T( complex50("76508.95489387618227964010375682886326650562991069394","74965.20259892646511120789817795374620970115965341005") ),
		T( complex50("-696929.6074541035097968878310956726506239687580339685","-37941.54586540734530719872720546109848820662525732873") ),
		T( complex50("6550459.660496413392559977862522729043217666917127941","-7715864.137420130646770329174223065415614081718105144") ),
		T( complex50("92272836.40288271068572711084220778757830040200531182","117377123.745022922220926962796933007696565642961146") ),
		T( complex50("-1651062067.990868591409789519481465292972588422694699","1113389060.693196703867320285433657818707674717531323") ),
		T( complex50("-12989368634.93378871840204307544923305910291376589462","-21284867369.95333360405699661223329611404051063516819") ),
		T( complex50("264179424056.6065703828256447308607516270662162860089","-140322602681.7565058434977778041329835249250261026463") ),
		T( complex50("1281835054286.353441946077638089876313629280175191131","3228149057207.492508462704607066943930231009926554322") ),
		T( complex50("-39123975489992.60325917664247778957362354396422970695","6617169790981.837991981713821262692896484036685581484") ),
		T( complex50("94997691777216.90024195223236985247533615976989829353","-469383256220414.5392912394641008308820257036802209032") ),
		T( complex50("5663118041530312.080481394568697902353795145056943259","4497791639054646.489959870904936485123227991485725259") ),
		T( complex50("-114563148775708181.0683043330974061203015031976881757","61695369769802191.52301098722727616892960152140093478") ),
		T( complex50("-487075561715334732.7872809687163018438172638618192433","-2414894575857040942.047002429527327817639099584259605") ),
		T( complex50("44762991880007564453.05379278466787776630600595745202","-2232774523395700183.188635458807696255514606507753085") ),
		T( complex50("16014318633038950247.44442878825347844656360128937067","725222939587673131870.661223544154437311704309778185") )

	};

	z -= alpha_value;

	T result;
	T term = 1;

	for( unsigned int i = 0; i < array.size(); i++ ){
		
		result += term * array[ i ];
		term *= z / T( i + 1 );

	}

	return result;
}

template< typename T >
T exphalf( const T & z ){
	
	return exphalf( z , alpha_tet( exp( T( 1 ) ) , z ) );

}

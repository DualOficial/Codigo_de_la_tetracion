#include"tetration.hpp"

Sum::Sum() : products(){
	
	//nothing

}

void Sum::insert( const Product & product ){
	
	for( Product & a : products ){
		
		if( a.elements == product.elements ){
			
			a.constant += product.constant;

			return;
		}

	}

	products.push_back( product );

}

Sum Derivate( const Sum & sum ){
	
	if( sum.products.empty() ){
		
		Sum result;
		Product product;

		product.elements.insert( make_pair( 0 , 1 ) );

		result.products.push_back( product );

		return result;
	}

	Sum result;

	for( const Product & product : sum.products ){
		
		for( const auto & i : product.elements ){
			
			Product a = product;

			if( i.second - 1 == 0 ){
				
				a.elements.erase( i.first );

			}
			else{
				
				a.elements[ i.first ] -= 1;

			}

			a.constant *= i.second;
			a.insert( i.first + 1 , 1 );

			result.insert( a );
		}

		Product a = product;

		a.insert( 0 , 1 );

		result.insert( a );
	}

	return result;
}

void Print( const Sum & sum ){
	
	for( unsigned int i = 0; i < sum.products.size(); i++ ){
		
		auto & r = sum.products[ i ];

		if( r.constant != 1 ) cout<<r.constant<<" * ";

		for( auto j = r.elements.begin(); j != r.elements.end(); ){
			
			cout<<"S"<<j->first;

			if( j->second != 1 ) cout<<"^"<<j->second;

			j++;

			if( j != r.elements.end() ) cout<<" * ";

		}

		if( i != sum.products.size() - 1 ) cout<<" + ";
		
	}

	cout<<endl;

}

Product::Product() : elements() , constant( 1 ){
	
	//nothing

}

void Product::insert( unsigned int index , unsigned int power ){
	
	auto i = elements.find( index );

	if( i == elements.end() ) elements.insert( make_pair( index , power ) );

	i->second += power;

}

int tetration_complexity = 20;
bool tetration_recursive = true;

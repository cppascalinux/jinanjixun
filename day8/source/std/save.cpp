#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <algorithm>
#define MAXN 100010
#define ratio 4
#define new_LTT( s , v , r , a , b ) ( & ( * st1[ cnt1++ ] = Node( s , v , r , a , b ) ) )
#define new_Trie( s , v , r , p , d , a , b ) ( & ( * st2[ cnt2++ ] = Node( s , v , r , p , d , a , b ) ) )
#define merge( a , b ) new_LTT( a -> size + b -> size , a -> value ^ b -> value , 0 , a , b )

using namespace std;

int n , m , cnt1 , cnt2 , num , a[ MAXN ];

#define Node Trie

struct Node
{
	int size , value , real , path , xortag;
	char sorttag , dep;
	Node * left , * right;
	Node( int s , int v , int r , int p , char d , Node * a , Node * b ) : size( s ) , value( v ) , real( r ) , path( p ) , dep( d ) , left( a ) , right( b ) , sorttag( 0 ) , xortag( 0 ) {}
	Node() {}
	inline Node * only_child()
	{
		if( left && !right ) return left;
		if( right && !left ) return right;
		return 0;
	}
	inline void bicompress()
	{
		
	}
	inline void decompress();
	inline void compress();
	inline void Xor( int x )
	{
		xortag ^= x , real ^= x , path ^= x >> dep + 1 & 1;
		if( size & 1 ) value ^= x;
	}
	inline void sort()
	{
		decompress();
		sorttag = 1;
		if( xortag )
		{
			left ? left -> Xor( xortag ) : void();
			right ? right -> Xor( xortag ) : void();
			xortag = 0;
		}
		if( ( left && left -> path ) || ( right && !right -> path ) )
			swap( left , right );
	}
	inline void pushdown()
	{
		decompress();
		if( sorttag )
			left ? left -> sort() : void() , right ? right -> sort() : void() , sorttag = 0;
		if( xortag )
			left ? left -> Xor( xortag ) : void() , right ? right -> Xor( xortag ) : void() , xortag = 0;
	}
	inline void update()
	{
		if( left || right )
		{
			size = value = 0;
			if( left ) size += left -> size , value ^= left -> value;
			if( right ) size += right -> size , value ^= right -> value;
		}
	}
} t2[500000] , * st2[500000];

inline void Trie :: decompress()
{
	bool f = 0;
	if( left && !right && left -> dep != dep - 1 )
	{
		Node * cur = left;
		int d = cur -> path >> dep - cur -> dep - 1 & 1 ;
		f = cur -> path >> dep - cur -> dep - 2 & 1 ;
		cur -> path &= ~( 1 << dep - cur -> dep - 1 );
		left = new_Trie( left -> size , left -> value , 0 , d , dep - 1 , 0 , 0 );
		if( f ) left -> right = cur;
		else left -> left = cur;
	}
	if( right && !left && right -> dep != dep - 1 )
	{
		Node * cur = right;
		int d = cur -> path >> dep - cur -> dep - 1 & 1 ;
		f = cur -> path >> dep - cur -> dep - 2 & 1 ;
		cur -> path &= ~( 1 << dep - cur -> dep - 1 );
		right = new_Trie( right -> size , right -> value , 0 , d , dep - 1 , 0 , 0 );
		if( f ) right -> right = cur;
		else right -> left = cur;
	}
}

inline void Trie :: compress()
{
	Node * a = only_child();
	if( a && !a -> xortag && !a -> sorttag )
	{
		Node * b = a -> only_child();
		if( b )
		{
			int path = ( a -> path << a -> dep - b -> dep ) | b -> path;
			* a = * b;
			a -> path = path;
			st2[ --cnt2 ] = b;
		}
	}
}

inline Node * make_Trie( int x )
{
	Node * real = new_Trie( 1 , x , x , x , -1 , 0 , 0 );
	return new_Trie( 1 , x , x , 0 , 29 , real , 0 );
}
	
Node * Merge( Node * a , Node * b )
{
	if( !a ) return b;
	if( !b ) return a;
	a -> pushdown() , b -> pushdown();
	a -> size += b -> size , a -> value ^= b -> value;
	a -> left = Merge( a -> left , b -> left );
	a -> right = Merge( a -> right , b -> right );
	st2[ --cnt2 ] = b;
	a -> compress();
	return a;
}

pair < Node * , Node * > split( int x , Node * cur )
{
	cur -> pushdown();
	if( !cur -> left && !cur -> right )
		return pair < Node * , Node * > ( new_Trie( x , ( x & 1 ) * cur -> real , cur -> real , cur -> path , -1 , 0 , 0 ) , new_Trie( cur -> size - x , ( cur -> size - x & 1 ) * cur -> real , cur -> real , cur -> path , -1 , 0 , 0 ) );
	if( !cur -> left || x > cur -> left -> size )
	{
		pair < Node * , Node * > a = split( x - ( cur -> left ? cur -> left -> size : 0 ) , cur -> right );
		cur -> right = a.first , cur -> update() , a.first = cur , a.second = new_Trie( a.second -> size , a.second -> value , 0 , 0 , a.second -> dep + 1 , 0 , a.second );
		a.second -> path = cur -> path; 
		a.first -> compress() , a.second -> compress();
		return a;
	}
	if( x < cur -> left -> size )
	{
		pair < Node * , Node * > a = split( x , cur -> left );
		cur -> left = a.second , cur -> update() , a.second = cur , a.first = new_Trie( a.first -> size , a.first -> value , 0 , 0 , a.first -> dep + 1 , a.first , 0 );
		a.first -> path = cur -> path;
		a.first -> compress() , a.second -> compress();
		return a;
	}
	if( !cur -> right ) return pair < Node * , Node * > ( cur , 0 );
	Node * a = new_Trie( cur -> right -> size , cur -> right -> value , 0 , cur -> path , cur -> dep , 0 , cur -> right );
	* cur = Trie( cur -> left -> size , cur -> left -> value , 0 , cur -> path , cur -> dep , cur -> left , 0 );
	return pair < Node * , Node * > ( cur , a );
}

#undef Node

#define Node LazyTagTree

struct Node
{
	int size , value , xortag;
	Node * left , * right;
	Trie * root;
	Node( int s , int v , Trie * path , Node * a , Node * b ) : size( s ) , value( v ) , root( path ) , left( a ) , right( b ) , xortag( 0 ) {}
	Node() {}
	inline void Xor( int x )
	{
		xortag ^= x;
		if( size & 1 ) value ^= x;
	}
	inline void pushdown()
	{
		if( xortag )
		{
			if( left -> size ) left -> Xor( xortag ) , right -> Xor( xortag );
			else root -> Xor( xortag ) , value = root -> value;
			xortag = 0;
		}
	}
	inline void update()
	{
		if( left -> size )
			size = left -> size + right -> size , value = left -> value ^ right -> value;
	}
} * root , * o[ MAXN ] , * null , * st1[300000] , t1[300000];

void split( int x , Node * cur )
{
	cur -> pushdown();
	if( !cur -> left -> size )
	{
		pair < Trie * , Trie * > a = split( x , cur -> root );
		cur -> left = new_LTT( x , a.first -> value , a.first , null , null ) , cur -> right = new_LTT( cur -> size - x , a.second -> value , a.second , null , null );
	}
	if( x > cur -> left -> size ) split( x - cur -> left -> size , cur -> right ) , cur -> left = merge( cur -> left , cur -> right -> left ) , st1[ --cnt1 ] = cur -> right , cur -> right = cur -> right -> right;
	else if( x < cur -> left -> size ) split( x , cur -> left ) , cur -> right = merge( cur -> left -> right , cur -> right ) , st1[ --cnt1 ] = cur -> left , cur -> left = cur -> left -> left;
	cur -> update();
}

inline Node * get_interval( int l , int r )
{
	return split( r + 1 , root ) , split( l , root -> left ) , root -> left -> right;
}

void dfs( Node * cur )
{
	cur -> pushdown() , cur -> update();
	if( !cur -> left -> size ) o[ num++ ] = cur;
	else dfs( cur -> left ) , dfs( cur -> right );
}

void dispose( Node * cur )
{
	if( cur -> left -> size ) st1[ --cnt1 ] = cur -> left , st1[ --cnt1 ] = cur -> right , dispose( cur -> left ) , dispose( cur -> right );
}

Node * build( int l , int r )
{
	if( l == r ) return new_LTT( 1 , a[l] , make_Trie( a[l] ) , null , null );
	Node * left = build( l , l + r >> 1 ) , * right = build( ( l + r >> 1 ) + 1 , r );
	return merge( left , right );
}

#define cur root -> left -> right

struct io
{
	char ibuf[1 << 22] , * s , obuf[1 << 20] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "save.in" , "r" , stdin );
		freopen( "save.out" , "w" , stdout );
		fread( s = ibuf , 1 , 1 << 22 , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( !isdigit( * s ) ) s++;
		while( isdigit( * s ) )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( T u , int v )
	{
		print( u );
		* t++ = v;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			if( u < 0 )
				* t++ = 45 , u *= -1;
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = 10;
	}
} ip;

#define read ip.read
#define print ip.print

inline void init_LazyTagTree()
{
	for( register int i = 0 ; i < 300000 ; i++ ) st1[i] = & t1[i];
	for( register int i = 0 ; i < 500000 ; i++ ) st2[i] = & t2[i];
	++++n;
	for( int i = 2 ; i <= n - 1 ; i++ ) a[i] = read();
	a[1] = a[n] = 0;
	null = new_LTT( 0 , 0 , 0 , 0 , 0 );
	root = build( 1 , n );
}

inline void Sort( int l , int r )
{
	num = 0;
	dfs( get_interval( l , r ) );
	o[0] -> root -> sort();
	for( int i = 1 ; i < num ; i++ )
		o[i] -> root -> sort() , o[0] -> root = Merge( o[0] -> root , o[i] -> root );
	dispose( cur ) , * cur = Node( cur -> size , o[0] -> root -> value , o[0] -> root , null , null );
}

inline void Xor( int l , int r , int x )
{
	get_interval( l , r ) -> Xor( x );
}

inline int find( int l , int r )
{
	return get_interval( l , r ) -> value;
}

int main()
{
	n = read() , m = read();
	init_LazyTagTree();
	while( m-- )
	{
		int opt = read() , l = read() , r = read();
		if( opt == 1 )
			Xor( l , r , read() );
		else if( opt == 2 )
			Sort( l , r );
		else
			print( find( l , r ) );
	}
	return 0;
}

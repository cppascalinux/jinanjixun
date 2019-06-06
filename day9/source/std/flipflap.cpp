#include <iostream>
#include <set>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
#define MAXN 100010

using namespace std;

int n , m , now_pos;
long long memory_pool[ MAXN * 5 ];
vector < int > q;
vector < pair < int , int > > map[ MAXN ];

inline long long * get_memory( int x )
{
	now_pos += x;
	return memory_pool + now_pos - x;
}

struct block
{
	int n , block;
	long long * a , * b , * tag;
	inline void assign( int x )
	{
		n = x , block = sqrt( n * 0.1 ) + 1;
		a = get_memory( n + 3 );
		b = get_memory( n + 3 );
		tag = get_memory( n / block + 3 );
	}
	inline int pos( int x )
	{
		return ( x - 1 ) / block + 1;
	}
	inline void build( int x )
	{
		int l = ( x - 1 ) * block + 1 , r = min( x * block , n );
		for( register int i = l ; i <= r ; i++ )
			b[i] = a[i];
		sort( b + l , b + r + 1 );
	}
	inline void modify( int l , int r , long long v , long long x , long long y )
	{
		l++ , r++;
		if( l > r ) return;
		a[l] += x - v;
		if( l != r ) a[r] += y - v;
		if( pos( l ) == pos( r ) )
		{
			for( register int i = l ; i <= r ; i++ )
				a[i] += v;
			build( pos( l ) );
		}
		else
		{
			for( register int i = l ; i <= pos( l ) * block ; i++ ) a[i] += v;
			for( register int i = ( pos( r ) - 1 ) * block + 1 ; i <= r ; i++ ) a[i] += v;
			for( register int i = pos( l ) + 1 ; i <= pos( r ) - 1 ; i++ ) tag[i] += v;
			build( pos( l ) ) , build( pos( r ) );
		}
	}
	inline int find( int l , int r , int v )
	{
		l++ , r++;
		if( l > r ) return 0;
		register int ans = 0;
		if( pos( l ) == pos( r ) )
			for( register int i = l , j = pos( i ) ; i <= r ; i++ )
				ans += a[i] <= v - tag[ pos( i ) ];
		else
		{
			for( register int i = l ; i <= pos( l ) * block ; i++ ) ans += a[i] <= v - tag[ pos( i ) ];
			for( register int i = ( pos( r ) - 1 ) * block + 1 ; i <= r ; i++ ) ans += a[i] <= v - tag[ pos( i ) ];
			for( register int i = pos( l ) + 1 ; i <= pos( r ) - 1 ; i++ )
				if( b[ min( i * block , n ) ] <= v - tag[i] )
					ans += min( i * block , n ) - ( i - 1 ) * block;
				else if( b[ ( i - 1 ) * block + 1 ] <= v - tag[i] )
					ans += upper_bound( b + ( i - 1 ) * block + 1 , b + min( i * block , n ) + 1 , v - tag[i] ) - ( b + ( i - 1 ) * block + 1 );
		}
		return ans;
	}
} block[50];

inline int read()
{
	register int x = 0;
	register char v = 1 , ch = getchar();
	while( !isdigit( ch ) )
	{
		if( ch == '-' ) v = -1;
		ch = getchar();
	}
	while( isdigit( ch ) ) x = x * 10 + ch - '0' , ch = getchar();
	return x * v;
}

void build( int l , int r )
{
	if( !map[ r - l + 1 ].size() ) q.push_back( r - l + 1 );
	map[ r - l + 1 ].push_back( pair < int , int > ( l , r ) );
	if( l != r ) build( l , l + r >> 1 ) , build( ( l + r >> 1 ) + 1 , r );
}

inline void init()
{
	for( int i = 0 ; i < q.size() ; i++ )
		sort( map[ q[i] ].begin() , map[ q[i] ].end() ) , block[i].assign( map[ q[i] ].size() );
}

inline int get_sec( int l1 , int r1 , int l2 , int r2 )
{
	if( l1 > l2 ) swap( l1 , l2 ) , swap( r1 , r2 );
	if( r1 < l2 ) return 0;
	if( r1 >= l2 && r1 <= r2 ) return r1 - l2 + 1;
	return r2 - l2 + 1;
}

inline void modify( int l , int r , int a )
{
	for( int i = 0 ; i < q.size() ; i++ )
	{
		int L = lower_bound( map[ q[i] ].begin() , map[ q[i] ].end() , pair < int , int > ( l , n + 1 ) ) - map[ q[i] ].begin() - 1 , R = lower_bound( map[ q[i] ].begin() , map[ q[i] ].end() , pair < int , int > ( r , n + 1 ) ) - map[ q[i] ].begin() - 1;
		block[i].modify( L , R , a * 1ll * q[i] , a * 1ll * get_sec( map[ q[i] ][L].first , map[ q[i] ][L].second , l , r ) , a * 1ll * get_sec( map[ q[i] ][R].first , map[ q[i] ][R].second , l , r ) );
	}
}

inline int find( int l , int r , int a )
{
	int ans = 0;
	for( int i = 0 ; i < q.size() ; i++ )
	{
		int L = lower_bound( map[ q[i] ].begin() , map[ q[i] ].end() , pair < int , int > ( l , 0 ) ) - map[ q[i] ].begin() , R = lower_bound( map[ q[i] ].begin() , map[ q[i] ].end() , pair < int , int > ( r , n + 1 ) ) - map[ q[i] ].begin() - 1;
		if( map[ q[i] ][L].first < l ) L++;
		if( map[ q[i] ][R].second > r ) R--;
		ans += block[i].find( L , R , a );
	}
	return ans;
}

struct io
{
	char ibuf[1 << 21] , * s , obuf[1 << 20] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "flipflap.in" , "r" , stdin );
		freopen( "flipflap.out" , "w" , stdout );
		fread( s = ibuf , 1 , 1 << 21 , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0 , v = 1;
		while( * s < 48 )
			v = * s++ ^ 45 ? 1 : -1;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u * v;
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
	}
} ip;

#define read ip.read
#define print ip.print

int main()
{
	n = read() , m = read();
	build( 1 , n );
	init();
	while( m-- )
	{
		int opt = read() , l = read() , r = read() , a = read();
		if( opt == 1 ) modify( l , r , a );
		else print( find( l , r , a ) , 10 );
	}
	return 0;
}

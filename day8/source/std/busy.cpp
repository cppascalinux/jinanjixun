//µÚËÄ·Ö¿é 
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define inf 233333
#define MAXN 100010
#define LIM 500
#define LOGN 15
#define Abs( a , b ) ( a > b ? a - b : b - a )

using namespace std;

int n , m , size[ MAXN ] , ans[ MAXN / LIM + 5 ][ MAXN ] , map[ MAXN ] , f[ MAXN ] , belong[ MAXN ] , timetag;
short ext_size[ MAXN ] , num = 1 , big[ MAXN ];
bool use[ MAXN / LIM + 5 ];
int memory_pool[ MAXN * LOGN ] , now_pos;

inline int * get_memory( int x )
{
	now_pos += x;
	return memory_pool + now_pos - x;
}

struct Vector
{
	int * a , lim;
	inline void assign( int c )
	{
		if( c > LIM ) c = LIM;
		a = get_memory( lim = c );
	}
	inline int & operator[]( int i )
	{
		return a[i];
	}
} v[ MAXN ];

inline short getnum()
{
	for( register short i = 1 ; ; i++ )
		if( !use[i] )
		{
			use[i] = 1;
			if( num < i ) num = i;
			return i;
		}
}

inline void update( int & x , int y )
{
	if( x > y ) x = y;
}

inline void merge( int a , int b )
{
	register short i = size[a] , j = size[b] < LIM ? size[b] : ext_size[b] , k;
	if( i + j <= v[b].lim )
	{
		for( k = i + j ; i && j ; )
			v[b][ k-- ] = v[a][i] > v[b][j] ? v[a][ i-- ] : v[b][ j-- ];
		while( i )
			v[b][ k-- ] = v[a][ i-- ];
	}
	else
	{
		Vector temp = v[b];
		v[b].assign( i + j << 1 );
		for( k = i + j ; i && j ; )
			v[b][ k-- ] = v[a][i] > temp[j] ? v[a][ i-- ] : temp[ j-- ];
		while( i )
			v[b][ k-- ] = v[a][ i-- ];
		while( j )
			v[b][ k-- ] = temp[ j-- ];
	}
}

inline void recalc( int v )
{
	for( register int i = 1 ; i <= n ; i++ )
		ans[v][i] = inf;
	for( register int i = 1 , now = inf ; i <= n ; i++ )
		if( f[i] == timetag ) now = 0;
		else update( ans[v][ belong[i] ] , ++now );
	for( register int i = n , now = inf ; i ; i-- )
		if( f[i] == timetag ) now = 0;
		else update( ans[v][ belong[i] ] , ++now );
}

inline void rebuild( int a , int b )
{
	timetag++;
	short v = big[b];
	if( big[a] )
		use[ big[a] ] = 0;
	for( register int i = 1 ; i <= n ; i++ )
		if( belong[i] == a || belong[i] == b )
			f[i] = timetag , belong[i] = b;
	ext_size[b] = 0;
	recalc( v );
}

inline void merge_into( int a , int b )
{
	for( register short i = 1 ; i <= size[a] ; i++ )
		belong[ v[a][i] ] = b;
}

inline void modify( int x , int y )
{
	int a = map[x] , b = map[y];
	if( a == b || !size[a] ) return;
	if( size[a] > size[b] ) swap( a , b ) , swap( x , y ) , map[y] = 0 , map[x] = b;
	else map[x] = 0;
	if( !a || !b ) return;
	if( size[b] < LIM )
		if( size[a] + size[b] < LIM )
		{
			merge( a , b );
			for( register short i = 1 ; i <= num ; i++ )
				update( ans[i][b] , ans[i][a] );
			merge_into( a , b );
		}
		else
		{
			big[b] = getnum() , timetag++;
			for( register short i = 1 ; i <= size[a] ; i++ )
				f[ v[a][i] ] = timetag;
			for( register short i = 1 ; i <= size[b] ; i++ )
				f[ v[b][i] ] = timetag;
			merge_into( a , b );
			recalc( big[b] );
		}
	else if( size[a] < LIM )
		if( ext_size[b] + size[a] < LIM )
		{
			merge( a , b );
			for( register short i = 1 ; i <= num ; i++ )
				update( ans[i][b] , ans[i][a] );
			merge_into( a , b );
			ext_size[b] += size[a];
		}
		else
			rebuild( a , b );
	else
		rebuild( a , b );
	size[b] += size[a] , size[a] = 0;
}

inline void update_ans( int & res , int a , int b )
{
	register short i = 1 , j = 1;
	short sa , sb;
	if( size[a] >= LIM ) sa = ext_size[a];
	else sa = size[a];
	if( size[b] >= LIM ) sb = ext_size[b];
	else sb = size[b];
	if( !sa || !sb ) return;
	for( ; i <= sa && j <= sb ; )
		update( res , v[a][i] < v[b][j] ? v[b][j] - v[a][ i++ ] : v[a][i] - v[b][ j++ ] );
	if( i <= sa && sa )
		update( res , Abs( v[a][i] , v[b][ sb ] ) );
	if( j <= sb && sb )
		update( res , Abs( v[a][ sa ] , v[b][j] ) );
}

inline int find( int x , int y )
{
	int a = map[x] , b = map[y];
	if( a == b )
		if( size[a] ) return 0;
		else return inf;
	if( !size[a] || !size[b] ) return inf;
	if( size[a] > size[b] ) swap( x , y ) , swap( a , b );
	short A = big[a] , B = big[b];
	register int res = inf;
	if( size[b] < LIM )
		update_ans( res , a , b );
	else if( size[a] < LIM )
	{
		res = ans[B][a];
		update_ans( res , a , b );
	}
	else
	{
		res = min( ans[A][b] , ans[B][a] );
		update_ans( res , a , b );
	}
	return res;
}

inline void build( int a )
{
	big[a] = getnum() , timetag++;
	for( register int i = 1 ; i <= n ; i++ )
		if( belong[i] == a )
			f[i] = timetag;
	recalc( big[a] );
	ans[ big[a] ][a] = 0;
}

int Ans;

struct io
{
	char ibuf[1 << 22] , * s , obuf[1 << 20] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "busy.in" , "r" , stdin );
		freopen( "busy.out" , "w" , stdout );
		fread( s = ibuf , 1 , 1 << 22 , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( T u , int v )
	{
		if( u == inf ) Ans = 0 , * t++ = 'C' , * t++ = 'h' , * t++ = 't' , * t++ = 'h' , * t++ = 'o' , * t++ = 'l' , * t++ = 'l' , * t++ = 'y';
		else print( Ans = u );
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
	for( register int i = 1 ; i <= n ; i++ )
		size[ belong[i] = read() ]++;
	for( register int i = 1 ; i <= n ; i++ )
		map[i] = i;
	for( register int i = 1 ; i <= n ; i++ )
		if( size[i] >= LIM )
		{
			build( i );
			v[i].assign( 0 );
		}
		else
			v[i].assign( size[i] ) , size[i] = 0;
	for( register int i = 1 ; i <= n ; i++ )
		if( size[ belong[i] ] < LIM )
			v[ belong[i] ][ ++size[ belong[i] ] ] = i;
	while( m-- )
	{
		int opt = read() , x = read() ^ Ans , y = read() ^ Ans;
		if( opt == 1 ) modify( x , y );
		else print( find( x , y ) , 10 );
	}
	return 0;
}


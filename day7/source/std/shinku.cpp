#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#define lowbit( i ) i & -i
#define MAXN 1000010
#define MAXK 10
#define RG 11
#define MAXD 25

using namespace std;

struct point
{
	int x , y;
	point( int x , int y ) : x( x ) , y( y ) {}
	point() {}
} t[ MAXD ] , temp3[233];

inline bool cmp( const point & a , const point & b )
{
	return a.x == b.x ? a.y > b.y : a.x > b.x;
}

vector < point > q[ MAXN ];
int n , m , cnt , a[ MAXN ] , b[ ( MAXN + MAXK ) << 1 ] , last_pos[ MAXN << 1 ] , f[ MAXN ][ MAXK ] , g[ MAXK ][ MAXN ] , res[ MAXK ] , temp1[ MAXD ] , temp2[ MAXD ];
char ans[ MAXN ][ MAXD ];

inline void modify( int x , unsigned char y , char c )
{
	for( register int i = x ; i ; i ^= lowbit( i ) )
		f[i][y] += c;
}

inline void query( int x , int max_pos )
{
	for( register int i = 0 ; i < MAXK ; i++ ) res[i] = 0;
	for( register int i = x ; i <= max_pos ; i += lowbit( i ) )
		for( register unsigned char j = 0 ; j < MAXK ; j++ )
			res[j] += f[i][j];
}

int pos;

inline void Modify( int x , unsigned char y , char c )
{
	temp3[ pos++ ] = point( x , y );
	g[y][x] += c;
}

inline void make()
{
	for( register unsigned char i = 0 ; i < pos ; i++ )
		if( g[ temp3[i].y ][ temp3[i].x ] )
		{
			modify( temp3[i].x , temp3[i].y , g[ temp3[i].y ][ temp3[i].x ] );
			g[ temp3[i].y ][ temp3[i].x ] = 0;
		}
	pos = 0;
}

struct io
{
	char ibuf[1 << 25] , * s , obuf[1 << 24] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "shinku.in" , "rb" , stdin );
		freopen( "shinku.out" , "w" , stdout );
		s[ fread( s = ibuf , 1 , 1 << 25 , stdin ) ] = 0;
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
	inline void print( register char * u )
	{
		for( register unsigned char i = 0 ; i < MAXK ; i++ )
			* t++ = * u++;
		* t++ = '\n';
	}
} ip;

#define read ip.read
#define print ip.print

int main()
{
	n = read() , m = read();
	for( register int i = 1 ; i <= n ; i++ ) a[i] = read();
	for( register int i = 1 ; i <= m ; i++ )
	{
		int l = read() , r = read();
		q[r].push_back( point( l , i ) );
	}
	for( register char i = 1 ; i <= MAXD ; i++ ) b[ ++cnt ] = 0;
	for( register int i = 1 ; i <= n ; i++ ) b[ ++cnt ] = a[i] , b[ ++cnt ] = a[i] + 1;
	sort( b + MAXD + 1 , b + cnt + 1 );
	cnt = unique( b + MAXD + 1 , b + cnt + 1 ) - b - 1;
	for( register int i = 1 ; i <= n ; i++ )
		a[i] = upper_bound( b + 1 , b + cnt + 1 , a[i] ) - b - 1;
	for( register int i = 1 ; i <= n ; i++ )
	{
		int c = 0;
		for( register char j = -RG ; j <= RG ; j++ )
			if( last_pos[ a[i] + j ] )
				t[ c++ ] = point( last_pos[ a[i] + j ] , j + RG );
		sort( t , t + c , cmp );
		t[c].x = 0;
		temp2[ RG ] = last_pos[ a[i] ] = i;
		Modify( i , 0 , 1 );
		Modify( t[0].x , 0 , -1 );
		for( register int j = 0 , a , b ; j < c && t[j].y != RG ; j++ )
		{
			temp1[ t[j].y ] = temp2[ t[j].y ] = i;
			for( a = 0 ; a < RG && temp1[ RG - a - 1 ] == i ; a++ );
			for( b = 0 ; b < RG && temp1[ RG + b + 1 ] == i ; b++ );
			if( a && a < RG )
				Modify( t[j].x , a - 1 , -1 ) , Modify( t[j + 1].x , a - 1 , 1 );
			if( b && b < RG )
				Modify( t[j].x , b - 1 , -1 ) , Modify( t[j + 1].x , b - 1 , 1 );
			if( a + b < MAXK )
				Modify( t[j].x , a + b , 1 ) , Modify( t[j + 1].x , a + b , -1 );
		}
		make();
		for( register vector < point > :: iterator j = q[i].begin() ; j != q[i].end() ; j++ )
		{
			query( j -> x , i );
			for( register int k = 0 ; k < MAXK ; k++ )
				ans[ j -> y ][k] = res[k] % 10 + 48;
		}
	}
	for( register int i = 1 ; i <= m ; i++ )
		print( ans[i] );
	return 0;
}

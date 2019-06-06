#include <stdio.h>
#include <algorithm>
#define MAXN 1000010
#define ratio 4
#define inf 1000000000
#define new_Node( s , v , a , b , c , d , e , f ) ( & ( * st[ cnt++ ] = Node( s , v , a , b , c , d , e , f ) ) )
#define merge( a , b ) new_Node( a -> size + b -> size , a -> sum + b -> sum , min( a -> whitemin , b -> whitemin ) , min( a -> blackmin , b -> blackmin ) , a -> whitenum + b -> whitenum , a -> blacknum + b -> blacknum , a , b )

using namespace std;

int n , m , a[ MAXN ] , cnt , tx;

struct Node
{
	int size , sum , tag , whitemin , blackmin , whitenum , blacknum;
	Node * left , * right;
	Node( int s , int v , int wm , int bm , int wn , int bn , Node * a , Node * b ) :
	size( s ) , sum( v ) , whitemin( wm ) , blackmin( bm ) , whitenum( wn ) , blacknum( bn ) , left( a ) , right( b ) , tag( 0 ) {}
	Node() {}
	inline void make( int x )
	{
		tag += x;
		blackmin += x;
		whitemin -= x;
		sum += x * blacknum;
		size += x * ( blacknum - whitenum );
	}
	inline void pushdown();
	inline int maintain();
	inline void update();
} t[ MAXN << 1 ] , * st[ MAXN << 1 ] , * temp , * root , * null , * father;

void rotate( Node * cur )
{
	cur -> pushdown();
	if( cur -> left != null && cur -> right != null )
		if( ( cur -> left -> right != null ) && ( cur -> left -> blacknum + cur -> left -> whitenum ) > ( cur -> right -> blacknum + cur -> right -> whitenum ) * ratio )
			cur -> left -> pushdown() , cur -> right = merge( cur -> left -> right , cur -> right ) , st[ --cnt ] = cur -> left , cur -> left = cur -> left -> left;
		else if( ( cur -> right -> left != null ) && ( cur -> right -> blacknum + cur -> right -> whitenum ) > ( cur -> left -> blacknum + cur -> left -> whitenum ) * ratio )
			cur -> right -> pushdown() , cur -> left = merge( cur -> left , cur -> right -> left ) , st[ --cnt ] = cur -> right , cur -> right = cur -> right -> right;
}

inline void Node :: pushdown()
{
	if( tag )
	{
		if( left != null )
			left -> make( tag ) , right -> make( tag );
		tag = 0;
	}
}

inline void Node :: update()
{
	if( left != null )
	{
		size = left -> size + right -> size;
		sum = left -> sum + right -> sum;
		blackmin = min( left -> blackmin , right -> blackmin );
		whitemin = min( left -> whitemin , right -> whitemin );
		blacknum = left -> blacknum + right -> blacknum;
		whitenum = left -> whitenum + right -> whitenum;
	}
}

int Node :: maintain()
{
	pushdown();
	rotate( this );
	if( left == null ) return temp = this , 1;
	else
		if( !left -> blackmin || !left -> whitemin ) return left -> maintain();
		else return left -> blacknum + left -> whitenum + right -> maintain();
}

void split_block( int x , Node * cur )
{
	cur -> pushdown();
	if( x > cur -> left -> blacknum + cur -> left -> whitenum ) split_block( x - cur -> left -> blacknum - cur -> left -> whitenum , cur -> right ) , cur -> left = merge( cur -> left , cur -> right -> left ) , st[ --cnt ] = cur -> right , cur -> right = cur -> right -> right;
	else if( x < cur -> left -> blacknum + cur -> left -> whitenum ) split_block( x , cur -> left ) , cur -> right = merge( cur -> left -> right , cur -> right ) , st[ --cnt ] = cur -> left , cur -> left = cur -> left -> left;
}

void split_array( int x , Node * cur )
{
	cur -> pushdown();
	if( cur -> left == null )
	{
		bool c = cur -> sum;
		cur -> left = new_Node( x , c * x , c ? inf : x , c ? x : inf , c ? 0 : 1 , c ? 1 : 0 , null , null );
		cur -> right = new_Node( cur -> size - x , c * ( cur -> size - x ) , c ? inf : cur -> size - x , c ? cur -> size - x : inf , c ? 0 : 1 , c ? 1 : 0 , null , null );
	}
	if( x > cur -> left -> size ) split_array( x - cur -> left -> size , cur -> right ) , cur -> left = merge( cur -> left , cur -> right -> left ) , st[ --cnt ] = cur -> right , cur -> right = cur -> right -> right;
	else if( x < cur -> left -> size ) split_array( x , cur -> left ) , cur -> right = merge( cur -> left -> right , cur -> right ) , st[ --cnt ] = cur -> left , cur -> left = cur -> left -> left;
}

void split_mock( int x , Node * cur )
{
	cur -> pushdown();
	if( cur -> left == null )
	{
		temp = cur , tx = x;
		return;
	}
	if( x > cur -> left -> size ) split_mock( x - cur -> left -> size , cur -> right );
	else split_mock( x , cur -> left );
}

bool color( int x , Node * cur )
{
	cur -> pushdown();
	if( cur -> left == null ) return cur -> blacknum;
	return x > cur -> left -> size ? color( x - cur -> left -> size , cur -> right ) : color( x , cur -> left );
}

int find( int x , Node * cur )
{
	cur -> pushdown();
	if( cur -> left == null ) return x * cur -> blacknum;
	return x > cur -> left -> size ? find( x - cur -> left -> size , cur -> right ) + cur -> left -> sum : find( x , cur -> left );
}

int rank_array_block( int x , Node * cur )
{
	cur -> pushdown();
	if( cur -> left == null ) return temp = cur , 1;
	return x > cur -> left -> size ? rank_array_block( x - cur -> left -> size , cur -> right ) + cur -> left -> blacknum + cur -> left -> whitenum : rank_array_block( x , cur -> left );
}

inline bool get_mock_interval( int & l , int & r , int c )
{
	if( rank_array_block( max( 2 , l ) , root ) == rank_array_block( min( n + 1 , r + 2 ) , root ) ) return 0;
	if( r != n )
	{
		temp = 0 , tx = 0;
		split_mock( r + 2 , root );
		tx--;
		if( temp && temp -> blacknum == c ) r += temp -> size - tx;
	}
	if( l != 1 )
	{
		temp = 0 , tx = 0;
		split_mock( l , root );
		tx++;
		if( temp && temp -> blacknum == c ) l -= tx - 1;
	}
	return 1;
}

inline void get_array_interval( int l , int r )
{
	split_array( min( root -> size , r + 1 ) , root ) , split_array( max( 1 , l ) , root -> left );
}

inline void get_block_interval( int l , int r )
{
	split_block( r , root ) , split_block( l - 1 , root -> left );
}

void dispose( Node * cur )
{
	if( cur -> left != null )
		st[ --cnt ] = cur -> left , dispose( cur -> left ) , st[ --cnt ] = cur -> right , dispose( cur -> right );
}

inline int Abs( int x )
{
	return x > 0 ? x : -x;
}

Node * build( int l , int r )
{
	if( l == r )
		return new_Node( Abs( a[l] ) , max( a[l] , 0 ) , a[l] > 0 ? inf : Abs( a[l] ) , a[l] > 0 ? Abs( a[l] ) : inf , a[l] > 0 ? 0 : 1 , a[l] > 0 ? 1 : 0 , null , null );
	Node * left = build( l , l + r >> 1 ) , * right = build( ( l + r >> 1 ) + 1 , r );
	return merge( left , right );
}

struct io
{
	char ibuf[1 << 25] , * s , obuf[1 << 23] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "plasticmem.in" , "r" , stdin );
		freopen( "plasticmem.out" , "w" , stdout );
		fread( s = ibuf , 1 , 1 << 25 , stdin );
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
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = '\n';
	}
} ip;

#define read ip.read
#define print ip.print

inline void init()
{
	for( register int i = 0 ; i < MAXN << 1 ; i++ ) st[i] = & t[i];
	null = new_Node( 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 );
	int now = 0;
	a[n + 1] = -1;
	for( register int i = 1 , last = a[1] , num = 0 ; i <= n + 1 ; i++ )
		if( a[i] == last ) num++;
		else a[ ++now ] = last ? num : -num , last = a[i] , num = 1;
	a[0] = a[ now + 1 ] = 1;
	root = build( 0 , now + 1 );
}

#define cur root -> left -> right

int main()
{
	n = read() , m = read();
	for( register int i = 1 ; i <= n ; i++ ) a[i] = read();
	init();
	while( m-- )
	{
		int opt = read() , l = read() , r = read();
		if( opt == 1 )
			if( get_mock_interval( l , r , 0 ) || color( l + 1 , root ) )
			{
				get_array_interval( l , r );
				dispose( cur );
				* cur = Node( cur -> size , 0 , cur -> size , inf , 1 , 0 , null , null );
			}
			else;
		else if( opt == 2 )
			if( get_mock_interval( l , r , 1 ) || !color( l + 1 , root ) )
			{
				get_array_interval( l , r );
				dispose( cur );
				* cur = Node( cur -> size , cur -> size , inf , cur -> size , 0 , 1 , null , null );
			}
			else;
		else if( opt == 3 )
		{
			int Bl = rank_array_block( l + 1 , root );
			if( temp -> blacknum ) Bl++;
			int Br = rank_array_block( r + 1 , root );
			if( !temp -> blacknum ) Br--;
			Bl = max( 2 , Bl );
			Br = min( root -> whitenum + root -> blacknum - 1 , Br );
			if( Bl <= Br )
			{
				get_block_interval( Bl , Br );
				cur -> make( 1 );
			}
		}
		else if( opt == 4 )
		{
			int Bl = rank_array_block( l + 1 , root );
			if( !temp -> blacknum ) Bl++;
			int Br = rank_array_block( r + 1 , root );
			if( temp -> blacknum ) Br--;
			Bl = max( 2 , Bl );
			Br = min( root -> whitenum + root -> blacknum - 1 , Br );
			if( Bl <= Br )
			{
				get_block_interval( Bl , Br );
				cur -> make( 1 );
			}
		}
		else if( opt == 5 )
		{
			int Bl = rank_array_block( l + 1 , root );
			if( !temp -> blacknum ) Bl++;
			int Br = rank_array_block( r + 1 , root );
			if( temp -> blacknum ) Br--;
			Bl = max( 2 , Bl );
			Br = min( root -> whitenum + root -> blacknum - 1 , Br );
			if( Bl <= Br )
			{
				get_block_interval( Bl , Br );
				cur -> make( -1 );
			}
		}
		else if( opt == 6 )
		{
			int Bl = rank_array_block( l + 1 , root );
			if( temp -> blacknum ) Bl++;
			int Br = rank_array_block( r + 1 , root );
			if( !temp -> blacknum ) Br--;
			Bl = max( 2 , Bl );
			Br = min( root -> whitenum + root -> blacknum - 1 , Br );
			if( Bl <= Br )
			{
				get_block_interval( Bl , Br );
				cur -> make( -1 );
			}
		}
		else
			print( find( r + 1 , root ) - find( l , root ) );
		if( root -> left != null ) root -> left -> update();
		root -> update();
		while( !root -> whitemin || !root -> blackmin )
		{
			int v = root -> maintain();
			get_block_interval( max( 2 , v - 1 ) , min( root -> whitenum + root -> blacknum - 1 , v + 1 ) );
			dispose( cur );
			* cur = Node( cur -> size , temp -> whitenum * cur -> size , temp -> blacknum ? cur -> size : inf , temp -> whitenum ? cur -> size : inf , temp -> blacknum , temp -> whitenum , null , null );
			if( root -> left != null ) root -> left -> update();
			root -> update();
		}
	}
	return 0;
}


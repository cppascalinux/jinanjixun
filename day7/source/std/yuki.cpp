#include <stdio.h>
#include <iostream>
#include <algorithm>
#define lowbit( i ) i & -i
#define inf 2000000000
#define MAXN 1000010

using namespace std;

int n , m , stack_top , cnt , a[ MAXN ] , VT[3];
int memory_pool[ MAXN * 11 ] , now_pos;

inline int * get_memory( int x )
{
	now_pos += x;
	return memory_pool + now_pos - x;
}

struct Vector
{
	int * a , * b , lim;
	inline void assign( int c )
	{
		if( !c ) c = 1;
		b = a = get_memory( lim = c );
	}
	inline int & operator[]( int i )
	{
		return a[i];
	}
	inline void push_back( int x )
	{
		if( b - a >= lim )
		{
			int * v = get_memory( lim <<= 1 ) , * t = v;
			for( register int * i = a ; i < b ; i++ )
				* v++ = * i;
			a = t , b = v;
		}
		* b++ = x;
	}
	inline int size()
	{
		return b - a;
	}
	inline void clear()
	{
		b = a;
	}
} linker[ MAXN ] , change[ MAXN ] , add[ MAXN ] , value[ MAXN ];

#define Node RedBlackTree_Node

struct Node
{
	int data , size , c;
	bool color;
	Node * fa , * ch[2];
	inline void set( const int & _v , const bool & _color , const int & i , Node * p )
	{
		data = _v , color = _color , size = c = i;
		fa = ch[0] = ch[1] = p;
	}
	inline void push_up()
	{
		size = ch[0] -> size + ch[1] -> size + c;
	}
	inline void push_down()
	{
		for( Node * x = this ; x -> size ; x = x -> fa ) x -> size--;
	}
	inline int cmp( const int & v ) const
	{
		return data == v ? -1 : v > data;
	}
} stack[ MAXN << 1 ] , * tail , * store[ MAXN << 1 ] , * rbt_null;

inline void init_RedBlackTree()
{
	tail = & stack[0];
	rbt_null = tail++;
	rbt_null -> set( 0 , 0 , 0 , 0 );
	stack_top = 0;
}

struct RedBlackTree
{
	Node * rbt_root;
	inline void init()
	{
		rbt_root = rbt_null;
	}
	inline Node * new_Node( const int & v )
	{
		register Node * p = rbt_null;
		if( !stack_top ) p = tail++;
		else p = store[ --stack_top ];
		p -> set( v , 1 , 1 , rbt_null );
		return p;
	}
	inline void rotate( register Node * & x , const bool & d )
	{
		register Node * y = x -> ch[ !d ];
		x -> ch[ !d ] = y -> ch[d];
		if( y -> ch[ d ] -> size ) y -> ch[ d ] -> fa = x;
		y -> fa = x -> fa;
		if( ! x -> fa -> size ) rbt_root = y;
		else x -> fa -> ch[ x -> fa -> ch[ 0 ] != x ] = y;
		y -> ch[ d ] = x;
		x -> fa = y;
		y -> size = x -> size;
		x -> push_up();
	}
	inline void insert( const int & v )
	{
		register Node * x = rbt_root , * y = rbt_null;
		while( x -> size )
		{
			x -> size++ , y = x;	
			int d = x -> cmp( v );
			if( d == -1 )
			{
				x -> c++;
				return;
			}
			x = x -> ch[ d ];
		}
		x = new_Node( v );
		if( y -> size ) y -> ch[ v > y -> data ] = x;
		else rbt_root = x;
		x -> fa = y;
		insert_fix( x );
	}
	inline void insert_fix( register Node * & x )
	{
		while( x -> fa -> color )
		{
			Node * parent = x -> fa , * grandparent = parent -> fa;
			bool d = parent == grandparent -> ch[ 0 ];
			Node * uncle = grandparent -> ch[ d ];
			if( uncle -> color )
			{
				parent -> color = uncle -> color = 0;
				grandparent -> color = 1;
				x = grandparent;
			}
			else if( x == parent -> ch[ d ] )
				rotate( x = parent , !d );
			else
			{
				grandparent -> color = 1;
				parent -> color = 0;
				rotate( grandparent , d );
			}
		}
		rbt_root -> color = 0;
	}
	inline Node * find( register Node * x , int data )
	{
		while( x -> size && x -> data != data )
			x = x -> ch[ x -> data < data ];
		return x;
	}
	inline void del_fix( register Node * & x )
	{
		while( x != rbt_root && !x -> color )
		{
			bool d = x == x -> fa -> ch[ 0 ];
			Node * parent = x -> fa , * sibling = parent -> ch[ d ];
			if( sibling -> color )
			{
				sibling -> color = 0;
				parent -> color = 1;
				rotate( x -> fa , !d );
				sibling = parent -> ch[ d ];
			}
			else if( !sibling -> ch[ 0 ] -> color && !sibling -> ch[ 1 ] -> color )
				sibling -> color = 1 , x = parent;
			else
			{
				if( !sibling -> ch[ d ] -> color )
				{
					sibling -> ch[ !d ] -> color = 0;
					sibling -> color = 1;
					rotate( sibling , d );
					sibling = parent -> ch[ d ];
				}
				sibling -> color = parent -> color;
				sibling -> ch[ d ] -> color = parent -> color = 0;
				rotate( parent , !d );
				break;
			}
		}
		x -> color = 0;
	}
	inline void erase( const int & data )
	{
		Node * z = find( rbt_root , data );
		if( !z -> size ) return;
		if( z -> c > 1 )
		{		
			z -> c--;
			z -> push_down();
			return;
		}
		Node * y = z , * x = rbt_null;
		if( z -> ch[ 0 ] -> size && z -> ch[ 1 ] -> size )
		{
			y = z -> ch[ 1 ];
			while( y -> ch[ 0 ] -> size )
				y = y -> ch[ 0 ];
		}
		x = y -> ch[ !y -> ch[ 0 ] -> size ];
		x -> fa = y -> fa;
		if( !y -> fa -> size ) rbt_root = x;
		else y -> fa -> ch[ y -> fa -> ch[ 1 ] == y ] = x;
		if( z != y ) z -> data = y -> data , z -> c = y -> c;
		y -> fa -> push_down();
		for( Node * k = y -> fa ; y -> c > 1 && k -> size && k != z ; k = k -> fa ) k -> size -= y -> c - 1;
		if( !y -> color ) del_fix( x );
		store[ stack_top++ ] = y;
	}
	inline int find( int k )
	{
		int t , p , l = -1;
		register Node * x = rbt_root;
		while( x -> size )
		{
			t = x -> ch[ 0 ] -> size + ( l < VT[0] && VT[0] < x -> data ) + ( l < VT[1] && VT[1] < x -> data ) + ( l < VT[2] && VT[2] < x -> data );
			p = t + x -> c + ( VT[0] == x -> data ) + ( VT[1] == x -> data ) + ( VT[2] == x -> data );
			if( k <= t ) x = x -> ch[ 0 ];
			else if( t + 1 <= k && k <= p ) return x -> data;
			else k -= p , l = x -> data , x = x -> ch[ 1 ];
		}
		k--;
		if( l >= VT[0] )
		{
			k++;
			if( l >= VT[1] )
			{
				k++;
				if( l >= VT[2] )
					k++;
			}
		}
		return VT[k];
	}
} rbt_root[ MAXN ];

#undef Node

int size[ MAXN ] , fa[ MAXN ] , son[ MAXN ] , top[ MAXN ] , dep[ MAXN ] , l[ MAXN ] , r[ MAXN ] , v[ MAXN ];

#define cur linker[x][i]

void dfs1( int x )
{
	size[x] = 1;
	for( int i = 0 ; i < linker[x].size() ; i++ )
		if( cur != fa[x] )
		{
			dep[ cur ] = dep[x] + 1 , fa[ cur ] = x;
			dfs1( cur ) , size[x] += size[ cur ];
			if( size[ cur ] > size[ son[x] ] ) son[x] = cur;
		}
}

int tot;

void dfs2( int x , int t )
{
	l[x] = ++tot , top[x] = t;
	if( son[x] ) dfs2( son[x] , t );
	for( int i = 0 ; i < linker[x].size() ; i++ )
		if( cur != fa[x] && cur != son[x] )
			dfs2( cur , cur );
	r[x] = tot;
}

int select[ MAXN ];
bool use[ MAXN ];

#undef cur

#define len( a ) v[a].y - v[a].x + 1

inline int find( int x )
{
	register int ans = 0;
	for( register int i = x ; i ; i -= lowbit( i ) )
		ans += v[i];
	return ans;
}

inline int find_value( int x )
{
	return find( r[x] ) - find( l[x] - 1 );
}

inline void modify( int x , int y  )
{
	if( x )
		for( register int i = x ; i <= n ; i += lowbit( i ) )
			v[i] += y;
}

inline void fix( int x , int c )
{
	if( fa[x] && !add[ fa[x] ][ select[x] ] )
		change[ fa[x] ].push_back( select[x] );
	add[ fa[x] ][ select[x] ] += c;
}

inline void Modify( int a , int b , int c )
{
	int t = a , p = b , f;
	while( top[a] != top[b] )
	{
		if( dep[ top[a] ] < dep[ top[b] ] ) swap( a , b );
		fix( top[a] , c );
		a = fa[ top[a] ];
	}
	if( dep[a] > dep[b] ) swap( a , b );
	if( a == top[a] )
		fix( a , c );
	modify( l[t] , c ) , modify( l[p] , c );
	modify( l[a] , -c ) , modify( l[ fa[a] ] , -c );
}

#define cur change[x][i]

inline void find_begin( int x )
{
	VT[0] = VT[1] = VT[2] = inf;
	if( son[x] ) VT[0] = find_value( son[x] );
	if( fa[x] ) VT[1] = find_value( fa[x] );
	VT[2] = find_value( x );
	sort( VT , VT + 3 );
	for( int i = 0 ; i < change[x].size() ; i++ )
		if( !use[ cur ] )
		{
			use[ cur ] = 1;
			rbt_root[x].erase( value[x][ cur ] );
			value[x][ cur ] += add[x][ cur ] , add[x][ cur ] = 0;
			rbt_root[x].insert( value[x][ cur ] );
		}
	for( register int i = 0 ; i < change[x].size() ; i++ )
		use[ cur ] = 0;
	change[x].clear();
}

#undef cur

inline void addedge( int x , int y )
{
	linker[x].push_back( y );
	linker[y].push_back( x );
}

#undef cur
#define cur linker[x][i]

struct io
{
	char ibuf[36 << 20] , * s , obuf[5 << 20] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "yuki.in" , "rb" , stdin );
		freopen( "yuki.out" , "w" , stdout );
		fread( s = ibuf , 1 , 36 << 20 , stdin );
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
	init_RedBlackTree();
	dfs1( 1 ) , dfs2( 1 , 1 );
	for( register int i = 0 ; i <= n ; i++ )
		value[i].assign( linker[i].size() ) , add[i].assign( linker[i].size() ) , change[i].assign( linker[i].size() );
	for( int x = 1 ; x <= n ; x++ )
	{
		rbt_root[x].init();
		for( int i = 0 ; i < linker[x].size() ; i++ )
		{
			value[x].push_back( a[ cur ] );
			if( cur != son[x] && cur != fa[x] )
			{
				rbt_root[x].insert( a[ cur ] );
				select[ cur ] = i;
			}
		}
	}
}

#include <time.h>

int main()
{
	n = read() , m = read();
	for( int i = 1 ; i <= n ; i++ ) a[i] = read() , linker[i].assign( 1 );
	for( int i = 1 ; i < n ; i++ ) addedge( read() , read() );
	init();
	for( int i = 1 ; i <= n ; i++ )
		modify( l[i] , a[i] ) , modify( l[ fa[i] ] , -a[i] );
	while( m-- )
	{
		int opt = read() , x = read() , y = read();
		if( opt == 1 )
			Modify( x , y , read() ); 
		else
		{
			find_begin( x );
			print( rbt_root[x].find( y ) );
		}
	}
	cerr << " " << clock() << " ms" << endl;
	cerr << " " << now_pos << endl;
	return 0;
}


struct io
{
	char ibuf[ 读入量 ] , * s , obuf[ 输出量 ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "test.in" , "r" , stdin );
		freopen( "test.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  读入量  , stdin );
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

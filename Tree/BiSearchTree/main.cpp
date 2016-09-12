#include "BiSearchTree.h"
#include <stdio.h>
#include "fatal.h"

int main( )
{
    SearchTree T;
    Position P;
    int i;
    int j = 0;

	const int MAXSIZE = 10;

    T = MakeEmpty( NULL );
    for( i = 0; i < MAXSIZE; i++, j = ( j + 7 ) % 50 )
	{
		printf("%5d", j);
		if ((i+1) % 10 == 0)
			putchar('\n');
        T = Insert( j, T );
	}

    for( i = 0; i < 50; i++ )
       if( ( P = Find( i, T ) ) == NULL || Retrieve( P ) != i )
           printf( "Error at %d\n", i );

/* 	printf("\n前序遍历查找二叉树:\n");
	PreOrderTraverse(T); */

    for( i = 0; i < 50; i += 2 )
        T = Delete( i, T );

/* 	printf("\n前序遍历查找二叉树:\n");
	PreOrderTraverse(T); */

    for( i = 1; i < 50; i += 2 )
        if( ( P = Find( i, T ) ) == NULL || Retrieve( P ) != i )
            printf( "Error at %d\n", i );

    for( i = 0; i < 50; i += 2 )
        if( ( P = Find( i, T ) ) != NULL )
            printf( "Error at %d\n", i );

    printf( "Min is %d, Max is %d\n", Retrieve( FindMin( T ) ),
               Retrieve( FindMax( T ) ) );

    return 0;
}

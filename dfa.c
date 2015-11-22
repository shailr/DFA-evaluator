#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check(char , int , int , char** , int** );

int main()
{
	int no_states , no_symbols , no_final_states =0 , ch = 1 , i ,j , flag = 1;
	int **dfa , *f;
	char str[20] , **in_sym;
	
    		printf("----DFA Assignment----\n");
    		
			printf ( "\nEnter total number of states:" );
    		scanf ( "%d" , &no_states );
    	
			printf( "\nEnter total number of input symbols:" );
 			scanf( "%d" , &no_symbols );
    	
			dfa = (int**)malloc(no_states * sizeof(int*));
    		for( i=0 ; i < no_states ; i++)
    		{
    				dfa[i] = (int*)malloc(no_symbols * sizeof(int) );
    		}
    				
    		in_sym = (char**)malloc( no_symbols ) ;
    		
			for( i=0; i < no_symbols ; i++)
   			{
				flag = 1;
				while( flag == 1)
				{
    					printf("\nEnter name of symbol %d:",i+1);
    					scanf("%s", str);
    					if ( strlen(str) == 1)
    						flag = 0;
    					else
    						printf( "\nMultiple characters cannot be taken as input symbol!!!\n" );
    			}
    			in_sym[i]=(char *)malloc(strlen(str)*sizeof(char));
    			strcpy(in_sym[i],str);
    		}
	    	while( no_final_states <= 0 || no_final_states > no_states)
	    	{
	    		printf( "\nEnter the number of final states:" );
		    	scanf( "%d" , &no_final_states );
		    	if( no_final_states == 0)
		    	{
		    		printf( "\nNumber of final states cannot be zero or negative!!\n" );
		    	}
		    	else if( no_final_states > no_states )
		    		printf( "\nNumber of final states cannot be greater than total states!!!\n" );
		    	else
	    		{
	    			f = (int*)malloc(no_final_states * sizeof(int));
	    			for( i=0 ; i < no_final_states ; i++ )
					{
						flag = 1;
						while( flag == 1 )
						{
			      				printf("\nFinal state %d : q",i+1);
			      				scanf("%d" , &f[i]);
			      				if( f[i] >= 0 && f[i] < no_states )
			      					flag = 0;
			      				else
			      					printf( "\nInvalid final state!!" );
		      				}
		      			//printf("%d",flag);
					}
				}
			}
    				
	        printf("\nDefine transitions as\t(initial state, input symbol ) = target state");
	        printf("\nEnter -1 if the target state is NULL" );
	        for(i=0; i<no_states ; i++)
			{
      				for(j=0; j<no_symbols ; j++)
      				{
      					flag = 0;
      					while( flag == 0 )
      					{
               					printf("\n(q%d , %s ) = q" , i , in_sym[j]);
               					scanf("%d",&dfa[i][j]);
               					if( dfa[i][j] >= 0 && dfa[i][j] < no_states)
               						flag = 1;
               					else
               					{
               						printf( "\nState Does not exit!!!\n" );
               						printf( "\nEvery non-existing state will be taken as state NULL\n" );
               						printf( "\nContinue or Re-enter state(1/0)\t" );
               						scanf( "%d" , &flag );
               					}
               				}
      				}
			}
			while(flag == 1)
			{
		    		printf( "\nEnter Input String :");
		    		scanf( "%s" , str);
		    				
		    		int s = 0 , valid = 0;
		    				
		    		for( i=0 ; flag == 1 && str[i] != '\0' ; i++ )
		    		{
		    			s = check( str[i] , s , no_symbols , in_sym , dfa);
		    			if( s < 0)
		    				flag = 0;
		    		}
				if( s != -1 )
					printf("\nString Terminated at state:q%d",s);
					
				for( i=0 ; flag == 1 && i < no_final_states && valid == 0 ; i++)
				{	
					if( s == f[i] )
						valid = 1;
				}
				
				if( valid == 1)
					printf( "\nString accepted.\n" );
				else
					printf( "\nString not accepted.\n" );
				
				printf( "\nContinue?(1/0):" );
				scanf( "%d" , &flag);
			}
}

int check(char b , int d , int no_symbols , char **in_sym , int **dfa)
{
    int i , j = b , k;

    for( i=0 ; i < no_symbols ; i++)
    {
    	k = in_sym[i][0];
    	if( j == k )
    		return(dfa[d][i]);
    }
    return -1;   
}

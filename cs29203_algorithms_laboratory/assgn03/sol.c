#include <stdio.h>
#include <stdlib.h>


/*initialising the struct to store different battalions*/
struct battalion{
    char beta;
    int  num;

};



/*function to print the units left in each battalion after the commander places them in saddle point*/
void print_soldiers_left(struct battalion *different_battalions, int number_types)
{
    for (int i = 0; i < number_types; i++)
    {   

        printf("There are %d units left in %c-battalion\n",different_battalions[i].num,different_battalions[i].beta);
        
    }
}



/*Setting up the saddle point initially.
Input: 
1. double pointers to matrix to store the pattern, matrix to store the sequence of placing the units
2. r and c takes in the row and columns of the mien location
3. grid size is the total size
Process: place '*' in pattern and -1 in sequence matrix for the mine location and '@' and 0 for other locations*/
void setup_2d_array(char **arr_type, int **arr_seq, int r,int c,int grid_size)
{
    for(int i = 0; i < grid_size; i++)
    {
        for(int j = 0; j < grid_size; j++)
        {
            if(i==r && j==c)
            {
                arr_type[i][j]='*';
                arr_seq[i][j]=-1;
                
            }   
            else
            {
                arr_type[i][j]='@';
                arr_seq[i][j]=0;
                
            } 
        }
    }



}


/*finally print the 2d matrix to show the pattern of the soilders and sequence of placing those soilders*/
void print_array(char **arr_type, int **arr_seq, int grid_size)
{
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++)
            printf("%c \t",arr_type[i][j]);
         printf("\n");
    }

    printf("\n");

    // The grid is sequence
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++)
           printf("%6d \t", arr_seq[i][j]);
         printf("\n");
    }


    printf("\n");

}

/*finding the correct battalion type to use, one having the largest number of battalions left and having the highest rank in case of two or more battalions types with same number of battalions*/

char find_max_battalion(struct battalion *different_battalions, int number_types)
{
 	int max_count=0;
 	char max_tile='@';

 	for (int i = 0; i < number_types; i++)
    {
        /* check if the battlaion has >= max number of units till now*/
    	if(different_battalions[i].num>=max_count)
        {
            //if the number of units are same as the maximum number of units, then choose one with higher rank
            if(different_battalions[i].num==max_count)
            {
                //choose the one with lower ascii value
                if(max_tile>different_battalions[i].beta)
                {
                    max_tile=different_battalions[i].beta;
                }
                max_count=different_battalions[i].num;
            }   
            else
            {   
                max_tile=different_battalions[i].beta;
                max_count=different_battalions[i].num;
        
            }
        } 
            
    }


    for (int i = 0; i < number_types; i++)
    {
        //check if the type matches the max type reduce one unit
        //Don't compare with number as it might be same.
    	if(different_battalions[i].beta==max_tile)
    		different_battalions[i].num=different_battalions[i].num-1;
    }
    return max_tile;


}

// get the location of where to place the three soldiers and then place them int he matrix//
void place_soldiers(char **arr_type,int **arr_seq, int x1, int y1, int x2,int y2, int x3, int y3, int place_int,char tile)
{
    if(tile!='@')
    {    
    
    arr_type[x1][y1] = tile;
    arr_type[x2][y2] = tile;
    arr_type[x3][y3] = tile;
    //sequence array 
    arr_seq[x1][y1] = place_int;
    arr_seq[x2][y2] = place_int;
    arr_seq[x3][y3] = place_int;
    }


	
}
// // Quadrant order followed here (can be different in your case)
// // 1   2
// // 3   4
 // algorithm to place the soldiers.
int soldiers_placing_strategy(char **arr_type, int **arr_seq, int r, int c, int n, struct battalion *different_battalion, int number_types, int x, int y,int count, char tile_max)
{


    /*we always try to place the soldiers in a unit with the following logic. 

    Note: Each time we will get a square area where one of the elements will be a mine or an already placed soldier (called as invalid cell). Try to do few of the steps manually.
    
    1. if the square is 2*2 then it is easy place the soliders in remaining left places and return
    2. else we have to place the soldiers strategicallyin a 2X2 square in that square, we choose the centre 2X2 cell and leave the cell in the quadrant in which the invalid cell is present.
    3. Divide the square into four parts and recur the same algorithm in 4 different quadrants.
    */

    // when 2X2 square left
    if (n == 2) {
    	for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr_seq[x + i][y + j] == 0) {
                    arr_type[x + i][y + j] = tile_max;
                    arr_seq[x + i][y + j] = count;
                }
            }
        }
        count+=1;
        return count;
    }



   



     int r1,c1,r2,c2,r3,c3,r4,c4;
    // Possible locations in the quadrant 1,2,3,4 where the soldiers might be placed at the centre cell
    // You can also use two for loops and identify a non zero cell but it will not be optimal solution.
    r1=x+n/2-1;
    c1=y+n/2-1;
    r2=x+n/2;
    c2=y+n/2-1;
    r3=x+n/2-1;
    c3=y+n/2;
    r4=x+n/2;
    c4=y+n/2;


    // If mine/soldier already placed is in 1st quadrant
    if (r < x + n / 2 && c < y + n / 2)
    {
        place_soldiers(arr_type, arr_seq, x + n / 2, y + (n / 2) - 1, x + n / 2,
              y + n / 2, x + n / 2 - 1, y + n / 2, count, tile_max);
        //replace invalid cell for 1st quadrant as the mine location//
 	    r1=r;
        c1=c;
    }


    // If mine/soldier placed is in 2nd quadrant
    else if (r < x + n / 2 && c >= y + n / 2)
    {
        //replace invalid cell for 2nd quadrant as the mine location//
        
        place_soldiers(arr_type, arr_seq, x + n / 2, y + (n / 2) - 1, x + n / 2,
              y + n / 2, x + n / 2 - 1, y + n / 2 - 1,count, tile_max);
 	    r2=r;
        c2=c;
    }


 	// If mine/soldier placed is in 3rd quadrant
    else if (r >= x + n / 2 && c < y + n / 2)
    {
        
        place_soldiers(arr_type, arr_seq, x + (n / 2) - 1, y + (n / 2), x + (n / 2),
              y + n / 2, x + (n / 2) - 1, y + (n / 2) - 1,count, tile_max);
        //replace invalid cell for 3rd quadrant as the mine location//

        r3=r;
        c3=c;
    }    


    // If mine/soldier placed is in 4th quadrant
    else if (r >= x + n / 2 && c >= y + n / 2)
    {
        place_soldiers(arr_type, arr_seq, x + (n / 2) - 1, y + (n / 2), x + (n / 2),
              y + (n / 2) - 1, x + (n / 2) - 1,
              y + (n / 2) - 1,count,tile_max);
        //replace invalid cell for 4th quadrant as the mine location//
        
        r4=r;
        c4=c;
    }


    //update the count after placing the unit.
 	count+=1;


    // dividing the 2d matrix into four parts - we call the battalion selection function and the soldier placing function
    tile_max=find_max_battalion(different_battalion,number_types);
    count=soldiers_placing_strategy(arr_type, arr_seq, r1,c1, n / 2, different_battalion, number_types, x, y, count,tile_max);
    
    tile_max=find_max_battalion(different_battalion, number_types);
    count=soldiers_placing_strategy(arr_type, arr_seq, r2,c2, n / 2, different_battalion, number_types, x, y + n / 2, count,tile_max);
    
    tile_max=find_max_battalion(different_battalion, number_types);
    count=soldiers_placing_strategy(arr_type, arr_seq, r3,c3, n / 2, different_battalion, number_types, x + n / 2, y,count,tile_max);
    
    tile_max=find_max_battalion(different_battalion, number_types);
    count=soldiers_placing_strategy(arr_type, arr_seq, r4,c4, n / 2, different_battalion, number_types, x + n / 2, y + n / 2, count,tile_max);

    //return count to update it in the parent function
    return count;
}



int main()
{
    // take inputs from the file/command line correctly
    int n;
    //take the first input as the size of saddle point
    scanf("%d ",&n);
    

    // declaring the matrix which shows the sequence 
    char** strategy;
    strategy = (char**)malloc(n * sizeof(char*));
    for (int i=0; i<n; i++)
         strategy[i] = (char*)malloc(n * sizeof(char));
 

    // declaring the matrix which shows the pattern 
    int** sequence;
    sequence = (int**)malloc(n * sizeof(int*));
    for (int i=0; i<n; i++)
         sequence[i] = (int*)malloc(n * sizeof(int));
 
    

    //take mine location
    int x,y;
    scanf("%d %d ",&x,&y);

    //setup the matrices
    setup_2d_array(strategy,sequence,x,y, n);

    int m;
    scanf("%d ",&m);
    
    //initialise different battalions
    struct battalion *different_battalions= (struct battalion *)malloc(sizeof(struct battalion)*m);
    

    //take inputs for different battalions
    for (int i = 0; i < m; i++)
    {   
        char temp_beta;
        int temp_num;
        scanf(" %c %d", &temp_beta,&temp_num);
        different_battalions[i].beta=temp_beta;
        different_battalions[i].num=temp_num;



    }
    //get initial battlaion from where the unit should be chosen
    char tile_max=find_max_battalion(different_battalions,m);
    soldiers_placing_strategy(strategy,sequence, x,y, n, different_battalions, m,0, 0, 1,tile_max);
    
    //print both the matrices
    print_array(strategy,sequence,n);
    printf("\n");
    //print the soldiers left
    print_soldiers_left(different_battalions,m);
    
    return 0;
}
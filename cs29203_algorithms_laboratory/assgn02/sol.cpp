#include <iostream>
using namespace std;
#define fMAX_LIMIT 20000
#define MAX_LIMIT 20000
typedef struct {
    char * color ;
    int npetals;
    int leaves;
    int radius;
    int height;} Flower;


int main() {
    int maxplrh[4];maxplrh[0]=0;maxplrh[1]=0;maxplrh[2]=0;maxplrh[3]=0;
    
    char yellow='y';
    char white = 'w';
    int ninputs,plrh[4],flag;
    Flower farray[fMAX_LIMIT];
    string inputline;
    scanf("%d\n",&ninputs);


    //Reading the inputs and storing in farray and also evaluating maximum dimensions needed for the 4D array to store counts at index position: [p,l,r,h]

    for(int i =0;i<ninputs;i++){
        char str[MAX_LIMIT];
        fgets(str, MAX_LIMIT, stdin);
        flag=0;
        int temp=0,index=0;
        for(int j=0;str[j]!='\n' && str[j]!='\0' ;j++){
            
            if(str[j]==','){
                
                if(flag==1){
                    plrh[index]=temp;
                    if(maxplrh[index]<plrh[index]){maxplrh[index]=plrh[index];}
                    temp=0;
                    index+=1;
                    
                }
               flag=1 ;
               
            }else{
            if(flag==1){
                temp*=10;
		//converting to number and storing
                temp+=(str[j]-'0');
            }
            }
        }
	//last index was not stored, storing now
        plrh[index]=temp;
        
        if(maxplrh[index]<plrh[index]){maxplrh[index]=plrh[index];}
        
        
        
        Flower f;
        if(str[0]=='y'){f.color=&yellow;}else{f.color=&white;}
        f.npetals=plrh[0];
        f.leaves=plrh[1];
        f.radius=plrh[2];
        f.height=plrh[3];
        farray[i]=f;
        
        
        
        
    }
    //resolving conflict of 0 based indexing and 1 based indexing by increasing memory .
    //All inputs are taken, initializing 4D array now
    maxplrh[0]+=1;
    maxplrh[1]+=1;
    maxplrh[2]+=1;
    maxplrh[3]+=1;
    int carray[maxplrh[0]][maxplrh[1]][maxplrh[2]][maxplrh[3]];
    
    for(int i1=0;i1<maxplrh[0];i1++){
            for(int i2=0;i2<maxplrh[1];i2++){
                for(int i3=0;i3<maxplrh[2];i3++){
                    for(int i4=0;i4<maxplrh[3];i4++){
                        carray[i1][i2][i3][i4]=0;}}}}
    
    
    int count=0;//count of possible answers

    for(int i =0;i<ninputs;i++){
        Flower f=farray[i];
        carray[f.npetals][f.leaves][f.radius][f.height]++;
        if(carray[f.npetals][f.leaves][f.radius][f.height]>1){
            
            
            
            
            
            count++;
        }
    }
    
    if(count==0){
        printf("RIP");
    }else{

	//I announced in the lab that by dictionary sorting we meant number wise sorting along with white ranked first, yellow second. 
	//In this solution we use number wise sorting; we have set the testcases so that both number sorters and actual dictionary sorters will pass.

        for(int i1=0;i1<maxplrh[0];i1++){
            for(int i2=0;i2<maxplrh[1];i2++){
                for(int i3=0;i3<maxplrh[2];i3++){
                    for(int i4=0;i4<maxplrh[3];i4++){
                        if(carray[i1][i2][i3][i4]>1){
                            
                            printf("white,%d,%d,%d,%d\n",i1,i2,i3,i4);
                            
                        }
                        
            
                    }
            
                }
            
            }
            
        }
        
    }
    
//The complexity of the algorithm is max(p)*max(l)*max(r)*max(h)
//As n is a large number, if n ~=max(p)*max(l)*max(r)*max(h) and m=O(n), it is the best solution.
//Other ways to solve the problem involve dictionary sorting(not characters, 4 numbers with left ones assuming higher significance than right ones) and pairwise comparision for white and yellow array, which will be of order m*log(m) or max(max(p),max(l),max(r),max(h)) depending on the sorting you use(quick/merge/heap vs counting). It can be solved using recursion easily.
//In case of counting sort the complexity is O(max(max(p),max(l),max(r),max(h)))=O(n) as n<=p,l,r,h
//While the last mentioned solution is the best approach, you will be given full marks with even O(max(p)*max(l)*max(r)*max(h)) also.     
    
    
    
    
    
    return 0;
}


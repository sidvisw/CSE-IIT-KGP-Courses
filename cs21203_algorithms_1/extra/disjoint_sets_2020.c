#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLOSED 0
#define OPEN 1

typedef struct _node {
   int rank;
   struct _node *parent;
} node;

node **makeset ( int m, int n )
{
   node **C;
   int i, j;

   C = (node **)malloc(m * sizeof(node *));
   for (i=0; i<m; ++i) {
      C[i] = (node *)malloc(n * sizeof(node));
      for (j=0; j<n; ++j) {
         C[i][j].rank = 0;
         C[i][j].parent = &(C[i][j]);
      }
   }
   return C;
}

char **inithorwalls ( int m, int n )
{
   int i, j;
   char **H;

   H = (char **)malloc((m-1) * sizeof(char *));
   for (i=0; i<=m-2; ++i) {
      H[i] = (char *)malloc(n * sizeof(char));
      for (j=0; j<n; ++j) {
         H[i][j] = CLOSED;
      }
   }
   return H;
}

char **initverwalls ( int m, int n )
{
   int i, j;
   char **V;

   V = (char **)malloc(m * sizeof(char *));
   for (i=0; i<m; ++i) {
      V[i] = (char *)malloc((n-1) * sizeof(char));
      for (j=0; j<=n-2; ++j)
        V[i][j] = CLOSED;
   }
   return V;
}

void printgrid ( char **H, char **V, int m, int n )
{
   int i, j;

   printf("    +"); 
   printf("   +");
   
   for (j=0; j<n-1; ++j) 
      printf("---+"); 
   
   printf("\n");
   
   for (i=0; i<m; ++i) 
   {
      printf("    |");
      for (j=0; j<=n-2; ++j)
         printf("   %c", (V[i][j] == CLOSED) ? '|' : ' ');

      if (i==m-1)
         printf("     \n");
      else 
         printf("   |\n");

      if (i != m-1) {
         printf("    ");
         for (j=0; j<n; ++j) 
            printf("+%s", (H[i][j] == CLOSED) ? "---" : "   ");
         
         printf("+\n");
      }
   }
   printf("    +"); 
   
   for (j=0; j<n; ++j) 
      printf("---+"); 
   
   printf("\n");
}

//PATH COMPRESSION
node *findset ( node *x)
{

   if (x -> parent != x)
      x->parent = findset(x->parent);
   return x->parent;
}



int mergeset (node *x, node *y )
{
   if (x == y) return 0;
   if (x -> rank > y -> rank) 
      y -> parent = x;
   else if (x -> rank < y -> rank) 
      x -> parent = y;
   else 
   {
      x -> parent = y;
      y -> rank += 1;
   }
      return 1;
}



void findtreasure ( node **C, char **H, char **V, int m, int n )
{
   int i1, i2, j1, j2, s, nmerge;
   node *x, *y;

   s = 1; nmerge = 0;

   while (s < (m*n)) {
      if (rand() % 2) {   
         /* Break horizontal stone wall */         
         i1 = rand() % (m-1); 
         i2 = i1 + 1;
         j1 = j2 = rand() % n;
         
         if (H[i1][j1] == OPEN) {
            continue;
         }

         x = findset(&C[i1][j1]);
         y = findset(&C[i2][j2]);
         if (x == y) {
            continue;
         } 
         H[i1][j1] = OPEN;
      
      } else {       
         /* Break vertical stone wall */
         i1 = i2 = rand() % m;  
         j1 = rand() % (n-1); 
         j2 = j1 + 1;

         if (V[i1][j1] == OPEN) {
            continue;
         } 
         x = findset(&C[i1][j1]);
         y = findset(&C[i2][j2]);

         if (x == y) {
            continue;
         } 
         
         V[i1][j1] = OPEN;
      }

      if (mergeset(x,y)==1) 
         {s++;
         ++nmerge;
      }
   }
   printf("\n grid created after %d stone wall removals\n", nmerge);
}

int main ( int argc, char *argv[] )
{
   int m, n;
   node **C;
   char **H, **V;
   int i,j,u,v;
   node *x,*y;

   if (argc >= 3) { 
      m = atoi(argv[1]); 
      n = atoi(argv[2]); 
   }
   else {
      scanf("%d%d", &m, &n);
   } 

   printf("    m = %d\n    n = %d\n", m, n);

   srand((unsigned int)time(NULL));

   C = makeset(m,n);
   H = inithorwalls(m,n);
   V = initverwalls(m,n);

   printf("\n Initial grid\n");
   printgrid(H,V,m,n);

   findtreasure(C,H,V,m,n);
   printf("\n Final grid\n");
   printgrid(H,V,m,n);
   x = findset(&C[m-1][n-1]); 
   y = findset(&C[0][0]);
   if (x==y) 
      printf("Found\n");
   else  
      printf("NOT Found\n");
   exit(0);

}

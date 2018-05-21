/*Libraries*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*Globals*/

/*Function Definitions*/
float** dispersal(char*, int, int);
float** vandermonde (int, int);
float determinant(float**, float);
float** cofactor(float**, float);
float** transpose(float**, float**, float);

int main(int argc, char const *argv[])
{
	int i, j, k;	
	FILE *textp, *output, *decomp;
	textp = fopen(argv[1], "rb");
	if(textp == NULL){
		printf("Input file not found\n");
		exit(1);
	}	
	fseek(textp, 0, SEEK_END);
	int lengthOfText = ftell(textp);
	char *content;
	fseek(textp, 0, SEEK_SET);
	//content = malloc(lengthOfText);
	//fread(content, 1, lengthOfText, textp);
	content = malloc(32 * sizeof(char));
	content = "abcdefghijklmnopqurtuvwxyz012345";
	lengthOfText = 32;

	float** packets;

	printf("Making Packets ... \n");
	int m = 4; 
	int n = 8;
	packets = dispersal(content, m, n);
	printf("Finished making packets\n");

	float **appendedarray, **inverse;
	appendedarray = vandermonde(4, 4); //to simulate getting first 4 packets;
	printf("Simulating first four a values\n");
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			printf("%f   ", appendedarray[i][j]);
		}
		printf("\n");
	}

	printf("\nBuilding inverse\n");
	inverse = cofactor(appendedarray, 4);

	float **recivedPackets = malloc(sizeof(float *) * m);

	printf("Grabing first four packets\n");
	for(i = 0; i < 4; i++){
		recivedPackets[i] = packets[i];
	}

	printf("Multiplying by inverse\n");
	float tot;
	float** final;
	final = malloc(sizeof(float*) * (lengthOfText / m));
	for(i = 0; i < (lengthOfText / m); i++){//top to bottom
		final[i] = malloc(sizeof(float) * (m)); 
		for(j = 0; j < (m); j++){ //left to right
			tot = 0;
			for(k = 0; k < m; k++){ 
				tot = tot + (inverse[j][k] * recivedPackets[k][i]);
			} 
			final[i][j] = tot;
		}
	}


	printf("printing results:\n\n");
	int new, itt;
	for(i = 0; i < (lengthOfText / m); i++){
		for(j = 0; j < (m); j++){
			new = final[i][j];
			itt++;
			printf("%c", new);
		}
	}
	printf("\n\n");
	return 0;
}


float** dispersal(char* content, int m, int n){
	int length = strlen(content);
	float** matrix = malloc(sizeof(float *) * (length/m)); //STARTS AT 1
	int i, j, k;
	float tot; 
	for(i = 0; i < (length/m); i++){ //building matrix M
		int firstElem = ((i)*m);
		matrix[i] = malloc(sizeof(float) * m); // IN THIS CASE BYTES START AT 1
		for(j = 0; j < m; j++){ //building array S
			matrix[i][j] = content[j + firstElem];
		}
	}

	float** A;
	int itt = 0;
	A = vandermonde(m, n);
	//Now multiply A and M to get packets to send
	float** packets;
	packets = malloc(sizeof(float*) * (n));
	for(i = 0; i < n; i++){ //top to bottom;
		packets[i] = malloc(sizeof(float) * (length/m));
		for(j = 0; j < (length / m); j++){ 	//left to right
			tot = 0;
			for(k = 0; k < m; k++){		//mult each elem together and add to tot		
				tot = tot + (A[i][k] * matrix[j][k]);
			}
			packets[i][j] = tot;
			itt++;
		}
	}
	return packets;
}


float **vandermonde (int m, int n){
  float **	a;
  a = malloc(sizeof(float *) * n);
  int i, j, k;
  for(i = 0; i < n; i++){
  	a[i] = malloc(sizeof(float) * m);
  	for(j = 0; j < m; j++){
  		a[i][j] = pow(i + 1, j);
  	}
  }
  return a;
}


/*
*  Original Author : Manish Bhojasia
*  Source          : https://www.sanfoundry.com/c-program-find-inverse-matrix/
*  Modified By     : Trent Vasquez 5/20/2018
*/
float determinant(float **a, float k)
{
  float s = 1, det = 0;
  int i, j, m, n, c;
  float** b = malloc(sizeof(float *) * k);
  for(i = 0; i < k; i++){
 	b[i] = malloc(sizeof(float) * k);
  }
  if (k == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < k; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < k; i++)
          {
            for (j = 0 ;j < k; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = a[i][j];
                   if (n < (k - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * determinant(b, k - 1));
          s = -1 * s;
          }
    }
 
    return (det);
}
 
/*
*  Original Author : Manish Bhojasia
*  Source          : https://www.sanfoundry.com/c-program-find-inverse-matrix/
*  Modified By     : Trent Vasquez 5/20/2018
*/ 
float** cofactor(float **num, float f)
{
 float** b = malloc(sizeof(float*) * f);
 float** fac = malloc(sizeof(float*) * f);
 int p, q, m, n, i, j;
 for(i = 0; i < f; i++){
 	b[i] = malloc(sizeof(float) * f);
  	fac[i] = malloc(sizeof(float) * f);	
 }
 for (q = 0;q < f; q++)
 {
   for (p = 0;p < f; p++)
    {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++)
     {
       for (j = 0;j < f; j++)
        {
          if (i != q && j != p)
          {
            b[m][n] = num[i][j];
            if (n < (f - 2))
             n++;
            else
             {
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }
  return transpose(num, fac, f);
}

/*
*  Original Author : Manish Bhojasia
*  Source          : https://www.sanfoundry.com/c-program-find-inverse-matrix/
*  Modified By     : Trent Vasquez 5/20/2018
*/
float** transpose(float **num, float **fac, float r)
{
  int i, j;
  float d;
  float** b = malloc(sizeof(float*) * r);
  float** inverse = malloc(sizeof(float*) * r);
  for(i = 0; i < r; i++){
  	b[i] = malloc(sizeof(float) * r);
   	inverse[i] = malloc(sizeof(float) * r);	
  }
 
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         b[i][j] = fac[j][i];
        }
    }
  d = determinant(num, r);
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
        inverse[i][j] = b[i][j] / d;
        }
    }
   printf("\n\n\nThe inverse of matrix is : \n");
 
   for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         printf("%f   ", inverse[i][j]);
        }
    printf("\n");
     }
     return inverse;
}
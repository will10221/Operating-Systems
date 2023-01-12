/*William Bailey
Dr. Chunyan Bai
COMSC420 Operating Systems
11/7/2022
Purpose: to use multithreaded programming to calculate different values of an array
Note: because of sqrt funcition -lm needs to be added at the end of compilation command
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

//Global variable declaration
int sum = 0;
int min = 0;
int max = 0;
float nmean;
int med;
int n = 7;
float avgg;

//Average calulator
void *cavg(void *param){
    int *val = (int *)param;
    int sum = 0;

    for(int i=0; i < n; i++){
        sum += val[i];
    }
    avgg = sum / n;
    pthread_exit(0);
}
//Minimum Calculator
void *cmin(void*param){
    int *ar = (int *)param;

    int i;
    min = ar[0];
    for(i = 0; i < n; i++) {
        if(ar[i]<min){
        min = ar[i];
        }

   }
    pthread_exit(0);
}
//Maximum Calculator
void *cmax(void*param){
    int *ar = (int *)param;
    int i;
    max = ar[0];
    for(i = 0; i < n; i++) {
        if(ar[i]>max){
        max = ar[i];
        }

   }
    pthread_exit(0);
}
//Median Calculator
void *cmed(void*param){
    int *ar = (int *)param;

    int i;
    if(n%2 == 1){
        med=ar[((n+1)/2)-1];
    }else{
        med=ar[(((n/2)-1)+(n/2))/2];
    }
    pthread_exit(0);
}
//Standard Deviation Calculator
void *cstdev(void*param){
    int *ar = (int *)param;

    int mean = 0;
    int total = 0;
    int ntotal = 0;

    int val = 0;
    for(int i = 0; i < n; i++) {
      total += ar[i];
   }
   
   mean = total/n;
   for(int i = 0; i<n; i++){
      val = (ar[i] - mean)*(ar[i] - mean);
      ntotal = ntotal + val;
   }
    nmean = sqrt(ntotal/(float)n);
    pthread_exit(0);

}

int main(int argc, char *argv[]){
//Memory allocation using malloc
int size;
int *num = (int*)malloc((argc-1)*sizeof(int));
    for(int i=1; i<argc ; i++){
        num[i-1] = atoi(argv[i]);
        size++;
    }  
    int ar[] = {90, 81, 78, 95, 79, 72, 85};
    //The different threads that will execute each function
    pthread_t avgf;
    pthread_t minf;
    pthread_t maxf;
    pthread_t medf;
    pthread_t stdevf;

    //Creation of the threads
    pthread_create(&avgf,NULL,cavg,ar);
    pthread_create(&minf,NULL,cmin,ar);
    pthread_create(&maxf,NULL,cmax,ar);
    pthread_create(&medf,NULL,cmed,ar);
    pthread_create(&stdevf,NULL,cstdev,ar);

    //Joining of threads
    pthread_join(avgf,NULL);
    pthread_join(minf,NULL);
    pthread_join(maxf,NULL);
    pthread_join(medf,NULL);
    pthread_join(stdevf,NULL);

    //Prints the values
    printf("Average = %f\n", avgg);
    printf("Minimum = %d\n", min);
    printf("Maximum = %d\n", max);
    printf("Median  = %d\n", med);
    printf("Standard Deviation = %f\n", nmean);

   
    //Exits the threads
    pthread_exit(NULL);  
    pthread_exit(NULL);
    pthread_exit(NULL);  
    pthread_exit(NULL);
    pthread_exit(NULL);  

   
    return 0;
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int get_sample_num(char* in_arr);
void get_samples(char* in_arr, int num_sample, double* sample);
double get_mean(double* sample, int n);
double get_second_moment(double* sample1, double* sample2, double mean1, double mean2, int n);


int  main (int argc, char** argv)
{  
   // You don't need to modify the main function
    
   //for(int i; i <= argc; i++){
      //printf("input %s, length %d \n", argv[i], sizeof(argv[i]));
   //}
   //printf("\n");
   int i;
   
   i = 1;
   int n1 = get_sample_num(argv[i]);
   double s1[n1];
   get_samples(argv[i], n1, s1);
   //for(int i = 0; i<n1; i++){
   //   printf("%lf \n", s1[i]);
   //}
   double m1 = get_mean(s1, n1);
   double v1 = get_second_moment(s1, s1, m1, m1, n1);
   
   i = 2;
   int n2 = get_sample_num(argv[i]);
   double s2[n2];
   get_samples(argv[i], n2, s2);
   //for(int i = 0; i<n2; i++){
   //   printf("%lf \n", s2[i]);
   //}
   double m2 = get_mean(s2, n2);
   double v2 = get_second_moment(s2, s2, m2, m2, n2);
   
   double cov = get_second_moment(s1, s2, m1, m2, n2);
   
   printf("The Cov of two input arrays is %0.2lf, and their own Var are %0.2lf and %0.2lf. \n", cov, v1, v2);
   return 0;
}

int get_sample_num(char* in_arr){
   // determine the sample number by counting space
   int i = 0;
   int spaces = 0;
   while (in_arr[i] != '\0') {
      if (in_arr[i] == ' ') {
         spaces++;
      }
      i++;
   }
   return spaces + 1;
    
}

void get_samples(char* in_arr, int num_sample, double* sample){
   int len = strlen(in_arr);
   //printf("len %d \n", len);
   // parse the string (char arr) and convert double
   char pure_in_arr[len-2];
   for(int i = 0; i < len-2; i++){
      pure_in_arr[i] = in_arr[i+1];
   }
   //printf("ori in: %s \n", in_arr);
   //printf("pure in: %s \n", pure_in_arr);
   
   //double sample[num_space+1];
   char *token;
   char *d = "[], ";
   token = strtok(pure_in_arr, d);
   int sample_idx = 0;
   while(token != NULL){
      //printf("token %s %lf \n", token, atof(token));
      sample[sample_idx] = atof(token);
      token = strtok(NULL, d);
      sample_idx ++;
   }  
}

double get_mean(double* sample, int n){
   // compute the mean value of input array (sample), given its length (n)
   double sum = 0;
   for (int i = 0; i < n; i++) {
      sum += sample[i];
   }
   return sum / n;
}

double get_second_moment(double* sample1, double* sample2, double mean1, double mean2, int n){
   // compute the second moment of two input arrays (sample1 and sample2), given their mean values (mean1 and mean2) and the length (n)
   double sum = 0;
   for (int i = 0; i < n; i++) {
      sum += (sample1[i] - mean1) * (sample2[i] - mean2);
   }
   return sum / (n-1); 
}






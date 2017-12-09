// Code sample from https://www.programiz.com/c-programming/c-arrays-functions

#include <stdio.h>

float average(float age[]);
const int CITY = 2;
const int WEEK = 7;

int main() {
  float avg, age[] = {23.4, 55, 22.6, 3, 40.5, 18};
  avg = average(age); /* Only name of array is passed as argument. */
  printf("Average age=%.2f", avg);

  int temperature[CITY][WEEK];
  for (int i = 0; i < CITY; ++i) {
    for (int j = 0; j < WEEK; ++j) {
      printf("City %d, Day %d: ", i + 1, j + 1);
      scanf("%d", &temperature[i][j]);
    }
  }

  printf("\nDisplaying values: \n\n");
  for (int i = 0; i < CITY; ++i) {
    for (int j = 0; j < WEEK; ++j) {
      printf("City %d, Day %d = %d\n", i + 1, j + 1, temperature[i][j]);
    }
  }
  return 0;
}

float average(float age[]) {
  int i;
  float avg, sum = 0.0;
  for (i = 0; i < 6; ++i) {
    sum += age[i];
  }
  avg = (sum / 6);
  return avg;
}
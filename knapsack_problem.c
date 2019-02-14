#include<stdio.h>

#define SIZE_A 4
#define CAPACITY_A 10
#define SIZE_B 10
#define CAPACITY_B 165
#define MAX_CAPACITY CAPACITY_B
#define MAX_N SIZE_B


int m[MAX_N][MAX_CAPACITY+1];

int max(int x, int y) {

return x > y ? x : y;
}

void prepareMemoizationArray() {

 int i, j;
 for(i = 0; i < MAX_N; i++){

 	for(j = 0; j < MAX_CAPACITY + 1; j++){
 
		m[i][j] = -1; 
		}
	}
 }
 
int knapsackRecursive(int capacity, int mass[], int profit[], int n){

if (n == 0 || capacity == 0) return 0;
int dont_take = knapsackRecursive(capacity, mass, profit, n-1);
int do_take = mass[n-1] > capacity ? 0 :
	profit[n-1] + knapsackRecursive(capacity-mass[n-1], mass, profit, n-1);

 return max(dont_take, do_take);
 }

int knapsackMemoized(int capacity, int mass[], int profit[], int n) {

 if (n == 0 || capacity == 0) return 0;
 if(m[n-1][capacity - 1] > -1) return m[n-1][capacity -1];
 int dont_take = knapsackMemoized(capacity, mass, profit, n-1);
int do_take = mass[n-1] > capacity ? 0 :
		profit[n-1] + knapsackMemoized(capacity- mass[n-1], mass, profit, n-1);
 return m[n-1][capacity-1] = max(dont_take, do_take);
}

int knapsackDynamic(int capacity, int mass[], int profit[], int n) {
int i, w;

for(w = 0; w < mass[0] && w <=capacity; w++) m[0][w] = 0; 
for(w = mass[0]; w<=capacity; w++) m[0][w] = profit[0]; 

for(i = 1; i < n; i++){

for(w = 0; w <=capacity; w++) {

	int dont_take = m[i-1][w];
	int do_take = mass[i] > w ? 0 : profit[i] + m[i-1][w - mass[i]];
	m[i][w] = max(dont_take, do_take);
}
}
return m[n-1][capacity];
}

int main(){
int testMassA[] = {6, 3, 2, 4};
int testProfitA[] = {50, 60, 40, 20};

int testMassB[] = {23, 31, 29, 44, 53, 38, 63, 85, 89, 82};
int testProfitB[] = {92, 57, 49, 68, 60, 43, 67, 84, 87, 72};

printf("knapsackRecursive:\n");
printf("Max value A: %d\n", knapsackRecursive(CAPACITY_A, testMassA, testProfitA, SIZE_A));
printf("Max value B: %d\n", knapsackRecursive(CAPACITY_B, testMassB, testProfitB, SIZE_B));
printf("\n");

prepareMemoizationArray();
printf("knapsackMemoized:\n");
printf("Max value A: %d\n", knapsackMemoized(CAPACITY_A, testMassA, testProfitA, SIZE_A));
prepareMemoizationArray();
printf("Max value B: %d\n", knapsackMemoized(CAPACITY_B, testMassB, testProfitB, SIZE_B));
printf("\n");

printf("knapsackDynamic:\n");
printf("Max value A: %d\n", knapsackDynamic(CAPACITY_A, testMassA, testProfitA, SIZE_A));
printf("Max value B: %d\n", knapsackDynamic(CAPACITY_B, testMassB, testProfitB, SIZE_B));
return 0;
}

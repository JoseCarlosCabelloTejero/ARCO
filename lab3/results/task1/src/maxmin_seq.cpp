#include <iostream>
#include <ctime>
#include <omp.h>

void get_max_min_value(int arr[], int size, int *max, int *min);

int main() {

    int size = 10000000;
    int* arr = (int* ) malloc(size * sizeof(int));

    srand(0);

    for(int i = 0; i < size; i++) {
        arr[i] = rand() % 10;
    }

	int max = arr[0];
	int min = arr[0];
	double wtime;

	wtime = omp_get_wtime();
	get_max_min_value(arr, size, &max, &min);
	wtime = omp_get_wtime() - wtime;

	std::cout << "Max value is: " << max << std::endl;
	std::cout << "Min value is: " << min << std::endl;
	
	std::cout << "Elapsed time: " << wtime << " s" << std::endl;

	free(arr);

	return 0;
}

void get_max_min_value(int arr[], int size, int *max, int *min) {

	for (int i = 1; i < size; i++) {
		if (*max < arr[i]) {
			*max = arr[i]; 
		}
		if (*min > arr[i]) {
			*min = arr[i];
		}
	}
}

#include <iostream>
#include <ctime>
#include <omp.h>

void get_max_min_value(int arr[], int size, int &max, int &min);

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
	get_max_min_value(arr, size, max, min);
	wtime = omp_get_wtime() - wtime;

	std::cout << "Max value is: " << max << std::endl;
	std::cout << "Min value is: " << min << std::endl;
	
	std::cout << "Elapsed time: " << wtime << " s" << std::endl;
	
	free(arr);

	return 0;
}

void get_max_min_value(int arr[], int size, int &max, int &min) {
    
	omp_set_num_threads(2);

	if (size == 1) {
        max = arr[0];
        min = arr[0];
        return;
    }
    int mid = size / 2;
    int max1, min1, max2, min2;

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			get_max_min_value(arr, mid, max1, min1);
		}
		#pragma omp section
		{
			get_max_min_value(arr + mid, size - mid, max2, min2);
		}
	}
    max = max1 > max2 ? max1 : max2;
    min = min1 < min2 ? min1 : min2;
}


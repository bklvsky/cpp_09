#include <iostream>

void swap(int & a, int & b) {
	a += b;
	b = a - b;
	a -= b;
}

void insertionSort(int arr[], int n) {
	for (int right = 1; right < n; right++) {
		int left = right - 1;
		int key = arr[right];
		while (left >= 0 && key < arr[left]) {
			arr[left + 1] = arr[left];
			left -= 1;
		}
		arr[left + 1] = key;
	}
}

void putArray (int arr[], int n) {
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	int arr[] = {0, 3, 4, 10, 7, 2, 9, 1, 5, 6, 8};

	int size = sizeof(arr) / sizeof(arr[0]);
	insertionSort(arr, size);
	putArray(arr, size);
}

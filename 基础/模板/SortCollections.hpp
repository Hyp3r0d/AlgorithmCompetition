#include<bits/stdc++.h>

template<typename T>
struct SortCollections {
public:
	i64 pairtition(std::vector<T>&a, i64 low, i64 high) {
		T pivot = a[low];
		while (low < high) {
			while (low < high and pivot <= a[high])--high;
			a[low] = a[high];
			while (low < high and a[low] <= pivot)++low;
			a[high] = a[low];
		}
		a[low] = pivot;
		return low;
	}
	
	void preQuickSort(std::vector<T>&a, i64 low, i64 high) {
		if (low >= high)return;
		i64 pivot = pairtition(a, low, high);
		preQuickSort(a, low, pivot - 1);
		preQuickSort(a, pivot + 1, high);
	}

	void quickSort(std::vector<T>&a, i64 len) {
		preQuickSort(a, 1, len);
	}
};



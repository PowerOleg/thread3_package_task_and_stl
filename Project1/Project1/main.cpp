#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

template <typename T>
void print(const T array, const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void sort(const std::vector<int> source, const int size, std::promise<int*> promise)
{
	int* array = new int[size];
	std::copy(source.begin(), source.end(), array);

	for (size_t i = 0; i < size - 1; i++)
	{
		int imin = i;
		for (size_t j = i + 1; j < size; j++)//code to find index of the min value
		{
			if (array[j] < array[imin])
			{
				imin = j;
			}
		}
		int a = array[i];//just swap() between the min value element and the end element of the array
		array[i] = array[imin];
		array[imin] = a;
	}
	promise.set_value(array);//promise.set_value_at_thread_exit(array);//error here
}

std::vector<int> init_filled_vector(const int n)
{
	std::vector<int> vector;//(n);
	vector.reserve(n);
	for (size_t i = 0, j = n - 1; i < n; i++, j--)//fill the array
	{
		vector.push_back(j);//vector[i] = j;
	}
	print(vector, n);
	return vector;
}

int main(int argc, char** argv)
{
	std::promise<int*> promise;
	std::future<int*> future = promise.get_future();
	
	const int n = 20;
	std::vector<int> vector = init_filled_vector(n);
	std::thread thread1(sort, vector, n, std::move(promise));
	thread1.join();//No one reacts to this
	int* sorted_array = future.get();

	print(sorted_array, n);
	delete[] sorted_array;
	return 0;
}



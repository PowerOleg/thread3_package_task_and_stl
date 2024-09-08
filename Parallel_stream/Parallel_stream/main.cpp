#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <future>
#include <functional>


template <typename T>
void print(const T array, const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

std::vector<int> init_filled_vector(const int n)
{
	std::vector<int> vector;
	vector.reserve(n);
	for (int i = 0, j = n - 1; i < n; i++, j--)
	{
		vector.push_back(i);
	}
	print(vector, n);
	return vector;
}

/*void work(int number)
{
	std::this_thread::sleep_for(std::chrono::seconds(number));
	//task();
}*/

//template<typename T>
void parallel_stream(std::vector<int>::iterator first, std::vector<int>::iterator last, /*T&&*/ std::function<int(int)> const& function)
{
	std::transform(first, last, first, function);
	std::for_each(first, last, [](int n) {std::cout << n << " "; });
	std::cout << std::endl;


	unsigned int cores_quantity = std::thread::hardware_concurrency();
	//std::packaged_task<int()> task(std::bind(parallel_stream, vector.begin(), vector.end(), std::move(function)));
	//std::future<int> future = task.get_future();
	//std::thread t1(std::move(task));
	//future.get();
	//t1.join();


	//std::execution::seq дл€ последовательного выполнени€ алгоритма;
	//используйте std::execution::par дл€ паралельного выполнени€
}

//auto p_lambda = std::make_unique<void()>(lambda);
int main(int argc, char** argv)
{
	const int size = 10;
	std::vector<int> vector = init_filled_vector(size);
	auto lambda = [](int n) { return n * n;	};
	std::function<int(int)> function(lambda);
	parallel_stream(vector.begin(), vector.end(), std::move(function));

	print(vector, 10);

	return 0;
}
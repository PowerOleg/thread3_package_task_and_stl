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
	for (size_t i = 0, j = n - 1; i < n; i++, j--)
	{
		vector.push_back(i);
	}
	print(vector, n);
	return vector;
}

void work()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

template<typename T>
void parallel_stream(std::vector<int>::iterator first, std::vector<int>::iterator last, T&& /*std::function<void()> const&*/  /*std::unique_ptr<void()>*/ lambda)
{
	unsigned int cores_quantity = std::thread::hardware_concurrency();
	//create package_task and run
	for (size_t i = 0; i < cores_quantity - 2; i++)
	{

	}

	std::for_each(first, last, lambda);

}

int main(int argc, char** argv)
{
	const int size = 10;
	std::vector<int> vector = init_filled_vector(size);

	auto lambda = [](int n) { return ++n; };
	//std::function<void()> function  = lambda;
	//std::shared_ptr<std::unique_ptr<int>> pplambda = std::make_shared<std::unique_ptr<int>>(std::move(lambda));
	auto plambda = std::make_unique<void()>(lambda);
	

	parallel_stream(vector.begin(), vector.end(), std::move(lambda));
	

	return 0;
}
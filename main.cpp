#include <fstream>
#include <string>
#include <sstream>

struct Data
{
	int n = -1;
	std::string s = std::string{ 0 };
};

void downHeap(Data* a, long k, long n) 
{
	Data new_elem = std::move(a[k]);
	long child;
	while (k <= n / 2) {   
		child = 2 * k;

		if (child < n && a[child].n < a[child + 1].n)
			child++;
		if (new_elem.n >= a[child].n) break;

		a[k] = a[child];
		k = child;
	}
	a[k] = new_elem;
}

int main(int argc, char *argv[])
{
	if (argc != 3) return 1;

	std::ifstream input{ argv[1] };
	if (input.is_open() == false)
		return 2;
	
	int count = -1;
	input >> count;
	if (count == -1)
		return 3;
	if (input.get() != '\n')
		return 3;
	Data* array = new Data[count];
	for (int i = 0; i < count; i++)
	{
		Data current;
		int n = -1;
		input >> n;
		if (n == -1) return 3;
		std::getline(input, current.s);
		if (current.s[0] != ' ') return 3;
		current.n = n;
		array[i] = std::move(current);
	}


	for (int i = count / 2; i >= 0; i--) 
		downHeap(array, i, count - 1);

	for (int i = count - 1; i > 0; i--) 
	{
		Data temp = std::move(array[i]);
		array[i] = std::move(array[0]);
		array[0] = std::move(temp);

		downHeap(array, 0, i - 1);
	}

	std::stringstream output_stream;
	output_stream << count;
	for (int i = 0; i < count; i++)
	{
		Data& data = array[i];
		output_stream.put('\n') << data.n << data.s;
	}
	std::ofstream output{ argv[2], std::ios_base::out }; 
	output << output_stream.str();
	output.close();
	return 0;
}

#include <iostream>
#include <string>
#include <assert.h>
#include <functional>
#include <set>
#include <vector>
#include <thread>
#include "../src/Hashmap.h"

using std::cout;
using std::string;
using std::set;
using std::vector;
using std::thread;

using tshm::Hashmap;

int main() {
	cout << "\n\nHASHMAP TESTING...\n\n";

	cout << "Testing single value...\n";
	Hashmap<string, int> hashmap(5'000);
	hashmap.put("test", 5);
	auto [contained, value] = hashmap.get("test");
	assert(contained && value == 5);

	// Generate 1,000 random unique strings for testing
	set<string> seen;
	for (int i = 0; i < 1'000; i++) {
		string str;
		do {
			str = "";
			for (int j = 0; j < 5; j++)
				str += 'a' + (rand() % 26);
		} while (!(seen.insert(str).second));
	}
	vector<string> rands(seen.begin(), seen.end());

	auto putJob = [&](int start, int end) {
		for (int i = start; i <= end; i++)
			hashmap.put(rands[i], i);
	};

	auto getJob = [&](int start, int end) {
		for (int i = start; i <= end; i++) {
			auto [contained, value] = hashmap.get(rands[i]);
			assert(contained && value == i);
		}
	};

	cout << "Testing threaded put...\n";
	vector<thread> threads;
	for (int i = 0; i < 10; i++)
		threads.emplace_back(putJob, i*10, i*10 + 9);
	for (thread &t : threads)
		t.join();
	threads.clear();

	cout << "Testing threaded get...\n";
	for (int i = 0; i < 10; i++)
		threads.emplace_back(getJob, i*10, i*10 + 9);
	for (thread &t : threads)
		t.join();
	threads.clear();

	cout << "\nSuccess :D\n";

	return 0;
}


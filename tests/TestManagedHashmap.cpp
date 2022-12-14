#include <iostream>
#include <string>
#include <assert.h>
#include <functional>
#include "../src/Hashmap.h"

using std::cout;
using std::string;

using tshm::ManagedHashmap;

int main() {
	cout << "\n\nMANAGED HASHMAP TESTING...\n\n";

	cout << "Testing single value...\n";
	ManagedHashmap<string, int> hashmap(5'000);
	hashmap.put("test", 5);
	auto [contained, value] = hashmap.get("test");
	assert(contained && value == 5);

	cout << "Testing threaded put...\n";
	for (int i = 0; i < 26; i++) {
		string key(1, 'a' + i);
		hashmap.put(key, i);
	}

	cout << "Testing sequential get...\n";
	for (int i = 0; i < 26; i++) {
		string key(1, 'a' + i);
		auto [contained, value] = hashmap.get(key);
		assert(contained && value == i);
	}

	cout << "Testing threaded overwrites...\n";
	for (int i = 0; i < 26; i++) {
		string key(1, 'a' + i);
		hashmap.put(key, 2*i);
	}
	for (int i = 0; i < 26; i++) {
		string key(1, 'a' + i);
		auto [contained, value] = hashmap.get(key);
		assert(contained && value == 2*i);
	}

	cout << "\nSuccess :D\n";

	return 0;
}


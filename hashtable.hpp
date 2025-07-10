// Gerard Kramer
// COP4530
// Assignment 5 - hashtable.hpp



// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}



// BELOW IS NEW CODE FOR ASSIGNMENT



// constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) 
    : table(prime_below(size > 0 ? size : default_capacity)), numElements(0) {}

// destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    clear();
}

// clears the hash table
template <typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}

template <typename K, typename V>
typename std::vector<std::list<std::pair<K, V>>>::iterator HashTable<K, V>::begin() {
    // returns iterator to the first element
    return table.begin();
}

template <typename K, typename V>
typename std::vector<std::list<std::pair<K, V>>>::iterator HashTable<K, V>::end() {
    // returns iterator past the last element
    return table.end();
}

template <typename K, typename V>
K HashTable<K, V>::getKey(const V &value) const {
    // iterate through all the lists in the hash table
    for (const auto &bucket : table) {
        for (const auto &pair : bucket) {
            // if value matches, return the corresponding key
            if (pair.second == value) {
                return pair.first; // return the key associated with the value
            }
        }
    }

    // if the value was not found
    throw std::invalid_argument("Value not found in the hash table");
}

template <typename K, typename V>
V HashTable<K, V>::getValue(const K &key) const {
    size_t index = myhash(key);

    // searchfor the key-value pair
    for (const auto &pair : table[index]) {
        if (pair.first == key) {
            return pair.second; // return the value corresponding to the key
        }
    }

    // if not found
    throw std::invalid_argument("Key not found in the hash table");
}

template <typename K, typename V>
std::list<std::pair<K, V>>* HashTable<K, V>::find(const K &key) { // find entry - self-explanatory
    size_t index = myhash(key);

    for (auto &pair : table[index]) {
        if (pair.first == key) {
            return &table[index];
        }
    }

    return nullptr;
}

// checks if a key is in the hash table
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const {
    auto &list = table[myhash(k)];
    for (auto &pair : list) {
        if (pair.first == k) {
            return true;
        }
    }
    return false;
}

// matches a key-value pair
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const {
    auto &list = table[myhash(kv.first)];
    for (const auto &pair : list) {
        if (pair == kv) {
            return true;
        }
    }
    return false;
}

// inserts a key-value pair
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> &kv) {
    auto &list = table[myhash(kv.first)];
    for (auto &pair : list) {
        if (pair.first == kv.first) {
            if (pair.second == kv.second)
                return false;
            pair.second = kv.second;
            return true;
        }
    }
    list.push_back(kv);
    if (++numElements > table.size()) {
        rehash();
    }
    return true;
}

// inserts a key-value pair using move semantics
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> &&kv) {
    auto &list = table[myhash(kv.first)];
    for (auto &pair : list) {
        if (pair.first == kv.first) {
            if (pair.second == kv.second)
                return false;
            pair.second = std::move(kv.second);
            return true;
        }
    }
    list.push_back(std::move(kv));
    if (++numElements > table.size()) {
        rehash();
    }
    return true;
}

// removes a key from the hash table
template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k) {
    auto &list = table[myhash(k)];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->first == k) {
            list.erase(it);
            --numElements;
            return true;
        }
    }
    return false;
}

// outputs the hash table's contents
template <typename K, typename V>
void HashTable<K, V>::dump() const {
    for (size_t i = 0; i < table.size(); ++i) {
        std::cout << "v[" << i << "]: ";
        const auto &pair = table[i];
        for (auto it = pair.begin(); it != pair.end(); ++it) {
            std::cout << it->first << " " << it->second;
            if (std::next(it) != table[i].end()) { // check if not the last element
                std::cout << ":"; // print colon if more elements follow
            }
        }
        std::cout << std::endl;
    }
}

// returns the size of the hash table
template <typename K, typename V>
size_t HashTable<K, V>::size() const {
    return numElements;
}

// writes the hash table to a file
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return false;
    }
    for (const auto &list : table) {
        for (const auto &pair : list) {
            outFile << pair.first << " " << pair.second << "\n";
        }
    }
    return true;
}

// loads key-value pairs from a file
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false;
    }
    K key;
    V value;
    while (inFile >> key >> value) {
        insert({key, value});
    }
    return true;
}

// clears all elements in the table
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for (auto &list : table) {
        list.clear();
    }
    numElements = 0;
}

// rehashes the hash table when it grows too large
template <typename K, typename V>
void HashTable<K, V>::rehash() {
    auto oldTable = table;
    table.resize(prime_below(2 * table.size()));
    for (auto &list : table) {
        list.clear();
    }
    numElements = 0;
    for (const auto &list : oldTable) {
        for (const auto &pair : list) {
            insert(pair);
        }
    }
}

// computes the hash index for a key
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const {
    static std::hash<K> hashFunc;
    return hashFunc(k) % table.size();
}

#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned int (HashFunc)(const char*);


template <typename Value, size_t B, HashFunc HF>
class HashTable
{
	struct Bucket
	{
		MyString key;
		Value val;
		Bucket* next;
		Bucket(MyString k, Value v) : key(k), val(v), next(0){}
		~Bucket() {}
	};

	Bucket buckets*[B];

	public:

	HashTable();
	~HashTable();

	bool has(const char* key) const;
	Value& get(const char* key);
	const Value& get(const char* key) const;
	void insert(const char* key, Value& val);

	friend class iterator;

	class iterator
	{
	  friend class HashTable;
		Bucket* buckets;
		size_t  S;
		size_t  cur_bucket;
		Bucket* cur_element;
		
		iterator(Bucket* b, size_t s, size_t cb, Bucket* ce)
		: buckets(b), S(s), cur_bucket(cb), cur_element(ce)
		{}

		public:
		iterator(); // empty
		iterator(const iterator& ) = default;
		iterator& operator++();
		const char* key();
    Value& val();
		const Value& val() const;
		bool operator=(const iterator& it) const;
	};

	iterator begin();
	iterator end();

};

template <typename Value, size_t B, HashFunc HF>
HashTable<Value,B,HF>::HashTable()
{
	for(Bucket** it = buckets; it != buckets+B; ++it) *it = 0;
}

template <typename Value, size_t B, HashFunc HF>
HashTable<Value,B,HF>::~HashTable()
{
	for(Bucket** it = buckets; it != buckets+B; ++it)
	{
		while (*it)
		{
		  Bucket* next = *it->next;
			delete *it;
			*it = next;
		}
	}
}


template <typename Value, size_t B, HashFunc HF>
bool HashTable<Value,B,HF>::has(const char* key) const
{
	size_t idx = HF(key) % B;
	Bucket* it = buckets[idx];
	while(it)
	{
		if(!strcmp(it->key,key)) return true;
		it = it->next;
	}
	return false;
}

template <typename Value, size_t B, HashFunc HF>
void HashTable<Value,B,HF>::insert(const char* key, Value v) 
{
	size_t idx = HF(key) % B;
	Bucket* cur = buckets[idx];

  Bucket* newBucket = new Bucket(key, v);
	newBucket->next = cur;
	buckets[idx] = newBucket;
}

///////////

unsigned int HashH37(const char * str)
{

	unsigned int hash = 2139062143;

	for(; *str; str++)
		hash = 37 * hash + *str;

	return hash;

}



int main()
{

  HashTable<int, 100, HashH37> htH37;

	htH37.insert("Ivanov",    100);
	htH37.insert("Petrov",    1000);
	htH37.insert("Sidorov",   14);
	htH37.insert("Kuznetsov", 1);

  cout << "{" << endl;
	for(auto it = htH37.begin(); it != htH37.end(); it++)
	{
	  cout << "\"" << it.key << "\" : " << key.value << " ," << endl;
	}
  cout << "}" << endl;

	if (htH37.has("Ivanov")) htH37.get("Ivanov") = 1000;

  cout << "{" << endl;
	for(auto it = htH37.begin(); it != htH37.end(); it++)
	{
	  cout << "\"" << it.key << "\" : " << key.value << " ," << endl;
	}
  cout << "}" << endl;


  return 0;
}


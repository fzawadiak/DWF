typedef struct HashEntry {
	char* key;
	int value;
	HashEntry* prev;
	HashEntry* next;
} HashEntry;

class HashTable {
private:
	long size;
	HashEntry* first;
	HashEntry* last;
	HashEntry* entries;

	long calc_hash(char* key);
public:
	HashTable(long size);
	~HashTable();
	void insert(char* key, int value);
	void remove(char* key);
	int get(char* key);
	HashEntry* get_last();
	HashEntry* get_first();
};
	

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "HashTable.hh"

long
HashTable::calc_hash(char* key) {
	long hash = 0;

	while(*key != 0) {
		hash += *key++;
		hash <<= 4;
	}

	return hash;
};

HashTable::HashTable(long nsize) {
	size = nsize;
	entries = new HashEntry[nsize];
};

HashTable::~HashTable() {
	for(long slot = 0; slot < size; slot++) {
		HashEntry* entry = &entries[slot];
		if(entry->key != NULL)
			free(entry->key);
	}
};

void
HashTable::insert(char* key, int value) {
	// Calculate hash key
	long hash = calc_hash(key);

	// Find slot in the entry table
	long slot = hash % size;

	// Find empty slot or used by the same key
	long tries = size;
	while(tries > 0) {
		HashEntry* entry = &entries[slot];

		if(entry->key == NULL) {
			// First time we store, copy key
			entry->key = strdup(key);
			entry->value = value;
		} else if(strcmp(entry->key,key) == 0) {
			// Already there, just update value
			entry->value = value;
		} else {
			tries--;
			slot = ++slot % size;
			continue;
		}

		if(first == NULL) {
			// Store first element
			first = entry;
		} else if(first == entry) {
			// Or move to other end
			first = first->next;
			entry->next = NULL;
		}
			

		// Link previous last element
		entry->prev = last;

		if(last != NULL)
			last->next = entry;

		// Store new last element
		last = entry;

		return;
	}
};

void
HashTable::remove(char* key) {
	// Calculate hash key
	long hash = calc_hash(key);

	// Find slot in the entry table
	long slot = hash % size;

	// Find empty slot or used by the same key
	long tries = size;
	while(tries > 0) {
		HashEntry* entry = &entries[slot];
	
		if(entry->key == NULL || strcmp(entry->key,key) != 0) {
			tries--;
			slot = ++slot % size;
			continue;
		}

		// Release key string
		free(entry->key);
		if(entry->prev != NULL)
			entry->prev->next = entry->next;
		else
			first = entry->next;

		if(entry->next != NULL)
			entry->next->prev = entry->prev;
		else
			last = entry->prev;


		// Reset HashEntry storage
		entry->key = NULL;
		entry->value = 0;
		entry->next = NULL;
		entry->prev = NULL;
	}
};

int
HashTable::get(char* key) {
	// Calculate hash key
	long hash = calc_hash(key);

	// Find slot in the entry table
	long slot = hash % size;

	// Find empty slot or used by the same key
	long tries = size;
	while(tries > 0) {
		HashEntry* entry = &entries[slot];

		if(entry->key != NULL && strcmp(entry->key,key) == 0) {
			// Key is found
			return entry->value;
		} else {
			tries--;
			slot = ++slot % size;
			continue;
		}
	}

	return 0;
};

HashEntry*
HashTable::get_last() {
	return last;
};

HashEntry*
HashTable::get_first() {
	return first;
};

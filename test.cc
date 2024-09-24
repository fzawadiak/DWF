#include "HashTable.hh"
#include <assert.h>

int main() {
	int value;
	HashEntry* entry;
	HashTable* ht = new HashTable(100);

	ht->insert("hello",1);
	entry = ht->get_last();
	assert(entry->value==1);

	ht->insert("world",2);
	entry = ht->get_last();
	assert(entry->value==2);

	value = ht->get("here");
	assert(value == 0);

	ht->insert("here",3);

	value = ht->get("world");
	assert(entry->value==2);

	entry = ht->get_first();
	assert(entry->value==1);
	ht->remove("hello");
	entry = ht->get_first();
	assert(entry->value==2);

	value = ht->get("world");
	assert(entry->value==2);

	ht->insert("world",4);
	entry = ht->get_last();
	assert(entry->value==4);

	value = ht->get("world");
	assert(entry->value==4);

}

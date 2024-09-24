Solution Hash Map:

Hash map plus double linked list of entries for LRU.
Removal is not very efficient as might require traversal of entire hash table looking for entries.
Could optimize by marking entries os "had collision" and do traversal only in those cases.
There are no error handling for overflows of hashmap capacity (one to handle that would have linked lists for each bucket).

I spent most of the time on this one, took almost 3 hours inclusive some dev env setup.

Solution Dataset:

If speed is not that important (and in this case I don't see why it would) I would mmap the file and then
go sequentially over if with two pointers, head and tail of current word. After finding whitespace character
whatever was between two pointers would be lowercased and added to the HashMap.

Did quick analysis of the file with commandline tools, about 13000 words there, so hashmap should be quite big as well.

Solution Trading:

What is described as output format is essentially what Binance is outputting, so I could not do much parsing beyond delimiting
at {}. In this case parsing cost would be neglible in comparison of connecting to Binance server, especially that enpoint is
TLS protected. For better performance I would use WebSocket connectivity and keep connection open at all times.

For parsing I would create state machine going over if standard JSON parsers were not performance enough.
But again, given network delays it is hard for me to imagine need for such implementation.

Check if it works:
curl https://fapi.binance.com/fapi/v1/ping

Get symbols:
curl https://fapi.binance.com/fapi/v1/ticker/price

Get trade data:
curl https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT

Quick measurement is 372ms for retrieval of the data.
real	0m0.372s
user	0m0.061s
sys	0m0.013s

I doubt parsing could take longer than 1ms here.

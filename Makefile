CPPFLAGS=-g -O0

test:test.o HashTable.o
	c++ -g -o test test.o HashTable.o

test.o: test.cc
HashTable.o: HashTable.hh HashTable.cc

prepare:
	wget http://www.gutenberg.org/files/98/98-0.txt
	grep -o -E '\w+' < 98-0.txt > words.txt
	echo Unique words:
	sort  < words.txt | uniq | wc -l

clean:
	rm -f test *.o *.txt

b_ping:
	time -p curl https://fapi.binance.com/fapi/v1/ping

b_symbols:
	time -p curl https://fapi.binance.com/fapi/v1/ticker/price

b_trades:
	time -p curl https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT


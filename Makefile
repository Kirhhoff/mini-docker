all:
	g++ main.cc -o mocker

run:
	./mocker run /bin/bash

clean:
	rm mocker
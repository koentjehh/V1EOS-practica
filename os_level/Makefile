all: shell tool

clean:
	rm -f shell tool

test: all
	./testShell.sh ./shell
	./testTool.sh ./tool

%: %.cc %.hh
	g++ -o $@ $<

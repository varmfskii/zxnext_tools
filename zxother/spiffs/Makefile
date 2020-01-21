OPTS=main.o spiffs_cache.o spiffs_check.o spiffs_gc.o	\
	spiffs_hydrogen.o spiffs_nucleus.o

spiffs: $(OPTS)
	$(CXX) -o $@ $^

clean:
	rm -f $(OPTS) *~

distclean: clean
	rm -f spiffs

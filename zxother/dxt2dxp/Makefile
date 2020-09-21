OBJS=dxt2dxp.o splitpath.o
CFLAGS+=-std=gnu99

dxt2dxp: $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f dxt2dxp

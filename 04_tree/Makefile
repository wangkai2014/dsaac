CFLAGS = -g
PROGS  = 00_test_stack 00_transform_expr_order \

00_SOBJ = 00_test_stack.o stack.o utils.o
00_TOBJ = 00_transform_expr_order.o expr.o stack.o bstree.o utils.o

all: $(PROGS)

00_test_stack: $(00_SOBJ)
	cc $(CFLAGS) -o $@ $(00_SOBJ)

00_transform_expr_order: $(00_TOBJ)
	cc $(CFLAGS) -o $@ $(00_TOBJ)

clean:
	rm -rf $(PROGS) *.o

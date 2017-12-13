CFLAGS = -g
PROGS  = 00_test_stack 00_transform_expr_order 00_test_bstree \
		 00_test_avltree 00_test_sptree 11_test_cbstree \
		 13_test_del_tree 19_insert_avl_nonrecur  27_count_tree_node \
		 29_random_bstree \

00_AOBJ = 00_test_avltree.o avltree.o stack.o utils.o
00_BOBJ = 00_test_bstree.o bstree.o utils.o
00_POBJ = 00_test_sptree.o sptree.o utils.o
00_SOBJ = 00_test_stack.o stack.o utils.o
00_TOBJ = 00_transform_expr_order.o expr.o stack.o bstree.o utils.o
11_OBJ = 11_test_cbstree.o cbstree.o utils.o 
13_OBJ = 13_test_del_tree.o bstree.o utils.o
19_OBJ = 19_insert_avl_nonrecur.o avltree.o stack.o utils.o
27_OBJ = 27_count_tree_node.o bstree.o utils.o
29_OBJ = 29_random_bstree.o bstree.o utils.o

all: $(PROGS)

00_test_stack: $(00_SOBJ)
	cc $(CFLAGS) -o $@ $(00_SOBJ)

00_transform_expr_order: $(00_TOBJ)
	cc $(CFLAGS) -o $@ $(00_TOBJ)

00_test_bstree: $(00_BOBJ)
	cc $(CFLAGS) -o $@ $(00_BOBJ)

00_test_avltree: $(00_AOBJ)
	cc $(CFLAGS) -o $@ $(00_AOBJ)

00_test_sptree: $(00_POBJ)
	cc $(CFLAGS) -o $@ $(00_POBJ)

11_test_cbstree: $(11_OBJ)
	cc $(CFLAGS) -o $@ $(11_OBJ)

13_test_del_tree: $(13_OBJ)
	cc $(CFLAGS) -o $@ $(13_OBJ)

19_insert_avl_nonrecur: $(19_OBJ)
	cc $(CFLAGS) -o $@ $(19_OBJ)

27_count_tree_node: $(27_OBJ)
	cc $(CFLAGS) -o $@ $(27_OBJ)

29_random_bstree: $(29_OBJ)
	cc $(CFLAGS) -o $@ $(29_OBJ)

clean:
	rm -rf $(PROGS) *.o

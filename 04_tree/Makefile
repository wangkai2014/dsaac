CFLAGS = -g
PROGS  = 00_test_stack 00_transform_expr_order 00_test_bstree \
		 00_test_list 00_test_queue \
		 00_test_avltree 00_test_sptree 11_test_cbstree \
		 13_test_del_tree 19_insert_avl_nonrecur  27_count_tree_node \
		 29_random_bstree 29_recur_random_bstree 30_avltree_with_fewest_node \
		 31_perfect_bstree 32_print_bounded_bstree 33_set_tree_coordinate \
		 35_tree_level_order 37_test_btree 40_test_cstree \
     	 41_test_tree_similar 42_test_tree_isomorphic 43_tree_transform \
		 44_find_Kth_tree_node \

BS_OBJ  = bstree.o queue.o list.o utils.o
BT_OBJ  = btree.o queue.o list.o utils.o
CS_OBJ  = cstree.o queue.o list.o utils.o
00_AOBJ = 00_test_avltree.o avltree.o stack.o utils.o
00_BOBJ = 00_test_bstree.o $(BS_OBJ)
00_LOBJ = 00_test_list.o list.o utils.o
00_POBJ = 00_test_sptree.o sptree.o utils.o
00_QOBJ = 00_test_queue.o queue.o list.o utils.o
00_SOBJ = 00_test_stack.o stack.o utils.o
00_TOBJ = 00_transform_expr_order.o expr.o stack.o $(BS_OBJ)
11_OBJ = 11_test_cbstree.o cbstree.o utils.o 
13_OBJ = 13_test_del_tree.o $(BS_OBJ)
19_OBJ = 19_insert_avl_nonrecur.o avltree.o stack.o utils.o
27_OBJ = 27_count_tree_node.o $(BS_OBJ)
29_OBJ = 29_random_bstree.o $(BS_OBJ)
29_ROBJ = 29_recur_random_bstree.o $(BS_OBJ)
30_OBJ = 30_avltree_with_fewest_node.o $(BS_OBJ)
31_OBJ = 31_perfect_bstree.o $(BS_OBJ)
32_OBJ = 32_print_bounded_bstree.o $(BS_OBJ)
33_OBJ = 33_set_tree_coordinate.o $(BS_OBJ)
35_OBJ = 35_tree_level_order.o $(BS_OBJ)
37_OBJ = 37_test_btree.o $(BT_OBJ) 
40_OBJ = 40_test_cstree.o $(CS_OBJ)
41_OBJ = 41_test_tree_similar.o $(BS_OBJ)
42_OBJ = 42_test_tree_isomorphic.o $(BS_OBJ)
43_OBJ = 43_tree_transform.o $(BS_OBJ)
44_OBJ = 44_find_Kth_tree_node.o $(BS_OBJ)

all: $(PROGS)

00_test_stack: $(00_SOBJ)
	cc $(CFLAGS) -o $@ $(00_SOBJ)

00_transform_expr_order: $(00_TOBJ)
	cc $(CFLAGS) -o $@ $(00_TOBJ)

00_test_list: $(00_LOBJ)
	cc $(CFLAGS) -o $@ $(00_LOBJ)

00_test_queue: $(00_QOBJ)
	cc $(CFLAGS) -o $@ $(00_QOBJ)

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

29_recur_random_bstree: $(29_ROBJ)
	cc $(CFLAGS) -o $@ $(29_ROBJ)

30_avltree_with_fewest_node: $(30_OBJ)
	cc $(CFLAGS) -o $@ $(30_OBJ)

31_perfect_bstree: $(31_OBJ)
	cc $(CFLAGS) -o $@ $(31_OBJ)

32_print_bounded_bstree: $(32_OBJ)
	cc $(CFLAGS) -o $@ $(32_OBJ)

33_set_tree_coordinate: $(33_OBJ)
	cc $(CFLAGS) -o $@ $(33_OBJ)

35_tree_level_order: $(35_OBJ)
	cc $(CFLAGS) -o $@ $(35_OBJ)

37_test_btree: $(37_OBJ)
	cc $(CFLAGS) -o $@ $(37_OBJ)

40_test_cstree: $(40_OBJ)
	cc $(CFLAGS) -o $@ $(40_OBJ)

41_test_tree_similar: $(41_OBJ)
	cc $(CFLAGS) -o $@ $(41_OBJ)

42_test_tree_isomorphic: $(42_OBJ)
	cc $(CFLAGS) -o $@ $(42_OBJ)

43_tree_transform: $(43_OBJ)
	cc $(CFLAGS) -o $@ $(43_OBJ)

44_find_Kth_tree_node: $(44_OBJ)
	cc $(CFLAGS) -o $@ $(44_OBJ)

clean:
	rm -rf $(PROGS) *.o

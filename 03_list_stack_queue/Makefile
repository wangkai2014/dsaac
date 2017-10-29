CFLAGS = -g
PROGS = 00_test_list 01_print_list 02_print_lots 03_swap_list_elements \
		03_swap_dlist_elements 04_intersect_list 05_union_list \
		06_add_polynomials 07_multiply_polynomials 08_power_polynomials \
		09_integer_arithmetic 10_josephus_problem 11_find_element \
		12_reverse_list 13_sort_student_records 14_store_graph_with_list \
		00_test_cursor 14_store_graph_with_cursor 15_self_adjust_list_use_array \
		15_self_adjust_list_use_linked 16_list_unique 16_list_unique_with_sort \
		17_lazy_deletion_list 00_test_stack 18_balance_symbols \

00_OBJ = 00_test_list.o clist.o utils.o
00_COBJ = 00_test_cursor.o cursor.o utils.o
00_SOBJ = 00_test_stack.o stack.o utils.o
01_OBJ = 01_print_list.o list.o utils.o
02_OBJ = 02_print_lots.o list.o utils.o
03_OBJ = 03_swap_list_elements.o list.o utils.o
03_DOBJ = 03_swap_dlist_elements.o dlist.o utils.o
04_OBJ = 04_intersect_list.o list.o utils.o
05_OBJ = 05_union_list.o list.o utils.o
06_OBJ = 06_add_polynomials.o polynomial.o list.o utils.o
07_OBJ = 07_multiply_polynomials.o polynomial.o list.o utils.o
08_OBJ = 08_power_polynomials.o polynomial.o list.o utils.o
09_OBJ = 09_integer_arithmetic.o arithmetic.o polynomial.o list.o utils.o
10_OBJ = 10_josephus_problem.o clist.o utils.o
11_OBJ = 11_find_element.o list.o utils.o
12_OBJ = 12_reverse_list.o list.o utils.o
13_OBJ = 13_sort_student_records.o list.o utils.o
14_OBJ = 14_store_graph_with_list.o list.o utils.o
14_DOBJ = 14_store_graph_with_cursor.o cursor.o utils.o
15_AOBJ = 15_self_adjust_list_use_array.o utils.o
15_LOBJ = 15_self_adjust_list_use_linked.o list.o utils.o
16_OBJ = 16_list_unique.o list.o utils.o
16_SOBJ = 16_list_unique_with_sort.o list.o utils.o
17_OBJ = 17_lazy_deletion_list.o lazy_list.o utils.o
18_OBJ = 18_balance_symbols.o stack.o utils.o

all: $(PROGS)

00_test_list: $(00_OBJ)
	cc $(CFLAGS) -o $@ $(00_OBJ)

00_test_cursor: $(00_COBJ)
	cc $(CFLAGS) -o $@ $(00_COBJ)

00_test_stack: $(00_SOBJ)
	cc $(CFLAGS) -o $@ $(00_SOBJ)

01_print_list: $(01_OBJ)
	cc $(CFLAGS) -o $@ $(01_OBJ)

02_print_lots: $(02_OBJ)
	cc $(CFLAGS) -o $@ $(02_OBJ)

03_swap_list_elements: $(03_OBJ)
	cc $(CFLAGS) -o $@ $(03_OBJ)

03_swap_dlist_elements: $(03_DOBJ)
	cc $(CFLAGS) -o $@ $(03_DOBJ)

04_intersect_list: $(04_OBJ)
	cc $(CFLAGS) -o $@ $(04_OBJ)

05_union_list: $(05_OBJ)
	cc $(CFLAGS) -o $@ $(05_OBJ)

06_add_polynomials: $(06_OBJ)
	cc $(CFLAGS) -o $@ $(06_OBJ)

07_multiply_polynomials: $(07_OBJ)
	cc $(CFLAGS) -o $@ $(07_OBJ)

08_power_polynomials: $(08_OBJ)
	cc $(CFLAGS) -o $@ $(08_OBJ)

09_integer_arithmetic: $(09_OBJ)
	cc $(CFLAGS) -o $@ $(09_OBJ)

10_josephus_problem: $(10_OBJ)
	cc $(CFLAGS) -o $@ $(10_OBJ)

11_find_element: $(11_OBJ)
	cc $(CFLAGS) -o $@ $(11_OBJ)

12_reverse_list: $(12_OBJ)
	cc $(CFLAGS) -o $@ $(12_OBJ)

13_sort_student_records: $(13_OBJ)
	cc $(CFLAGS) -o $@ $(13_OBJ)

14_store_graph_with_list: $(14_OBJ)
	cc $(CFLAGS) -o $@ $(14_OBJ)

14_store_graph_with_cursor: $(14_DOBJ)
	cc $(CFLAGS) -o $@ $(14_DOBJ)

15_self_adjust_list_use_array: $(15_AOBJ)
	cc $(CFLAGS) -o $@ $(15_AOBJ)

15_self_adjust_list_use_linked: $(15_LOBJ)
	cc $(CFLAGS) -o $@ $(15_LOBJ)

16_list_unique: $(16_OBJ)
	cc $(CFLAGS) -o $@ $(16_OBJ)

16_list_unique_with_sort: $(16_SOBJ)
	cc $(CFLAGS) -o $@ $(16_SOBJ)

17_lazy_deletion_list: $(17_OBJ)
	cc $(CFLAGS) -o $@ $(17_OBJ)

18_balance_symbols: $(18_OBJ)
	cc $(CFLAGS) -o $@ $(18_OBJ)

clean:
	rm -rf $(PROGS) *.o

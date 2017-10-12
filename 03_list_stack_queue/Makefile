CFLAGS = -g
PROGS = 00_test_list 01_print_list 02_print_lots 03_swap_list_elements \
		03_swap_dlist_elements 04_intersect_list 05_union_list \
		06_add_polynomials

00_OBJ = 00_test_list.o list.o 
01_OBJ = 01_print_list.o list.o
02_OBJ = 02_print_lots.o list.o
03_OBJ = 03_swap_list_elements.o list.o
03_DOBJ = 03_swap_dlist_elements.o dlist.o
04_OBJ = 04_intersect_list.o list.o
05_OBJ = 05_union_list.o list.o
06_OBJ = 06_add_polynomials.o list.o

all: $(PROGS)

00_test_list: $(00_OBJ)
	cc $(CFLAGS) -o $@ $(00_OBJ)

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

clean:
	rm -rf $(PROGS) *.o

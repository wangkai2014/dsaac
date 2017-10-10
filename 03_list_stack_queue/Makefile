CFLAGS = -g
PROGS = 00_test_list 01_print_list 02_print_lots 03_swap_list_elements \
		03_swap_dlist_elements

00_OBJ = 00_test_list.o list.o 
01_OBJ = 01_print_list.o list.o
02_OBJ = 02_print_lots.o list.o
03_OBJ = 03_swap_list_elements.o list.o
03_DOBJ = 03_swap_dlist_elements.o dlist.o

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

clean:
	rm -rf $(PROGS) *.o

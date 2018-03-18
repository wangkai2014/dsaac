CC = gcc
CFLAGS = -g
PROGS = 00_test_graph_create 03_topo_sort_graph 

GRAPH_OBJ = graph.o list.o queue.o
00_OBJ = 00_test_graph_create.o $(GRAPH_OBJ)
03_OBJ = 03_topo_sort_graph.o $(GRAPH_OBJ)

all: $(PROGS)

00_test_graph_create: $(00_OBJ)
	$(CC) $(CFLAGS) -o $@ $(00_OBJ) 

03_topo_sort_graph: $(03_OBJ)
	$(CC) $(CFLAGS) -o $@ $(03_OBJ)

clean:
	rm -rf *.o $(PROGS)

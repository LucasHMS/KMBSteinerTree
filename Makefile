all:
	g++ src/*.cpp -o bin/KMBSteinerTree

run:
	./bin/KMBSteinerTree instances/1.stp
	./bin/KMBSteinerTree instances/2.stp
	./bin/KMBSteinerTree instances/3.stp
	./bin/KMBSteinerTree instances/4.stp
	./bin/KMBSteinerTree instances/5.stp
	./bin/KMBSteinerTree instances/6.stp
	./bin/KMBSteinerTree instances/7.stp
	./bin/KMBSteinerTree instances/8.stp

test:
	./bin/KMBSteinerTree instances/test_graphs/big.stp
	./bin/KMBSteinerTree instances/test_graphs/big_desc.stp
	./bin/KMBSteinerTree instances/test_graphs/big_t=2.stp
	./bin/KMBSteinerTree instances/test_graphs/big_v=t.stp
	./bin/KMBSteinerTree instances/test_graphs/small.stp
	./bin/KMBSteinerTree instances/test_graphs/small_desc.stp
	./bin/KMBSteinerTree instances/test_graphs/small_t=2.stp
	./bin/KMBSteinerTree instances/test_graphs/small_v=t.stp
	./bin/KMBSteinerTree instances/test_graphs/test_mst.stp

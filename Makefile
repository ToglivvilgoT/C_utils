flags=

test_arr: test_arr.c d_array.c d_array.h
	gcc test_arr.c d_array.c d_array.h -o test
	./test

test_bitset: test_bitset.c bitset.c bitset.h
	gcc test_bitset.c bitset.c bitset.h -o test
	./test

test_hashtable: test_hashtable.c hashtable.c hashtable.h
	gcc test_hashtable.c hashtable.c hashtable.h -o test
	./test

test_files: test_files.c file_handling.c file_handling.h
	gcc test_files.c file_handling.c file_handling.h -o test
	./test file_handling.c

test_obj_loader: obj_loader.c 
	gcc obj_loader.c $(flags) -o test
	./test utah_teapot.obj

test_vector: vector.h
	gcc test_vector.c -o test
	./test

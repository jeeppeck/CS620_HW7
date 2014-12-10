
// #define FRAME struct memory_frame
// #define HASH_SIZE 1013 // N=41
// // the following 2 definitions are not required in your program
// // since these values will be read from standard input.
// #define MEMORY_SIZE M // number of frames M=1024
// #define PAGE_TABLE_SIZE P // number of pages in virtual memory P=2048
// int ihash_size // read from standard input
// FRAME
// {
// 	FRAME *f_hash_next;
// 	FRAME *f_hash_prev;
// 	FRAME *f_free_next;
// 	FRAME *f_lru_next;
// 	FRAME *f_lru_prev;
// 	long page_num;
// 	long frame_num;
// };
// FRAME *page_table[HASH_SIZE];
// FRAME *fm_free_list;
// FRAME *fm_lru_head;
// FRAME *fm_lru_tail;
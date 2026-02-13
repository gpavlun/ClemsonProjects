/* mem.h 
 * Lab4: Dynamic Memory Allocation
 * Version: 1
 * ECE 2230, Fall 2025
 */

#define PAGESIZE 4096      // number of bytes in one page
#define FIRST_FIT 2025 
#define BEST_FIT  2026
#define TRUE 1
#define FALSE 0

/* set configuration options for dynamic memory manager
 */
void Mem_configure(int coalescing_state, int search_type);

/* deallocates the space pointed to by return_ptr; it does nothing if
 * return_ptr is NULL.  
 */
void Mem_free(void *return_ptr);

/* returns a pointer to space for an object of size nbytes, or NULL if the
 * request cannot be satisfied.  The space is uninitialized.
 */
void *Mem_alloc(const int nbytes);

/* prints stats about the current free list
 *
 * number of items in the linked list
 * min, max, and average size of each item (bytes)
 * total memory in list (bytes)
 * number of calls to sbrk and number of pages requested
 */
void Mem_stats(void);

/* print table of memory in free list.
 * A unit is the size of one mem_chunk_t structure
 * example format
 *     mem_chunk_t *p;
 *     printf("p=%p, size=%d (units), end=%p, next=%p\n", 
 *              p, p->num_units, p + p->num_units, p->next);
 */
void Mem_print(int nunits);

/* an example of a mem_chunk_t definition.  You can modify this to
 * match your design, but you must get instructor approval for any changes
 */
typedef struct memory_chunk_tag {
    int num_units;                  // one unit equals sizeof(mem_chunk_t)
    struct memory_chunk_tag *next;   // next block in free list
    struct memory_chunk_tag *prev;  
    int dumb;
    int dumber;
} mem_chunk_t;

/* vi:set ts=8 sts=4 sw=4 et: */

/* hashes.h 
 * Lab6: Hash Tables 
 * ECE 2230, Fall 2025
 *
 * See notes in hashes.c for details
 *
 * No changes are needed unless you want to add your own hash function and 
 * code.
 */
enum Hash_Alg_t {ABS_HASH, DJB_HASH, SAX_HASH, FNV_HASH, OAT_HASH, JEN_HASH, JSW_HASH, ELF_HASH, TAB_HASH};

int hashes_table_pos(hashkey_t key, int tablesize);
int hashes_probe_dec(hashkey_t key, int size);
void hashes_configure(int alg);

// added for my experiements with cuckcoo hashing.  Can be deleted.
void jsw_make_table(void);


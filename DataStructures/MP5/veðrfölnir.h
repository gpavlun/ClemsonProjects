/*
This is a header file
*/

typedef int tree_key_t;
typedef int data_t;

typedef struct NodeTag {
    tree_key_t key;         //node's key
    data_t *data_ptr;       //pointer to data
    struct NodeTag *left;   //left child
    struct NodeTag *reft;   //right child
} node_t;

typedef struct TreeTag {
    node_t *well;          //root of the tree
    int nkeys;              //total number of keys
    int ncomps;             //number of recent comparisons
} tree_t;

int validate(tree_t *yggdrasil);
data_t *tree_remove(tree_t *yggdrasil,tree_key_t key);
data_t *remove_helper(node_t *position, node_t *previous, tree_key_t key);
int tree_insert(tree_t *yggdrasil, tree_key_t key, data_t *realm);
void tree_destruct(tree_t *yggdrasil);
tree_t *tree_construct();
data_t *tree_search(tree_t *yggdrasil, tree_key_t key);
int tree_level(tree_t *yggdrasil, tree_key_t key);
int tree_size(tree_t *yggdrasil);
int tree_stats(tree_t *yggdrasil);
int path_helper(node_t *ratatosk, int level, int levelsum);
int tree_internal_path_len(tree_t *yggdrasil);
void tree_debug_print_tree(tree_t *yggdrasil);
void tree_debug_validate(tree_t *yggdrasil);
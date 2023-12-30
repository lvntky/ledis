#ifndef __LEDIS_AVL_H__
#define __LEDIS_AVL_H__

typedef struct ledis_avl_node
{
    int key;
    ledis_avl_node *left_node;
    ledis_avl_node *right_node;
    int height;
} ledis_avl_node_t;

ledis_avl_node_t *ledis_avl_create_new_node();
ledis_avl_node_t *ledis_avl_insert_node(ledis_avl_node_t*, int);
ledis_avl_node_t *ledis_avl_delete_node(ledis_avl_node_t*, int);
ledis_avl_node_t *ledis_avl_search_node(ledis_avl_node_t*, int);
ledis_avl_node_t *ledis_avl_rigt_rotate(ledis_avl_node_t *);
ledis_avl_node_t *ledis_avl_left_rotate(ledis_avl_node_t *);

int ledis_avl_get_balace(ledis_avl_node_t *);
int ledis_avl_get_max(ledis_avl_node_t *);
int ledis_avl_get_min(ledis_avl_node_t *);
void ledis_avl_print_tree(ledis_avl_node_t *);
void ledis_avl_destroy_tree(ledis_avl_node_t *);

#endif
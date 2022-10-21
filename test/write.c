#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include <libguide/guide.h>
#include <libguide/tree.h>

int main(int argc, char *argv[])
{
    wchar_t *filename = L"test.gde";

    // Create new empty Guide file
    struct guide_t *guide = guide_create();

    // Creat root node
    struct tree_node_t *root = tree_get_root(guide->tree);
    struct guide_nodedata_t *data = (struct guide_nodedata_t *)tree_get_data(root);
    guide_nodedata_set_title(data, L"The Beginning 🐣");    
    guide_nodedata_set_text(data, "Text of the root node");

    // Create children
    struct guide_nodedata_t *child1 = guide_nodedata_create_with_data(
        guide,
        L"My child",
        "Lorem ipsum dolor sit amet.");
    guide_add_child(guide, root, child1, NULL);

    struct guide_nodedata_t *child2 = guide_nodedata_create_with_data(
        guide, L"My child 2",
        "Lorem ipsum dolor sit amet.");
    guide_add_child(guide, root, child2, NULL);

    // Save to file
    guide_store(filename, guide);
}
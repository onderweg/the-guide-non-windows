#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include <libguide/guide.h>
#include <libguide/tree.h>

/* print 'n' chars */
static void fspace(FILE *fp, int n, char c)
{
    while (n--)
        fprintf(fp, "%c", c);
}

static int _guide_reader(struct tree_node_t *node, int depth)
{
    struct guide_nodedata_t *data =
        (struct guide_nodedata_t *)tree_get_data(node);
    fspace(stdout, depth, '-');
    printf("📗 %ls [%d]\n", data->title, data->uid);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        printf("Missing file name argument. Usage: %s <file.gde>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Convert argv[2] to wide string */
    size_t mbslen = mbstowcs(NULL, argv[1], 0);
    wchar_t *filename = calloc(mbslen + 1, sizeof(*filename));
    mbstowcs(filename, argv[1], mbslen + 1);

    unsigned os_errcode;
    struct guide_t *guide;
    uint32 format;
    guide = guide_load(filename, &os_errcode, &format, ARCH64);
    if (guide == NULL)
    {
        printf("Failed to load tree: %s\n", strerror(os_errcode));
        exit(EXIT_FAILURE);
    }
    printf("Filename=%ls\n", filename);

    tree_traverse_preorder_wd(guide->tree, _guide_reader);
}
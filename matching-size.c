#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file;
    char line[100];
    int m_size, m_cnt=0, m_sum=0;

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "the maximum matching size = %d", &m_size) != 1)
        {
            fprintf(stderr, "Error reading matching size\n");
            return -1;
        }
        m_sum += m_size;
        m_cnt++;
    }
    fclose(file);
    printf("%.3f\n", ((float)m_sum)/((float)m_cnt));

    return 0;
}

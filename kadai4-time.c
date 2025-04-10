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
    float real_time, user_time, sys_time;

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // // 空行を読み飛ばす
        // fgets(line, sizeof(line), file);

        // 実行時間の読み取り
        fgets(line, sizeof(line), file);
        if (sscanf(line, "real 0m%fs", &real_time) != 1)
        {
            fprintf(stderr, "Error reading real time\n");
            return -1;
        }

        fgets(line, sizeof(line), file);
        if (sscanf(line, "user 0m%fs", &user_time) != 1)
        {
            fprintf(stderr, "Error reading user time\n");
            return -1;
        }

        fgets(line, sizeof(line), file);
        if (sscanf(line, "sys 0m%fs", &sys_time) != 1)
        {
            fprintf(stderr, "Error reading sys time\n");
            return -1;
        }


        // フォーマットに従って出力
        printf("%.3f %.3f %.3f\n", real_time, user_time, sys_time);
    }
    fclose(file);

    return 0;
}

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
    float real_time_s, user_time_s, sys_time_s;
    int real_time_m, user_time_m, sys_time_m;

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
        if (sscanf(line, "real\t%dm%fs", &real_time_m, &real_time_s) != 2)  // sscanfの戻り値は、正常に代入を行えた変数の個数
        {
            fprintf(stderr, "Error reading real time\n");
            return -1;
        }

        fgets(line, sizeof(line), file);
        if (sscanf(line, "user\t%dm%fs", &user_time_m, &user_time_s) != 2)
        {
            fprintf(stderr, "Error reading user time\n");
            return -1;
        }

        fgets(line, sizeof(line), file);
        if (sscanf(line, "sys\t%dm%fs", &sys_time_m, &sys_time_s) != 2)
        {
            fprintf(stderr, "Error reading sys time\n");
            return -1;
        }


        // フォーマットに従ってユーザCPU時間を出力
        printf("%.3f\n", user_time_m*60.0 + user_time_s);
    }
    fclose(file);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int compare_scores(const void* score_a, const void* score_b)
{
    int  a = *(int*) score_a;
    int  b = *(int*) score_b;
    return a - b;
}

int compare_scores_desendant(const void* score_a, const void* score_b)
{
    int  a = *(int*) score_a;
    int  b = *(int*) score_b;
    return b - a;
}

typedef struct
{
    int width;
    int height;
} rectangle;

int compare_areas(const void* a, const void* b)
{
    rectangle*  ra = (rectangle*)a;
    rectangle*  rb = (rectangle*)b;
    int area_a = (ra -> width * ra -> height);
    int area_b = (rb -> width * rb -> height);
    return area_a - area_b;
}

int compare_areas_desendant(const void* a, const void* b)
{
    return compare_areas(b,a);
}

int compare_names(const void* a, const void* b){
    char** sa = (char**)a;
    char** sb = (char**)b;
    return strcmp(*sa,*sb);
}


int main(int argc, char const *argv[])
{
    int scores[] = {543,323,32,554,11,3,112};
    int i;
    qsort(scores, 7, sizeof(int), compare_scores);
    puts("These are the scores in order");
    for (i = 0; i < 7; i++)
    {
        printf("Score = %i\n",scores[i]);
        /* code */
    }
    
    return 0;
}

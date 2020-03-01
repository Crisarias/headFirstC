#include <stdio.h>
#include <string.h>

char tracks[][80] = {
    "Song 1",
    "Song 2",
    "Song 3",
    "Song 4",
    "Song 5"
};

void find_track(char search_for[]) {
    int i;
    for (i = 0; i < 5; i++)
    {
        if (strstr(tracks[i],search_for))
        {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }      
        
    }
    
}

int main()
{
 char search_for[80];
  printf("Search for: ");
  fgets(search_for, 79, stdin);
  search_for[strlen(search_for) - 1] = '\0';
  find_track(search_for);
  return 0;
}

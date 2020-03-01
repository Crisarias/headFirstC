#include <stdio.h>
#include <stdlib.h>

int main()
{
    char card_name[3];    
    do
    {
        puts("Enter the card_name: ");
        scanf("%2s", card_name);
        int val = 0;
        switch (card_name[0])
        {
            case 'K':
            case 'Q':
            case 'J':
                val = 10;
                break;
            case 'A':
                val = 11;
                break;
            case 'X':
                continue;    
            default:
                val = atoi(card_name);
                if (val < 1 || val > 10)
                {
                    puts("The value cannot be less than 1 or more than 10.");
                    continue;
                }                
                break;
        }
        /* Check if the value is 3 to 6 */
        if (val >= 3 && val <= 6)
            puts("Count has gone up");
        /* Otherwise check if the card was 10, J, Q, or K */
        else if (val == 10)
            puts("Count has gone down");
            /* code */
    } while ( card_name[0] != 'X');
    return 0;
}
//
//  main.c
//  SkipList
//
//  Created by AugustRush on 1/12/17.
//  Copyright © 2017 August. All rights reserved.
//

#include <stdio.h>
#include "skiplist.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    skip_list *sl=create_sl();
    int i=1;
    for(;i<11111; ++i)
    {
        insert(sl, i, i);
    }
    for(i=11; i<11111; ++i)
    {
        if(!erased(sl, i))
            printf("No!\n");
    }
    print_sl(sl);
    int *p=search(sl, 10);
    if(p)
        printf("value of key 10 is %d\n", *p);
    sl_free(sl);

    
    printf("Hello, World!\n");
    
    return 0;
}

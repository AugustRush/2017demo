//
//  main.m
//  FishhookDemo
//
//  Created by AugustRush on 2/7/17.
//  Copyright © 2017 August. All rights reserved.
//

#import <dlfcn.h>
#import <Foundation/Foundation.h>
#import "fishhook.h"
#import <FishhookDemo-Swift.h>

static int (*orig_close)(int);
static int (*orig_open)(const char *, int, ...);

static int (*orig_MyClass_Method1)(void);
static int (*orig_MyClass_Method1)(void);

int my_method1() {
    printf("call my method1 !!!!");
    return orig_MyClass_Method1();
}

int my_close(int fd) {
    printf("Calling real close(%d)\n", fd);
    return orig_close(fd);
}

int my_open(const char *path, int oflag, ...) {
    va_list ap = {0};
    mode_t mode = 0;
    
    if ((oflag & O_CREAT) != 0) {
        // mode only applies to O_CREAT
        va_start(ap, oflag);
        mode = va_arg(ap, int);
        va_end(ap);
        printf("Calling real open('%s', %d, %d)\n", path, oflag, mode);
        return orig_open(path, oflag, mode);
    } else {
        printf("Calling real open('%s', %d)\n", path, oflag);
        return orig_open(path, oflag, mode);
    }
}


int main(int argc, const char * argv[]) {
    @autoreleasepool {
        rebind_symbols((struct rebinding[2]){{"close", my_close, (void *)&orig_close}, {"open", my_open, (void *)&orig_open}}, 2);
//
//        // Open our own binary and print out first 4 bytes (which is the same
//        // for all Mach-O binaries on a given architecture)
//        int fd = open(argv[0], O_RDONLY);
//        uint32_t magic_number = 0;
//        read(fd, &magic_number, 4);
//        printf("Mach-O Magic Number: %x \n", magic_number);
//        close(fd);
//        int ret = rebind_symbols((struct rebinding[1]){{"_TFC12FishhookDemo7MyClass7method1fT_Si", my_method1, (void *)&orig_MyClass_Method1}}, 1);
//        
//        
//        my_method1();
        
    
        var my = myclas
        
    }
    return 0;
}

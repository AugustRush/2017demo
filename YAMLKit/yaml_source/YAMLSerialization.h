//
//  YAMLSerialization.h
//  YAML Serialization support by Mirek Rusin based on C library LibYAML by Kirill Simonov
//	Released under MIT License
//
//  Copyright 2010 Mirek Rusin
//	Copyright 2010 Stanislav Yudin
//

#import <Foundation/Foundation.h>
#import "yaml.h"

// Mimics NSPropertyListMutabilityOptions
typedef NS_OPTIONS(NSUInteger, YAMLReadOptions) {
    YAMLReadOptionImmutable = 1 << 0,
    YAMLReadOptionMutableContainersAndLeaves = 1 << 1,
    YAMLReadOptionStringScalars = 1 << 2,
};

typedef NS_ENUM(NSUInteger, YAMLErrorCode) {
    YAMLErrorNoErrors,
    YAMLErrorCodeParserInitializationFailed,
    YAMLErrorCodeParseError,
    YAMLErrorCodeEmitterError,
    YAMLErrorInvalidOptions,
    YAMLErrorCodeOutOfMemory,
    YAMLErrorInvalidYamlObject,
};

typedef NS_OPTIONS(NSUInteger, YAMLWriteOptions) {
    YAMLWriteOptionSingleDocument = 1 << 0,
    YAMLWriteOptionMultipleDocuments = 1 << 1,
};

extern NSString *const YAMLErrorDomain;

@interface YAMLSerialization : NSObject {
}

+ (void) writeYAML: (id) yaml
          toStream: (NSOutputStream *) stream
           options: (YAMLWriteOptions) opt
             error: (NSError **) error;

+ (NSData *) dataFromYAML: (id) yaml
                  options: (YAMLWriteOptions) opt
                    error: (NSError **) error;

+ (NSMutableArray *) YAMLWithStream: (NSInputStream *) stream
                            options: (YAMLReadOptions) opt
                              error: (NSError **) error;

+ (NSMutableArray *) YAMLWithData: (NSData *) data
                          options: (YAMLReadOptions) opt
                            error: (NSError **) error;

@end

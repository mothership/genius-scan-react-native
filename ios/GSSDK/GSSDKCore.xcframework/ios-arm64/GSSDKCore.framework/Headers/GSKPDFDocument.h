// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from sdk-pdf.djinni

#import "GSKPDFPage.h"
#import <Foundation/Foundation.h>

/** Describes the structure of a PDF document for the PDF generator. */
@interface GSKPDFDocument : NSObject
- (nonnull instancetype)initWithTitle:(nullable NSString *)title
                             password:(nullable NSString *)password
                             keywords:(nullable NSString *)keywords
                         creationDate:(nullable NSDate *)creationDate
                       lastUpdateDate:(nullable NSDate *)lastUpdateDate
                                pages:(nonnull NSArray<GSKPDFPage *> *)pages;
+ (nonnull instancetype)PDFDocumentWithTitle:(nullable NSString *)title
                                    password:(nullable NSString *)password
                                    keywords:(nullable NSString *)keywords
                                creationDate:(nullable NSDate *)creationDate
                              lastUpdateDate:(nullable NSDate *)lastUpdateDate
                                       pages:(nonnull NSArray<GSKPDFPage *> *)pages;

/** If provided, this title will be included in the PDF document properties */
@property (nonatomic, readonly, nullable) NSString * title;

/**
 * If provided, this password will be used to protect the PDF document.
 * It will need to be entered to view or edit the document.
 * RC4 encryption algorithm is used with a 128-bit key.
 */
@property (nonatomic, readonly, nullable) NSString * password;

/** If provided, the keywords will be included in the PDF document properties */
@property (nonatomic, readonly, nullable) NSString * keywords;

/** If provided, this date will be included in the PDF document properties */
@property (nonatomic, readonly, nullable) NSDate * creationDate;

/** If provided, this date will be included in the PDF document properties */
@property (nonatomic, readonly, nullable) NSDate * lastUpdateDate;

/** List of pages that will be included in the PDF document */
@property (nonatomic, readonly, nonnull) NSArray<GSKPDFPage *> * pages;

@end

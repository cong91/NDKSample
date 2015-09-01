/*
 * Store.h
 *
 *  Created on: Sep 1, 2015
 *      Author: FRAMGIA\nguyen.thanh.cong
 */

#ifndef STORE_H_
#define STORE_H_

#include <jni.h>
#include <stdint.h>

#endif /* STORE_H_ */
#define STORE_MAX_CAPACITY 16
#ifndef NULL
#define NULL   ((void *) 0)
#endif
#include <android/log.h>
#define LOG_TAG "Store.class"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

typedef enum {
	StoreType_Integer, StoreType_String
} StoreType;
typedef union {
	int32_t mInteger;
	char* mString;
} StoreValue;
typedef struct {
	char* mKey;
	StoreType mType;
	StoreValue mValue;
} StoreEntry;

typedef struct {
	StoreEntry mEntries[STORE_MAX_CAPACITY];
	int32_t mLength;
} Store;
int32_t isEntryValid(JNIEnv* pEnv, StoreEntry* pEntry, StoreType pType);
StoreEntry* allocateEntry(JNIEnv* pEnv, Store* pStore, jstring pKey);
StoreEntry* findEntry(JNIEnv* pEnv, Store* pStore, jstring pKey,
		int32_t* pError);
void releaseEntryValue(JNIEnv* pEnv, StoreEntry* pEntry);

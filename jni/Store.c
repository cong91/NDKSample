/*
 * Store.c
 *
 *  Created on: Sep 1, 2015
 *      Author: FRAMGIA\nguyen.thanh.cong
 */
#include <jni.h>
#include <Store.h>
#include <string.h>

int32_t isEntryValid(JNIEnv* pEnv, StoreEntry* pEntry, StoreType pType) {
	if (pEntry == NULL) {
		throwNotExistingKeyException(pEnv);
	} else if (pEntry->mType != pType) {
		throwInvalidTypeException(pEnv);
	} else {
		return 1;
	}
	return 0;
}

StoreEntry* findEntry(JNIEnv* pEnv, Store* pStore, jstring pKey,
		int32_t* pError) {
	StoreEntry* lEntry = pStore->mEntries;
	StoreEntry* lEntryEnd = lEntry + pStore->mLength;
	const char* lKeyTmp = (*pEnv)->GetStringUTFChars(pEnv, pKey,
	NULL);
	if (lKeyTmp == NULL) {
		if (pError != NULL) {
			*pError = 1;
		}
		return NULL ;
	}
	while ((lEntry < lEntryEnd) && (strcmp(lEntry->mKey, lKeyTmp) != 0)) {
		++lEntry;
	}
	(*pEnv)->ReleaseStringUTFChars(pEnv, pKey, lKeyTmp);
	return (lEntry == lEntryEnd) ? NULL : lEntry;
}

StoreEntry* allocateEntry(JNIEnv* pEnv, Store* pStore, jstring pKey) {
	int32_t lError = 0;
	StoreEntry* lEntry = findEntry(pEnv, pStore, pKey, &lError);
	if (lEntry != NULL) {
		releaseEntryValue(pEnv, lEntry);
	} else if (!lError) {
		if (pStore->mLength >= STORE_MAX_CAPACITY) {
			throwStoreFullException(pEnv);
			return NULL ;
		}
		lEntry = pStore->mEntries + pStore->mLength;
		const char* lKeyTmp = (*pEnv)->GetStringUTFChars(pEnv, pKey, NULL);
		if (lKeyTmp == NULL) {
			return NULL ;
		}
		lEntry->mKey = (char*) malloc(strlen(lKeyTmp));
		strcpy(lEntry->mKey, lKeyTmp);
		(*pEnv)->ReleaseStringUTFChars(pEnv, pKey, lKeyTmp);
		++pStore->mLength;
	}
	return lEntry;
}
void releaseEntryValue(JNIEnv* pEnv, StoreEntry* pEntry) {
	int32_t i;
	switch (pEntry->mType) {
	case StoreType_String:
		free(pEntry->mValue.mString);
		break;
	case StoreType_Color:
		(*pEnv)->DeleteGlobalRef(pEnv, pEntry->mValue.mColor);
		break;
	case StoreType_ArrayInteger:
		free(pEntry->mValue.mIntegerArray);
		break;
	case StoreType_ArrayColor:
		for (i = 0; i < pEntry->mLength; ++i) {
			(*pEnv)->DeleteGlobalRef(pEnv,pEntry->mValue.mColorArray[i]);
		}
		free(pEntry->mValue.mColorArray);
		break;
	}
}
void throwNotExistingKeyException(JNIEnv *pEnv) {
	jclass lclass = (*pEnv)->FindClass(pEnv,
			"com/congnt/ndkguide/exception/NotExistingKeyException");
	if (lclass != NULL) {
		(*pEnv)->ThrowNew(pEnv, lclass, "The Key does not exist");
	}
	(*pEnv)->DeleteLocalRef(pEnv, lclass);
}
void throwInvalidTypeException(JNIEnv *pEnv) {
	jclass lclass = (*pEnv)->FindClass(pEnv,
			"com/congnt/ndkguide/exception/InvalidTypeException");
	if (lclass != NULL) {
		(*pEnv)->ThrowNew(pEnv, lclass, "Incorrect type.");
	}
	(*pEnv)->DeleteLocalRef(pEnv, lclass);

}
void throwStoreFullException(JNIEnv *pEnv) {
	jclass lclass = (*pEnv)->FindClass(pEnv,
			"com/congnt/ndkguide/exception/StoreFullException");
	if (lclass != NULL) {
		(*pEnv)->ThrowNew(pEnv, lclass, "Store is full.");
	}
	(*pEnv)->DeleteLocalRef(pEnv, lclass);
}

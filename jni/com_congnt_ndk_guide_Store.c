/*
 * comcongntndkguideStore.c
 *
 *  Created on: Sep 1, 2015
 *      Author: FRAMGIA\nguyen.thanh.cong
 */

#include <com_congnt_ndk_guide_Store.h>
#include "Store.h"
#include <stdint.h>
#include <string.h>
#include <jni.h>
#include <android/log.h>
static Store gStore = { { }, 0 };

JNIEXPORT jint JNICALL Java_com_congnt_ndkguide_Store_getInteger(JNIEnv* pEnv,
		jobject pThis, jstring pKey) {
	StoreEntry* lEntry = findEntry(pEnv, &gStore, pKey, NULL);
	if (isEntryValid(pEnv, lEntry, StoreType_Integer)) {
		LOGI("===================> Java_com_congnt_ndkguide_Store_getInteger ");
		return lEntry->mValue.mInteger;
	} else {
		return 0.0f;
	}
}
JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setInteger(JNIEnv* pEnv,
		jobject pThis, jstring pKey, jint pInteger) {
	StoreEntry* lEntry = allocateEntry(pEnv, &gStore, pKey);
	if (lEntry != NULL) {
		lEntry->mType = StoreType_Integer;
		lEntry->mValue.mInteger = pInteger;
	}
}
JNIEXPORT jstring JNICALL Java_com_congnt_ndkguide_Store_getString(JNIEnv* pEnv,
		jobject pThis, jstring pKey) {
	StoreEntry* lEntry = findEntry(pEnv, &gStore, pKey, NULL);
	if (isEntryValid(pEnv, lEntry, StoreType_String)) {
		return (*pEnv)->NewStringUTF(pEnv, lEntry->mValue.mString);
	} else {
		return NULL;
	}
}
JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setString(JNIEnv* pEnv,
		jobject pThis, jstring pKey, jstring pString) {
	const char* lStringTmp = (*pEnv)->GetStringUTFChars(pEnv, pString, NULL);
	if (lStringTmp == NULL) {
		return;
	}
	StoreEntry* lEntry = allocateEntry(pEnv, &gStore, pKey);
	if (lEntry != NULL) {
		lEntry->mType = StoreType_String;
		jsize lStringLength = (*pEnv)->GetStringUTFLength(pEnv, pString);
		lEntry->mValue.mString = (char*) malloc(
				sizeof(char) * (lStringLength + 1));
		strcpy(lEntry->mValue.mString, lStringTmp);
	}
	(*pEnv)->ReleaseStringUTFChars(pEnv, pString, lStringTmp);
}

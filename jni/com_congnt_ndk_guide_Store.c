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
		return NULL ;
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

JNIEXPORT jobject JNICALL Java_com_congnt_ndkguide_Store_getColor(JNIEnv* pEnv,
		jobject pThis, jstring pKey) {
	StoreEntry* lEntry = findEntry(pEnv, &gStore, pKey, NULL);
	if (isEntryValid(pEnv, lEntry, StoreType_Color)) {
		return lEntry->mValue.mColor;
	} else {
		return NULL ;
	}
}
JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setColor(JNIEnv* pEnv,
		jobject pThis, jstring pKey, jobject pColor) {
	jobject lColor = (*pEnv)->NewGlobalRef(pEnv, pColor);
	if (lColor == NULL) {
		return;
	}
	StoreEntry* lEntry = allocateEntry(pEnv, &gStore, pKey);
	if (lEntry != NULL) {
		lEntry->mType = StoreType_Color;
		lEntry->mValue.mColor = lColor;
	} else {
		(*pEnv)->DeleteGlobalRef(pEnv, lColor);
	}
}
JNIEXPORT jintArray JNICALL Java_com_congnt_ndkguide_Store_getIntegerArray(
		JNIEnv* pEnv, jobject pThis, jstring pKey) {
	StoreEntry* lEntry = findEntry(pEnv, &gStore, pKey, NULL);
	if (isEntryValid(pEnv, lEntry, StoreType_ArrayInteger)) {
		jintArray lJavaArray = (*pEnv)->NewIntArray(pEnv, lEntry->mLength);
		if (lJavaArray == NULL)
			return;
		(*pEnv)->SetIntArrayRegion(pEnv, lJavaArray, 0, lEntry->mLength,
				lEntry->mValue.mIntegerArray);
		return lJavaArray;
	} else {
		return NULL ;
	}
}
JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setIntegerArray(
		JNIEnv* pEnv, jobject pThis, jstring pKey, jintArray pIntegerArray) {
	jsize lLength = (*pEnv)->GetArrayLength(pEnv, pIntegerArray);
	int32_t* lArray = (int32_t*) malloc(lLength * sizeof(int32_t));
	(*pEnv)->GetIntArrayRegion(pEnv, pIntegerArray, 0, lLength, lArray);
	if ((*pEnv)->ExceptionCheck(pEnv)) {
		free(lArray);
		return;
	}
	StoreEntry* lEntry = allocateEntry(pEnv, &gStore, pKey);
	if (lEntry != NULL) {
		lEntry->mType = StoreType_IntegerArray;
		lEntry->mLength = lLength;
		lEntry->mValue.mIntegerArray = lArray;
	} else {
		free(lArray);
		return;
	}
}


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
		if (lJavaArray == NULL){
			return;
		}
		(*pEnv)->SetIntArrayRegion(pEnv, lJavaArray, 0, lEntry->mLength,
				lEntry->mValue.mIntegerArray);
		return lJavaArray;
	} else {
		return NULL;
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
		lEntry->mType = StoreType_ArrayInteger;
		lEntry->mLength = lLength;
		lEntry->mValue.mIntegerArray = lArray;
	} else {
		free(lArray);
		return;
	}
}


JNIEXPORT jobjectArray JNICALL Java_com_congnt_ndkguide_Store_getColorArray(
		JNIEnv* pEnv, jobject pThis, jstring pKey) {
	StoreEntry* lEntry = findEntry(pEnv, &gStore, pKey, NULL);
	if (isEntryValid(pEnv, lEntry, StoreType_ArrayColor)) {
		jclass lColorClass = (*pEnv)->FindClass(pEnv,
				"com/congnt/ndkguide/Color");
		if (lColorClass == NULL)
			return NULL ;
		jobjectArray lColorJavaArray = (*pEnv)->NewObjectArray(pEnv,
				lEntry->mLength, lColorClass, NULL);
		(*pEnv)->DeleteLocalRef(pEnv, lColorClass);
		if (lColorJavaArray == NULL)
			return NULL ;
		int32_t i;
		for (i = 0; i < lEntry->mLength; ++i) {
			(*pEnv)->SetObjectArrayElement(pEnv, lColorJavaArray, i,
					lEntry->mValue.mColorArray[i]);
			if ((*pEnv)->ExceptionCheck(pEnv)) {
				return NULL ;
			}
		}
		return lColorJavaArray;
	} else {
		return NULL ;
	}

}

JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setColorArray(
		JNIEnv* pEnv, jobject pThis, jstring pKey, jobjectArray pObjectArray) {
	jsize lLength = (*pEnv)->GetArrayLength(pEnv,pObjectArray);
	jobject* lArray = (jobject*) malloc(lLength * sizeof(jobject));
	int32_t i, j;
	for (i = 0; i < lLength; ++i) {
		jobject lLocalColor = (*pEnv)->GetObjectArrayElement(pEnv, pObjectArray,
				i);
		if (lLocalColor == NULL) {
			for (j = 0; j < i; ++j) {
				(*pEnv)->DeleteGlobalRef(pEnv, lArray[j]);
			}
			free(lArray);
			return;
		}
		lArray[i] = (*pEnv)->NewGlobalRef(pEnv, lLocalColor);
		if (lArray[i] == NULL) {
			for (j = 0; j < i; ++j) {
				(*pEnv)->DeleteGlobalRef(pEnv, lArray[j]);
			}
			free(lArray);
			return;
		}
		(*pEnv)->DeleteLocalRef(pEnv, lLocalColor);
	}
	StoreEntry* lEntry = allocateEntry(pEnv, &gStore, pKey);
	if (lEntry != NULL) {
		lEntry->mType = StoreType_ArrayColor;
		lEntry->mLength = lLength;
		lEntry->mValue.mColorArray = lArray;
	} else {
		for (j = 0; j < i; ++j) {
			(*pEnv)->DeleteGlobalRef(pEnv, lArray[j]);
		}
		free(lArray);
		return;
	}
}


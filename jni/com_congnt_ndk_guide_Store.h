/*
 * comcongntndkguideStore.h
 *
 *  Created on: Sep 1, 2015
 *      Author: FRAMGIA\nguyen.thanh.cong
 */
#include <jni.h>

JNIEXPORT jint JNICALL Java_com_congnt_ndkguide_Store_getInteger(JNIEnv *env,
		jobject pThis, jstring pString);
JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setInteger(JNIEnv *env,
		jobject pThis, jstring pString, jint pInteger);
JNIEXPORT jstring JNICALL Java_com_congnt_ndkguide_Store_getString(JNIEnv *env,
		jobject pThis, jstring pString);
JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setString(JNIEnv *env,
		jobject pThis, jstring pKey, jstring pString);

JNIEXPORT jobject JNICALL Java_com_congnt_ndkguide_Store_getColor(JNIEnv* pEnv, jobject pThis, jstring pKey);

JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setColor(JNIEnv* pEnv, jobject pThis, jstring pKey, jobject pColor);


JNIEXPORT jintArray JNICALL Java_com_congnt_ndkguide_Store_getIntegerArray(JNIEnv* pEnv, jobject pThis, jstring pKey);

JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setIntegerArray(
		JNIEnv* pEnv, jobject pThis, jstring pKey, jintArray pIntegerArray);

JNIEXPORT jobjectArray JNICALL Java_com_congnt_ndkguide_Store_getColorArray(JNIEnv* pEnv, jobject pThis, jstring pKey);

JNIEXPORT void JNICALL Java_com_congnt_ndkguide_Store_setColorArray(JNIEnv* pEnv, jobject pThis, jstring pKey,jobjectArray pObjectArray);

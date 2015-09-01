package com.congnt.ndkguide;

import com.congnt.ndkguide.exception.InvalidTypeException;
import com.congnt.ndkguide.exception.NotExistingKeyException;

public class Store {
    static {
        System.loadLibrary("ndk-guide");
    }
    
    public native int getInteger(String pKey) throws NotExistingKeyException, InvalidTypeException;
    
    public native void setInteger(String pKey, int pInt);
    
    public native String getString(String pKey)
        throws NotExistingKeyException, InvalidTypeException;
        
    public native void setString(String pKey, String pString);
    
    public native Color getColor(String pKey) throws NotExistingKeyException, InvalidTypeException;
    
    public native void setColor(String pKey, Color pColor);
    
    public native void setIntegerArray(String pKey, int[] pIntArray);
    
    public native int[] getIntegerArray(String pKey) throws NotExistingKeyException, InvalidTypeException;
    
    public native void setColorArray(String pKey, Color[] colorArray);
    
    public native Color[] getColorArray(String pKey) throws NotExistingKeyException, InvalidTypeException;
}

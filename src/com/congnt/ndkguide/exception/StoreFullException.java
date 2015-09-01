package com.congnt.ndkguide.exception;

public class StoreFullException extends RuntimeException {

    /**
     * 
     */
    private static final long serialVersionUID = 52494934029912605L;
    public StoreFullException(String pStr) {
           super(pStr);
    }
 }

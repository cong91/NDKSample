package com.congnt.ndkguide.exception;

public class NotExistingKeyException extends Exception {
    /**
     * 
     */
    private static final long serialVersionUID = -1799107874078843474L;

    /**
     * 
     */

    public NotExistingKeyException(String pDetailMessage) {
        super(pDetailMessage);
    }
}

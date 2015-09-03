package com.congnt.ndkguide;

public class Color {
	private int mColor;

	public Color(String mColor) {
		super();
		this.mColor = android.graphics.Color.parseColor(mColor) ;
	}
	@Override
	public String toString() {
		return String.format("#%06X", mColor);
	}

}

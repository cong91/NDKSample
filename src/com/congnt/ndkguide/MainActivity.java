package com.congnt.ndkguide;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

@SuppressLint("NewApi")
public class MainActivity extends ActionBarActivity {
	private EditText mUIKeyEdit, mUIValueEdit;
	private Spinner mUITypeSpinner;
	private Store mStore;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		mUIKeyEdit = (EditText) findViewById(R.id.key);
		mUIValueEdit = (EditText) findViewById(R.id.value);
		mUITypeSpinner = (Spinner) findViewById(R.id.sniper_type);
		mStore = new Store();

		mUITypeSpinner.setAdapter(
				new ArrayAdapter<StoreType>(this, android.R.layout.simple_spinner_item, StoreType.values()));
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	public void setValueOnClick(View v) {
		onSetValue();
	}

	public void getValueOnClick(View v) {
		onGetValue();
	}

	private void onGetValue() {
		String lKey = mUIKeyEdit.getText().toString();
		StoreType lType = (StoreType) mUITypeSpinner.getSelectedItem();
		switch (lType) {
		case Integer:
			mUIValueEdit.setText(Integer.toString(mStore.getInteger(lKey)));
			break;
		case String:
			mUIValueEdit.setText(mStore.getString(lKey));
			break;
		}
	}

	private void onSetValue() {
		String lKey = mUIKeyEdit.getText().toString();
		String lValue = mUIValueEdit.getText().toString();
		StoreType lType = (StoreType) mUITypeSpinner.getSelectedItem();
		try {
			switch (lType) {
			case Integer:
				mStore.setInteger(lKey, Integer.parseInt(lValue));
				break;
			case String:
				mStore.setString(lKey, lValue);
				break;
			}
		} catch (NumberFormatException eNumberFormatException) {
			displayError("Incorrect value.");
		}
	}

	private void displayError(String pError) {
		Toast.makeText(getApplicationContext(), pError, Toast.LENGTH_LONG).show();
	}
}

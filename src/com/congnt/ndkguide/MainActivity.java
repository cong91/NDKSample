package com.congnt.ndkguide;

import java.util.Arrays;
import java.util.List;

import com.congnt.ndkguide.exception.InvalidTypeException;
import com.congnt.ndkguide.exception.NotExistingKeyException;
import com.congnt.ndkguide.exception.StoreFullException;
import com.google.common.base.Function;
import com.google.common.base.Joiner;
import com.google.common.collect.Lists;
import com.google.common.primitives.Ints;

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

@SuppressWarnings("deprecation")
@SuppressLint("NewApi")
public class MainActivity extends ActionBarActivity implements StoreListener {
    private EditText mUIKeyEdit, mUIValueEdit;
    private Spinner mUITypeSpinner;
    private Store mStore;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mUIKeyEdit = (EditText) findViewById(R.id.key);
        mUIKeyEdit.setText("watcherCounter");
        mUIValueEdit = (EditText) findViewById(R.id.value);
        mUITypeSpinner = (Spinner) findViewById(R.id.sniper_type);
        mStore = new Store(this);
        mUITypeSpinner.setAdapter(new ArrayAdapter<StoreType>(this,
            android.R.layout.simple_spinner_item, StoreType.values()));
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
    
    @Override
    protected void onStart() {
        // TODO Auto-generated method stub
        super.onStart();
        mStore.initializeStore();
        mStore.setInteger("watcherCounter", 0);
    }
    
    @Override
    protected void onStop() {
        // TODO Auto-generated method stub
        super.onStop();
        mStore.finalizeStore();
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
        try {
            switch (lType) {
            case Integer:
                mUIValueEdit.setText(Integer.toString(mStore.getInteger(lKey)));
                break;
            case String:
                mUIValueEdit.setText(mStore.getString(lKey));
                break;
            case Color:
                mUIValueEdit.setText(mStore.getColor(lKey).toString());
                break;
            case IntegerArray:
                mUIValueEdit.setText(Ints.join(";", mStore.getIntegerArray(lKey)));
                break;
            case ColorArray:
                mUIValueEdit.setText(Joiner.on(";").join(mStore.getColorArray(lKey)));
                break;
            }
        } catch (NotExistingKeyException e) {
            // TODO Auto-generated catch block
            displayError("Key does not exist in store");
        } catch (InvalidTypeException e) {
            // TODO Auto-generated catch block
            displayError("Incorrect type.");
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
            case Color:
                mStore.setColor(lKey, new Color(lValue));
                break;
            case IntegerArray:
                mStore.setIntegerArray(lKey,
                    Ints.toArray(stringToList(new Function<String, Integer>() {
                        @Override
                        public Integer apply(String arg0) {
                            return Integer.parseInt(arg0);
                        }
                    }, lValue)));
                break;
            case ColorArray:
                List<Color> lIdList = stringToList(new Function<String, Color>() {
                    @Override
                    public Color apply(String arg0) {
                        return new Color(arg0);
                    }
                }, lValue);
                Color[] lIdArray = lIdList.toArray(new Color[lIdList.size()]);
                mStore.setColorArray(lKey, lIdArray);
                break;
            }
        } catch (NumberFormatException eNumberFormatException) {
            displayError("Incorrect value.");
        } catch (StoreFullException eStoreFullException) {
            displayError("Store is full.");
        }
    }
    
    private void displayError(String pError) {
        Toast.makeText(getApplicationContext(), pError, Toast.LENGTH_LONG).show();
    }
    
    private <TType> List<TType> stringToList(Function<String, TType> pConversion, String pValue) {
        String[] lSplitArray = pValue.split(";");
        List<String> lSplitList = Arrays.asList(lSplitArray);
        return Lists.transform(lSplitList, pConversion);
    }
    
    @Override
    public void onAlert(int pValue) {
        displayError(String.format("%1$d is not an allowed integer", pValue));
    }
    
    @Override
    public void onAlert(String pValue) {
        displayError(String.format("%1$s is not an allowed string", pValue));
    }
    
    @Override
    public void onAlert(Color pValue) {
        displayError(String.format("%1$s is not an allowed color", pValue.toString()));
    }
}

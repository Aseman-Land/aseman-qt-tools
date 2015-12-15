/*
    Copyright (C) 2014 Aseman
    http://aseman.co

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

package land.aseman.android;

import org.qtproject.qt5.android.bindings.QtActivity;

import land.aseman.android.store.StoreManager;
import land.aseman.android.store.util.IabHelper;
import land.aseman.android.store.util.IabResult;
import land.aseman.android.store.util.Inventory;
import land.aseman.android.store.util.Purchase;
import com.android.vending.billing.IInAppBillingService;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Build;
import android.view.WindowManager;
import android.view.Window;
import android.provider.MediaStore;
import android.database.Cursor;
import android.util.Log;
import java.util.HashMap;
import java.util.Iterator;

public class AsemanActivity extends QtActivity
{
    static final String STORE_MANAGER_TAG = "StoreManager";
    static final int STORE_MANAGER_RC_REQUEST = 0;

    private static AsemanActivity instance;
    public boolean _transparentStatusBar = false;
    public boolean _transparentNavigationBar = false;
    public static final int SELECT_IMAGE = 1;

    boolean _storeHasFound;
    String _storeManagerLastPurchaseSku;
    IabHelper mStoreManagerHelper;

    public AsemanActivity() {
        AsemanActivity.instance = this;
    }

    public static AsemanActivity getActivityInstance() {
        return AsemanActivity.instance;
    }

    public boolean transparentStatusBar() {
        return _transparentStatusBar;
    }

    public boolean transparentNavigationBar() {
        return _transparentNavigationBar;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (resultCode == RESULT_OK) {
            if (requestCode == AsemanActivity.SELECT_IMAGE) {
                Uri selectedImageUri = data.getData();
                AsemanJavaLayer.selectImageResult( getPath(selectedImageUri) );
            }
        }

        Iterator sm_itrs = StoreManager.instances.iterator();
        while (sm_itrs.hasNext()) {
            StoreManager sm = (StoreManager)sm_itrs.next();
            if(sm != null && sm.mStoreManagerHelper != null)
                sm.mStoreManagerHelper.handleActivityResult(requestCode, resultCode, data);
        }

        super.onActivityResult(requestCode, resultCode, data);
    }

    public String getPath(Uri uri) {
        String selectedImagePath;
        String[] projection = { MediaStore.Images.Media.DATA };
        Cursor cursor = managedQuery(uri, projection, null, null, null);
        if(cursor != null){
            int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
            cursor.moveToFirst();
            selectedImagePath = cursor.getString(column_index);
        }else{
            selectedImagePath = null;
        }

        if(selectedImagePath == null){
            selectedImagePath = uri.getPath();
        }
        return selectedImagePath;
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Window w = getWindow();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            w.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS, WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
            //w.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION, WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
            _transparentStatusBar = true;
            //_transparentNavigationBar = true;
        } else {
            w.setFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS, WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
            _transparentStatusBar = true;
        }

        checkIntent(getIntent());
    }

    @Override
    protected void onNewIntent(Intent intent)
    {
        super.onNewIntent(intent);
        checkIntent(intent);
    }

    protected void checkIntent(Intent intent)
    {
        String action = intent.getAction();
        String type = intent.getType();
        if ( !Intent.ACTION_SEND.equals(action) || type == null)
            return;

        if ("text/plain".equals(type))
            AsemanJavaLayer.sendNote(intent.getStringExtra(Intent.EXTRA_SUBJECT), intent.getStringExtra(Intent.EXTRA_TEXT) );
        else
        if("image/png".equals(type) || "image/jpeg".equals(type))
            AsemanJavaLayer.sendImage( (Uri)intent.getExtras().get(Intent.EXTRA_STREAM) );
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        AsemanJavaLayer.activityStarted();
    }

    @Override
    protected void onRestart()
    {
        super.onRestart();
        AsemanJavaLayer.activityRestarted();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        AsemanJavaLayer.activityResumed();
    }

    @Override
    protected void onPause()
    {
        AsemanJavaLayer.activityPaused();
        super.onPause();
    }

    @Override
    protected void onStop()
    {
        AsemanJavaLayer.activityStopped();
        super.onStop();
    }

    @Override
    protected void onDestroy()
    {
        AsemanJavaLayer.activityDestroyed();
        super.onDestroy();
    }
}

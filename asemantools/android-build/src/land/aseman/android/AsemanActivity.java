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

    private static AsemanActivity instance;
    public boolean _transparentStatusBar = false;
    public boolean _transparentNavigationBar = false;
    public static final int SELECT_IMAGE = 1;

    boolean _storeHasFound;
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
        if (mStoreManagerHelper != null) {
            mStoreManagerHelper.handleActivityResult(requestCode, resultCode, data);
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

    public void storeManagerSetup(String base64EncodedPublicKey, String storePackageName, String billingBindIntentPath)
    {
        if (mStoreManagerHelper != null)
            mStoreManagerHelper.dispose();

        mStoreManagerHelper = new IabHelper(this, base64EncodedPublicKey);
        try {
            Log.d(STORE_MANAGER_TAG, "Starting setup.");
            mStoreManagerHelper.startSetup(storePackageName, billingBindIntentPath,
                new IabHelper.OnIabSetupFinishedListener() {
                    public void onIabSetupFinished(IabResult result) {
                        if (!result.isSuccess()) {
                            Log.d(STORE_MANAGER_TAG, "Problem setting up In-app Billing: " + result);
                        } else {
                            _storeHasFound = true;
                            mStoreManagerHelper.queryInventoryAsync(mGotInventoryListener);
                            Log.d(STORE_MANAGER_TAG, "Setup finished.");
                        }
                        StoreManager._setupFinished(_storeHasFound);
                    }
                });

        } catch(Exception e) {
            return;
        }
    }

    public void storeManagerGetInventoriesState() {
        if(!_storeHasFound)
            return;

        Log.d(STORE_MANAGER_TAG, "Start getting inventories.");
        try {
            mStoreManagerHelper.queryInventoryAsync(mGotInventoryListener);
        } catch(Exception e) {
            return;
        }
    }

    IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            Log.d(STORE_MANAGER_TAG, "Query inventory finished.");
            if (result.isFailure()) {
                Log.d(STORE_MANAGER_TAG, "Failed to query inventory: " + result);
                return;
            }
            else {
                Log.d(STORE_MANAGER_TAG, "Query inventory was successful.");

                HashMap<String, Boolean> inventoriesMap = StoreManager.data;
                if (inventoriesMap != null) {
                    Iterator it = inventoriesMap.keySet().iterator();
                    while(it.hasNext()) {
                        String inventoryKey = (String)it.next();
                        boolean newState = inventory.hasPurchase(inventoryKey);
                        StoreManager.setState(inventoryKey, newState);
                    }
                }
            }
        }
    };

    IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
            if (result.isFailure()) {
                Log.d(STORE_MANAGER_TAG, "Error purchasing: " + result);
                return;
            }
            else
                StoreManager.setState(purchase.getSku(), true);
        }
    };

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mStoreManagerHelper != null) mStoreManagerHelper.dispose();
        mStoreManagerHelper = null;
    }
}

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

package land.aseman.android.store;

import land.aseman.android.AsemanApplication;
import land.aseman.android.AsemanActivity;
import land.aseman.android.AsemanService;

import android.util.Log;
import java.util.HashMap;

public class StoreManager
{
    public static native void _inventoryStateChanged(String sku, boolean state);
    public static native void _setupFinished(boolean state);

    public static HashMap<String, Boolean> data;

    StoreManager() {
        data = new HashMap<String, Boolean>();
    }

    public void setup(String base64EncodedPublicKey, String storePackageName, String billingBindIntentPath) {
        AsemanActivity.getActivityInstance().storeManagerSetup(base64EncodedPublicKey,
                                                               storePackageName,
                                                               billingBindIntentPath);
    }

    public void updateStates() {
        AsemanActivity.getActivityInstance().storeManagerGetInventoriesState();
    }

    public boolean containsInventory(String sku) {
        return data.containsKey(sku);
    }

    public static void setState(String sku, boolean state) {
        boolean contains = data.containsKey(sku);
        data.put(sku, state);
        if(contains)
            _inventoryStateChanged(sku, state);
    }

    public void insertInventory(String sku, boolean state) {
        data.put(sku, state);
    }

    public void insertInventory(String sku) {
        if(!containsInventory(sku))
            insertInventory(sku, false);
    }

    public void removeInventory(String sku) {
        data.remove(sku);
    }

    public boolean getState(String sku) {
        return data.get(sku).booleanValue();
    }

    public int count() {
        return data.size();
    }
}


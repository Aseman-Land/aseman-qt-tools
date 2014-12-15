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

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;

import dalvik.system.DexClassLoader;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.pm.ServiceInfo;
import android.content.Intent;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.os.Process;
import android.widget.Toast;

import land.aseman.android.AsemanActivity;
import org.qtproject.qt5.android.bindings.QtApplication;

public class AsemanService extends Service
{
    public Boolean started=false;
    private String[] m_qtLibs = null;
    private DexClassLoader m_classLoader = null;

    private static ServiceInfo m_serviceInfo = null;
    protected static NotificationManager m_notificationManager;
    protected static Notification.Builder m_builder;
    protected static PendingIntent pi;
    private static AsemanService m_instance;
    private static String m_lib_name;

    private static final String ERROR_CODE_KEY = "error.code";
    private static final String DEX_PATH_KEY = "dex.path";
    private static final String STATIC_INIT_CLASSES_KEY = "static.init.classes";
    private static final String NATIVE_LIBRARIES_KEY = "native.libraries";
    private static final String MAIN_LIBRARY_KEY = "main.library";
    private static final String BUNDLED_LIBRARIES_KEY = "bundled.libraries";
    private static final String LOADER_CLASS_NAME_KEY = "loader.class.name";
    private static final String LIB_PATH_KEY = "lib.path";
    private static final String ENVIRONMENT_VARIABLES_KEY = "env.variable";

    @Override
    public void onCreate() {
        m_instance = this;

        try{
            ComponentName myService = new ComponentName(this, this.getClass());
            m_serviceInfo = getPackageManager().getServiceInfo(myService, PackageManager.GET_META_DATA);
            m_lib_name = splitCamelCase (m_serviceInfo.metaData.getString("android.app.lib_name"));
        }
        catch (Exception e) {
            e.printStackTrace();
        }

        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        startApp();
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    private void startApp(){
        if (!started){
            started = true;
            Toast.makeText(getBaseContext(), m_lib_name + " starting", Toast.LENGTH_LONG).show();

            try{

                if (m_serviceInfo.metaData.containsKey("android.app.qt_libs_resource_id")) {
                    int resourceId = m_serviceInfo.metaData.getInt("android.app.qt_libs_resource_id");
                    m_qtLibs = getResources().getStringArray(resourceId);
                }

                if (m_serviceInfo.metaData.containsKey("android.app.use_local_qt_libs")
                        && m_serviceInfo.metaData.getInt("android.app.use_local_qt_libs") == 1) {
                    ArrayList<String> libraryList = new ArrayList<String>();


                    String localPrefix = "/data/local/tmp/qt/";
                    if (m_serviceInfo.metaData.containsKey("android.app.libs_prefix"))
                        localPrefix = m_serviceInfo.metaData.getString("android.app.libs_prefix");

                    boolean bundlingQtLibs = false;
                    if (m_serviceInfo.metaData.containsKey("android.app.bundle_local_qt_libs")
                        && m_serviceInfo.metaData.getInt("android.app.bundle_local_qt_libs") == 1) {
                        localPrefix = getApplicationInfo().dataDir + "/";
                        bundlingQtLibs = true;
                    }

                    if (m_qtLibs != null) {
                        for (int i=0;i<m_qtLibs.length;i++) {
                            libraryList.add(localPrefix
                                            + "lib/lib"
                                            + m_qtLibs[i]
                                            + ".so");
                        }
                    }

                    libraryList.add(localPrefix + "lib/libQtAndroidService.so");

                    String dexPaths = new String();
                    String pathSeparator = System.getProperty("path.separator", ":");
                    if (!bundlingQtLibs && m_serviceInfo.metaData.containsKey("android.app.load_local_jars")) {
                        String[] jarFiles = m_serviceInfo.metaData.getString("android.app.load_local_jars").split(":");
                        for (String jar:jarFiles) {
                            if (jar.length() > 0) {
                                if (dexPaths.length() > 0)
                                    dexPaths += pathSeparator;
                                dexPaths += localPrefix + jar;
                            }
                        }
                    }

                    Bundle loaderParams = new Bundle();
                    loaderParams.putInt(ERROR_CODE_KEY, 0);
                    loaderParams.putString(DEX_PATH_KEY, dexPaths);
                    loaderParams.putString(LOADER_CLASS_NAME_KEY, "land.aseman.android.AsemanServiceDelegate");
                    loaderParams.putString(ENVIRONMENT_VARIABLES_KEY, "");
                    if (m_serviceInfo.metaData.containsKey("android.app.static_init_classes")) {
                        loaderParams.putStringArray(STATIC_INIT_CLASSES_KEY,
                                                    m_serviceInfo.metaData.getString("android.app.static_init_classes").split(":"));
                    }
                    loaderParams.putStringArrayList(NATIVE_LIBRARIES_KEY, libraryList);

                    loadApplication(loaderParams);
                    return;
                }
            }
            catch (Exception e) {
                started = false;
                e.printStackTrace();
            }
        }
    }

    @SuppressLint("NewApi")
    public void loadApplication(Bundle loaderParams){

        try{

            ArrayList<String> libs = new ArrayList<String>();
            if ( m_serviceInfo.metaData.containsKey("android.app.bundled_libs_resource_id") )
                libs.addAll(Arrays.asList(getResources().getStringArray(m_serviceInfo.metaData.getInt("android.app.bundled_libs_resource_id"))));

            String libName = null;
            if ( m_serviceInfo.metaData.containsKey("android.app.lib_name") ) {
                libName = m_serviceInfo.metaData.getString("android.app.lib_name");
                loaderParams.putString(MAIN_LIBRARY_KEY, libName); //main library contains main() function
            }

            loaderParams.putStringArrayList(BUNDLED_LIBRARIES_KEY, libs);
            loaderParams.putString(ENVIRONMENT_VARIABLES_KEY, "");

            m_classLoader = new DexClassLoader(loaderParams.getString(DEX_PATH_KEY), // .jar/.apk files
                    getDir("outdex", Context.MODE_PRIVATE).getAbsolutePath(), // directory where optimized DEX files should be written.
                    loaderParams.containsKey(LIB_PATH_KEY) ? loaderParams.getString(LIB_PATH_KEY) : null, // libs folder (if exists)
                    getClassLoader()); // parent loader

            String loaderClassName = loaderParams.getString(LOADER_CLASS_NAME_KEY);

            Log.w(getClass().getName(), "Loader : " + loaderClassName);

            Class<?> loaderClass = m_classLoader.loadClass(loaderClassName); // load QtLoader class
            Object qtLoader = loaderClass.newInstance(); // create an instance

            Method perpareAppMethod = qtLoader.getClass().getMethod("loadApplication",
                                                                    Service.class,
                                                                    ClassLoader.class,
                                                                    Bundle.class);

            if (!(Boolean)perpareAppMethod.invoke(qtLoader, this, m_classLoader, loaderParams))
                throw new Exception("");

            // now load the application library so it's accessible from this class loader
            if (libName != null)
                System.loadLibrary(libName);

            Method startAppMethod=qtLoader.getClass().getMethod("startApplication");
            if (!(Boolean)startAppMethod.invoke(qtLoader))
                throw new Exception("");


        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    static String splitCamelCase(String sp) {

        String s = Character.toUpperCase(sp.charAt(0)) + sp.substring(1);

        return s.replaceAll(
          String.format("%s|%s|%s",
             "(?<=[A-Z])(?=[A-Z][a-z])",
             "(?<=[^A-Z])(?=[A-Z])",
             "(?<=[A-Za-z])(?=[^A-Za-z])"
          ),
          " "
       );
    }
}

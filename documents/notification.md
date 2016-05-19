# Notification

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>Notification</font>|
|C++ class|<font color='#074885'>AsemanLinuxNativeNotification</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>color</b></font>: QColor


### Methods

 * uint <font color='#074885'><b>sendNotify</b></font>(string title, string body, string icon, uint replace_id, int timeOut, list&lt;string&gt; actions)
 * uint <font color='#074885'><b>sendNotify</b></font>(string title, string body, string icon, uint replace_id, int timeOut)
 * uint <font color='#074885'><b>sendNotify</b></font>(string title, string body, string icon, uint replace_id)
 * uint <font color='#074885'><b>sendNotify</b></font>(string title, string body, string icon)
 * void <font color='#074885'><b>closeNotification</b></font>(uint id)


### Signals

 * void <font color='#074885'><b>notifyClosed</b></font>(uint id)
 * void <font color='#074885'><b>notifyTimedOut</b></font>(uint id)
 * void <font color='#074885'><b>notifyAction</b></font>(uint id, string action)



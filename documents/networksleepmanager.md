# NetworkSleepManager

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>NetworkSleepManager</font>|
|C++ class|<font color='#074885'>AsemanNetworkSleepManager</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>host</b></font>: string
* <font color='#074885'><b>port</b></font>: int
* <font color='#074885'><b>interval</b></font>: int
* <font color='#074885'><b>networkManager</b></font>: boolean
* <font color='#074885'><b>available</b></font>: boolean (readOnly)


### Methods

 * void <font color='#074885'><b>defaultNetworkChanged</b></font>()
 * void <font color='#074885'><b>networkRecheckAll</b></font>()
 * void <font color='#074885'><b>networkBearerTypeChanged</b></font>()
 * void <font color='#074885'><b>networkBearerTypeFamilyChanged</b></font>()
 * void <font color='#074885'><b>networkIdentifierChanged</b></font>()
 * void <font color='#074885'><b>networkIsValidChanged</b></font>()
 * void <font color='#074885'><b>networkStateChanged</b></font>()
 * void <font color='#074885'><b>networkTypeChanged</b></font>()
 * void <font color='#074885'><b>startResetTimer</b></font>()
 * void <font color='#074885'><b>finishResetTimer</b></font>()
 * void <font color='#074885'><b>updateAvailablity</b></font>()


### Signals

 * void <font color='#074885'><b>wake</b></font>()
 * void <font color='#074885'><b>sleep</b></font>()



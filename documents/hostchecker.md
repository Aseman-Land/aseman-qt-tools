# HostChecker

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>HostChecker</font>|
|C++ class|<font color='#074885'>AsemanHostChecker</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>host</b></font>: string
* <font color='#074885'><b>port</b></font>: int
* <font color='#074885'><b>interval</b></font>: int
* <font color='#074885'><b>available</b></font>: boolean (readOnly)


### Methods

 * void <font color='#074885'><b>socketStateChanged</b></font>(QAbstractSocket::SocketState socketState)
 * void <font color='#074885'><b>socketError</b></font>(QAbstractSocket::SocketError socketError)
 * void <font color='#074885'><b>timedOut</b></font>()
 * void <font color='#074885'><b>refresh</b></font>()




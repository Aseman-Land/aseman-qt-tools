# View

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>View</font>|
|C++ class|<font color='#074885'>AsemanQuickViewWrapper</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>fullscreen</b></font>: boolean
* <font color='#074885'><b>backController</b></font>: boolean
* <font color='#074885'><b>reverseScroll</b></font>: boolean
* <font color='#074885'><b>statusBarHeight</b></font>: real (readOnly)
* <font color='#074885'><b>navigationBarHeight</b></font>: real (readOnly)
* <font color='#074885'><b>root</b></font>: object
* <font color='#074885'><b>focusedText</b></font>: QQuickItem*
* <font color='#074885'><b>layoutDirection</b></font>: int
* <font color='#074885'><b>offlineStoragePath</b></font>: string
* <font color='#074885'><b>flickVelocity</b></font>: real (readOnly)
* <font color='#074885'><b>window</b></font>: QWindow* (readOnly)


### Methods

 * void <font color='#074885'><b>discardFocusedText</b></font>()
 * void <font color='#074885'><b>tryClose</b></font>()
 * void <font color='#074885'><b>setMask</b></font>(real x, real y, real width, real height)
 * void <font color='#074885'><b>move</b></font>(real x, real y)
 * void <font color='#074885'><b>resize</b></font>(real w, real h)
 * void <font color='#074885'><b>viewDestroyed</b></font>()


### Signals

 * void <font color='#074885'><b>closeRequest</b></font>()



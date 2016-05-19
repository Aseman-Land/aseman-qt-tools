# Downloader

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>Downloader</font>|
|C++ class|<font color='#074885'>AsemanDownloader</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>recievedBytes</b></font>: qlonglong (readOnly)
* <font color='#074885'><b>totalBytes</b></font>: qlonglong (readOnly)
* <font color='#074885'><b>destination</b></font>: string
* <font color='#074885'><b>path</b></font>: string
* <font color='#074885'><b>downloaderId</b></font>: int


### Methods

 * void <font color='#074885'><b>start</b></font>()
 * void <font color='#074885'><b>downloadFinished</b></font>(QNetworkReply* reply)
 * void <font color='#074885'><b>sslErrors</b></font>(QList<QSslError> list)
 * void <font color='#074885'><b>downloadProgress</b></font>(qlonglong bytesReceived, qlonglong bytesTotal)


### Signals

 * void <font color='#074885'><b>error</b></font>(list&lt;string&gt; error)
 * void <font color='#074885'><b>finished</b></font>(byte data)
 * void <font color='#074885'><b>finishedWithId</b></font>(int id, byte data)
 * void <font color='#074885'><b>failed</b></font>()



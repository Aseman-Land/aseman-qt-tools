# MixedListModel

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Roles](#roles)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>MixedListModel</font>|
|C++ class|<font color='#074885'>AsemanMixedListModel</font>|
|Inherits|<font color='#074885'>AsemanAbstractListModel</font>|
|Model|<font color='#074885'>Yes</font>|


### Normal Properties

* <font color='#074885'><b>count</b></font>: int (readOnly)
* <font color='#074885'><b>models</b></font>: list&lt;variant&gt;


### Methods

 * void <font color='#074885'><b>columnsAboutToBeInserted_slt</b></font>(QModelIndex parent, int first, int last)
 * void <font color='#074885'><b>columnsAboutToBeMoved_slt</b></font>(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn)
 * void <font color='#074885'><b>columnsAboutToBeRemoved_slt</b></font>(QModelIndex parent, int first, int last)
 * void <font color='#074885'><b>columnsInserted_slt</b></font>(QModelIndex parent, int first, int last)
 * void <font color='#074885'><b>columnsMoved_slt</b></font>(QModelIndex parent, int start, int end, QModelIndex destination, int column)
 * void <font color='#074885'><b>columnsRemoved_slt</b></font>(QModelIndex parent, int first, int last)
 * void <font color='#074885'><b>dataChanged_slt</b></font>(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> roles)
 * void <font color='#074885'><b>dataChanged_slt</b></font>(QModelIndex topLeft, QModelIndex bottomRight)
 * void <font color='#074885'><b>headerDataChanged_slt</b></font>(Qt::Orientation orientation, int first, int last)
 * void <font color='#074885'><b>layoutAboutToBeChanged_slt</b></font>(QList<QPersistentModelIndex> parents, QAbstractItemModel::LayoutChangeHint hint)
 * void <font color='#074885'><b>layoutAboutToBeChanged_slt</b></font>(QList<QPersistentModelIndex> parents)
 * void <font color='#074885'><b>layoutAboutToBeChanged_slt</b></font>()
 * void <font color='#074885'><b>layoutChanged_slt</b></font>(QList<QPersistentModelIndex> parents, QAbstractItemModel::LayoutChangeHint hint)
 * void <font color='#074885'><b>layoutChanged_slt</b></font>(QList<QPersistentModelIndex> parents)
 * void <font color='#074885'><b>layoutChanged_slt</b></font>()
 * void <font color='#074885'><b>modelAboutToBeReset_slt</b></font>()
 * void <font color='#074885'><b>modelReset_slt</b></font>()
 * void <font color='#074885'><b>rowsAboutToBeInserted_slt</b></font>(QModelIndex parent, int start, int end)
 * void <font color='#074885'><b>rowsAboutToBeMoved_slt</b></font>(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationRow)
 * void <font color='#074885'><b>rowsAboutToBeRemoved_slt</b></font>(QModelIndex parent, int first, int last)
 * void <font color='#074885'><b>rowsInserted_slt</b></font>(QModelIndex parent, int first, int last)
 * void <font color='#074885'><b>rowsMoved_slt</b></font>(QModelIndex parent, int start, int end, QModelIndex destination, int row)
 * void <font color='#074885'><b>rowsRemoved_slt</b></font>(QModelIndex parent, int first, int last)
 * void <font color='#074885'><b>modelDestroyed</b></font>(object obj)
 * void <font color='#074885'><b>reinit_prv</b></font>()




### Roles

 * model.<font color='#074885'>modelObject</font>
 * model.<font color='#074885'>modelIndex</font>
 * model.<font color='#074885'>modelName</font>

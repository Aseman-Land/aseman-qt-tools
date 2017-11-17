isEmpty(QMAKE_QMLPLUGINDUMP) {
    win32:QMAKE_QMLPLUGINDUMP = $$[QT_INSTALL_BINS]/qmlplugindump.exe
    else:QMAKE_QMLPLUGINDUMP = $$[QT_INSTALL_BINS]/qmlplugindump
}

qmldirSrc = $$_PRO_FILE_PWD_/qml/AsemanTools/qmldir
qmkdirDst = $$DESTDIR/qmldir
qmkdirDst2 = $$OUT_PWD/qmldir

win32 {
    qmldirSrc = $$replace(qmldirSrc, /, \\)
    qmldirSrc ~= s,\\\\\\.?\\\\,\\,

    qmkdirDst = $$replace(qmkdirDst, /, \\)
    qmkdirDst ~= s,\\\\\\.?\\\\,\\,

    qmkdirDst2 = $$replace(qmkdirDst2, /, \\)
    qmkdirDst2 ~= s,\\\\\\.?\\\\,\\,
}

dmpPluginCommand = $(COPY_FILE) $$qmldirSrc $$qmkdirDst
dmpPluginCommand = $$dmpPluginCommand && $(COPY_FILE) $$qmkdirDst $$qmkdirDst2
dmpPluginCommand = @echo Generating plugin types file... && $$dmpPluginCommand

dmpPluginDeploymentfolders.commands = $$dmpPluginCommand

QMAKE_POST_LINK += $$dmpPluginCommand

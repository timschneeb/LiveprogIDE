TEMPLATE = subdirs

SUBDIRS += \
    docking-system \
    src
	
docking-system.subdir = 3rdparty/Qt-Advanced-Docking-System/src

src.depends = docking-system

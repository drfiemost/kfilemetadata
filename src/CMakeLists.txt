kde4_add_library(kfilemetadata SHARED
    extractionresult.cpp
    extractorplugin.cpp
    extractorpluginmanager.cpp
    propertyinfo.cpp
    typeinfo.cpp
)

target_link_libraries(kfilemetadata
   LINK_PRIVATE
  Qt4::QtCore
  ${KDE4_KDECORE_LIBS}
)

set_target_properties(kfilemetadata PROPERTIES
    VERSION ${GENERIC_LIB_VERSION}
    SOVERSION ${GENERIC_LIB_SOVERSION}
)

install(TARGETS kfilemetadata ${INSTALL_TARGETS_DEFAULT_ARGS})

install(TARGETS kfilemetadata EXPORT KdeLibsLibraryTargets ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES kfilemetadataextractor.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR})

install(EXPORT KdeLibsLibraryTargets
        DESTINATION ${LIB_INSTALL_DIR}/cmake/KFileMetaData
        FILE KFileMetaDataTargetsWithPrefix.cmake)

install(FILES
    extractionresult.h
    extractorplugin.h
    extractorpluginmanager.h
    properties.h
    propertyinfo.h
    types.h
    typeinfo.h
    kfilemetadata_export.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/kfilemetadata COMPONENT Devel
)

add_subdirectory(extractors)

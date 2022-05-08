configure_file(indexerextractortestsconfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/indexerextractortestsconfig.h @ONLY)

kde4_add_unit_test(extractortests NOGUI
  indexerextractortests.cpp
  simpleresult.cpp
  ../src/extractors/plaintextextractor.cpp
)

target_link_libraries(extractortests
  Qt4::QtTest
  ${KDE4_KDECORE_LIBS}
  kfilemetadata
)

#
# Property Info
#
kde4_add_unit_test(propertyinfotest NOGUI
  propertyinfotest.cpp
)

target_link_libraries(propertyinfotest
  Qt4::QtTest
  ${KDE4_KDECORE_LIBS}
  kfilemetadata
)


file(GLOB srcs [A-Z|a-z]*.cpp [A-Z|a-z]*.c [A-Z|a-z]*.f)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}  ${TRUST_ROOT}/include/backward  ${TRUST_ICOCOAPI}/include  ${TRUST_MEDCOUPLING_ROOT}/include  ${TRUST_ROOT}/src/Kernel/Champs  ${TRUST_ROOT}/src/Kernel/Framework  ${TRUST_ROOT}/src/Kernel/Geometrie  ${TRUST_ROOT}/src/Kernel/ICoCo  ${TRUST_ROOT}/src/Kernel/Math/Matrices  ${TRUST_ROOT}/src/Kernel/Math/SolvSys  ${TRUST_ROOT}/src/Kernel/Math  ${TRUST_ROOT}/src/Kernel/Statistiques_temps  ${TRUST_ROOT}/src/Kernel/Utilitaires  ${TRUST_ROOT}/src/Kernel/VF/Zones )
add_library(obj_chpdis OBJECT  ${srcs} )
set(listlibs ${listlibs} chpdis PARENT_SCOPE    )
#add_custom_target(check_sources_chpdis   COMMAND check_sources.sh ${CMAKE_CURRENT_SOURCE_DIR} ) #COMMENT  "checking code validity chpdis" )
#add_DEPENDENCIES(obj_chpdis check_sources_chpdis)
if(COMPIL_DYN)
  add_library(chpdis SHARED   $<TARGET_OBJECTS:obj_chpdis> )
  install(TARGETS chpdis  DESTINATION lib)
endif(COMPIL_DYN)

file(GLOB srcs [A-Z|a-z]*.cpp [A-Z|a-z]*.c [A-Z|a-z]*.f)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}  ${TRUST_ROOT}/include/backward  ${TRUST_ROOT}/src/Kernel/Champs  ${TRUST_ROOT}/src/Kernel/Cond_Lim  ${TRUST_ROOT}/src/Kernel/Framework  ${TRUST_ROOT}/src/Kernel/Geometrie  ${TRUST_ROOT}/src/Kernel/Math  ${TRUST_ROOT}/src/Kernel/Math/Matrices  ${TRUST_ROOT}/src/Kernel/Utilitaires  ${TRUST_ROOT}/src/Kernel/VF/Zones  ${TRUST_ROOT}/src/VDF/Zones )
add_library(obj_itsovdf OBJECT  ${srcs} )
set(listlibs ${listlibs} itsovdf PARENT_SCOPE    )
#add_custom_target(check_sources_itsovdf   COMMAND check_sources.sh ${CMAKE_CURRENT_SOURCE_DIR} ) #COMMENT  "checking code validity itsovdf" )
#add_DEPENDENCIES(obj_itsovdf check_sources_itsovdf)
if(COMPIL_DYN)
  add_library(itsovdf SHARED   $<TARGET_OBJECTS:obj_itsovdf> )
  install(TARGETS itsovdf  DESTINATION lib)
endif(COMPIL_DYN)
